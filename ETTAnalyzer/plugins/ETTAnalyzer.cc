//------------------------------------------------------------------------//
// 21 June 2021                                                           //
//                                                                        //
// Raman Khurana                                                          //
// Abraham Tishelman-Charny                                               //
//                                                                        //
// The purpose of this plugin is to save trigger primitive and Level 1    //
// information from CMS data and MC AODs. This source code file defines   //
// the member functions used by the ETTAnalyzer class.                    //
//------------------------------------------------------------------------//

#include "ECALDoubleWeights/ETTAnalyzer/interface/ETTAnalyzer.h"

// ------------ method called for each event  ------------
void ETTAnalyzer::analyze(const edm::Event& e, const edm::EventSetup& c)
{
   using namespace edm;
  //  std::cout << "In ETTAnalyzer::analyze()" << std::endl;

   ESHandle< EcalElectronicsMapping > ecalmapping;
   c.get< EcalMappingRcd >().get(ecalmapping);
   theMapping_ = ecalmapping.product();
   
   for (int i=0; i<4032;i++){
     count_ADC[i] = -999;
     gain_id[i] = -999;
     index_df[i] = -999;
     index_ts[i] = -999;
     tower_eta[i] = -999;
     tower_phi[i] = -999;
     xtal_ix[i] = -999;
     xtal_iy[i] = -999;
   }
 
   if(savePreFireInfo_){

   for (int i=0; i<10; i++){
     L1preIsoIetam2[i] = -999;
     L1preIsoIetam1[i] = -999;
     L1preIsoIetazero[i] = -999;
     L1preIsoIetap1[i] = -999;
     L1preIsoIetap2[i] = -999;
     
     L1preNonisoIetam2[i] = -999;
     L1preNonisoIetam1[i] = -999;
     L1preNonisoIetazero[i] = -999;
     L1preNonisoIetap1[i] = -999;
     L1preNonisoIetap2[i] = -999;
     
     L1preIsoIphim2[i] = -999;
     L1preIsoIphim1[i] = -999;
     L1preIsoIphizero[i] = -999;
     L1preIsoIphip1[i] = -999;
     L1preIsoIphip2[i] = -999;
     
     L1preNonisoIphim2[i] = -999;
     L1preNonisoIphim1[i] = -999;
     L1preNonisoIphizero[i] = -999;
     L1preNonisoIphip1[i] = -999;
     L1preNonisoIphip2[i] = -999;
     
     L1preIsoEnergym2[i] = -999;
     L1preIsoEnergym1[i] = -999;
     L1preIsoEnergyzero[i] = -999;
     L1preIsoEnergyp1[i] = -999;
     L1preIsoEnergyp2[i] = -999;

     L1preNonisoEnergym2[i] = -999;
     L1preNonisoEnergym1[i] = -999;
     L1preNonisoEnergyzero[i] = -999;
     L1preNonisoEnergyp1[i] = -999;
     L1preNonisoEnergyp2[i] = -999;

   
     L1preIsoPtm2[i] = -999;
     L1preIsoPtm1[i] = -999;
     L1preIsoPtzero[i] = -999;
     L1preIsoPtp1[i] = -999;
     L1preIsoPtp2[i] = -999;

     L1preNonisoPtm2[i] = -999;
     L1preNonisoPtm1[i] = -999;
     L1preNonisoPtzero[i] = -999;
     L1preNonisoPtp1[i] = -999;
     L1preNonisoPtp2[i] = -999;

   }

   }

   v_nonisocounterm2     = 0 ;
   v_nonisocounterm1     = 0 ;
   v_nonisocounterzero   = 0 ;
   v_nonisocounterp1     = 0 ;
   v_nonisocounterp2     = 0 ;
   
   v_isocounterm2     = 0 ;
   v_isocounterm1     = 0 ;
   v_isocounterzero   = 0 ;
   v_isocounterp1     = 0 ;
   v_isocounterp2     = 0 ;
   
   // ------------------------------*----------------*-------------**********--------------------------------------------------------------------------------------------
   // ------------------------------*--------------*-*------------------*------------------------------------------------------------------------------------------------
   // ------------------------------*----------------*------------------*------------------------------------------------------------------------------------------------
   // ------------------------------*----------------*------------------*------------------------------------------------------------------------------------------------
   // ------------------------------*----------------*------------------*------------------------------------------------------------------------------------------------
   // ------------------------------*----------------*------------------*------------------------------------------------------------------------------------------------
   // ------------------------------**********------***-----------------*------------------------------------------------------------------------------------------------
   
   // Open uGT readout record
   edm::Handle<GlobalAlgBlkBxCollection> uGtAlgs;
   e.getByToken(l1tStage2uGtProducer_, uGtAlgs);
   
   // EGamma Collection
   edm::Handle<l1t::EGammaBxCollection> EGammaBxCollection;
   e.getByToken(stage2CaloLayer2EGammaToken_, EGammaBxCollection);
   
   // Find out in which BX the first collision in train, isolated bunch, and last collision in train have fired.
   // In case of pre firing it will be in BX 1 or BX 2 and this will determine the BX shift that
   // will be applied to the timing histogram later.
   int bxShiftFirst = -999;
  //  int bxShiftIso = -999;
  //  int bxShiftLast = -999;
   for (int bx = uGtAlgs->getFirstBX(); bx <= uGtAlgs->getLastBX(); ++bx) {
     for (GlobalAlgBlkBxCollection::const_iterator itr = uGtAlgs->begin(bx); itr != uGtAlgs->end(bx); ++itr) {
       // first bunch in train
       if (algoBitFirstBxInTrain_ != -1) {
	 bool bit = false;
	 switch (useAlgoDecision_) {
	 case 0:
	   bit = itr->getAlgoDecisionInitial(algoBitFirstBxInTrain_);
	   break;
	 case 1:
	   bit = itr->getAlgoDecisionInterm(algoBitFirstBxInTrain_);
	   break;
	 case 2:
	   bit = itr->getAlgoDecisionFinal(algoBitFirstBxInTrain_);
	   break;
	 }
	 if (bit) {
	   bxShiftFirst = bx;
	 }
       }
       // last bunch in train
       if(algoBitLastBxInTrain_ != -1) {
	 bool bit = false;
	 switch (useAlgoDecision_) {
	 case 0:
	   bit = itr->getAlgoDecisionInitial(algoBitLastBxInTrain_);
	   break;
	 case 1:
	   bit = itr->getAlgoDecisionInterm(algoBitLastBxInTrain_);
	   break;
	 case 2:
	   bit = itr->getAlgoDecisionFinal(algoBitLastBxInTrain_);
	   break;
	 }
	 if (bit) {
	   ;//bxShiftLast = bx;
	 }
       }
       // isolated bunch
       if (algoBitIsoBx_ != -1) {
	 bool bit = false;
	 switch (useAlgoDecision_) {
	 case 0:
	   bit = itr->getAlgoDecisionInitial(algoBitIsoBx_);
	   break;
	 case 1:
	   bit = itr->getAlgoDecisionInterm(algoBitIsoBx_);
	   break;
	 case 2:
	   bit = itr->getAlgoDecisionFinal(algoBitIsoBx_);
	   break;
	 }
	 if (bit) {
	   ;//bxShiftIso = bx;
	 }
       }
     }
   }
   
   //std::cout<<" bxShiftFirst = " << bxShiftFirst<< " "<<bxShiftIso<< " "<<bxShiftLast<<std::endl;
   
   // the following shifting is needed for following reason: 
   // we want to use only those events which comes as a result of the begining of the bunch train, each bunch train can have crossings multiple times. 
   // if the egamma triggering happended one bx before the begining of bunch train i.e. egamma trigger pre-fired then we need to correct for this effect. 
   // The data is written only once, for all the five bunch crossings. if the egamma trigger was prefired then (-1 bx) then everything needs to be translated. 
   
   int nonisocounterm2    = 0 ;
   int nonisocounterm1    = 0 ;
   int nonisocounterzero  = 0 ;
   int nonisocounterp1    = 0 ;
   int nonisocounterp2    = 0 ;

   int isocounterm2    = 0 ;
   int isocounterm1    = 0 ;
   int isocounterzero  = 0 ;
   int isocounterp1    = 0 ;
   int isocounterp2    = 0 ;
   
   for (int itBX = std::max(EGammaBxCollection->getFirstBX(), EGammaBxCollection->getFirstBX() + bxShiftFirst); itBX <= std::min(EGammaBxCollection->getLastBX(), EGammaBxCollection->getLastBX() + bxShiftFirst); ++itBX) {
    //  std::cout<<"inside itBx" <<std::endl;
     

     //int index = itBX - bxShiftFirst - uGtAlgs->getFirstBX();
     for (l1t::EGammaBxCollection::const_iterator egamma = EGammaBxCollection->begin(itBX); egamma != EGammaBxCollection->end(itBX); ++egamma) {
      //  std::cout<<"inside egamma" <<std::endl;
       
       
       for (size_t i = 0; i < egammaPtCuts_.size(); ++i) {
	//  std::cout<<" for pt cut "<<egammaPtCuts_[i]<<"  "<<egamma->pt() << std::endl;
	 if (egamma->pt() >= egammaPtCuts_.at(i)) {
	   //if (index >= 0 and index < (int)egamma_eta_phi_firstbunch.size()) {
	   //denominator_egamma_firstbunch.at(i)->Fill(egamma->eta(), egamma->phi());
	   //egamma_eta_phi_firstbunch.at(i).at(index)->Fill(egamma->eta(), egamma->phi());
	   //}
	   
	   int bxNumberActual = itBX - bxShiftFirst;
	  	   
	   
	  //  std::cout<<" all candidates egamma->pt, egamma->hwPt, egamma->energy, egamma->hwEta, egamma->hwPhi ="<<egamma->pt()<<" "<<egamma->hwPt()<<"  "<<egamma->energy()<<"  "<<egamma->hwEta()<<"  "<<egamma->hwPhi()<<std::endl;
	   
	   if ((bool)egamma->hwIso()) {
	    //  std::cout<<" isolated bx, eta, counter "<<itBX - bxShiftFirst<<"  "<< egamma->hwEta()<<"  "<<isocounterp2<<std::endl;
	     
      //  if(savePreFireInfo_)
        // ibx_vs_ieta_Iso->Fill(itBX - bxShiftFirst, egamma->hwEta() );

	     // see the description of variables at the twiki 
	     //https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideL1TCaloFormats 
	     
	     if (bxNumberActual == -2){ 
	       L1preIsoIetam2[isocounterm2] = egamma->hwEta();
	       L1preIsoIphim2[isocounterm2] = egamma->hwPhi();
	       L1preIsoPtm2[isocounterm2] = egamma->pt();
	       L1preIsoEnergym2[isocounterm2] = egamma->energy();
	       isocounterm2++;
	     }
	     if (bxNumberActual == -1){ 
	       L1preIsoIetam1[isocounterm1] = egamma->hwEta();
	       L1preIsoIphim1[isocounterm1] = egamma->hwPhi();
	       L1preIsoPtm1[isocounterm1]   = egamma->pt();
	       L1preIsoEnergym1[isocounterm1] = egamma->energy();
	       isocounterm1++;
	     }
	     if (bxNumberActual ==  0){ 
	       L1preIsoIetazero[isocounterzero] = egamma->hwEta();
	       L1preIsoIphizero[isocounterzero] = egamma->hwPhi();
	       L1preIsoPtzero[isocounterzero]   = egamma->pt();
	       L1preIsoEnergyzero[isocounterzero] = egamma->energy();
	       isocounterzero++;
	     }
	     if (bxNumberActual ==  1){ 
	       L1preIsoIetap1[isocounterp1] = egamma->hwEta();
	       L1preIsoIphip1[isocounterp1] = egamma->hwPhi();
	       L1preIsoEnergyp1[isocounterp1] = egamma->energy();
	       isocounterp1++;
	     }
	     if (bxNumberActual ==  2){
	       L1preIsoIetap2[isocounterp2] = egamma->hwEta();
	       L1preIsoIphip2[isocounterp2] = egamma->hwPhi();
	       L1preIsoPtp2[isocounterp2]   = egamma->pt();
	       L1preIsoEnergyp2[isocounterp2] = egamma->energy();
	       isocounterp2++;
	     }
	   }// end of  if ((bool)egamma->hwIso()) {
	 

	   // ----------------------------------------------------------
	   // -------- non-isolated branches starts from here. ---------
	   // ----------------------------------------------------------
	  //  ibx_vs_ieta_NonIso->Fill(itBX - bxShiftFirst, egamma->hwEta());

	  //  std::cout<<" eta and hweta "<<egamma->hwEta() <<" "<<egamma->eta() <<std::endl;
	   
	   // non-isolated 
	   if (bxNumberActual == -2){ 
	     L1preNonisoIetam2[nonisocounterm2] = egamma->hwEta();
     	     L1preNonisoIphim2[nonisocounterm2] = egamma->hwPhi();
	     L1preNonisoPtm2[nonisocounterm2]   = egamma->pt();
	     L1preNonisoEnergym2[nonisocounterm2] = egamma->energy();
	     nonisocounterm2++;
	   }
	   if (bxNumberActual == -1){ 
	     L1preNonisoIetam1[nonisocounterm1] = egamma->hwEta();
	     L1preNonisoIphim1[nonisocounterm1] = egamma->hwPhi();
	     L1preNonisoPtm1[nonisocounterm1]   = egamma->pt();
	     L1preNonisoEnergym1[nonisocounterm1] = egamma->energy();
	     nonisocounterm1++;
	   }
	   if (bxNumberActual ==  0){ 
	     L1preNonisoIetazero[nonisocounterzero] = egamma->hwEta();
	     L1preNonisoIphizero[nonisocounterzero] = egamma->hwPhi();
	     L1preNonisoPtzero[nonisocounterzero]   = egamma->pt();
	     L1preNonisoEnergyzero[nonisocounterzero] = egamma->energy();
	       nonisocounterzero++;
	   }
	   if (bxNumberActual ==  1){ 
	     L1preNonisoIetap1[nonisocounterp1] = egamma->hwEta();
	     L1preNonisoIphip1[nonisocounterp1] = egamma->hwPhi();
	     L1preNonisoPtp1[nonisocounterp1]   = egamma->pt();
	     L1preNonisoEnergyp1[nonisocounterp1] = egamma->energy();
	     nonisocounterp1++;
	   }
	   if (bxNumberActual ==  2){
	     L1preNonisoIetap2[nonisocounterp2] = egamma->hwEta();
	     L1preNonisoIphip2[nonisocounterp2] = egamma->hwPhi();
	     L1preNonisoPtp2[nonisocounterp2]   = egamma->pt();
	     L1preNonisoEnergyp2[nonisocounterp2] = egamma->energy();
	     nonisocounterp2++;
	   }

	   // fill all counters 
	   
	   v_nonisocounterm2  = nonisocounterm2    ;    
	   v_nonisocounterm1  = nonisocounterm1    ; 
	   v_nonisocounterzero  = nonisocounterzero; 
	   v_nonisocounterp1  = nonisocounterp1    ; 
	   v_nonisocounterp2  = nonisocounterp2    ; 

	   v_isocounterm2     = isocounterm2       ;
	   v_isocounterm1     = isocounterm1       ;
	   v_isocounterzero   = isocounterzero     ;
	   v_isocounterp1     = isocounterp1       ;
	   v_isocounterp2     = isocounterp2       ;

	   
	   	   
	 }
       }
     }
   }
   
   
   // for the last bunch crossing 
   /*


   for (int itBX = std::max(EGammaBxCollection->getFirstBX(), EGammaBxCollection->getFirstBX() + bxShiftLast); itBX <= std::min(EGammaBxCollection->getLastBX(), EGammaBxCollection->getLastBX() + bxShiftLast); ++itBX) {
     std::cout<<"inside itBx" <<std::endl;
     auto correctedBx = itBX - bxShiftLast;
     for (l1t::EGammaBxCollection::const_iterator egamma = EGammaBxCollection->begin(itBX); egamma != EGammaBxCollection->end(itBX); ++egamma) {
       std::cout<<"inside egamma" <<std::endl;
       for (size_t i = 0; i < egammaPtCuts_.size(); ++i) {
	 if (egamma->pt() >= egammaPtCuts_.at(i)) {
	   //if (correctedBx >= 0 and correctedBx < (int)egamma_eta_phi_lastbunch.size()) {
	     //denominator_egamma_lastbunch.at(i)->Fill(egamma->eta(), egamma->phi());
	     //egamma_eta_phi_lastbunch.at(i).at(correctedBx)->Fill(egamma->eta(), egamma->phi());
	   //}
	   if ((bool)egamma->hwIso()) {
	     std::cout<<" isolated "<<correctedBx<<"  "<< egamma->hwEta()<<std::endl;
	     //egamma_iso_bx_ieta_lastbunch.at(i)->Fill(correctedBx, egamma->hwEta());
	   }
	   //egamma_noniso_bx_ieta_lastbunch.at(i)->Fill(correctedBx, egamma->hwEta());
	   std::cout<<" non-isolated "<<correctedBx<<"  "<< egamma->hwEta()<<std::endl;
	   
	 }
       }
     }
   }

   */
   
   // ------------------------------------------**********----------***-------------------------------------------------------------------------
   // -----------------------------------------------*--------------*--***----------------------------------------------------------------------
   // -----------------------------------------------*--------------*----**---------------------------------------------------------------------
   // -----------------------------------------------*--------------*--***----------------------------------------------------------------------
   // -----------------------------------------------*--------------***-------------------------------------------------------------------------
   // -----------------------------------------------*--------------*---------------------------------------------------------------------------
   // -----------------------------------------------*--------------*---------------------------------------------------------------------------

   // ---------------------------------
   // event information 
   // ---------------------------------
   runNb = e.id().run() ;
   evtNb = e.id().event() ;
   bxNb = e.bunchCrossing() ;
   orbitNb = e.orbitNumber() ;
   lumiBlock = e.luminosityBlock();
   
   float startTime_ = 1461466500; //                                                                                                                                                                               
   unsigned int  timeStampLow = ( 0xFFFFFFFF & e.time().value() );
   unsigned int  timeStampHigh = ( e.time().value() >> 32 );

   double rawEventTime = ( double)(timeStampHigh)+((double )(timeStampLow)/1000000.);
   double eventTime = rawEventTime - startTime_; //Notice the subtraction of the "starttime"
   
   timeStamp =  eventTime;

   // -------------------------------
   //  TT information 
   // -------------------------------
   
   edm::Handle<EcalTrigPrimDigiCollection> tp; 
   e.getByToken(tpCollection_,tp);
   //std::cout<<"TP collection size="<<tp.product()->size()<<std::endl ;
   
   map<EcalTrigTowerDetId, towerEner>::iterator itTT ;
   map<EcalTrigTowerDetId, towerEner> mapTower ;
   
   edm::Handle<EEDigiCollection>  EEdigis;
  //  std::cout << "Getting EEdigis..." << std::endl;
   e.getByToken(EEdigistoken_,EEdigis);
  //  std::cout << "Got EEdigis" << std::endl;
   if(not e.getByToken(EEdigistoken_,EEdigis)){
     std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: EEdigistoken_ "<<std::endl;
     exit(0);
   }

  //  int j=0;
  //  int countNadc=0;
   c.get<IdealGeometryRecord>().get(eTTmap_);
   
  //  // EE only 
  //  for ( EEDigiCollection::const_iterator hitItr = EEdigis->begin(); hitItr != EEdigis->end(); ++hitItr ) {
  //    EEDataFrame df(*hitItr);
  //    const EEDetId & id = df.id();
  //    const EcalTrigTowerDetId towid = (*eTTmap_).towerOf(id);
     
  //   //  const EcalTriggerElectronicsId elId = theMapping_->getTriggerElectronicsId(df.id());
  //   //  uint32_t stripid = elId.rawId() & 0xfffffff8;  // from Pascal
  //    //std::cout<<" strip id : "<<stripid<<std::endl;
     
  //    for(int i=0; i<10;++i){
  //      //std::cout<<" tower (eta, phi): ("<<towid.ieta() << ", "<<towid.iphi()<<")"
  //      //     <<" xtal (ix, iy): ("<<id.ix() <<", "<<id.iy()<<")"
  //      //     <<" ADC for EEDataFrame: "<<j << "  sample number "<<i<<"  "<<df.sample(i).adc()<<std::endl;
     
  //    // Will all be set to EE values here 

  //    // these, tower_eta for example, is set to size 4092, but elements being filled for each digi per rec hit 
  //    tower_eta[countNadc] = towid.ieta();
  //    tower_phi[countNadc] = towid.iphi();
  //    xtal_ix[countNadc] = id.ix();
  //    xtal_iy[countNadc] = id.iy();
     
  //    index_df[countNadc] = j;
  //    index_ts[countNadc] = i;
  //    count_ADC[countNadc] = df.sample(i).adc();
  //    gain_id[countNadc]    = df.sample(i).gainId();
       
  //    countNadc++;
     
  //    }
  //    j++;
     
  //  }
   
   // //  ndataframe = j;
   //  nADC       = countNadc;
   
   
   // pulseshape setup ends here 

   for (unsigned int i=0;i<tp.product()->size();i++) {
     EcalTriggerPrimitiveDigi d = (*(tp.product()))[i];
     const EcalTrigTowerDetId TPtowid= d.id();
     towerEner tE ;

     // SKIP EE
     if(TPtowid.ieta() > 17 || TPtowid.ieta() < -17) continue; 
     
     // suggested by David 
     // follow from https://github.com/cms-ecal-L1TriggerTeam/CMS-ECAL_TPGAnalysis/blob/master/TriggerAnalysis/plugins/EcalTPGAnalyzer.cc#L845
     tE.TCCid_= theMapping_->TCCid(TPtowid);                                                                                                                                                           
     tE.TowerInTCC_ = theMapping_->iTT(TPtowid);                                                                                                                                                       
     //const EcalTriggerElectronicsId elId = theMapping_->getTriggerElectronicsId(id) ;                                                                                                            
     //tE.strip_ = 0;//elId.pseudoStripId() ;                                                                                                                                                            
     
     tE.iphi_ = TPtowid.iphi() ;
     tE.ieta_ = TPtowid.ieta() ;
     tE.ttFlag_ = d[0].ttFlag();
     tE.tpgADC_ = (d[0].raw()&0xfff) ;
     tE.twrADC = (d[0].raw()&0xff) ;
     tE.sFGVB = (d[0].sFGVB());
     //if ((d[0].raw()&0xfff)>0 ) {std::cout<<" EcalTrigTowerDetId :: filling "<<TPtowid<<" twradc: "<<(d[0].raw()&0xff)<<std::endl;}
     mapTower[TPtowid] = tE ;
   }

   // -------------------------------
   //  emulator information 
   // -------------------------------
   //  std::cout << "Getting tpEmul..." << std::endl;
   edm::Handle<EcalTrigPrimDigiCollection> tpEmul ;
   e.getByToken(tpEmulatorCollection_, tpEmul);
   //  std::cout << "Got tpEmul" << std::endl;
   
   for (unsigned int i = 0; i < tpEmul.product()->size(); i++) {
     EcalTriggerPrimitiveDigi d = (*(tpEmul.product()))[i];
     const EcalTrigTowerDetId TPtowid= d.id();

     // SKIP EE
     if(TPtowid.ieta() > 17 || TPtowid.ieta() < -17) continue;    

     itTT = mapTower.find(TPtowid) ;
     if (itTT != mapTower.end())
       for (int j=0 ; j<5 ; j++) {
        (itTT->second).tpgEmul_[j] = (d[j].raw()&0xfff) ;
        (itTT->second).tpgEmulFlag_[j] = d[j].ttFlag();
        (itTT->second).tpgEmulsFGVB_[j] = d[j].sFGVB();
       }
   }

   // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // ----------------REC HITS -------------------------------------------------------------------------------------------------------------------------------------------------------
   // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

   ESHandle<CaloGeometry> theGeometry;
   ESHandle<CaloSubdetectorGeometry> theEndcapGeometry_handle, theBarrelGeometry_handle;
    
   c.get<CaloGeometryRecord>().get( theGeometry );
   c.get<EcalEndcapGeometryRecord>().get("EcalEndcap",theEndcapGeometry_handle);
   c.get<EcalBarrelGeometryRecord>().get("EcalBarrel",theBarrelGeometry_handle);
    
   c.get<IdealGeometryRecord>().get(eTTmap_);
   theEndcapGeometry_ = &(*theEndcapGeometry_handle);
   theBarrelGeometry_ = &(*theBarrelGeometry_handle);

   edm::ESHandle<EcalSeverityLevelAlgo> sevlv1;
   c.get<EcalSeverityLevelAlgoRcd>().get(sevlv1);

   // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideEcalRecoLocalReco#Mapping_into_severity_levels

   // EB rec hits only 
   edm::Handle<EcalRecHitCollection> rechitsEB; 
   e.getByToken(EcalRecHitCollectionEB1_,rechitsEB); 
   float maxRecHitEnergy = 0. ;
   int irechit=0;
   if (rechitsEB.product()->size()!=0) {
     for ( EcalRecHitCollection::const_iterator rechitItr = rechitsEB->begin(); rechitItr != rechitsEB->end(); ++rechitItr ) {   
       EBDetId id = rechitItr->id(); 
       const EcalTrigTowerDetId towid = id.tower();
       irechit++;
       itTT = mapTower.find(towid) ;
       if (itTT != mapTower.end()) {
      // double theta = theBarrelGeometry_->getGeometry(id)->getPosition().theta() ;
      // (itTT->second).eRec_ += rechitItr->energy()*sin(theta) ;
      int sevlvl_tmp =  (sevlv1->severityLevel(id, *rechitsEB)) ;
      //  if ( rechitItr->energy() > maxRecHitEnergy && ((itTT->second).twrADC>32) ){
      if ( rechitItr->energy() > maxRecHitEnergy ){
        maxRecHitEnergy = rechitItr->energy();
        (itTT->second).sevlv_ = sevlvl_tmp; 	
        (itTT->second).time_ = rechitItr->time();
      }
      (itTT->second).crystNb_++;
       }
     }
   }

   // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
   // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
   // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
   // -----------write tree----------------------------------------------------------------------------------------------------------------------------------------------------------- 
   // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
   // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
   // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 

  //  double recHitEnergy_ = -999; 
  //  int iRecHit = 0; 
  //  if (rechitsEB.product()->size()!=0) {

  //    // For each EB Rec Hit
  //    for ( EcalRecHitCollection::const_iterator rechitItr = rechitsEB->begin(); rechitItr != rechitsEB->end(); ++rechitItr ) {   
  //      recHitEnergy_ = rechitItr->energy(); 
  //      recHitEnergy[iRecHit] = recHitEnergy_;
  //      iRecHit ++; 
  //    }
  //  }

  //  std::cout << "About to start writing tree" << std::endl; 

   int towerNb = 0 ;
   for (itTT = mapTower.begin() ; itTT != mapTower.end() ; ++itTT) {

    // Only save non-zero TPs 
    if((itTT->second).twrADC == 0){
      continue; 
    }

     //-- Save entries per tower 
     ieta[towerNb] = (itTT->second).ieta_ ;
     iphi[towerNb] = (itTT->second).iphi_ ;
    //  nbOfXtals[towerNb] = (itTT->second).nbXtal_ ;
    //  rawTPData[towerNb] = (itTT->second).tpgADC_ ;
    //  rawTPEmul1[towerNb] = (itTT->second).tpgEmul_[0] ;
    //  rawTPEmul2[towerNb] = (itTT->second).tpgEmul_[1] ;
     rawTPEmul3[towerNb] = (itTT->second).tpgEmul_[2] ;
    //  rawTPEmul4[towerNb] = (itTT->second).tpgEmul_[3] ;
    //  rawTPEmul5[towerNb] = (itTT->second).tpgEmul_[4] ;
     
     // Et values for emulated TP with index 2 (BX = 0?)
     twrEmul3ADC[towerNb] = ((itTT->second).tpgEmul_[2]&0xff) ;
     
    //  rawTPEmulttFlag1[towerNb] = (itTT->second).tpgEmulFlag_[0] ;
    //  rawTPEmulttFlag2[towerNb] = (itTT->second).tpgEmulFlag_[1] ;
     rawTPEmulttFlag3[towerNb] = (itTT->second).tpgEmulFlag_[2] ;
    //  rawTPEmulttFlag4[towerNb] = (itTT->second).tpgEmulFlag_[3] ;
    //  rawTPEmulttFlag5[towerNb] = (itTT->second).tpgEmulFlag_[4] ;
    //  rawTPEmulsFGVB1[towerNb] = (itTT->second).tpgEmulsFGVB_[0] ;
    //  rawTPEmulsFGVB2[towerNb] = (itTT->second).tpgEmulsFGVB_[1] ;
     rawTPEmulsFGVB3[towerNb] = (itTT->second).tpgEmulsFGVB_[2] ;
    //  rawTPEmulsFGVB4[towerNb] = (itTT->second).tpgEmulsFGVB_[3] ;
    //  rawTPEmulsFGVB5[towerNb] = (itTT->second).tpgEmulsFGVB_[4] ;

     crystNb[towerNb] = (itTT->second).crystNb_ ;

    //  for(int ixtal = 0; ixtal < 25; ixtal++){
    //    eRec[towerNb][ixtal] = (itTT->second).eRec_ ;
    //  }

    //  eRec[towerNb] = (itTT->second).eRec_ ;
     sevlv[towerNb] = (itTT->second).sevlv_ ; 
     time[towerNb] = (itTT->second).time_ ; 
     ttFlag[towerNb] = (itTT->second).ttFlag_ ;
     spike[towerNb] = (itTT->second).spike_ ;
     twrADC[towerNb] =  (itTT->second).twrADC;
     sFGVB[towerNb] =  (itTT->second).sFGVB;
    
     TCCid[towerNb] = (itTT->second).TCCid_;
     TowerInTCC[towerNb] = (itTT->second).TowerInTCC_;

     towerNb++ ;
     
   }

   nbOfTowers = towerNb ;
   
   ETTAnalyzerTree->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void ETTAnalyzer::beginJob()
{

}

void ETTAnalyzer::beginRun(const edm::Run& r, const edm::EventSetup& c) {
  
  // this should be moved to begin run 
  // but where is begin run 
  // begin job does not have the event setup infp 
  // Get the trigger menu information
  gtUtil_->retrieveL1Setup(c);
  
  // Get the algo bits needed for the timing histograms
  if (!gtUtil_->getAlgBitFromName(algoNameFirstBxInTrain_, algoBitFirstBxInTrain_)) {
    edm::LogWarning("L1TObjectsTiming") << "Algo \"" << algoNameFirstBxInTrain_ << "\" not found in the trigger menu " << gtUtil_->gtTriggerMenuName() << ". Could not retrieve algo bit number.";
  }
  
  if (!gtUtil_->getAlgBitFromName(algoNameLastBxInTrain_, algoBitLastBxInTrain_)) {
    edm::LogWarning("L1TObjectsTiming") << "Algo \"" << algoNameLastBxInTrain_ << "\" not found in the trigger menu " << gtUtil_->gtTriggerMenuName() << ". Could not retrieve algo bit number.";
  }
  
  if (!gtUtil_->getAlgBitFromName(algoNameIsoBx_, algoBitIsoBx_)) {
    edm::LogWarning("L1TObjectsTiming") << "Algo \"" << algoNameIsoBx_ << "\" not found in the trigger menu " << gtUtil_->gtTriggerMenuName() << ". Could not retrieve algo bit number.";
  }
  
}

// ------------ method called once each job just after ending the event loop  ------------
void ETTAnalyzer::endJob()
{
  ETTAnalyzerTree->Write();
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void ETTAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  // The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  desc.addUntracked<std::string>("useAlgoDecision", "initial")->setComment("Which algo decision should be checked [initial, intermediate, final].");
  desc.addUntracked<std::vector<double>>("egammaPtCuts", {20., 10., 30.})->setComment("List if min egamman pT vaules");
  descriptions.addDefault(desc);
  
}

// Define this as a plug-in
DEFINE_FWK_MODULE(ETTAnalyzer);
