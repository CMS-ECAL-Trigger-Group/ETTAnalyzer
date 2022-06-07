# ETTAnalyzer Examples 

The purpose of this file is to keep track of examples for running ETTAnalyzer.

## 2022 Beam Splash analysis

In 2022, CMS received beam splashes as a part of LHC/CMS commissioning for LHC Run 3. These are very useful for the testing of ECAL Double Weights, which may be useful for out of time tagging, as splashes produce a high energy ECAL hits with a range of timings. In order to re-emulate one of the splashes with the ECAL configuration used at the time of data-taking, one should run:

```
cmsRun ETTAnalyzer_cfg_12_3_0.py BarrelOnly=1 RunETTAnalyzer=1 inFile="file:/afs/cern.ch/user/d/dkonst/work/public/splashes_350966_FEVT.root" OverrideWeights=0 RecoMethod=weights UserGlobalTag=123X_dataRun3_HLT_v7 era=Run3
```

One can also run with an old global tag and config, but stil plot the data quantities, using:

```
cmsRun ETTAnalyzer_cfg_12_3_0.py Debug=0 TPModeSqliteFile=TPModes/output/EcalTPG_TPMode_Tagging.db TPModeTag=EcalTPG_TPMode_Tagging TPinfoPrintout=0 userMaxEvents=-1 BarrelOnly=1 RunETTAnalyzer=1 inFile="file:/afs/cern.ch/user/d/dkonst/work/public/splashes_350966_FEVT.root" OverrideWeights=0 UserGlobalTag=120X_dataRun3_HLT_v3 RecoMethod=weights OddWeightsSqliteFile=weights/output/MinDelta_0p5Prime_OddWeights.db

python3 plot/PlotBeamSplashes.py --TPMode Tagging --Weights 0p5 --year 2022
```

## 2021 Beam Splash analysis 

To check global tag from a file:

```
edmProvDump /eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/2021BeamSplashes/skimSplashEvents2021_run_346050.root | grep "globaltag"
```

