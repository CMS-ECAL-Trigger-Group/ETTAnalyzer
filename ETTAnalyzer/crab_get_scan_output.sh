#!/bin/bash

for i in {-6..6}
do
   {
   crab getoutput --dir=./crab_projects/crab_Scan_delay${i}ns/ --checksum=no --outputpath=/eos/user/t/tdesrous/scans/delay$i 
   hadd /eos/user/t/tdesrous/scans/delay$i/ETTAnalyzer_output${i}ns.root /eos/user/t/tdesrous/scans/delay$i/E*
   rm /eos/user/t/tdesrous/scans/delay$i/ETTAnalyzer_output_*
   } &
done