import FWCore.ParameterSet.Config as cms


from Configuration.StandardSequences.Eras import eras
process = cms.Process("ECALDoubleWeightsETTAnalyzer",eras.Run2_2017)
#process = cms.Process("L1PrefiringAnalyzerTPGANALYSIS")

process.load("FWCore.MessageService.MessageLogger_cfi")


process.load("SimCalorimetry.EcalTrigPrimProducers.ecalTriggerPrimitiveDigis_readDBOffline_cff")

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.GlobalTag.globaltag = '110X_dataRun2_v12'

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')


process.load('EventFilter.L1TRawToDigi.gtStage2Digis_cfi')




process.GlobalTag.toGet = cms.VPSet(
    cms.PSet(record = cms.string("EcalTPGLinearizationConstRcd"),
         ),
    cms.PSet(record = cms.string("EcalTPGPedestalsRcd"), 
         )
)

# ECAL Unpacker
process.load("EventFilter.EcalRawToDigi.EcalUnpackerMapping_cfi")
process.load("EventFilter.EcalRawToDigi.EcalUnpackerData_cfi")

process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
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

process.ecalTriggerPrimitiveDigis = cms.EDProducer("EcalTrigPrimProducer",
   InstanceEB = cms.string('ebDigis'),
   InstanceEE = cms.string('eeDigis'),
   Label = cms.string('ecalDigis'),
   BarrelOnly = cms.bool(False),
   Famos = cms.bool(False),
   TcpOutput = cms.bool(False),
                                                   Debug = cms.bool(True),
   binOfMaximum = cms.int32(6), ## optional from release 200 on, from 1-10

)










process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.source = cms.Source("PoolSource",
                            # replace 'myfile.root' with the source file you want to use
                            fileNames = cms.untracked.vstring(
                                
                                'file:/eos/user/p/petyt/tpgdata/320065/DAB74636-0F8E-E811-AC7A-FA163E5DEA72.root'
                                #'file:/eos/cms/store/data/Commissioning2020/Cosmics/RAW/v1/000/337/973/00000/50446142-8362-594F-9429-C17A552EA888.root'
                                #'file:/afs/cern.ch/work/k/khurana/L1Prefiring/EDAnalyzer/CMSSW_10_2_1/src/L1Prefiring/EventGeenration/step2_default.root'
                                #'file:/afs/cern.ch/work/k/khurana/L1Prefiring/EDAnalyzer/CMSSW_10_2_1/src/L1Prefiring/EventGeneration/rootfiles/step2_p17_singleEle.root'
                                

                            )
                        )

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



process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('ecal_l1t_team_tuples.root')
                                   #fileName = cms.string('Histo_L1Prefiring_0ns_FixLabel.root')
                                  )


#process.makedigis = cms.Path()

process.p = cms.Path(process.L1Reco*
                     process.gtStage2Digis*
                     process.ecalTriggerPrimitiveDigis*
                     process.tuplizer
                 )


process.schedule.append(process.p)
