# -*- coding: utf-8 -*-

import components
import numpy as np
import matplotlib.pyplot as plt
import os

path = os.path.dirname(os.path.abspath(__file__))
test_file = (path + os.path.sep + 'test_data.npz')
test_data = np.load(test_file)

def test_run_dsp():   
    exp_data_carriers = test_data['data_carriers']
    exp_super_frame_start = test_data['super_frame_start']
    
    iq_data_int = test_data['iq_data_int'] 
    iq_data = iq_data_int[::2] + 1j*iq_data_int[1::2]
    
    data_carriers, super_frame_start = components.run_dsp(iq_data)
    
    assert np.allclose(data_carriers, exp_data_carriers, atol=1e-5)
    assert super_frame_start == exp_super_frame_start
    
    _plot_dsp_constellations(data_carriers, exp_data_carriers)
    
    
def test_get_constellations():
    iq_data_int = test_data['iq_data_int'] 
    iq_data = iq_data_int[::2] + 1j*iq_data_int[1::2]
    
    exp_constellations = test_data['constellations']
    exp_num_symbols = test_data['num_symbols']
    
    constellations, num_symbols = components.get_constellations(iq_data)
    
    assert np.allclose(constellations, exp_constellations, atol=1e-5)
    assert num_symbols == exp_num_symbols
    

def test_align_clocks():
    constellations = test_data['constellations']
    num_symbols = test_data['num_symbols']
    
    exp_clock_aligned_carriers = test_data['clock_aligned_carriers']
    
    clock_aligned_carriers =  components.align_clocks(constellations, 
                                                      num_symbols)
                                                     
    assert np.allclose(clock_aligned_carriers, 
                       exp_clock_aligned_carriers, atol=1e-5)
                       
                       
def test_get_tps_data():
    clock_aligned_carriers = test_data['clock_aligned_carriers']
    exp_super_frame_start = test_data['super_frame_start']
    
    super_frame_start = components.get_tps_data(clock_aligned_carriers)

    assert super_frame_start == exp_super_frame_start
    

def test_channel_correction():
    clock_aligned_carriers = test_data['clock_aligned_carriers']
    super_frame_start = test_data['super_frame_start']
    
    exp_data_carriers = test_data['data_carriers']
    
    data_carriers = components.channel_correction(clock_aligned_carriers, 
                                                  super_frame_start)
                                                  
    assert np.allclose(data_carriers, exp_data_carriers, atol=1e-5)


def _plot_dsp_constellations(data_carriers, exp_data_carriers):
    symbol_num = 100
    titles = ['Constellation of Symbol Number: {}'.format(symbol_num),
              'Expected Constellation']
    colours = ['r','b']
    _plot_constellations([data_carriers[symbol_num,:], 
                         exp_data_carriers[symbol_num,:]], titles, colours)

    plt.savefig('test_constellations.png')

def _plot_constellations(constellations, titles, colours):
    axis_limits = _find_axes_limits(constellations)
     
    num_constellations = len(constellations)
    plt.figure(figsize=(14, 6))
                       
    for k, constellation in enumerate(constellations):
        plt.subplot(1, num_constellations, k+1)
        plt.plot(constellation.real, constellation.imag, colours[k] + '.')
        _add_grid()
        
        plt.axis('scaled')
        plt.xlim([-axis_limits, axis_limits])
        plt.ylim((-axis_limits, axis_limits))
        plt.title(titles[k])
        
def _add_grid():
    # plot vertical lines
    for k in range(-8,9,2):
        plt.plot([k,k], [-8,8], 'k')
    
    # plot horizontal lines
    for k in range(-8,9,2):
        plt.plot([-8,8], [k,k], 'k')
    
    
def _find_axes_limits(constellations):
    
    max_all = 8 # axes must contain the grid    
    for constellation in constellations:
        real_ax = np.max(np.abs(constellation.real))
        imag_ax = np.max(np.abs(constellation.imag))
        
        max_axis = max(real_ax, imag_ax)
        
        if max_axis > max_all:
            max_all = max_axis
            
    margin = 1.1
    return max_all*margin


if __name__ == '__main__':
    test_data = np.load('./test/test_data.npz')
    plt.close('all')
    
    test_run_dsp()
    test_get_constellations()
    test_align_clocks()
    test_get_tps_data()
    test_channel_correction()




