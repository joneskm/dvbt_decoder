SUB_DIR_VIT=./components/viterbi_decoder/
SUB_DIR_TEST=./test

all:
	$(MAKE) -C $(SUB_DIR_VIT)
	$(MAKE) -C $(SUB_DIR_TEST)
