"""
16 August 2021 
Abraham Tishelman-Charny 

The purpose of this crab configuration file is to run the ETTAnalyzer over many CMSSW data files in parallel. 
crab submit -c CrabConfig_12_1_0_pre3.py
"""

# import argparse 
# parser = argparse.ArgumentParser()
# parser.add_argument("--Run", required=True, type=str, help="Run number to run over.")
# args = parser.parse_args()
# Run = args.Run

oneFile = 1 ##-- Run over one file as a test 
addFilePrefix = 0 # Add "file:" to start of file paths 
removeEOSprefix = 1 
Run = "346446"

CMS_files = []

print("Adding CMS files...")

runs = [Run]

##-- By run number 
for run in runs:
     print("Run",run)
     text_file_path = "RunsAndFiles/Files_Run_%s.txt"%(run)
     with open(text_file_path) as f: # https://stackoverflow.com/questions/3277503/how-to-read-a-file-line-by-line-into-a-list
         content = f.readlines()
         content = [x.strip() for x in content] 
         for file in content:
             if(addFilePrefix): file_path = "file:%s"%(file)
             else: 
                 if(removeEOSprefix): file = file.replace("/eos/cms", "")
                 file_path = file 

             CMS_files.append(file_path)

if(oneFile):
  #CMS_files = ["/store/group/dpg_ecal/alca_ecalcalib/Trigger/2021StableBeams/Run_346447/0053ac71-c7ce-4ee0-9d5b-e1e09823f903.root"] 
  CMS_files = [CMS_files[0]] # take first file of files list 

print("Number of input files:",len(CMS_files))

"""
CRAB configuration parameters 
"""

inDir = "/afs/cern.ch/work/a/atishelm/private/CMS-ECAL-Trigger-Group/CMSSW_12_1_0_pre3/src/ETTAnalyzer/ETTAnalyzer/"

from CRABClient.UserUtilities import config
config = config()

oneFileStr = ""
if(oneFile): oneFileStr = "_oneFile"

config.General.requestName = 'Run_%s_PilotBeam_2021%s'%(Run, oneFileStr)
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True ##-- Need this True to transfer output files!! at least with eos output.
config.General.transferLogs = False 
 
##-- Set cmssw configuration file parameters 
config.JobType.pyCfgParams = [
                                'OverrideWeights=1', # whether or not to override weights 
                                'UserGlobalTag=120X_dataRun3_HLT_v3',
                                'TPModeSqliteFile=EcalTPG_TPMode_Run3_zeroing.db', # strip zeroing, with or without ODD PF configs to try: [EcalTPG_TPMode_Run3_zeroingOddPeakFinder.db, EcalTPG_TPMode_Run3_zeroing,db]
                                'OddWeightsGroupSqliteFile=OneEBOneEEset_adding2021Strips.db',
                                'BarrelOnly=1',
                                'RunETTAnalyzer=1',
                                'TPModeTag=EcalTPG_TPMode_Run3_zeroing',
                                'OddWeightsSqliteFile=MinDelta_2p5Prime_OddWeights.db', # Working points to try: [MinDelta_2p5Prime_OddWeights, MinDelta_0p5Prime_OddWeights.db]
                                'RecoMethod=weights', # offline reco methods to try: [Multifit, weights] 
                             ] 
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '%s/conf_12_1_0_pre3.py'%(inDir)

# Splitting
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1

# Namings
config.Data.outputPrimaryDataset = 'Run_%s_PilotBeam_2021%s'%(Run, oneFileStr)
config.Data.outputDatasetTag = 'ETTAnalyzer_CMSSW_12_1_0_pre3_DoubleWeights_StripZeroingMode'
config.Data.outLFNDirBase = '/store/group/dpg_ecal/alca_ecalcalib/Trigger/DoubleWeights/' 
config.Data.publication = False 

config.Data.userInputFiles = CMS_files 

config.Site.whitelist = ['T2_CH_CERN'] ##-- Eventually had to change from 'T2_FR_GRIF_LLR' whitelist to this 
config.Site.storageSite = 'T2_CH_CERN'
# config.Site.storageSite = 'T3_CH_CERNBOX' ##-- CERNBOX, takes outLFNDirBase and changes '/store/user' in outLFNDirBase to /eos/user/

# ##-- Strip zeroing 
# config.JobType.inputFiles = ['%s/EcalTPGOddWeightGroup.db'%(inDir),
#                              '%s/ZeroCandidateSet.db'%(inDir),
#                              '%s/EcalTPG_TPMode_Run3_zeroing.db'%(inDir),
#                              '%s/ConfigParams.py'%(inDir) ##-- For cmssw config options 
#                              ]                             

##-- Strip zeroing 
config.JobType.inputFiles = ['%s/weights/output/MinDelta_2p5Prime_OddWeights.db'%(inDir),
                             '%s/weights/output/OneEBOneEEset_adding2021Strips.db'%(inDir),
                             '%s/TPModes/output/EcalTPG_TPMode_Run3_zeroing.db'%(inDir),
                             '%s/ConfigParams.py'%(inDir) ##-- For cmssw config options 
                             ]    