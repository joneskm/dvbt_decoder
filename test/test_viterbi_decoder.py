# -*- coding: utf-8 -*-

import numpy as np
import components
from numpy.random import RandomState

def test_viterbi_decoder():    
    coded_bits, un_coded_bits = _generate_data()    
    vit_decoded = components.viterbi_decoder(coded_bits, rate=(2,3))
    
    assert np.alltrue(vit_decoded == un_coded_bits)


def _generate_data():
    '''
    Generate random input data (un_coded_bits) and subsequent output data 
    (coded_bits) of a rate (2,3) convolutional coder
    '''

    seq_length = 100000    
    prng = RandomState(314159265)
   
    un_coded_bits = prng.randint(2, size = seq_length)   
    initial_state = prng.randint(2, size = 6)
    
    coded_bits = _convolutional_coder(un_coded_bits, initial_state)
    
    return coded_bits, un_coded_bits


def _convolutional_coder(un_coded_bits, initial_state):
    '''
    Generates output of a rate (2,3) convolutional coder as defined in 
    ETSI EN 300 744 V1.5.1 sec. 4.3.3
    '''
    
    bit_seq = np.concatenate((initial_state, un_coded_bits)) 
    un_punctured = np.empty(2*len(un_coded_bits))
    
    for k in range(len(un_coded_bits)):
        x_out, y_out = _convolutional_coder_core(bit_seq[k:k+7])
        un_punctured[2*k] = x_out
        un_punctured[2*k + 1] = y_out
    
    return _puncture_data(un_punctured)


def _puncture_data(un_punctured):
    '''
    Puncture the data assuming a rate of (2,3)
    '''
    
    puncture_indcs = np.arange(2, len(un_punctured), 4)
    
    return np.delete(un_punctured, puncture_indcs)


def _convolutional_coder_core(bits):
    '''
    Given the state of the convolutional coder (in the form of the bit values
    at each position) determine the x and y bit outputs
    '''

    x_out = (bits[0] + bits[3] + bits[4] + bits[5] + bits[6])%2
    y_out = (bits[0] + bits[1] + bits[3] + bits[4] + bits[6])%2
    
    return bool(x_out), bool(y_out)
    
    
if __name__ == '__main__':
    test_viterbi_decoder()













