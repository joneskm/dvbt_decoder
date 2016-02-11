# -*- coding: utf-8 -*-

import components
import numpy as np
import os

path = os.path.dirname(os.path.abspath(__file__))
test_file = (path + os.path.sep + 'test_data.npz')
test_data = np.load(test_file)

def test_inner_processing():
    data_carriers = test_data['ip_data_carriers']
    super_frame_start = test_data['ip_super_frame_start']
    
    exp_demultiplex_bits = test_data['ip_demultiplex_bits']
    
    demultiplex_bits = components.inner_processing(data_carriers, 
                                                   super_frame_start)
    
    assert np.alltrue(demultiplex_bits == exp_demultiplex_bits)


def test_demodulate_edge_cases():
    data_carriers = np.array([1+2j, 
                              9+0j,
                              ])
                              
    exp_demodulated = np.array([34,
                                59,
                                ])
    
    demodulated = components.demodulate(data_carriers)
    
    assert np.alltrue(demodulated == exp_demodulated)


def test_demodulate():
    data_carriers = test_data['ip_data_carriers']
    exp_demodulated = test_data['ip_demodulated']
    
    demodulated = components.demodulate(data_carriers)
    
    assert np.alltrue(exp_demodulated == demodulated)


def test_symbol_deinterleaver():
    demodulated = test_data['ip_demodulated']
    super_frame_start = test_data['ip_super_frame_start']
    exp_symbol_deint = test_data['ip_symbol_deint']
    
    symbol_deint = components.symbol_deinterleaver(demodulated, 
                                                   super_frame_start)

    assert np.alltrue(symbol_deint==exp_symbol_deint)
    

def test_bit_deinterleaver():
    symbol_deint = test_data['ip_symbol_deint']
    exp_demultiplex_bits = test_data['ip_demultiplex_bits']
    
    demultiplex_bits = components.bit_deinterleaver(symbol_deint)

    assert np.alltrue(demultiplex_bits==exp_demultiplex_bits)


if __name__ == '__main__':
    test_inner_processing()
    test_demodulate_edge_cases()
    test_demodulate()
    test_symbol_deinterleaver()
    test_bit_deinterleaver()