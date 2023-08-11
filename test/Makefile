all: 

example: example.o
	ld -o a.out example.o

example.o: example.asm
	as -o example.o example.asm

formatted_example.asm:
	as -o formatted_example.o formatted_example.asm
	ld -o a.out formatted_example.o
