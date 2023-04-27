"""
Abraham Tishelman-Charny 

The purpose of this CMSSW configuration file is to run over CMSSW data files, with or without the ETTAnalyzer run on top. 
"""

# Imports 
import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras
import os 
from ConfigParams import options 

# Define cms process 
era = options.era
if(era == "Run2"): Process_Eras = eras.Run2_2017 
elif(era == "Run3"): Process_Eras = eras.Run3 
else:
  raise Exception("Don't know what to set Process_Eras to for the option:",era)
print("process era:",era)

process = cms.Process("ETTAnalyzer",Process_Eras)
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("SimCalorimetry.EcalTrigPrimProducers.ecalTriggerPrimitiveDigis_readDBOffline_cff") # Configuration for module which produces an EcalTrigPrimDigiCollection
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
                               
# Global Tag 
process.GlobalTag.globaltag = options.UserGlobalTag

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('EventFilter.L1TRawToDigi.gtStage2Digis_cfi')

process.GlobalTag.toGet = cms.VPSet(
    cms.PSet(record = cms.string("EcalTPGLinearizationConstRcd"),
         ),
    cms.PSet(record = cms.string("EcalTPGPedestalsRcd"), 
         )
)

# If overriding odd weights' records over global tag 
if(options.OverrideWeights):
    print("Setting double weights records to user input values")
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
                                connect = cms.string('sqlite_file:%s'%(options.OddWeightsGroupSqliteFile))
                            ),
                        cms.PSet(
                                record = cms.string('EcalTPGTPModeRcd'),
                                tag = cms.string(options.TPModeTag),
                                connect = cms.string('sqlite_file:%s'%(options.TPModeSqliteFile))
                            )
        ),
    )

    # If using 120X_dataRun3_HLT_v3 global tag which already has EcalTPGTPMode source defined, and you want to overwrite it, need to use an es_prefer below
    if(options.UserGlobalTag == "120X_dataRun3_HLT_v3"): 
        process.es_prefer_tpmode = cms.ESPrefer("PoolDBESSource","EcalOnTheFlyTPGconf") # https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideHowToUseESPrefer


# ECAL Unpacker
process.load("EventFilter.EcalRawToDigi.EcalUnpackerMapping_cfi")
process.load("EventFilter.EcalRawToDigi.EcalUnpackerData_cfi")
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff') #  --> RawToDigi_cff --> Loads ecalTriggerPrimitiveDigis_cfi.py 
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('L1Trigger.Configuration.L1TReco_cff')
process.load('Configuration.EventContent.EventContent_cff')

process.raw2digi_step = cms.Path(process.RawToDigi)
process.endjob_step = cms.EndPath(process.endOfProcess)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step)

from L1Trigger.Configuration.customiseReEmul import L1TReEmulFromRAW

#call to customisation function L1TReEmulFromRAW imported from L1Trigger.Configuration.customiseReEmul
from EventFilter.L1TRawToDigi.caloStage2Digis_cfi import caloStage2Digis
process.rawCaloStage2Digis = caloStage2Digis.clone()
process.rawCaloStage2Digis.InputLabel = cms.InputTag('rawDataCollector')

# Create ECAL TP digis module 
process.ecalTriggerPrimitiveDigis = cms.EDProducer("EcalTrigPrimProducer",
   InstanceEB = cms.string('ebDigis'),
   InstanceEE = cms.string('eeDigis'),
   Label = cms.string('ecalDigis'),
   BarrelOnly = cms.bool(True),
   Famos = cms.bool(False),
   TcpOutput = cms.bool(False),
   Debug = cms.bool(options.Debug), # Lots of printout 
   binOfMaximum = cms.int32(6), # optional from release 200 on, from 1-10
   TPinfoPrintout = cms.bool(options.TPinfoPrintout),
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.userMaxEvents) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 99999999 ) # Printout run, lumi, event info

# Save TPinfo
if(options.TPinfoPrintout or options.Debug):
    process.MessageLogger = cms.Service("MessageLogger",
                        destinations       =  cms.untracked.vstring('TPinfo'),
                        categories         = cms.untracked.vstring('EcalTPG'),
                        debugModules  = cms.untracked.vstring('*'),

                        TPinfo          = cms.untracked.PSet(
                                                    threshold =  cms.untracked.string('DEBUG'),
                                                    INFO       =  cms.untracked.PSet(limit = cms.untracked.int32(0)),
                                                    DEBUG   = cms.untracked.PSet(limit = cms.untracked.int32(0)),
                                                    EcalTPG = cms.untracked.PSet(limit = cms.untracked.int32(1000000000))
                                                    )
    )

files = []

# If a file is passed as a flag, run over it 
if(options.inFile != ""):
    print("inFile flag value found:")
    print(options.inFile)
    files.append(options.inFile)

# If not file is passed, process a default file from 2018 Zerobias data 
else:
    files = ["/store/data/Run2018C/ZeroBias/RAW/v1/000/320/063/00000/62F3929A-F08D-E811-8133-FA163E19E543.root"]

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                                files
                            )
                        )

