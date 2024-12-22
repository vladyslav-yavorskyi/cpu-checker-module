#!/bin/bash


load_cpu() {
	while :; do
		:
	done
}

for i in {1..9}; do
	load_cpu &
done
