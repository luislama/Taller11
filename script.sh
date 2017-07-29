#!/bin/bash

for i in  {1..20}; do
	./Hilos 10000000000 $i >> resultados.txt
done