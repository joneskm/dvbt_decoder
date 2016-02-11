# -*- coding: utf-8 -*-

import components
import numpy as np
import os

path = os.path.dirname(os.path.abspath(__file__))
test_file = (path + os.path.sep + 'test_data.npz')
test_data = np.load(test_file)

def test_outer_processing():
    interleaved_bits = test_data['op_interleaved_bits']
    super_frame_start = test_data['op_super_frame_start']
    rate = test_data['op_rate']
    
    exp_m2ts_byte_string = test_data['op_m2ts_byte_string']

    m2ts_byte_string = components.outer_processing(interleaved_bits, 
                                                   super_frame_start, 
                                                   rate)
 
    assert  m2ts_byte_string == exp_m2ts_byte_string
    

def test_outer_deinterleaver():
    interleaved_bits = test_data['op_interleaved_bits']
    super_frame_start = test_data['op_super_frame_start']
    rate = test_data['op_rate']

    exp_coded_bits = test_data['op_coded_bits']
    exp_first_sync_byte_seq_num = test_data['op_first_sync_byte_seq_num']    

    coded_bits,first_sync_byte_seq_num = components.outer_deinterleaver(
                                         interleaved_bits, 
                                         super_frame_start,
                                         rate)
                                         
    assert np.alltrue(coded_bits == exp_coded_bits)
    assert first_sync_byte_seq_num == exp_first_sync_byte_seq_num


def test_outer_decoder():
    coded_bits = test_data['op_coded_bits']
    first_sync_byte_seq_num = test_data['op_first_sync_byte_seq_num']
    
    exp_derandomized_bit_array = test_data['op_derandomized_bit_array']
    
    derandomized_bit_array = components.outer_decoder(coded_bits,
                                           first_sync_byte_seq_num)

    assert np.alltrue(derandomized_bit_array == exp_derandomized_bit_array)

def test_bit_packer():
    derandomized_bit_array = test_data['op_derandomized_bit_array']
    exp_m2ts_byte_string = test_data['op_m2ts_byte_string']
    
    m2ts_byte_string = components.bit_packer(derandomized_bit_array)

    assert  m2ts_byte_string == exp_m2ts_byte_string

if __name__ == '__main__':
    test_outer_processing()
    test_outer_deinterleaver()
    test_outer_decoder()
    test_bit_packer()