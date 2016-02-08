# -*- coding: utf-8 -*-

import numpy as np
from components.dvbt_constants import *

def inner_processing(data_carriers, super_frame_start):
    demodulated = demodulate(data_carriers)
    symbol_deint = symbol_deinterleaver(demodulated, super_frame_start)
    return bit_deinterleaver(symbol_deint)

def demodulate(data_carriers):
    '''
    Convert points on the argand diagram to constellation data points, 
    according to the following mapping: 
    
                                                         y_coord =
    
                     |    |    |    |    |    |    |        8
                  0  | 8  | 16 | 24 | 32 | 40 | 48 | 56    
                ------------------------------------------  6
                  1  | 9  | 17 | 25 | 33 | 41 | 49 | 57    
                ------------------------------------------  4
                  2  | 10 | 18 | 26 | 34 | 42 | 50 | 58    
                ------------------------------------------  2
                  3  | 11 | 19 | 27 | 35 | 43 | 51 | 59    
                ------------------------------------------  0
                  4  | 12 | 20 | 28 | 36 | 44 | 52 | 60    
                ------------------------------------------ -2
                  5  | 13 | 21 | 29 | 37 | 45 | 53 | 61    
                ------------------------------------------ -4
                  6  | 14 | 22 | 30 | 38 | 46 | 54 | 62    
                ------------------------------------------ -6
                  7  | 15 | 23 | 31 | 39 | 47 | 55 | 63    
                     |    |    |    |    |    |    |       -8

    x_coord =  -8   -6   -4   -2    0    2    4    6    8
    
    '''
    
    # use numpy floor so that negative values are rounded away from zero
    x_coords = np.floor(data_carriers.real)
    y_coords = np.floor(data_carriers.imag)
    
    x_coords = x_coords.astype('int')
    y_coords = y_coords.astype('int')
    
    x_coords //= 2
    y_coords //= 2
    
    x_coords = np.clip(x_coords,-4,3)
    y_coords = np.clip(y_coords,-4,3)
    
    x_row = x_coords + 4
    y_row = -y_coords + 3
    
    return x_row*8 + y_row


def symbol_deinterleaver(demodulated, super_frame_start):
    
    H = _get_permutation_array()
    even_symbols, odd_symbols = _get_symbol_parities(super_frame_start, 
                                                     demodulated.shape[0]) 
    
    symbol_deint = np.empty(demodulated.shape,'int')
    for k in even_symbols:
        symbol_deint[k,:] = demodulated[k,H]
    for k in odd_symbols:
        symbol_deint[k,H] = demodulated[k,:]
    
    return symbol_deint.flatten()

    
def _get_symbol_parities(super_frame_start, num_symbols):
    
    first_even_symbol = super_frame_start%2 # superframe has even parity
    first_odd_symbol = 1 - first_even_symbol
    
    even_symbols = range(first_even_symbol, num_symbols, 2) 
    odd_symbols = range(first_odd_symbol, num_symbols, 2)
    
    return even_symbols, odd_symbols

def _get_r_word_array():
    
    r_dash = _get_r_dash_word_array()
    permutation = np.array([8, 1, 3, 9, 2, 11, 5, 0, 6, 4, 7, 10])

    r = np.empty(r_dash.shape)
    for k in range(M_MAX):
        r[:,k] = r_dash[permutation,k]
    
    return r.astype('int')


def _get_r_dash_word_array():

    r_dash = np.zeros((12,M_MAX))
    r_dash[:,2] = np.array([1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
    
    for k in range(3, M_MAX):
        r_dash[0:11,k] = r_dash[1:12,k-1]
        r_dash[11,k] = (r_dash[0,k-1] + r_dash[1,k-1] + r_dash[4,k-1] +    
                                                             r_dash[6,k-1])%2

    return r_dash


def _get_permutation_array():
    
    r = _get_r_word_array()
    
    to_dec = 2**np.arange(12) 
    r_dec = np.dot(to_dec,r)
    
    H = np.empty(NUM_DATA_CARRIERS, 'int')    
    two_pow_twelve = 2**12
    q = 0
    
    for k in range(M_MAX):
        H[q] = (k%2)*two_pow_twelve + r_dec[k]
    
        if H[q] < NUM_DATA_CARRIERS:
            q = q + 1
        
    return H


def bit_deinterleaver(symbol_deint):
    
    H_inv = _get_inv_permutation_array()
    
    bit_data_array = _map_data_points_to_bits(symbol_deint)
    
    deint_bit = _core_bit_deinterleaver(bit_data_array, H_inv)
    
    return _permute_rows(deint_bit)

    
def _permute_rows(deint_bit):
    demultiplex_bits = deint_bit[[0,2,4,1,3,5]]
    
    return demultiplex_bits.flatten(order = 'F')


def _core_bit_deinterleaver(bit_data_array, H_inv):
    
    num_deint_blocks = bit_data_array.shape[1]//IBS
    H_inv_stretch = _stretch_H_inv(H_inv, num_deint_blocks)
    map_rows = [[i] for i in range(N_BPSC)]

    return bit_data_array[map_rows, H_inv_stretch]


def _stretch_H_inv(H_inv, num_deint_blocks):
    '''
    Stretch H_inv so that bit_data_array can be indexed in one go:
        
    H_inv_stretch = [H_inv H_inv H_inv ...] + [0 0 0 ... 1 1 1 ...2 2 2 ...]
                                                 .         .        .
                                                 .         .        .
                                                 .         .        .
    '''
    
    H_inv_stretch = np.tile(H_inv, (1,num_deint_blocks))
    
    deint_blocks_starts = np.arange(0,num_deint_blocks*IBS, IBS)
    deint_blocks_starts_stretch = np.repeat(deint_blocks_starts, IBS)    
    deint_blocks_starts_stretch = deint_blocks_starts_stretch[np.newaxis]
    
    return H_inv_stretch + deint_blocks_starts_stretch


def _map_data_points_to_bits(symbol_deint):
    '''
    Generate data_2_bit array. The k'th column of this array consists of the
    bit values of data point number k on the constellation. Use this array to
    map data points to bit values.
    '''

    constellation_width = int(np.sqrt(NUM_CONSTELLATION_POINTS))
    data_2_bit = np.empty((N_BPSC, NUM_CONSTELLATION_POINTS))
    for const_pt in range(NUM_CONSTELLATION_POINTS):

        x_coord = const_pt//constellation_width
        y_coord = const_pt%constellation_width

        x_bits = GRAY_BITS[-x_coord-1]
        y_bits = GRAY_BITS[y_coord]

        data_2_bit[[0,2,4], const_pt] = x_bits
        data_2_bit[[1,3,5], const_pt] = y_bits
    
    return data_2_bit[:,symbol_deint]

   
def _get_inv_permutation_array():

    H = np.empty((N_BPSC, IBS)) 
    k = np.arange(IBS)
    
    H[0] = k
    H[1] = (k + 63)%126
    H[2] = (k + 105)%126
    H[3] = (k + 42)%126
    H[4] = (k + 21)%126
    H[5] = (k + 84)%126
    
    return np.argsort(H)
                
                
                
                
                
                
                
                
                
                
