#!/bin/bash
for i in b s i m q
do
  for j in 1 2 3 4 5
  do
    for((k=1;k<=20;k++))
    do
      ./main $i $j
    done
  done
done
