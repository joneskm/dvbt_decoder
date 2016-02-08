# -*- coding: utf-8 -*-

'''
Viterbi decoder for use with dvbt convolutional encoder.
'''

from __future__ import division

import numpy as np
import ctypes
import os
from ..dvbt_constants import NUM_CONV_STATES

try:
    path = os.path.dirname(os.path.abspath(__file__))
    so_name = 'libviterbi_core.so'
    libviterbi_core = ctypes.cdll.LoadLibrary(path + os.path.sep + so_name)
except:
    print('Could not load viterbi_core library')
    

def viterbi_decoder(coded_data, rate):
    '''
    The state sequences are calculated with un-punctured data before
    the winning path is traversed
    '''
    
    unpunctured = _unpuncture_data(coded_data, rate)  
    state_history, final_state = _find_state_history(unpunctured)
    
    return _extract_winning_sequence(state_history, final_state)
    
    
def _unpuncture_data(coded_data, rate):
    '''
    Convert coded data to un-punctured data by placing zeros where there is
    missing data
    '''
    data_mask =  _get_data_mask(rate, len(coded_data))    
    unpunctured = _unpuncture(coded_data, data_mask)
    
    return unpunctured


def _get_data_mask(rate, coded_data_length):
    '''
    The data mask is a boolean array equal in length to the un-punctured data
    array. Each element in the mask identifies whether coded data should be
    placed at that element.
    '''
    
    decoded_data_length = coded_data_length*rate[0]//rate[1]
    unpunctured_data_length = 2*decoded_data_length
    
    x_punctured_indcs, y_punctued_indcs = _get_xy_punctures(rate, 
                                                     unpunctured_data_length)
        
    data_mask = np.ones((unpunctured_data_length),'bool') 
    data_mask[y_punctued_indcs] = False
    data_mask[x_punctured_indcs] = False

    return data_mask


def _get_xy_punctures(rate, unpunctured_data_length):
    '''
    Find indices of x and y values that are punctured as defined in 
    ETSI EN 300 744 V1.5.1 sec. 4.3.3
    '''
        
    if rate == (1,2):    
        x_punctued = []
        y_punctued = []
    elif rate == (2,3):    
        x_punctued = np.arange(2, unpunctured_data_length, 4)
        y_punctued = []
    elif rate == (3,4):
        x_punctued = np.arange(3, unpunctured_data_length, 6)
        y_punctued = x_punctued + 1
    else:
        print 'Unsupported Rate'
        
    return x_punctued, y_punctued


def _unpuncture(punctured, data_mask):
    '''
    Convert 0s and 1s to 1s and -1s and unpuncture the data
    '''
    
    punctured = 2*punctured - 1
    punctured = punctured.astype('int32')
    
    unpunctured = np.zeros(len(data_mask),'int32')  
    unpunctured[data_mask] = punctured
    
    return unpunctured


def  _find_state_history(unpunctured):
    '''
    Find longest paths through the state sequences. The path lengths are
    found by calling a c library function.
    '''
    
    length_output = len(unpunctured)//2  
    path_lengths = np.empty((NUM_CONV_STATES),'int32') 
    state_history = np.empty((length_output,NUM_CONV_STATES), 'int16')
 
    libviterbi_core.viterbi_core(unpunctured.ctypes, length_output, 
                                 state_history.ctypes, 
                                 path_lengths.ctypes)
    
    final_state = int(np.argmax(path_lengths))
    
    return state_history, final_state


def _extract_winning_sequence(state_history, final_state):
    '''
    Trace back through the states of the longest path and determine the bit 
    value at each step. This is done by calling a c library function
    '''
    
    length_output = state_history.shape[0]    
    win_seq = np.empty((length_output),'uint8')
    
    libviterbi_core.find_win_seq(win_seq.ctypes, length_output, 
                                 state_history.ctypes, final_state)
    
    return win_seq








