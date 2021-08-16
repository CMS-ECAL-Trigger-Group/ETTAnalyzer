##-- Imports 
import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
from Configuration.StandardSequences.Eras import eras
import os 

##-- Define cms process 
process = cms.Process("ECALDoubleWeightsETTAnalyzer",eras.Run2_2017)
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("SimCalorimetry.EcalTrigPrimProducers.ecalTriggerPrimitiveDigis_readDBOffline_cff") ##-- Configuration for module which produces an EcalTrigPrimDigiCollection
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = '113X_dataRun2_relval_v1'
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('EventFilter.L1TRawToDigi.gtStage2Digis_cfi')

##-- Options that can be set on the command line 
options = VarParsing.VarParsing('analysis')

options.register ('userMaxEvents',
                -1, # default value
                VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                VarParsing.VarParsing.varType.int,           # string, int, or float
                "userMaxEvents")
options.register ('SevLevel',
                'zero', # default value
                VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                VarParsing.VarParsing.varType.string,           # string, int, or float
                "SevLevel")
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
                False, # default value
                VarParsing.VarParsing.multiplicity.singleton, 
                VarParsing.VarParsing.varType.bool,          
                "BarrelOnly")                                
options.register ('TPModeSqliteFile',
                'none.db', # default value -- 0 = Run 2 
                VarParsing.VarParsing.multiplicity.singleton, 
                VarParsing.VarParsing.varType.string,          
                "TPModeSqliteFile")    
options.register ('TPModeTag',
                'EcalTPG_TPMode_Run2_default', # default value -- 0 = Run 2 
                VarParsing.VarParsing.multiplicity.singleton, 
                VarParsing.VarParsing.varType.string,          
                "TPModeTag")  
options.register ('OddWeightsSqliteFile',                                        
                'weights/EcalTPGOddWeightIdMap.db', 
                VarParsing.VarParsing.multiplicity.singleton, 
                VarParsing.VarParsing.varType.string,          
                "OddWeightsSqliteFile") 
options.register ('RunETTAnalyzer', ##-- If true, produce output ntuple with ETTAnalyzer 
                False, # default value
                VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                VarParsing.VarParsing.varType.bool,           # string, int, or float
                "RunETTAnalyzer")                   
options.parseArguments()

process.GlobalTag.toGet = cms.VPSet(
    cms.PSet(record = cms.string("EcalTPGLinearizationConstRcd"),
         ),
    cms.PSet(record = cms.string("EcalTPGPedestalsRcd"), 
         )
)

# Load the odd weights
process.load("CondCore.CondDB.CondDB_cfi")
# input database (in this case the local sqlite file)
process.EcalOnTheFlyTPGconf = cms.ESSource("PoolDBESSource",
    DumpStat=cms.untracked.bool(True),
    toGet = cms.VPSet(cms.PSet(
                            record = cms.string('EcalTPGOddWeightIdMapRcd'),
                            tag = cms.string("EcalTPGOddWeightIdMap_test"),
                            connect = cms.string('sqlite_file:%s'%(options.OddWeightsSqliteFile))
                        ),
                    cms.PSet(
                            record = cms.string('EcalTPGOddWeightGroupRcd'),
                            tag = cms.string("EcalTPGOddWeightGroup_test"),
                            connect = cms.string('sqlite_file:weights/EcalTPGOddWeightGroup.db')
                        ),
                    cms.PSet(
                            record = cms.string('EcalTPGTPModeRcd'),
                            tag = cms.string(options.TPModeTag),
                            connect = cms.string('sqlite_file:%s'%(options.TPModeSqliteFile))
                        )
    ),
)
# process.es_prefer_ecalweights = cms.ESPrefer("PoolDBESSource","EcalOddWeights")

# ECAL Unpacker
process.load("EventFilter.EcalRawToDigi.EcalUnpackerMapping_cfi")
process.load("EventFilter.EcalRawToDigi.EcalUnpackerData_cfi")
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff') ##--  --> RawToDigi_cff --> Loads ecalTriggerPrimitiveDigis_cfi.py 
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('L1Trigger.Configuration.L1TReco_cff')
process.load('Configuration.EventContent.EventContent_cff')

process.raw2digi_step = cms.Path(process.RawToDigi)
process.endjob_step = cms.EndPath(process.endOfProcess)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step)

from L1Trigger.Configuration.customiseReEmul import L1TReEmulFromRAW
#,L1TEventSetupForHF1x1TPs  this last one is not in the release

#call to customisation function L1TReEmulFromRAW imported from L1Trigger.Configuration.customiseReEmul
#process = L1TReEmulFromRAW(process)
from EventFilter.L1TRawToDigi.caloStage2Digis_cfi import caloStage2Digis
process.rawCaloStage2Digis = caloStage2Digis.clone()
process.rawCaloStage2Digis.InputLabel = cms.InputTag('rawDataCollector')

##-- Create ECAL TP digis module 
process.ecalTriggerPrimitiveDigis = cms.EDProducer("EcalTrigPrimProducer",
   InstanceEB = cms.string('ebDigis'),
   InstanceEE = cms.string('eeDigis'),
   Label = cms.string('ecalDigis'),
   BarrelOnly = cms.bool(options.BarrelOnly),
   Famos = cms.bool(False),
   TcpOutput = cms.bool(False),
   Debug = cms.bool(options.Debug), ##-- Lots of printout 
   binOfMaximum = cms.int32(6), ## optional from release 200 on, from 1-10
   TPinfoPrintout = cms.bool(options.TPinfoPrintout),
#    TPmode = cms.uint32(options.TPmode) 
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.userMaxEvents) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 1 ) ##-- Printout run, lumi, event info  

