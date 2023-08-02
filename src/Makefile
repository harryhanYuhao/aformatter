CC=gcc

CWARNINGS=-Wall -Wextra -Wpedantic -Wformat=2 -Wswitch-default -Wpointer-arith -Wbad-function-cast -Wstrict-overflow=5 -Wstrict-prototypes -Winline -Wundef -Wnested-externs -Wcast-qual -Wshadow -Wunreachable-code -Wlogical-op -Wfloat-equal -Wstrict-aliasing=2 -Wredundant-decls -Wold-style-definition 

COPTIMISING=-O0 -ggdb3 -fno-omit-frame-pointer -ffloat-store -fno-common -fstrict-aliasing -g

CFLAGS=-std=c11 $(CWARNINGS) $(COPTIMISING) -lm

INSTALL_DIR=$(HOME)/psu/bin

# Auxillary Variables

RED=\033[0;31m
BLUE=\033[0;34m
NC=\033[0m

aformatter: main.o utils.o
	@echo -e "------------------------------------------"
	@echo -e "$(BLUE)Linking: Producing executable$(NC)"
	@$(CC) $(CFLAGS) -o aformatter main.o utils.o
	@echo -e "------------------------------------------"

main.o: main.c 
	@echo -e "------------------------------------------"
	@echo -e "$(BLUE)Compiling: main.c$(NC)"
	@$(CC) $(CFLAGS) -c main.c


utils.o: utils.c utils.h
	@echo -e "------------------------------------------"
	@echo -e "$(BLUE)Compiling: utils.c$(NC)"
	@$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f *.o aformatter
