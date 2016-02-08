#!/bin/bash

gcc -shared -Wall -O3 -o libviterbi_core.so -fPIC viterbi_core.c
