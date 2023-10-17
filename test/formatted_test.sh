#!/bin/sh   

    set         -e          # Exit immediately if a command exits with a non-zero status.
    sh          make.sh     
    ./aformatter example.asm 