##-- Get list of files 
Direc = "/eos/cms/store/user/khurana/ECAL/edmFiles/%s/"%(options.SevLevel)
files = ["file:%s%s"%(Direc, f) for f in os.listdir(Direc) if os.path.isfile(os.path.join(Direc, f))]

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                                files
                                #'file:/eos/user/p/petyt/tpgdata/320065/DAB74636-0F8E-E811-AC7A-FA163E5DEA72.root'
                                #'file:/eos/cms/store/data/Commissioning2020/Cosmics/RAW/v1/000/337/973/00000/50446142-8362-594F-9429-C17A552EA888.root'
                                #'file:/afs/cern.ch/work/k/khurana/L1Prefiring/EDAnalyzer/CMSSW_10_2_1/src/L1Prefiring/EventGeenration/step2_default.root'
                                #'file:/afs/cern.ch/work/k/khurana/L1Prefiring/EDAnalyzer/CMSSW_10_2_1/src/L1Prefiring/EventGeneration/rootfiles/step2_p17_singleEle.root'

                            )
                        )

##-- If running ETT Analyzer
if(options.RunETTAnalyzer):

    ##-- Create EDAnalyzer 
    process.tuplizer = cms.EDAnalyzer('ETTAnalyzer',
                                    ugtProducer = cms.InputTag("gtStage2Digis"),
                                    TPEmulatorCollection =  cms.InputTag("ecalTriggerPrimitiveDigis",""),
                                    useAlgoDecision = cms.untracked.string("initial"),
                                    firstBXInTrainAlgo = cms.untracked.string("L1_FirstCollisionInTrain"),
                                    lastBXInTrainAlgo = cms.untracked.string("L1_LastCollisionInTrain"),
                                    isoBXAlgo = cms.untracked.string("L1_IsolatedBunch"),
                                    TPCollection = cms.InputTag("ecalDigis","EcalTriggerPrimitives"),
                                    ## for data 
                                    stage2CaloLayer2EGammaProducer = cms.InputTag("gtStage2Digis","EGamma"),
                                    ## for mc 
                                    #stage2CaloLayer2EGammaProducer = cms.InputTag("hltGtStage2Digis","EGamma"),
                                    
                                    ## For rechits 
                                    EcalRecHitCollectionEB = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
                                    EcalRecHitCollectionEE = cms.InputTag("ecalRecHit","EcalRecHitsEE"),                                                                        

                                    
                                    ## for data on Raw
                                    EBdigis      = cms.InputTag("ecalDigis","ebDigis"),
                                    EEdigis      = cms.InputTag("ecalDigis","eeDigis"),
                                    
                                    ## for data on DIGIS : make sure why is this diff, w.r.t. RAW
                                    #EBdigis      = cms.InputTag("selectDigi","selectedEcalEBDigiCollection"),
                                    #EEdigis      = cms.InputTag("selectDigi","selectedEcalEEDigiCollection"),
                                    
                                    ## for mc
                                    #EBdigis      = cms.InputTag("simEcalDigis","ebDigis"),
                                    #EEdigis      = cms.InputTag("simEcalDigis","eeDigis"),
                                    genparticles = cms.InputTag("genParticles")
                                )

    ## Load appropriate processes for Rec Hits 
    process.load("Configuration/StandardSequences/Reconstruction_cff")
    import RecoLocalCalo.EcalRecProducers.ecalGlobalUncalibRecHit_cfi
    process.ecalUncalibHit = RecoLocalCalo.EcalRecProducers.ecalGlobalUncalibRecHit_cfi.ecalGlobalUncalibRecHit.clone()
    process.load("RecoLocalCalo.EcalRecProducers.ecalRecHit_cfi")
    process.load("Geometry.CaloEventSetup.CaloTopology_cfi")
    process.load("RecoLocalCalo.EcalRecProducers.ecalDetIdToBeRecovered_cfi")
    process.ecalRecHit.EBuncalibRecHitCollection = 'ecalUncalibHit:EcalUncalibRecHitsEB'
    process.ecalRecHit.EEuncalibRecHitCollection = 'ecalUncalibHit:EcalUncalibRecHitsEE'

    ol = "/eos/user/a/atishelm/SWAN_projects/EcalL1Optimization/ETTAnalyzer/"
    outFileName = "%s/ETTAnalyzer_Outputs/ETTAnalyzer_CMSSW_11_3_0_pre1_Sev%s_%sConfig.root"%(ol, options.SevLevel, options.TPModeTag.split('_')[2])

    process.TFileService = cms.Service("TFileService",
                                    fileName = cms.string(outFileName)
                                    #fileName = cms.string('Histo_L1Prefiring_0ns_FixLabel.root')
                                    )

    ##-- Define Path Which includes necessary modules for ETTAnalyzer 
    process.p = cms.Path(process.gtDigis*process.RawToDigi*
                        process.L1Reco*
                        process.gtStage2Digis*
                        process.ecalTriggerPrimitiveDigis*
                        process.ecalUncalibHit*
                        process.ecalDetIdToBeRecovered*
                        process.ecalRecHit*
                        process.tuplizer
                    )

##-- If not running ETT Analyzer
else: 

    ##-- Define Path Without ETTAnalyzer modules 
    process.p = cms.Path(
                        process.L1Reco*
                        process.gtStage2Digis*
                        process.ecalTriggerPrimitiveDigis
                    )

##-- In either case, append process path to process schedule 
process.schedule.append(process.p)
