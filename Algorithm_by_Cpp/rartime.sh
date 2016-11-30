#!/bin/bash
start_tm=`date +%s%N`;
tar -czf ./test/TWInst.exe.tar.gz ./test/TWInst.exe
end_tm=`date +%s%N`;
use_tm=`echo $end_tm $start_tm | awk '{ print ($1 - $2) / 1000000}'`
echo $use_tm
