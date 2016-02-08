
/****************************************************************************
** WARNING: This code was auto-generated with gnerate_viterbi_decoder.py. All
** changes made to this file will be lost when generate_viterbi_decoder.py is
** run.
****************************************************************************/

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

        //===================================================
        // loop index = 0

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 0;
        prev_path_length = prev_path_lengths[0];

        length_0 = prev_path_length - x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 1;
        prev_path_length = prev_path_lengths[1];
        
        length_1 = prev_path_length + x_bit;    

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[0] = length_0;

            state_history[0+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[0] = length_1;

            state_history[0+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 1

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 2;
        prev_path_length = prev_path_lengths[2];

        length_0 = prev_path_length - x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 3;
        prev_path_length = prev_path_lengths[3];
        
        length_1 = prev_path_length + x_bit;    

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[1] = length_0;

            state_history[1+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[1] = length_1;

            state_history[1+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 2

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 4;
        prev_path_length = prev_path_lengths[4];

        length_0 = prev_path_length - x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 5;
        prev_path_length = prev_path_lengths[5];
        
        length_1 = prev_path_length + x_bit;    

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[2] = length_0;

            state_history[2+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[2] = length_1;

            state_history[2+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 3

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 6;
        prev_path_length = prev_path_lengths[6];

        length_0 = prev_path_length - x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 7;
        prev_path_length = prev_path_lengths[7];
        
        length_1 = prev_path_length + x_bit;    

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[3] = length_0;

            state_history[3+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[3] = length_1;

            state_history[3+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 4

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 8;
        prev_path_length = prev_path_lengths[8];

        length_0 = prev_path_length + x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 9;
        prev_path_length = prev_path_lengths[9];

        length_1 = prev_path_length - x_bit;

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[4] = length_0;

            state_history[4+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[4] = length_1;

            state_history[4+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 5

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 10;
        prev_path_length = prev_path_lengths[10];

        length_0 = prev_path_length + x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 11;
        prev_path_length = prev_path_lengths[11];

        length_1 = prev_path_length - x_bit;

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[5] = length_0;

            state_history[5+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[5] = length_1;

            state_history[5+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 6

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 12;
        prev_path_length = prev_path_lengths[12];

        length_0 = prev_path_length + x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 13;
        prev_path_length = prev_path_lengths[13];

        length_1 = prev_path_length - x_bit;

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[6] = length_0;

            state_history[6+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[6] = length_1;

            state_history[6+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 7

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 14;
        prev_path_length = prev_path_lengths[14];

        length_0 = prev_path_length + x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 15;
        prev_path_length = prev_path_lengths[15];

        length_1 = prev_path_length - x_bit;

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[7] = length_0;

            state_history[7+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[7] = length_1;

            state_history[7+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 8

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 16;
        prev_path_length = prev_path_lengths[16];

        length_0 = prev_path_length + x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 17;
        prev_path_length = prev_path_lengths[17];

        length_1 = prev_path_length - x_bit;

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[8] = length_0;

            state_history[8+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[8] = length_1;

            state_history[8+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 9

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 18;
        prev_path_length = prev_path_lengths[18];

        length_0 = prev_path_length + x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 19;
        prev_path_length = prev_path_lengths[19];

        length_1 = prev_path_length - x_bit;

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[9] = length_0;

            state_history[9+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[9] = length_1;

            state_history[9+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 10

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 20;
        prev_path_length = prev_path_lengths[20];

        length_0 = prev_path_length + x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 21;
        prev_path_length = prev_path_lengths[21];

        length_1 = prev_path_length - x_bit;

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[10] = length_0;

            state_history[10+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[10] = length_1;

            state_history[10+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 11

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 22;
        prev_path_length = prev_path_lengths[22];

        length_0 = prev_path_length + x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 23;
        prev_path_length = prev_path_lengths[23];

        length_1 = prev_path_length - x_bit;

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[11] = length_0;

            state_history[11+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[11] = length_1;

            state_history[11+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 12

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 24;
        prev_path_length = prev_path_lengths[24];

        length_0 = prev_path_length - x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 25;
        prev_path_length = prev_path_lengths[25];
        
        length_1 = prev_path_length + x_bit;    

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[12] = length_0;

            state_history[12+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[12] = length_1;

            state_history[12+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 13

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 26;
        prev_path_length = prev_path_lengths[26];

        length_0 = prev_path_length - x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 27;
        prev_path_length = prev_path_lengths[27];
        
        length_1 = prev_path_length + x_bit;    

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[13] = length_0;

            state_history[13+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[13] = length_1;

            state_history[13+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 14

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 28;
        prev_path_length = prev_path_lengths[28];

        length_0 = prev_path_length - x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 29;
        prev_path_length = prev_path_lengths[29];
        
        length_1 = prev_path_length + x_bit;    

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[14] = length_0;

            state_history[14+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[14] = length_1;

            state_history[14+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 15

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 30;
        prev_path_length = prev_path_lengths[30];

        length_0 = prev_path_length - x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 31;
        prev_path_length = prev_path_lengths[31];
        
        length_1 = prev_path_length + x_bit;    

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[15] = length_0;

            state_history[15+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[15] = length_1;

            state_history[15+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 16

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 32;
        prev_path_length = prev_path_lengths[32];

        length_0 = prev_path_length + x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 33;
        prev_path_length = prev_path_lengths[33];

        length_1 = prev_path_length - x_bit;

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[16] = length_0;

            state_history[16+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[16] = length_1;

            state_history[16+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 17

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 34;
        prev_path_length = prev_path_lengths[34];

        length_0 = prev_path_length + x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 35;
        prev_path_length = prev_path_lengths[35];

        length_1 = prev_path_length - x_bit;

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[17] = length_0;

            state_history[17+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[17] = length_1;

            state_history[17+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 18

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 36;
        prev_path_length = prev_path_lengths[36];

        length_0 = prev_path_length + x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 37;
        prev_path_length = prev_path_lengths[37];

        length_1 = prev_path_length - x_bit;

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[18] = length_0;

            state_history[18+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[18] = length_1;

            state_history[18+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 19

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 38;
        prev_path_length = prev_path_lengths[38];

        length_0 = prev_path_length + x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 39;
        prev_path_length = prev_path_lengths[39];

        length_1 = prev_path_length - x_bit;

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[19] = length_0;

            state_history[19+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[19] = length_1;

            state_history[19+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 20

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 40;
        prev_path_length = prev_path_lengths[40];

        length_0 = prev_path_length - x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 41;
        prev_path_length = prev_path_lengths[41];
        
        length_1 = prev_path_length + x_bit;    

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[20] = length_0;

            state_history[20+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[20] = length_1;

            state_history[20+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 21

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 42;
        prev_path_length = prev_path_lengths[42];

        length_0 = prev_path_length - x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 43;
        prev_path_length = prev_path_lengths[43];
        
        length_1 = prev_path_length + x_bit;    

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[21] = length_0;

            state_history[21+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[21] = length_1;

            state_history[21+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 22

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 44;
        prev_path_length = prev_path_lengths[44];

        length_0 = prev_path_length - x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 45;
        prev_path_length = prev_path_lengths[45];
        
        length_1 = prev_path_length + x_bit;    

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[22] = length_0;

            state_history[22+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[22] = length_1;

            state_history[22+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 23

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 46;
        prev_path_length = prev_path_lengths[46];

        length_0 = prev_path_length - x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 47;
        prev_path_length = prev_path_lengths[47];
        
        length_1 = prev_path_length + x_bit;    

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[23] = length_0;

            state_history[23+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[23] = length_1;

            state_history[23+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 24

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 48;
        prev_path_length = prev_path_lengths[48];

        length_0 = prev_path_length - x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 49;
        prev_path_length = prev_path_lengths[49];
        
        length_1 = prev_path_length + x_bit;    

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[24] = length_0;

            state_history[24+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[24] = length_1;

            state_history[24+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 25

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 50;
        prev_path_length = prev_path_lengths[50];

        length_0 = prev_path_length - x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 51;
        prev_path_length = prev_path_lengths[51];
        
        length_1 = prev_path_length + x_bit;    

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[25] = length_0;

            state_history[25+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[25] = length_1;

            state_history[25+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 26

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 52;
        prev_path_length = prev_path_lengths[52];

        length_0 = prev_path_length - x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 53;
        prev_path_length = prev_path_lengths[53];
        
        length_1 = prev_path_length + x_bit;    

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[26] = length_0;

            state_history[26+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[26] = length_1;

            state_history[26+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 27

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 54;
        prev_path_length = prev_path_lengths[54];

        length_0 = prev_path_length - x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 55;
        prev_path_length = prev_path_lengths[55];
        
        length_1 = prev_path_length + x_bit;    

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[27] = length_0;

            state_history[27+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[27] = length_1;

            state_history[27+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 28

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 56;
        prev_path_length = prev_path_lengths[56];

        length_0 = prev_path_length + x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 57;
        prev_path_length = prev_path_lengths[57];

        length_1 = prev_path_length - x_bit;

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[28] = length_0;

            state_history[28+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[28] = length_1;

            state_history[28+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 29

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 58;
        prev_path_length = prev_path_lengths[58];

        length_0 = prev_path_length + x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 59;
        prev_path_length = prev_path_lengths[59];

        length_1 = prev_path_length - x_bit;

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[29] = length_0;

            state_history[29+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[29] = length_1;

            state_history[29+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 30

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 60;
        prev_path_length = prev_path_lengths[60];

        length_0 = prev_path_length + x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 61;
        prev_path_length = prev_path_lengths[61];

        length_1 = prev_path_length - x_bit;

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[30] = length_0;

            state_history[30+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[30] = length_1;

            state_history[30+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 31

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 62;
        prev_path_length = prev_path_lengths[62];

        length_0 = prev_path_length + x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 63;
        prev_path_length = prev_path_lengths[63];

        length_1 = prev_path_length - x_bit;

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[31] = length_0;

            state_history[31+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[31] = length_1;

            state_history[31+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 32

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 0;
        prev_path_length = prev_path_lengths[0];

        length_0 = prev_path_length + x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 1;
        prev_path_length = prev_path_lengths[1];

        length_1 = prev_path_length - x_bit;

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[32] = length_0;

            state_history[32+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[32] = length_1;

            state_history[32+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 33

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 2;
        prev_path_length = prev_path_lengths[2];

        length_0 = prev_path_length + x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 3;
        prev_path_length = prev_path_lengths[3];

        length_1 = prev_path_length - x_bit;

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[33] = length_0;

            state_history[33+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[33] = length_1;

            state_history[33+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 34

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 4;
        prev_path_length = prev_path_lengths[4];

        length_0 = prev_path_length + x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 5;
        prev_path_length = prev_path_lengths[5];

        length_1 = prev_path_length - x_bit;

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[34] = length_0;

            state_history[34+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[34] = length_1;

            state_history[34+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 35

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 6;
        prev_path_length = prev_path_lengths[6];

        length_0 = prev_path_length + x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 7;
        prev_path_length = prev_path_lengths[7];

        length_1 = prev_path_length - x_bit;

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[35] = length_0;

            state_history[35+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[35] = length_1;

            state_history[35+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 36

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 8;
        prev_path_length = prev_path_lengths[8];

        length_0 = prev_path_length - x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 9;
        prev_path_length = prev_path_lengths[9];
        
        length_1 = prev_path_length + x_bit;    

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[36] = length_0;

            state_history[36+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[36] = length_1;

            state_history[36+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 37

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 10;
        prev_path_length = prev_path_lengths[10];

        length_0 = prev_path_length - x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 11;
        prev_path_length = prev_path_lengths[11];
        
        length_1 = prev_path_length + x_bit;    

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[37] = length_0;

            state_history[37+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[37] = length_1;

            state_history[37+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 38

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 12;
        prev_path_length = prev_path_lengths[12];

        length_0 = prev_path_length - x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 13;
        prev_path_length = prev_path_lengths[13];
        
        length_1 = prev_path_length + x_bit;    

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[38] = length_0;

            state_history[38+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[38] = length_1;

            state_history[38+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 39

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 14;
        prev_path_length = prev_path_lengths[14];

        length_0 = prev_path_length - x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 15;
        prev_path_length = prev_path_lengths[15];
        
        length_1 = prev_path_length + x_bit;    

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[39] = length_0;

            state_history[39+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[39] = length_1;

            state_history[39+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 40

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 16;
        prev_path_length = prev_path_lengths[16];

        length_0 = prev_path_length - x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 17;
        prev_path_length = prev_path_lengths[17];
        
        length_1 = prev_path_length + x_bit;    

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[40] = length_0;

            state_history[40+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[40] = length_1;

            state_history[40+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 41

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 18;
        prev_path_length = prev_path_lengths[18];

        length_0 = prev_path_length - x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 19;
        prev_path_length = prev_path_lengths[19];
        
        length_1 = prev_path_length + x_bit;    

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[41] = length_0;

            state_history[41+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[41] = length_1;

            state_history[41+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 42

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 20;
        prev_path_length = prev_path_lengths[20];

        length_0 = prev_path_length - x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 21;
        prev_path_length = prev_path_lengths[21];
        
        length_1 = prev_path_length + x_bit;    

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[42] = length_0;

            state_history[42+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[42] = length_1;

            state_history[42+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 43

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 22;
        prev_path_length = prev_path_lengths[22];

        length_0 = prev_path_length - x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 23;
        prev_path_length = prev_path_lengths[23];
        
        length_1 = prev_path_length + x_bit;    

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[43] = length_0;

            state_history[43+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[43] = length_1;

            state_history[43+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 44

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 24;
        prev_path_length = prev_path_lengths[24];

        length_0 = prev_path_length + x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 25;
        prev_path_length = prev_path_lengths[25];

        length_1 = prev_path_length - x_bit;

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[44] = length_0;

            state_history[44+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[44] = length_1;

            state_history[44+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 45

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 26;
        prev_path_length = prev_path_lengths[26];

        length_0 = prev_path_length + x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 27;
        prev_path_length = prev_path_lengths[27];

        length_1 = prev_path_length - x_bit;

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[45] = length_0;

            state_history[45+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[45] = length_1;

            state_history[45+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 46

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 28;
        prev_path_length = prev_path_lengths[28];

        length_0 = prev_path_length + x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 29;
        prev_path_length = prev_path_lengths[29];

        length_1 = prev_path_length - x_bit;

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[46] = length_0;

            state_history[46+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[46] = length_1;

            state_history[46+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 47

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 30;
        prev_path_length = prev_path_lengths[30];

        length_0 = prev_path_length + x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 31;
        prev_path_length = prev_path_lengths[31];

        length_1 = prev_path_length - x_bit;

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[47] = length_0;

            state_history[47+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[47] = length_1;

            state_history[47+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 48

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 32;
        prev_path_length = prev_path_lengths[32];

        length_0 = prev_path_length - x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 33;
        prev_path_length = prev_path_lengths[33];
        
        length_1 = prev_path_length + x_bit;    

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[48] = length_0;

            state_history[48+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[48] = length_1;

            state_history[48+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 49

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 34;
        prev_path_length = prev_path_lengths[34];

        length_0 = prev_path_length - x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 35;
        prev_path_length = prev_path_lengths[35];
        
        length_1 = prev_path_length + x_bit;    

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[49] = length_0;

            state_history[49+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[49] = length_1;

            state_history[49+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 50

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 36;
        prev_path_length = prev_path_lengths[36];

        length_0 = prev_path_length - x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 37;
        prev_path_length = prev_path_lengths[37];
        
        length_1 = prev_path_length + x_bit;    

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[50] = length_0;

            state_history[50+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[50] = length_1;

            state_history[50+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 51

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 38;
        prev_path_length = prev_path_lengths[38];

        length_0 = prev_path_length - x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 39;
        prev_path_length = prev_path_lengths[39];
        
        length_1 = prev_path_length + x_bit;    

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[51] = length_0;

            state_history[51+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[51] = length_1;

            state_history[51+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 52

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 40;
        prev_path_length = prev_path_lengths[40];

        length_0 = prev_path_length + x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 41;
        prev_path_length = prev_path_lengths[41];

        length_1 = prev_path_length - x_bit;

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[52] = length_0;

            state_history[52+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[52] = length_1;

            state_history[52+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 53

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 42;
        prev_path_length = prev_path_lengths[42];

        length_0 = prev_path_length + x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 43;
        prev_path_length = prev_path_lengths[43];

        length_1 = prev_path_length - x_bit;

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[53] = length_0;

            state_history[53+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[53] = length_1;

            state_history[53+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 54

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 44;
        prev_path_length = prev_path_lengths[44];

        length_0 = prev_path_length + x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 45;
        prev_path_length = prev_path_lengths[45];

        length_1 = prev_path_length - x_bit;

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[54] = length_0;

            state_history[54+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[54] = length_1;

            state_history[54+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 55

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 46;
        prev_path_length = prev_path_lengths[46];

        length_0 = prev_path_length + x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 47;
        prev_path_length = prev_path_lengths[47];

        length_1 = prev_path_length - x_bit;

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[55] = length_0;

            state_history[55+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[55] = length_1;

            state_history[55+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 56

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 48;
        prev_path_length = prev_path_lengths[48];

        length_0 = prev_path_length + x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 49;
        prev_path_length = prev_path_lengths[49];

        length_1 = prev_path_length - x_bit;

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[56] = length_0;

            state_history[56+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[56] = length_1;

            state_history[56+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 57

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 50;
        prev_path_length = prev_path_lengths[50];

        length_0 = prev_path_length + x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 51;
        prev_path_length = prev_path_lengths[51];

        length_1 = prev_path_length - x_bit;

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[57] = length_0;

            state_history[57+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[57] = length_1;

            state_history[57+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 58

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 52;
        prev_path_length = prev_path_lengths[52];

        length_0 = prev_path_length + x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 53;
        prev_path_length = prev_path_lengths[53];

        length_1 = prev_path_length - x_bit;

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[58] = length_0;

            state_history[58+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[58] = length_1;

            state_history[58+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 59

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 54;
        prev_path_length = prev_path_lengths[54];

        length_0 = prev_path_length + x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 55;
        prev_path_length = prev_path_lengths[55];

        length_1 = prev_path_length - x_bit;

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[59] = length_0;

            state_history[59+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[59] = length_1;

            state_history[59+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 60

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 56;
        prev_path_length = prev_path_lengths[56];

        length_0 = prev_path_length - x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 57;
        prev_path_length = prev_path_lengths[57];
        
        length_1 = prev_path_length + x_bit;    

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[60] = length_0;

            state_history[60+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[60] = length_1;

            state_history[60+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 61

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 58;
        prev_path_length = prev_path_lengths[58];

        length_0 = prev_path_length - x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 59;
        prev_path_length = prev_path_lengths[59];
        
        length_1 = prev_path_length + x_bit;    

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[61] = length_0;

            state_history[61+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[61] = length_1;

            state_history[61+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 62

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 60;
        prev_path_length = prev_path_lengths[60];

        length_0 = prev_path_length - x_bit;

        length_0 += y_bit;       

        //------------------------
        // LSB of old state = 1
        prev_state_1 = 61;
        prev_path_length = prev_path_lengths[61];
        
        length_1 = prev_path_length + x_bit;    

        length_1 -= y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[62] = length_0;

            state_history[62+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[62] = length_1;

            state_history[62+offset] = prev_state_1;    
        }

        //===================================================
        // loop index = 63

        //------------------------
        // LSB of old state = 0
        prev_state_0 = 62;
        prev_path_length = prev_path_lengths[62];

        length_0 = prev_path_length - x_bit;

        length_0 -= y_bit;


        //------------------------
        // LSB of old state = 1
        prev_state_1 = 63;
        prev_path_length = prev_path_lengths[63];
        
        length_1 = prev_path_length + x_bit;    

        length_1 += y_bit;
    
        //-------------------------------
        // Choose longest path, update state history and update path lengths
                
        if (length_0 > length_1) {
            new_path_lengths[63] = length_0;

            state_history[63+offset] = prev_state_0;
            
        }
        else {
            new_path_lengths[63] = length_1;

            state_history[63+offset] = prev_state_1;    
        }

	//--------------------------------------
	// set previous path lengths to new path lengths
    for (kk=0; kk<64; kk++) {
      prev_path_lengths[kk] = new_path_lengths[kk];
    }

	
  }
  return 0;
}    