# If running ETT Analyzer
if(options.RunETTAnalyzer):

    # Create EDAnalyzer 
    process.tuplizer = cms.EDAnalyzer('ETTAnalyzer', # Name ultimately comes from plugins/ETTAnalyzer.cc final lines with plugin name definition 
                                    ugtProducer = cms.InputTag("gtStage2Digis"),
                                    savePreFireInfo = cms.bool(True), 
                                    BarrelOnly = cms.bool(options.BarrelOnly),
                                    TPEmulatorCollection =  cms.InputTag("ecalTriggerPrimitiveDigis",""), # Different name for full readout?
                                    # TPEmulatorCollection =  cms.InputTag("ecalTriggerPrimitiveDigis","ecalTriggerPrimitiveDigis"), # Different name for full readout?
                                    useAlgoDecision = cms.untracked.string("initial"),
                                    firstBXInTrainAlgo = cms.untracked.string("L1_FirstCollisionInTrain"),
                                    lastBXInTrainAlgo = cms.untracked.string("L1_LastCollisionInTrain"),
                                    isoBXAlgo = cms.untracked.string("L1_IsolatedBunch"),
                                    TPCollection = cms.InputTag("ecalDigis","EcalTriggerPrimitives"), 
                                    # for data 
                                    stage2CaloLayer2EGammaProducer = cms.InputTag("gtStage2Digis","EGamma"),
                                    # for mc 
                                    #stage2CaloLayer2EGammaProducer = cms.InputTag("hltGtStage2Digis","EGamma"),
                                    
                                    # For rechits 
                                    EcalRecHitCollectionEB = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
                                    EcalRecHitCollectionEE = cms.InputTag("ecalRecHit","EcalRecHitsEE"),                                                                        
                                    
                                    # for data on Raw
                                    EBdigis      = cms.InputTag("ecalDigis","ebDigis"),
                                    EEdigis      = cms.InputTag("ecalDigis","eeDigis"),
                                    
                                    # for data on DIGIS : make sure why is this diff, w.r.t. RAW
                                    #EBdigis      = cms.InputTag("selectDigi","selectedEcalEBDigiCollection"),
                                    #EEdigis      = cms.InputTag("selectDigi","selectedEcalEEDigiCollection"),
                                    
                                    # for mc
                                    #EBdigis      = cms.InputTag("simEcalDigis","ebDigis"),
                                    #EEdigis      = cms.InputTag("simEcalDigis","eeDigis"),
                                    genparticles = cms.InputTag("genParticles")
                                )

    # Load appropriate processes for Rec Hits 
    process.load("Configuration/StandardSequences/Reconstruction_cff")

    # Multifit
    if(options.RecoMethod == "Multifit"):
        print("Offline energy reconstruction to be performed with Multifit")
        import RecoLocalCalo.EcalRecProducers.ecalMultiFitUncalibRecHit_cfi
        process.ecalUncalibHit =  RecoLocalCalo.EcalRecProducers.ecalMultiFitUncalibRecHit_cfi.ecalMultiFitUncalibRecHit.clone()
        process.ecalUncalibHit.algoPSet.activeBXs =cms.vint32(-5,-4,-3,-2,-1,0,1,2,3,4)
        process.ecalUncalibHit.algoPSet.useLumiInfoRunHeader = cms.bool (False)

    # Offline weights 
    elif(options.RecoMethod == "weights"):
        print("Offline energy reconstruction to be performed with offline weights")
        import RecoLocalCalo.EcalRecProducers.ecalGlobalUncalibRecHit_cfi
        process.ecalUncalibHit = RecoLocalCalo.EcalRecProducers.ecalGlobalUncalibRecHit_cfi.ecalGlobalUncalibRecHit.clone()

    else:
        raise Exception("Unknown reconstruction method: %s"%(options.RecoMethod))

    process.load("RecoLocalCalo.EcalRecProducers.ecalRecHit_cff") # This cff was introduced after 11_3_0 to handle the ECAL local reco configuration on GPU automatically.
    process.load("Geometry.CaloEventSetup.CaloTopology_cfi")
    process.load("RecoLocalCalo.EcalRecProducers.ecalDetIdToBeRecovered_cfi")
    process.ecalRecHit.cpu.EBuncalibRecHitCollection = cms.InputTag('ecalUncalibHit', 'EcalUncalibRecHitsEB') # ecalRecHit used to be a simple EDProducer in 11_3_0 but now it is a SwitchProducerCUDA
    process.ecalRecHit.cpu.EEuncalibRecHitCollection = cms.InputTag('ecalUncalibHit', 'EcalUncalibRecHitsEE')    

    # Name for output root files 
    process.TFileService = cms.Service("TFileService",
                                    fileName = cms.string("ETTAnalyzer_output.root")
                                    )

    # Define Path Which includes necessary modules for ETTAnalyzer 
    process.p = cms.Path(
                         process.gtDigis*
                         process.RawToDigi*
                         process.L1Reco*
                         process.gtStage2Digis*
                         process.ecalTriggerPrimitiveDigis*
                         process.ecalUncalibHit*
                         process.ecalDetIdToBeRecovered*
                         process.ecalRecHit*
                         process.tuplizer
                    )

# If not running ETT Analyzer
else: 

    # Define Path Without ETTAnalyzer modules 
    process.p = cms.Path(
                        process.L1Reco*
                        process.gtStage2Digis*
                        process.ecalTriggerPrimitiveDigis
                    )

# In either case, append process path to process schedule 
process.schedule.append(process.p)
