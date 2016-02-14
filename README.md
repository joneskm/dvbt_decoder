# DVB-T Decoder
Python module for decoding DVB-T transmissions.
## Dependencies
- Numpy
- Make
- GCC
## Installation
From a terminal execute the following commands:
```
git clone https://github.com/joneskm/dvbt_decoder.git
cd dvbt_decoder
make
```
## Test Installation
The tests can be run individually, alternatively if you have pytest installed all tests can be run with one command:
```
python -m pytest
```
If successful a constellation image and an MPEG2-TS file will be created.
![Alt text](/readme_images/readme_constellations.png?raw=true)
The MPEG2-TS file should contain a short capture of the PSB1 DVB-T multiplex from the UK. The image shows a frame from this capture. 
![Alt text](/readme_images/readme_frame.png?raw=true)
## Usage
The dvbt_decoder.py script can be run directly or the DVBTDecoder class can be instantiated. To run the script directly pass the name of a file containing iq data:
```
python dvbt_decoder.py filename
```
For a full list of arguments type:
```
python dvbt_decoder.py -h
```
