# -*- coding: utf-8 -*-

from dvbt_decoder import DVBTDecoder
import struct
import numpy as np
import StringIO
import os

path = os.path.dirname(os.path.abspath(__file__))
test_file = (path + os.path.sep + 'test_data.npz')
test_data = np.load(test_file)

def test_dvbt_decoder(): 
    file_ = _get_iq_file()
    exp_m2ts_byte_string = test_data['dvbt_decoder_m2ts_byte_string'] 
    
    dvbt_decoder = DVBTDecoder(rate=(2,3))
    m2ts_byte_string = dvbt_decoder.run(file_)
    file_.close()
    
    assert m2ts_byte_string == exp_m2ts_byte_string
    
    m2ts_byte_string = dvbt_decoder.read()
    
    assert m2ts_byte_string == exp_m2ts_byte_string
    
    _write_m2ts_to_file(m2ts_byte_string)


def _write_m2ts_to_file(m2ts_byte_string):
    out_filename = 'test_decoder_output.m2ts'
    out_file = open(out_filename,'wb')
    out_file.write(m2ts_byte_string)
    out_file.close()


def _get_iq_file():
    '''
    Converts numpy array of iq data (found in test_data) into a StringIO 
    type
    '''

    iq_data_int = test_data['iq_data_int']
    iq_string = struct.pack('{}h'.format(len(iq_data_int)), *iq_data_int)
    file_ = StringIO.StringIO()
    file_.write(iq_string)
    file_.seek(0)
    
    return file_


if __name__ == '__main__':
    test_dvbt_decoder()
