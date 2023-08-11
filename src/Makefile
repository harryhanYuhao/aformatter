CC=clang

CWARNINGS=-Wall -Wextra -Wpedantic -Wshadow -Wpointer-arith -Wcast-align \

COPTIMISING=-O0 -ggdb3 -fno-omit-frame-pointer -fno-common -fstrict-aliasing 

CFLAGS=-std=c11 $(CWARNINGS) $(COPTIMISING)

INSTALL_DIR=$(HOME)/psu/bin

# Auxillary Variables

RED=\033[0;31m
BLUE=\033[0;34m
NC=\033[0m

aformatter: main.o utils.o globals.o parse.o flags.o
	@echo -e "------------------------------------------"
	@echo -e "$(BLUE)Linking: Producing executable$(NC)"
	@$(CC) $(CFLAGS) -o aformatter main.o utils.o globals.o parse.o flags.o
	@echo -e "------------------------------------------"

main.o: main.c utils.h globals.h
	@echo -e "------------------------------------------"
	@echo -e "$(BLUE)Compiling: main.c$(NC)"
	@$(CC) $(CFLAGS) -c main.c


utils.o: utils.c utils.h globals.h
	@echo -e "------------------------------------------"
	@echo -e "$(BLUE)Compiling: utils.c$(NC)"
	@$(CC) $(CFLAGS) -c utils.c 

globals.o: globals.c globals.h
	@echo -e "------------------------------------------"
	@echo -e "$(BLUE)Compiling: globals.c$(NC)"
	@$(CC) $(CFLAGS) -c globals.c

parse.o: parse.c parse.h
	@echo -e "------------------------------------------"
	@echo -e "$(BLUE)Compiling: parse.c$(NC)"
	@$(CC) $(CFLAGS) -c parse.c

flags.o: flags.c flags.h
	@echo -e "------------------------------------------"
	@echo -e "$(BLUE)Compiling: flags.c$(NC)"
	@$(CC) $(CFLAGS) -c flags.c

clean:
	rm -f *.o aformatter





