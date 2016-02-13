#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import struct
import components
import argparse
import logging

class DVBTDecoder(object):
    def __init__(self, rate):
        self.rate = rate
        self.iq_data = None
        self.m2ts_byte_string = None

    def run(self, file_):        
        self._get_iq_data(file_)
        
        data_carriers, super_frame_start = components.run_dsp(self.iq_data)
        demultiplex_bits = components.inner_processing(data_carriers, 
                                                       super_frame_start)
                                                       
        vit_decoded = components.viterbi_decoder(demultiplex_bits, self.rate)
        self.m2ts_byte_string = components.outer_processing(vit_decoded, 
                                                        super_frame_start, 
                                                        self.rate)
        
        return self.m2ts_byte_string
        
    def read(self):
        return self.m2ts_byte_string

    def _get_iq_data(self, file_):
        indata = file_.read()
        self.num_samples = len(indata)/4
        data = struct.unpack('%ih' %(2*self.num_samples), indata)
        data = np.array(data,'int16')        
        self.iq_data = data[0:2*self.num_samples:2] + \
                                              1j*data[1:2*self.num_samples:2]    
    
        
if __name__=='__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument("filename", help="name of file containing iq data")
    parser.add_argument("--verbose", help="increase output verbosity",
                        action="store_true")
    args = parser.parse_args()
    
    if args.verbose:
        print "Verbosity turned on"
        logging.basicConfig(level=logging.DEBUG)

    in_file = open(args.filename, 'rb')    
    
    dvbt_decoder = DVBTDecoder(rate=(2,3))
    m2ts_byte_string = dvbt_decoder.run(in_file)    
    
    out_filename = 'dvbt_decoder_output.m2ts'
    out_file = open(out_filename,'wb')
    out_file.write(m2ts_byte_string)
    
    in_file.close()
    out_file.close()
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
