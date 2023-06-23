#!/bin/bash

for i in {-6..6}
do
   {
   xrdcp -r root://eos.grif.fr//eos/grif/cms/llr/store/user/tdesrous/Scan_delay_$i/Run_366713/ETTAnalyzer_CMSSW_12_3_0_DoubleWeights_ReemulateFromGlobalTag file:///eos/user/t/tdesrous/scans/delay$i/ > /dev/null
   hadd /eos/user/t/tdesrous/scans/delay$i/ETTAnalyzer_output${i}ns.root /eos/user/t/tdesrous/scans/delay$i/*/*/0000/E* > /dev/null
   rm -rf /eos/user/t/tdesrous/scans/delay$i/ETTAnalyzer_CMSSW_12_3_0_DoubleWeights_ReemulateFromGlobalTag > /dev/null
   } &
done