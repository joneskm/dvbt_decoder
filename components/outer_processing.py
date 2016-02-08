# -*- coding: utf-8 -*-
import numpy as np
from components.dvbt_constants import *


def outer_processing(interleaved_bits, super_frame_start, rate):
    '''
    Deinterleaves, decodes, and 'de-randomizes' bit stream    
    '''
    
    coded_bits,first_sync_byte_seq_num = outer_deinterleaver(
                                         interleaved_bits, 
                                         super_frame_start,
                                         rate)
                                         
    derandomized_bit_array = outer_decoder(coded_bits,
                                           first_sync_byte_seq_num)
    
    return bit_packer(derandomized_bit_array)
    
    
def outer_deinterleaver(interleaved_bits, super_frame_start, rate):
    ''' 
    Deinterleaves the bit stream as defined in ETSI EN 300 744 V1.5.1 sec. 
    4.3.2
        
    Parameters
    ----------
    interleaved_bits : array_like
        Input bit stream
    super_frame_start : int
        Symbol number of the first frame of a super frame
    rate : tuple
        dvbt rate
    '''
    
    (first_sync_byte_bit_num,first_sync_byte_seq_num) = \
                              _determine_first_sync_byte(super_frame_start, 
                                                         rate)
                              
    interleaved_bits = interleaved_bits[first_sync_byte_bit_num:]    
    num_deint_bytes = _determine_num_deint_bytes(len(interleaved_bits)//8)

    bit_mapper = _generate_bit_mapper(num_deint_bytes)
    
    return interleaved_bits[bit_mapper],first_sync_byte_seq_num
    
    
def _determine_first_sync_byte(super_frame_start, rate):
    '''
    Given the symbol number of the first frame of a super frame, this
    function returns the bit number of the first sync byte in the data
    stream. It also returns the sequence number of this sync byte (every 8th
    sync byte is inverted defining the start of a sequence)
    '''
    num_bits_symbol = (NUM_DATA_CARRIERS*NUM_BITS_PER_CARRIER*rate[0]
                      / rate[1])
                      
    super_frame_start_bit = super_frame_start*num_bits_symbol
    num_prcding_transport_packets = (super_frame_start_bit//
                                    (NUM_BYTES_TP*8))
                                    
    first_sync_byte_seq_num =  (NUM_TRNSPT_PCKTS_IN_PRBS_PERIOD - 
                               num_prcding_transport_packets%
                               NUM_TRNSPT_PCKTS_IN_PRBS_PERIOD) 
                               
    first_sync_byte_bit_num = (super_frame_start_bit -
                              (num_prcding_transport_packets*
                              NUM_BYTES_TP*8))
                              
    return first_sync_byte_bit_num, first_sync_byte_seq_num
    
    
def _determine_num_deint_bytes(num_interleaved_bytes):
    '''
    Determine number of bytes at the output of the outer deinterleaver
    '''

    max_fifo_delay = FIFO_UNIT_DELAY*FIFO_STAGES*(FIFO_STAGES-1)
    num_transport_packets = ((num_interleaved_bytes - max_fifo_delay) 
                            // NUM_BYTES_TP)
                            
    return num_transport_packets*NUM_BYTES_TP


def _generate_bit_mapper(num_deint_bytes):
    '''
    Returns an array of bit indices, such that the position of the k'th 
    bit in the de-interleaved bit stream is at position bit_mapper[k] in the 
    interleaved bit stream. This is equivalent to (appart from returning a 
    list rather than a numpy array):
    
    byte_mapper = [(x%FIFO_STAGES)*FIFO_UNIT_DELAY*FIFO_STAGES + x 
                  for x in range(num_deint_bytes)]
    bit_mapper = [x+y*8 for y in byte_mapper for x in range(8)]
    
    return bit_mapper
    
    However it's ~x10 slower than using numpy array operations.
    '''
     
    num_groups = num_deint_bytes//FIFO_STAGES 
    
    byte_mapper = _generate_byte_mapper(num_groups)
    bit_mapper = 8*byte_mapper
    bit_mapper = bit_mapper + np.arange(8)
    
    return np.reshape(bit_mapper,bit_mapper.size)
    
    
def _generate_byte_mapper(num_groups):
    '''
    Returns an array of byte indices, such that the position of the k'th 
    byte in the de-interleaved byte stream is at position byte_mapper[k] 
    in the interleaved byte stream.      
    '''

    group_indxs = np.arange(num_groups).reshape(num_groups,1)
    group_first_byte_indxs = FIFO_STAGES*group_indxs

    group_mapper = (NUM_BYTES_TP+1)*np.arange(FIFO_STAGES)
    byte_mapper = np.tile(group_mapper,(num_groups,1))
    byte_mapper += group_first_byte_indxs

    byte_mapper = np.array(byte_mapper)
    
    return byte_mapper.reshape((byte_mapper.size,1))


def outer_decoder(coded_bits,first_sync_byte_seq_num):
    '''
    The outer coding bits are simply removed and are not used for error
    correction. Following this the bits are derandomized
    '''

    num_protected_packets, protected_bits = _get_protected_bits(coded_bits)
    
    randomized_bits = _remove_error_correction_bits(num_protected_packets, 
                                                    protected_bits)

    wk = _gen_prbs_sequence()
    
    derandomized = _derandomize_bits(first_sync_byte_seq_num, 
                                     num_protected_packets, randomized_bits, 
                                     wk)
    
    return derandomized.astype('bool')
    

def _gen_prbs_sequence():
    '''
    Generate PRBS as defined in ETSI EN 300 744 V1.5.1 sec. 4.3.1
    '''

    wk = np.empty(PRBS_PERIODD_BYTES*8,'bool')
    reg_state = [1,0,0,1,0,1,0,1,0,0,0,0,0,0,0]
    
    for k in range(PRBS_PERIODD_BYTES*8):                  
    	  first_bit = (reg_state[14]+reg_state[13])%2
    	  reg_state[1:15] = reg_state[0:14]
    	  reg_state[0] = first_bit
    	  wk[k] = first_bit
    
    return wk


def _remove_error_correction_bits(num_protected_packets, protected_bits):
    '''
    Remove error correction bits at the end of each protected packet. These 
    could be used for error correction but are not.
    '''
    
    randomized_bits = np.empty(num_protected_packets*NUM_RNDM_BYTES_TP*8,'bool')
    num_bits_tp = NUM_BYTES_TP*8
    num_rndm_bits_tp = NUM_RNDM_BYTES_TP*8
    
    for k in range(num_protected_packets):
        start_w = k*num_rndm_bits_tp
        stop_w = start_w + num_rndm_bits_tp
    
        start_r = k*num_bits_tp
        stop_r  = start_r + num_rndm_bits_tp
    
        randomized_bits[start_w:stop_w] = protected_bits[start_r:stop_r]    
    
    return randomized_bits
    
def _derandomize_bits(first_sync_byte_seq_num, num_protected_packets, 
                      randomized_bits, wk):
    '''
    Derandomize bits using the descrambler described in 
    ETSI EN 300 744 V1.5.1 sec. 4.3.1
    '''
    
    sync_byte = [0,1,0,0,0,1,1,1]
    bits_tp = NUM_RNDM_BYTES_TP*8
    derandomized = np.empty(bits_tp*num_protected_packets,'bool')
    

    for k in range(num_protected_packets):
        derandomized[k*bits_tp : k*bits_tp + 8] = sync_byte
        
        packet_num = (k+first_sync_byte_seq_num)%8        
        packet_PRBS = wk[packet_num*bits_tp:packet_num*bits_tp + bits_tp - 8]
        
        rndm_bits = randomized_bits[k*bits_tp + 8:(k + 1)*bits_tp]
        derandomized[k*bits_tp + 8 : (k + 1)*bits_tp] = rndm_bits^packet_PRBS

    return derandomized
    
def _get_protected_bits(coded_bits):
    '''
    Calculate number of whole protected packets and prune data back to this
    number
    '''
    num_protected_packets = len(coded_bits)//(NUM_BYTES_TP*8)
    num_protected_bits = num_protected_packets*NUM_BYTES_TP*8  
    protected_bits = coded_bits[0:num_protected_bits]
    
    return num_protected_packets, protected_bits
    
    
def bit_packer(bit_array):
    '''
    Convert array of bit values to a byte string
    '''
    
    num_bytes = len(bit_array)//8
    bit_array = bit_array[0:num_bytes*8]        
    bit_array = bit_array.reshape((num_bytes,8))
    bits_2_byte = 2**np.arange(7,-1,-1)    
    byte_np_array = np.dot(bit_array,bits_2_byte)
    byte_array = bytearray(list(byte_np_array)) 
    return byte_array










