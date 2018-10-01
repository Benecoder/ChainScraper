#!/bin/bash
# Shortens c++ compilation by one command because I a m fucking lazy!
# Reqireds the input of the c++ file name without the extension

g++ -o $1 $1'.cpp'
./$1


