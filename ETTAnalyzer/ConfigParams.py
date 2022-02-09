"""
16 August 2021
Abraham Tishelman-Charny

The purpose of this cmssw configuration file is to provide command line options for CMSSW configuration files 
"""

import FWCore.ParameterSet.VarParsing as VarParsing

##-- Options that can be set on the command line 
options = VarParsing.VarParsing('analysis')

options.register ('userMaxEvents',
                -1, # default value
                VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                VarParsing.VarParsing.varType.int,           # string, int, or float
                "userMaxEvents")
options.register ('TPinfoPrintout',
                False, # default value
                VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                VarParsing.VarParsing.varType.bool,           # string, int, or float
                "TPinfoPrintout")
options.register ('Debug',
                False, # default value
                VarParsing.VarParsing.multiplicity.singleton, 
                VarParsing.VarParsing.varType.bool,          
                "Debug")   
options.register ('BarrelOnly',
                # False, # default value
                True, # default value
                VarParsing.VarParsing.multiplicity.singleton, 
                VarParsing.VarParsing.varType.bool,          
                "BarrelOnly")                                
options.register ('TPModeSqliteFile',
                'EcalTPG_TPMode_Run3_zeroing.db',
                VarParsing.VarParsing.multiplicity.singleton, 
                VarParsing.VarParsing.varType.string,          
                "TPModeSqliteFile")    
options.register ('TPModeTag',
                'EcalTPG_TPMode_Run3_zeroing', # default value -- 0 = Run 2 
                VarParsing.VarParsing.multiplicity.singleton, 
                VarParsing.VarParsing.varType.string,          
                "TPModeTag")  
options.register ('OddWeightsSqliteFile',                                        
                'ZeroCandidateSet.db', 
                VarParsing.VarParsing.multiplicity.singleton, 
                VarParsing.VarParsing.varType.string,          
                "OddWeightsSqliteFile") 
options.register ('OddWeightsGroupSqliteFile',                                        
                'weights/output/OneEBOneEEset.db', 
                VarParsing.VarParsing.multiplicity.singleton, 
                VarParsing.VarParsing.varType.string,          
                "OddWeightsGroupSqliteFile")                 
options.register ('RunETTAnalyzer', ##-- If true, produce output ntuple with ETTAnalyzer 
                True, # default value
                VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                VarParsing.VarParsing.varType.bool,           # string, int, or float
                "RunETTAnalyzer")     
options.register ('inFile',                                        
                '', 
                VarParsing.VarParsing.multiplicity.singleton, 
                VarParsing.VarParsing.varType.string,          
                "inFile")   
options.register ('RecoMethod', ##-- Offline energy reconstruction method                               
                'weights', 
                VarParsing.VarParsing.multiplicity.singleton, 
                VarParsing.VarParsing.varType.string,          
                "RecoMethod")                                               
options.register ('Printerval', ##-- How often to print event information  
                99999, # default value
                VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                VarParsing.VarParsing.varType.int,           # string, int, or float
                "Printerval")   
##-- If using es_prefer to override odd weights records over global tag. If global tag does not contain TPG odd weight records, may need to do this 
options.register ('OverrideWeights', 
                False, # default value
                VarParsing.VarParsing.multiplicity.singleton, 
                VarParsing.VarParsing.varType.bool,           
                "OverrideWeights")    
options.register ('UserGlobalTag', ##-- global tag                           
                '113X_dataRun2_relval_v1', 
                VarParsing.VarParsing.multiplicity.singleton, 
                VarParsing.VarParsing.varType.string,          
                "UserGlobalTag") 


options.parseArguments()