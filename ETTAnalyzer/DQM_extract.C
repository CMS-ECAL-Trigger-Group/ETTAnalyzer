void DQM_extrac(){
  
  TFile f0("/eos/user/t/tdesrous/scans/delay-6/ETTAnalyzer_output-6ns.root","READ");



  

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m6=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m6=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m6=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin30p0");

  
  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m6=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m6=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m6=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin30p0");
  
  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m6=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m6=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m6=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin30p0");


  
  TFile f1("/eos/user/t/tdesrous/scans/delay-5/ETTAnalyzer_output-5ns.root","READ");




  

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m5=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m5=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m5=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin30p0");

  
  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m5=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m5=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m5=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin30p0");
  
  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m5=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m5=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m5=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin30p0");


  
  TFile f2("/eos/user/t/tdesrous/scans/delay-4/ETTAnalyzer_output-4ns.root","READ");
  

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m4=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m4=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m4=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin30p0");

  
  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m4=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m4=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m4=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin30p0");
  
  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m4=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m4=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m4=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin30p0");
  

  TFile f3("/eos/user/t/tdesrous/scans/delay-3/ETTAnalyzer_output-3ns.root","READ");

  
  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m3=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m3=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m3=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin30p0");

  
  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m3=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m3=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m3=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin30p0");
  
  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m3=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m3=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m3=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin30p0");

  
 TFile f4("/eos/user/t/tdesrous/scans/delay-2/ETTAnalyzer_output-2ns.root","READ");

  
  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m2=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m2=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m2=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin30p0");

  
  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m2=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m2=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m2=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin30p0");
  
  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m2=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m2=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m2=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin30p0");

   TFile f5("/eos/user/t/tdesrous/scans/delay-1/ETTAnalyzer_output-1ns.root","READ");

  
  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m1=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m1=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m1=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin30p0");

  
  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m1=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m1=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m1=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin30p0");
  
  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m1=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m1=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m1=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin30p0");

 TFile f6("/eos/user/t/tdesrous/scans/delay0/ETTAnalyzer_output0ns.root","READ");

  
  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_0=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_0=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_0=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin30p0");

  
  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_0=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_0=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_0=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin30p0");
  
  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_0=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_0=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_0=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin30p0");

  


 TFile f7("/eos/user/t/tdesrous/scans/delay1/ETTAnalyzer_output1ns.root","READ");
  
  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p1=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p1=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p1=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin30p0");

  
  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p1=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p1=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p1=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin30p0");
  
  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p1=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p1=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p1=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin30p0");
  


 TFile f8("/eos/user/t/tdesrous/scans/delay2/ETTAnalyzer_output2ns.root","READ");
  
   TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p2=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p2=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p2=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin30p0");

  
  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p2=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p2=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p2=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin30p0");
  
  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p2=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p2=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p2=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin30p0");
  

   TFile f9("/eos/user/t/tdesrous/scans/delay3/ETTAnalyzer_output3ns.root","READ");
  
  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p3=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p3=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p3=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin30p0");

  
  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p3=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p3=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p3=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin30p0");
  
  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p3=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p3=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p3=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin30p0");


  

   TFile f10("/eos/user/t/tdesrous/scans/delay4/ETTAnalyzer_output4ns.root","READ");
  
   TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p4=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p4=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p4=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin30p0");

  
  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p4=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p4=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p4=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin30p0");
  
  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p4=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p4=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p4=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin30p0");
  

   TFile f11("/eos/user/t/tdesrous/scans/delay5/ETTAnalyzer_output5ns.root","READ");
  
   TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p5=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p5=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p5=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin30p0");

  
  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p5=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p5=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p5=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin30p0");
  
  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p5=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p5=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p5=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin30p0");
  
 TFile f12("/eos/user/t/tdesrous/scans/delay6/ETTAnalyzer_output6ns.root","READ");
  
   TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p6=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p6=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p6=(TH2F*)f0.Get("tuplizer/first_ibx_vs_ieta_NonIso_ptmin30p0");

  
  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p6=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p6=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p6=(TH2F*)f0.Get("tuplizer/last_ibx_vs_ieta_NonIso_ptmin30p0");
  
  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p6=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin10p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p6=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin20p0");

  TH2F* egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p6=(TH2F*)f0.Get("tuplizer/iso_ibx_vs_ieta_NonIso_ptmin30p0");
  




  
  TFile fout("l1tHistograms_Apr2023.root","RECREATE");

  fout.cd();


  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m6->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m6");
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m6->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m6");
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m6->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m6");

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m6->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m6");
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m6->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m6");
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m6->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m6");

  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m6->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m6");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m6->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m6");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m6->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m6");


  
  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m5->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m5");
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m5->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m5");
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m5->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m5");

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m5->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m5");
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m5->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m5");
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m5->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m5");

  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m5->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m5");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m5->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m5");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m5->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m5");


  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m4->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m4");
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m4->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m4");
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m4->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m4");

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m4->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m4");
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m4->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m4");
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m4->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m4");

  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m4->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m4");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m4->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m4");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m4->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m4");


  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m3->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m3");
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m3->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m3");
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m3->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m3");

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m3->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m3");
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m3->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m3");
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m3->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m3");

  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m3->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m3");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m3->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m3");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m3->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m3");

  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m2->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m2");
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m2->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m2");
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m2->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m2");

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m2->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m2");
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m2->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m2");
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m2->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m2");

  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m2->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m2");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m2->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m2");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m2->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m2");


  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m1->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m1");
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m1->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m1");
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m1->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m1");

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m1->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m1");
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m1->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m1");
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m1->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m1");

  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m1->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m1");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m1->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m1");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m1->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m1");


  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_0->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_0");
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_0->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_0");
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_0->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_0");

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_0->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_0");
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_0->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_0");
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_0->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_0");

  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_0->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_0");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_0->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_0");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_0->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_0");



  
  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p1->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p1");
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p1->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p1");
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p1->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p1");

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p1->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p1");
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p1->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p1");
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p1->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p1");

  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p1->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p1");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p1->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p1");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p1->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p1");

  
  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p2->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p2");
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p2->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p2");
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p2->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p2");

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p2->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p2");
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p2->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p2");
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p2->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p2");

  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p2->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p2");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p2->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p2");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p2->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p2");


  
   egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p3->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p3");
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p3->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p3");
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p3->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p3");

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p3->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p3");
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p3->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p3");
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p3->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p3");

  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p3->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p3");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p3->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p3");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p3->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p3");

  
  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p4->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p4");
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p4->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p4");
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p4->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p4");

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p4->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p4");
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p4->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p4");
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p4->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p4");

  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p4->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p4");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p4->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p4");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p4->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p4");

  
  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p5->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p5");
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p5->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p5");
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p5->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p5");

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p5->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p5");
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p5->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p5");
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p5->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p5");

  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p5->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p5");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p5->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p5");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p5->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p5");

  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p6->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p6");
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p6->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p6");
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p6->SetName("egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p6");

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p6->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p6");
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p6->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p6");
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p6->SetName("egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p6");

  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p6->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p6");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p6->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p6");
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p6->SetName("egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p6");





  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m6->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m6);
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m6->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m6);
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m6->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m6);

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m6->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m6);
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m6->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m6);
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m6->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m6);


  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m5->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m5);
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m5->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m5);
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m5->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m5);

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m5->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m5);
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m5->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m5);
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m5->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m5);


  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m4->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m4);
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m4->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m4);
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m4->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m4);

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m4->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m4);
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m4->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m4);
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m4->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m4);

  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m3->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m3);
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m3->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m3);
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m3->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m3);

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m3->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m3);
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m3->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m3);
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m3->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m3);

  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m2->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m2);
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m2->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m2);
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m2->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m2);

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m2->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m2);
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m2->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m2);
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m2->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m2);

  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m1->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m1);
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m1->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m1);
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m1->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m1);

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m1->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m1);
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m1->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m1);
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m1->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m1);
 

  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_0->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_0);
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_0->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_0);
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_0->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_0);

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_0->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_0);
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_0->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_0);
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_0->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_0);

  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p1->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p1);
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p1->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p1);
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p1->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p1);

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p1->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p1);
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p1->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p1);
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p1->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p1);
 

  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p2->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p2);
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p2->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p2);
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p2->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p2);

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p2->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p2);
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p2->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p2);
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p2->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p2);

  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p3->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p3);
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p3->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p3);
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p3->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p3);

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p3->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p3);
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p3->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p3);
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p3->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p3);

  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p4->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p4);
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p4->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p4);
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p4->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p4);

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p4->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p4);
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p4->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p4);
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p4->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p4);

  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p5->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p5);
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p5->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p5);
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p5->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p5);

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p5->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p5);
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p5->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p5);
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p5->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p5);

  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p6->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p6);
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p6->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p6);
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p6->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p6);

  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p6->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p6);
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p6->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p6);
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p6->Add(egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p6);


  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m6->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m6->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m6->Write();
  
  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m6->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m6->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m6->Write();
  
  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m6->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m6->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m6->Write();


  
  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m5->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m5->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m5->Write();
  
  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m5->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m5->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m5->Write();
  
  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m5->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m5->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m5->Write();


  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m4->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m4->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m4->Write();
  
  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m4->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m4->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m4->Write();
  
  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m4->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m4->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m4->Write();


  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m3->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m3->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m3->Write();
  
  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m3->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m3->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m3->Write();
  
  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m3->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m3->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m3->Write();

  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m2->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m2->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m2->Write();
  
  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m2->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m2->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m2->Write();
  
  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m2->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m2->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m2->Write();

  
  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_m1->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_m1->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_m1->Write();
  
  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_m1->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_m1->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_m1->Write();
  
  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_m1->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_m1->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_m1->Write();


  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_0->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_0->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_0->Write();
  
  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_0->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_0->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_0->Write();
  
  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_0->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_0->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_0->Write();

 


  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p1->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p1->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p1->Write();
  
  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p1->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p1->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p1->Write();
  
  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p1->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p1->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p1->Write();
  

  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p2->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p2->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p2->Write();
  
  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p2->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p2->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p2->Write();
  
  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p2->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p2->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p2->Write();
  
  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p3->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p3->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p3->Write();
  
  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p3->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p3->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p3->Write();
  
  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p3->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p3->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p3->Write();
  
  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p4->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p4->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p4->Write();
  
  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p4->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p4->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p4->Write();
  
  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p4->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p4->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p4->Write();
  
  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p5->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p5->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p5->Write();
  
  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p5->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p5->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p5->Write();
  
  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p5->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p5->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p5->Write();
  
  egamma_noniso_bx_ieta_firstbunch_ptmin10p0_delay_p6->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin20p0_delay_p6->Write();
  egamma_noniso_bx_ieta_firstbunch_ptmin30p0_delay_p6->Write();
  
  egamma_noniso_bx_ieta_lastbunch_ptmin10p0_delay_p6->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin20p0_delay_p6->Write();
  egamma_noniso_bx_ieta_lastbunch_ptmin30p0_delay_p6->Write();
  
  egamma_noniso_bx_ieta_isolatedbunch_ptmin10p0_delay_p6->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin20p0_delay_p6->Write();
  egamma_noniso_bx_ieta_isolatedbunch_ptmin30p0_delay_p6->Write();
  
  

  
  fout.Close();
  
  

}

int main(){DQM_extrac();}