all: word_finder

word_finder: word_finder.c
	gcc -fno-stack-protector -o word_finder word_finder.c
	#  -z execstack

	