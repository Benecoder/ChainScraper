#!/bin/bash
set -e

./input.py $1
./sorting


for i in {1..3}
do 
	./input.py
	./sorting 

done
