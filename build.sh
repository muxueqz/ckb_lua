#!/bin/sh
riscv64-unknown-elf-gcc -I. -I deps/ckb-c-stdlib/  -I/app/lua-5.1.5/src/ /app/entry.c -o entry -L/app/lua-5.1.5/src -llua -lm