If you run with this global tag and find a record is missing, you can search that tag in the CondDB and find which global tags it is available in, using `EcalSimPulseShapeRcd` as an example search: [CondDB_Search](https://cms-conddb.cern.ch/cmsDbBrowser/search/Prod/EcalSimPulseShapeRcd).

Run ETTAnalyzer over 2021 beam splash skim file:

```
cmsRun conf_12_1_0_pre3.py Debug=0 TPModeSqliteFile=TPModes/EcalTPG_TPMode_tagging.db \
TPinfoPrintout=0 userMaxEvents=-1 BarrelOnly=1 \
RunETTAnalyzer=1 inFile="file:/eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/2021BeamSplashes/skimSplashEvents2021_run_346050.root" \
OverrideWeights=0 UserGlobalTag=120X_dataRun3_HLT_v3 RecoMethod=weights
```

Plot fine grain bit for a given event:

```
ETTAnalyzerTree->Draw("iphi:ieta >> h(58,-29,29,81,0,81)","FineGrainBit==1&&ttFlag!=4&&twrADC>0&&evtNb==13707","COLZ1")
```

## 2018 Beam Splash re-emulation 

Run 2 mode:

```
cmsRun conf_12_1_0_pre3.py Debug=0 TPModeSqliteFile=TPModes/EcalTPG_TPMode_Run2_default.db \
TPModeTag=EcalTPG_TPMode_Run2_default TPinfoPrintout=0 userMaxEvents=50 OddWeightsSqliteFile=weights/ZeroCandidateSet.db BarrelOnly=1 \
RunETTAnalyzer=1 inFile="file:/eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/2018BeamSplashes/RAW/Splashes2018_highECALReadout_run313133.root" \
OverrideWeights=1 UserGlobalTag=113X_dataRun2_relval_v1 RecoMethod=weights
```

Tagging mode with sensible ODD weights:

```
cmsRun conf_12_1_0_pre3.py Debug=0 TPModeSqliteFile=TPModes/EcalTPG_TPMode_tagging.db \
TPModeTag=EcalTPG_TPMode_tagging TPinfoPrintout=0 userMaxEvents=50 OddWeightsSqliteFile=weights/ZeroCandidateSet.db BarrelOnly=1 \
RunETTAnalyzer=1 inFile="file:/eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/2018BeamSplashes/RAW/Splashes2018_highECALReadout_run313133.root" \
OverrideWeights=1 UserGlobalTag=113X_dataRun2_relval_v1 RecoMethod=weights
```


## More examples 

### Examples

First, if you need to access files on the grid, make sure to set your VOMS proxy first:

	voms-proxy-init --voms cms --valid 168:00	

To run the ETTAnalyzer locally over one file in Run 2 mode:
	  
	cmsRun conf_12_1_0_pre3.py Debug=0 TPModeSqliteFile=TPModes/EcalTPG_TPMode_Run2_default.db \
	  TPModeTag=EcalTPG_TPMode_Run2_default TPinfoPrintout=0 userMaxEvents=10 \
	  OddWeightsSqliteFile=weights/ZeroCandidateSet.db BarrelOnly=1 RunETTAnalyzer=1 \
	  inFile="/store/data/Run2018C/ZeroBias/RAW/v1/000/320/063/00000/62F3929A-F08D-E811-8133-FA163E19E543.root" \
	  OverrideWeights=1 UserGlobalTag=113X_dataRun2_relval_v1 RecoMethod=weights
	  
If this ran successfully, you should have an output file "ETTAnalyzer_output.root" containing a TDirectory "tuplizer" with a tree "ETTAnalyzerTree". This tree contains all of the variables defined in the ETTAnalyzer, such as TP associated severity level, max rec hit energy in the TT, associated time, real and emulated TP energy, etc. 
	  
To run with strip zeroing and a candidate set of odd weights:

	cmsRun conf_12_1_0_pre3.py Debug=0 TPModeSqliteFile=TPModes/EcalTPG_TPMode_Run3_zeroing.db \
	  TPModeTag=EcalTPG_TPMode_Run3_zeroing TPinfoPrintout=0 userMaxEvents=10 \
	  OddWeightsSqliteFile=weights/ZeroCandidateSet.db BarrelOnly=1 RunETTAnalyzer=1 \
	  inFile="/store/data/Run2018C/ZeroBias/RAW/v1/000/320/063/00000/62F3929A-F08D-E811-8133-FA163E19E543.root" \
	  OverrideWeights=1 UserGlobalTag=113X_dataRun2_relval_v1 RecoMethod=weights

Full readout file on disk:

	inFile="/store/data/Run2018D/ZeroBias3/RAW/v1/000/324/725/00000/93581922-91B4-9547-8212-B1D9B99C2AA5.root"

Run on a single TP view: 

	cmsRun conf_12_1_0_pre3.py Debug=1 TPModeSqliteFile=TPModes/EcalTPG_TPMode_Run2_default.db \
	TPModeTag=EcalTPG_TPMode_Run2_default TPinfoPrintout=1 userMaxEvents=1 OddWeightsSqliteFile=weights/ZeroCandidateSet.db \
	BarrelOnly=1 RunETTAnalyzer=1 \
	inFile="file:/eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/DoubleWeights/Single_TP_View/Root_Files/Run_319697_Lumi_253_Event_376665141.root" \
	OverrideWeights=1 UserGlobalTag=113X_dataRun2_relval_v1 RecoMethod=weights

### Optional: Add hack to remove TDirectory from ETTAnalyzer output files

By default the output TFile from the ETTAnalyzer plugin must have a TDirectory. To produce output files without this TDirectory, one can add a hacked cms package which removes it:

	cd CMSSW_12_1_0_pre3/src/
	git remote add unofficial-cmssw git@github.com:atishelmanch/cmssw.git
	git cms-addpkg CommonTools/UtilAlgos
	git cms-addpkg CommonTools/Utils
	wget https://raw.githubusercontent.com/atishelmanch/cmssw/from-CMSSW_11_3_0_TDirectory_Hack/CommonTools/Utils/src/TFileDirectory.cc
	mv TFileDirectory.cc CommonTools/Utils/src/TFileDirectory.cc 
	wget https://raw.githubusercontent.com/atishelmanch/cmssw/from-CMSSW_11_3_0_TDirectory_Hack/CommonTools/UtilAlgos/src/TFileService.cc
	mv TFileService.cc CommonTools/UtilAlgos/src/TFileService.cc 
	scram b -j 	

#### Run 2 

To run with the Run 2 ECAL L1 configuration, the TPmode should be set to zero, shown in binary form in the following command's for visual purposes, as this sets all of the optional configuration flags to their defaults: 

	cmsRun conf_11_3_0_pre1_withETTAnalyzer.py Debug=0 TPModeSqliteFile=TPModes/EcalTPG_TPMode_Run2_default.db TPModeTag=EcalTPG_TPMode_Run2_default TPinfoPrintout=0 userMaxEvents=10 OddWeightsSqliteFile=weights/ZeroCandidateSet.db BarrelOnly=1

This command will print various debug statements in the ECAL L1 data stream steps, run on one event, obtain odd filter weights from the sqlite file in the weights directory, and run only on the EB. 

#### Zeroing configuration

To run with a candidate zeroing mechanism, configuration 1, the only thing that changes is the TPmode tag and sqlite file:

	cmsRun conf_11_3_0_pre1.py Debug=1 TPModeTag=EcalTPG_TPMode_Run3_zeroing  \
     TPModeSqliteFile=TPModes/EcalTPGTPMode_Run3_zeroing.db\
	 TPinfoPrintout=1 maxEvents=1 OddWeightsSqliteFile=weights/EcalTPGOddWeightIdMap.db BarrelOnly=1

This zeroing mechanism zeroes at the strip level. If a strip's odd filter returns a greater value than the even filter, the even filter output will not be included in the TCP sum. As long as the total odd filter energy among the TT strips is greater than the even filter energy sum, this will be flagged in the form of the EB infobit1, where the FGVB is replaced. This is useful for monitoring zeroing, but at the cost of removing the FGVB.  


# Additional examples


# Re-emulation 

The purpose of this readme is to provide instructions for re-emulating CMS data using custom ECAL L1 configurations (TPModes) and different sets of ODD weights (the second set of double
weights). This type of study is useful as it describes the expected performance at ECAL and CMS if we had been running with a given TPMode and set of ODD weights previously, and
therefore gives us an idea of what performance we may expect when running with such configurations in the future. 

## 2021 Pilot Beam data 

In this example, we will go over the steps necessary to re-emulate the 2021 pilot beam data taken at CMS. First make sure to run the [ETTAnalyzer Setup](https://github.com/CMS-ECAL-Trigger-Group/ETTAnalyzer#setup) 
steps from the main README. 

One can run on a single file with:

```
cmsRun conf_12_1_0_pre3.py Debug=0 TPModeSqliteFile=TPModes/output/EcalTPG_TPMode_Run3_zeroing.db   TPModeTag=EcalTPG_TPMode_Run3_zeroing TPinfoPrintout=0 userMaxEvents=1 \
OddWeightsSqliteFile=weights/output/MinDelta_2p5Prime_OddWeights.db  OddWeightsGroupSqliteFile="weights/output/OneEBOneEEset_adding2021Strips.db"  BarrelOnly=1 RunETTAnalyzer=1 \
inFile="file:/eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/2021StableBeams/Run_346446/f811cb68-7ac4-4148-abbc-3a76d95881d2.root" OverrideWeights=1 \
UserGlobalTag=120X_dataRun3_HLT_v3 RecoMethod=weights
```

6 cases to look at: (WP X PF X RECO) --> 2 working points, with or without ODD peak finder, with weights or multifit offline reco. 

## Full readout data 

Example command:

```
cmsRun conf_12_1_0_pre3.py Debug=0 TPModeSqliteFile=TPModes/output/EcalTPG_TPMode_Run3_zeroing.db TPinfoPrintout=0 userMaxEvents=1 BarrelOnly=1 RunETTAnalyzer=1 \
inFile="file:/eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/Full_Readout_Data/One_Root_File/266DAA99-D153-8843-ADCA-6AFCB7FBD3EA.root" OverrideWeights=1 \
UserGlobalTag=101X_dataRun2_HLT_v7 RecoMethod=weights OddWeightsGroupSqliteFile="weights/output/OneEBOneEEset_adding2021Strips.db" TPModeTag=EcalTPG_TPMode_Run3_zeroing \
OddWeightsSqliteFile=weights/output/MinDelta_2p5Prime_OddWeights.db
```

## Useful ntuple commands

For plotting useful quantities quickly from single files:

```
ETTAnalyzerTree->Draw("(1 - (twrEmul3ADC/twrADC)):twrADC","ttFlag!=4&&twrADC>0&&sevlv==0","COLZ1")
```
## CRAB

After making sure things work locally, one can run over many files using a crab configuration, for example for the 2021 pilot beam data:

```
crab submit -c CrabConfig_12_1_0_pre3_PilotBeam2021.py
```

One can then analyze output ntuples using [ETT_Coffea](https://github.com/CMS-ECAL-Trigger-Group/ETT_Coffea).
