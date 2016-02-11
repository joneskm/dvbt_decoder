# -*- coding: utf-8 -*-

import numpy as np
NUM_CONV_STATES = 64

def _convolutional_coder(bits):
    '''
    Given the state of the convolutional coder (in the form of the bit values
    at each position) determine the x and y bit outputs
    '''

    x_out = (bits[0] + bits[3] + bits[4] + bits[5] + bits[6])%2
    y_out = (bits[0] + bits[1] + bits[3] + bits[4] + bits[6])%2
    
    return bool(x_out), bool(y_out)

def _get_conv_coder_params(new_state, lsb_prev_state):
    '''
    Given the new coder state and the lsb of the previous state, determine
    the previous state and the x and y bit outputs given these state 
    transitions.
    '''

    prev_state = ((new_state&31) << 1) + lsb_prev_state
    
    get_bits = lambda x: [(x >> i) & 1 for i in range(6)]
    bits = [lsb_prev_state] + get_bits(new_state)
    
    x_out, y_out = _convolutional_coder(bits)
    
    return prev_state, x_out, y_out


def initialise_arrays():
    '''
    For each state which the coder can be in, determine all (=2) previous 
    states that the coder could have been in at the previous step. For each
    state transition determine the expected x and y bit outputs of the coder
    '''
    
    prev_states = np.empty((NUM_CONV_STATES,2))
    expected_measurement = np.empty((NUM_CONV_STATES,4),'bool')
    
    for new_state in range(NUM_CONV_STATES):
        
        for k, lsb_prev_state in enumerate([0,1]):
            prev_state, x_out, y_out = _get_conv_coder_params(new_state, 
                                                              lsb_prev_state)
            
            prev_states[new_state, lsb_prev_state] = prev_state
            expected_measurement[new_state, 2*k:2*k+2] = [x_out, y_out]

    return expected_measurement, prev_states

def _write_header(f):
    
    f.write('''
/****************************************************************************
** WARNING: This code was auto-generated with generate_viterbi_decoder_c.py. 
** All changes made to this file will be lost when
** generate_viterbi_decoder_c.py is run.
****************************************************************************/
''')
    

def _write_find_win_seq(f):
    f.write('''
/* Trace back through the states of the longest path and determine the bit 
value at each step */   
int find_win_seq(unsigned char *win_seq, int length_output, 
                 short int *state_history, int final_state) {
    int next_state = final_state;
    int k;
    int last_row = length_output - 1;

    for (k=0; k<length_output; k++) {
        if (next_state>31)
            win_seq[length_output-1-k] = 1;
        else
            win_seq[length_output-1-k] = 0;

        next_state = state_history[(last_row - k)*64 + next_state];
    }
    return 0;
}
    ''')

def _write_viterbi_core(f):
    f.write(
'''
/* Finds the longest path lengths for each final state along with the state
history corresponding to each path. The algorithm iterates over all outputs
(i.e. coder inputs). At each iteration the path lengths to each of the 64
possible states is calculated and for each state the longest path is chosen.
The iteration across the 64 states is not done using a for loop. This
reduces the number of calculations required for each state and consequently
reduces the execution time. */   
int viterbi_core(int *unpunctured, int length_output, 
                 short int *state_history, int *new_path_lengths) {
  int k,kk;
  int count = 0;
  int x_bit, y_bit;
  int prev_path_lengths[64] = { 0 };
  short int prev_state_0, prev_state_1;
  int prev_path_length;
  int length_0, length_1;
  int offset;

  for (k=0; k < length_output; k++) {

    offset = 64*k;

    x_bit = unpunctured[count];
    y_bit = unpunctured[count+1];

    count += 2; 
''' 
    )
    _write_inner_for_loop(f)
    
    f.write(
'''
	//--------------------------------------
	// set previous path lengths to new path lengths
    for (kk=0; kk<64; kk++) {
      prev_path_lengths[kk] = new_path_lengths[kk];
    }

	
  }
  return 0;
}    
''' 
    )

    
def _write_inner_for_loop(f):
    '''
    Write contents of the for loop which iterates around all states of the
    coder. To reduce execution time this loop has been un-rolled.
    '''

    for kk in range(NUM_CONV_STATES):
        f.write(
'''
        //===================================================
        // loop index = %i
'''
        %kk)
    
        #-----------------------------------------------------------------
        # LSB of prev state = 0
    
        f.write(
'''
        //------------------------
        // LSB of old state = 0
        prev_state_0 = %i;
        prev_path_length = prev_path_lengths[%i];
'''
        %( transitions[kk,0], transitions[kk,0])
        )
        expected_x_bit = expected_measurement[kk,0]
    
        if expected_x_bit:
            f.write(
'''
        length_0 = prev_path_length + x_bit;
''' 
            )
        else:
            f.write(
'''
        length_0 = prev_path_length - x_bit;
'''
        )
        expected_y_bit = expected_measurement[kk,1]
    
        if expected_y_bit:
            f.write(    
'''
        length_0 += y_bit;       
'''
            )
        else:
            f.write(
        
'''
        length_0 -= y_bit;

'''
            )

        #-----------------------------------------------------------------
        # LSB of old state = 1
    
        f.write(
'''
        //------------------------
        // LSB of old state = 1
        prev_state_1 = %i;
        prev_path_length = prev_path_lengths[%i];
'''
        %( transitions[kk,1], transitions[kk,1])
        )

        expected_x_bit = expected_measurement[kk,2]
    
        if expected_x_bit:
            f.write(
'''        
        length_1 = prev_path_length + x_bit;    
'''        
            )
        else:
            f.write(
'''
        length_1 = prev_path_length - x_bit;
'''              
            )
        expected_y_bit = expected_measurement[kk,3]
    
        if expected_y_bit:
            f.write(
'''
        length_1 += y_bit;
'''        
            )
        else:
            f.write(
'''
        length_1 -= y_bit;
'''        
            )

        f.write(
'''    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[%i] = length_0;

            state_history[%i+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[%i] = length_1;

            state_history[%i+offset] = prev_state_1;    
        }
'''     %(kk,kk,kk,kk)    
    
        )

if __name__ == '__main__':
    '''
    This script generates c code for the core parts of the viterbi decoder.
    '''

    expected_measurement, transitions = initialise_arrays()
    
    filename = 'viterbi_core.c'
    f = open(filename,'w')
    
    _write_header(f)
    _write_find_win_seq(f)
    _write_viterbi_core(f)
    
    f.close()






    





