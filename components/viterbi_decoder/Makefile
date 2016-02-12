all: libviterbi_core.so

libviterbi_core.so: viterbi_core.c
	gcc -shared -Wall -O3 -o libviterbi_core.so -fPIC viterbi_core.c

viterbi_core.c: generate_viterbi_core_c.py
	python generate_viterbi_core_c.py
