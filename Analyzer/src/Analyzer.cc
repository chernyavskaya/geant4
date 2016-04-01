#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#define DOSHAPING 0

void Analyzer::addHisto(TString name, int nBins, float XLow, float XUp, TString XLabel){

  TH1F* histo = new TH1F(name,name,nBins,XLow,XUp);
  histo->GetXaxis()->SetTitle(XLabel);
  histos_[name]=histo;
}

void Analyzer::addHisto2D(TString name, int nBinsX, float XLow, float XUp,TString XLabel,int nBinsY, float YLow, float YUp,TString YLabel){
  TH2F* histo = new TH2F(name,name,nBinsX,XLow,XUp,nBinsY,YLow,YUp);
  histo->GetXaxis()->SetTitle(XLabel);
  histo->GetYaxis()->SetTitle(YLabel);
  histos2D_[name]=histo;
}



void Analyzer::drawHistos(){


  TCanvas c1;
   for(std::map<TString,TH1F*>::const_iterator it = histos_.begin();it!=histos_.end(); it++){
     it->second->Draw();
     std::cout<<outDir_+it->first+".png"<<std::endl;
     c1.SaveAs(outDir_+it->first+".png");
     c1.SaveAs(outDir_+it->first+".pdf");
     it->second->Write();
     c1.Clear();
   }

   for(std::map<TString,TH2F*>::const_iterator it2D = histos2D_.begin();it2D!=histos2D_.end(); it2D++){
     it2D->second->Draw("colz");
     TProfile* prof =  it2D->second->ProfileX("prof");
     prof->Draw("same");
     //     it2D->second->Draw("profXsame");
     std::cout<<outDir_+it2D->first+".png"<<std::endl;
     c1.SaveAs(outDir_+it2D->first+".png");
     c1.SaveAs(outDir_+it2D->first+".pdf");
     it2D->second->Write();
     c1.Clear();
   }


}

void Analyzer::createHistos(){
  if(setup_=="SingleFibre")  addHisto("timeArrival_avg",500,5,10,"time [ns]");
  else addHisto("timeArrival_avg",500,10,20,"time [ns]");
  addHisto("ZTimeArrival_avg",420,0,420,"Z [mm]");
  addHisto("processTimeArrival_avg",3,0.5,3.5,"process");
 
  addHisto("nPhotons",200,0,1000,"WLS Photons");

  if(setup_=="SingleFibre")   addHisto("timeArrival_avg_wls",500,5,10,"time [ns]");
  else   addHisto("timeArrival_avg_wls",500,10,20,"time [ns]");
  addHisto("ZTimeArrival_avg_wls",420,0,420,"Z [mm]");
  
  if(setup_=="SingleFibre")   addHisto("timeArrival_avg_scint",500,5,10,"time [ns]");
  else   addHisto("timeArrival_avg_scint",500,10,20,"time [ns]");
  addHisto("ZTimeArrival_avg_scint",420,0,420,"Z [mm]");
  
  if(setup_=="SingleFibre")   addHisto("timeArrival_avg_cher",500,5,10,"time [ns]");
  else   addHisto("timeArrival_avg_cher",500,10,20,"time [ns]");
  addHisto("ZTimeArrival_avg_cher",420,0,420,"Z [mm]");

  if(setup_=="SingleFibre")   addHisto("timeArrival",500,5,10,"time [ns]");
  else   addHisto("timeArrival",500,10,200,"time [ns]");
  addHisto("ZTimeArrival",420,0,420,"Z [mm]");
  addHisto("processTimeArrival",3,0.5,3.5,"process");

  if(setup_=="SingleFibre")   addHisto("timeArrival_scint",500,5,10,"time [ns]");
  else   addHisto("timeArrival_scint",500,10,20,"time [ns]");
  addHisto("ZTimeArrival_scint",420,0,420,"Z [mm]");

  if(setup_=="SingleFibre")   addHisto("timeArrival_cher",500,5,10,"time [ns]");
  else   addHisto("timeArrival_cher",500,10,20,"time [ns]");
  addHisto("ZTimeArrival_cher",420,0,420,"Z [mm]");

  if(setup_=="SingleFibre")   addHisto("timeArrival_wls",500,5,10,"time [ns]");
  else   addHisto("timeArrival_wls",500,10,20,"time [ns]");
  addHisto("ZTimeArrival_wls",420,0,420,"Z [mm]");

 addHisto("waveform_total",200,0,100,"time [ns]");
 addHisto("waveform_scint",200,0,100,"time [ns]");
 addHisto("waveform_cher",200,0,100,"time [ns]");
 addHisto("waveform_wls",200,0,100,"time [ns]");

 addHisto("time_at_max",100,0,50,"time [ns]");

 addHisto("Z_nPhotTiming",420,0,420,"Z [mm]");
 addHisto("Z_firstPhotons",420,0,420,"Z [mm]");
 addHisto("Process_nPhotTiming",3,0.5,3.5,"process"); 
 addHisto("Time_nPhotTiming",100,0,50,"time [ns]"); 

 addHisto("time_frac50",300,10,20,"time[ns]");
 addHisto("time_frac50_shaped",400,10,30,"time [ns]");

 addHisto2D("time_frac50_vs_Z",420,0,420,"Z [mm]",500,10,100,"time [ns]");
 addHisto2D("time_frac50_vs_Z_fast",420,0,420,"Z [mm]",500,10,30,"time [ns]");

}


void Analyzer::Loop(std::string setup, std::string energy)
{
  gROOT->ProcessLine("gPrintViaErrorHandler = kTRUE");
  gROOT->ProcessLine("gErrorIgnoreLevel = 6000");

//   In a ROOT session, you can do:
//      Root > .L Analyzer.C
//      Root > Analyzer t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;


   Long64_t nentries = fChain->GetEntries();
   //   nentries = 10;
   energy_=energy;
   setup_=setup;

   outDir_="outFiles/plots/"+energy+"/"+setup+"/";
   system(Form("mkdir -p %s", outDir_.Data()));
   TString fileName = "outFiles/plotterTiming_"+setup+"_"+energy+".root";

  TFile* outFile = TFile::Open(fileName,"recreate");

  createHistos();

  int nPhotTiming=200;
  LoadTree(0);
  fChain->GetEntry(0);
  //  nPhotTiming=(int)(Time_deposit->size()*0.01);
  std::cout<<"averaging time on "<<nPhotTiming<<" photons"<<std::endl;


   Long64_t nbytes = 0, nb = 0;
   TH1F* wave = new TH1F("wave","wave",200,0,200);
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if(jentry%100 == 0)std::cout<<"Entry:"<<jentry<<"/"<<nentries<<std::endl;
      float averageTiming = 0;
      float averageZ = 0;
      float averageTiming_wls = 0;
      float averageZ_wls = 0;
      float averageTiming_scint = 0;
      float averageZ_scint = 0;
      float averageTiming_cher = 0;
      float averageZ_cher = 0;

      int nPhotTiming_wls=0;
      int nPhotTiming_scint=0;
      int nPhotTiming_cher=0;



      histos_["nPhotons"]->Fill(Fibre_0);

      for(int j=0;j<Time_deposit->size();++j){

	float time = Time_deposit->at(j);
	int process = Process_deposit->at(j); 
	int Z = Z_deposit->at(j); 
	

	histos2D_["time_frac50_vs_Z"]->Fill(Z,time);
	histos2D_["time_frac50_vs_Z_fast"]->Fill(Z,time);

	histos_["timeArrival"]->Fill(time);
	histos_["ZTimeArrival"]->Fill(Z);
	histos_["processTimeArrival"]->Fill(process);
	if(jentry<10)	histos_["waveform_total"]->Fill(time);
	wave->Fill(time);
	if(process==1){
	histos_["timeArrival_wls"]->Fill(time);
	histos_["ZTimeArrival_wls"]->Fill(Z);
	if(jentry<10)	histos_["waveform_wls"]->Fill(time);
	}else if(process==2){
	histos_["timeArrival_scint"]->Fill(time);
	histos_["ZTimeArrival_scint"]->Fill(Z);
	if(jentry<10)	histos_["waveform_scint"]->Fill(time);
	}else  if(process==3){
	histos_["timeArrival_cher"]->Fill(time);
	histos_["ZTimeArrival_cher"]->Fill(Z);
	if(jentry<10)	histos_["waveform_cher"]->Fill(time);
	}
      }






      //shaping of photodetectors

      wave->Sumw2();
      wave->Scale(1./wave->Integral());//even if for our porposes it's not important pdfs should be normalized to avoid troubles in convolution

      TGraph* waveGraph = new TGraph(wave);
      Waveform* waveF = new Waveform(wave->GetNbinsX(),waveGraph->GetX(),waveGraph->GetY());
      Waveform::max_amplitude_informations wave_max_bare = waveF->max_amplitude(4,100,3);

      float time_frac50 = waveF->time_at_frac(0,100,0.5,wave_max_bare,3);

      histos_["time_frac50"]->Fill(time_frac50);

      

    
      if(DOSHAPING){
	RooRealVar t("t","t", 0, 200);
	RooDataHist waveHist("wave","dataset with t",t,RooFit::Import(*wave) );
	RooHistPdf histpdf1("histpdf1","histpdf1",t,waveHist);
	
	
	TF1 *f = new  TF1("f", "pow(exp(1.)*[1]*(x)/[0],[0])*exp(-[1]*(x))",0.,200.);
	f->SetParameters(3.0, 0.8);
	
	RooAbsPdf* rfa1 = RooFit::bindPdf(f,t);
	
	RooNumConvPdf convolutionShaping("convolutionShaping","exp (X) crrc",t,histpdf1,*rfa1) ;
	RooRealVar center("center","center",50,0,400);
	RooRealVar width("width","width",50,0,400);
	
	convolutionShaping.setConvolutionWindow(center,width,1);
	convolutionShaping.verboseEval(0);
	convolutionShaping.convIntConfig().setEpsAbs(0.001);//absolute precision
	convolutionShaping.convIntConfig().setEpsRel(0.001);//relative precision
	
	if(jentry==0){
	  RooPlot* frame1 = t.frame(RooFit::Title("histogram pdf")) ;
	  //      rfa1->plotOn(frame1);
	  waveHist.plotOn(frame1,RooFit::LineColor(kBlack),RooFit::DrawOption("L"),RooFit::LineWidth(2));
	  convolutionShaping.plotOn(frame1,RooFit::LineColor(kRed)) ;
	  
	  
	  TCanvas c1("c_histpdf");
	  frame1->Draw();
	  c1.SaveAs("histpdf_analyzer.png");
	}
	
	TH1* histo_shaped =  convolutionShaping.createHistogram("t",200);
	histo_shaped->SetName("histo_shaped");

	TGraph* waveGraph_shaped=new TGraph(histo_shaped);
	Waveform* waveF_shaped = new Waveform(200,waveGraph_shaped->GetX(),waveGraph_shaped->GetY());
	Waveform::max_amplitude_informations wave_max_bare_shaped = waveF_shaped->max_amplitude(4,100,3);


	histos_["time_frac50_shaped"]->Fill(waveF_shaped->time_at_frac(0,100,0.5,wave_max_bare_shaped,3));


      }

      
      if(jentry==200){
	TCanvas dummy;
	TF1 f("f","pol2",0,50);
	wave->Fit("f","R","",wave->GetBinCenter(wave->GetMaximumBin())-2*wave->GetBinWidth(0),wave->GetBinCenter(wave->GetMaximumBin())+2*wave->GetBinWidth(0));
	wave->Draw();
	f.SetLineColor(kRed);
	f.Draw("same");
	dummy.SaveAs("dummy.png");
      }
	  wave->Reset();	


      if(setup_=="SingleFibre")         nPhotTiming=(int)(Time_deposit->size()*0.01);
      else nPhotTiming=(int)(Time_deposit->size()*0.01);
      //      std::cout<<nPhotTiming<<std::endl;

      //      for (auto i: Analyzer::sort_indexes( *Time_deposit)) {
	//	std::cout << Time_deposit->at(i) << std::endl;
      //      } 


      int nPhot=0;      
      for (auto i: Analyzer::sort_indexes( *Time_deposit)) {
	nPhot++;
	if(nPhot>nPhotTiming)break;
	float time = Time_deposit->at(i);
	int process = Process_deposit->at(i); 
	int Z = Z_deposit->at(i); 
	//	std::cout<<nPhot<<" "<< time << std::endl;
	if(nPhot<Time_deposit->size()){
	  averageTiming+=time;
	  histos_["processTimeArrival_avg"]->Fill(process);
	  averageZ+=Z;
	  if(nPhot<4)	  histos_["Z_firstPhotons"]->Fill(Z);
	  histos_["Z_nPhotTiming"]->Fill(Z);
	  histos_["Process_nPhotTiming"]->Fill(process);
	  histos_["Time_nPhotTiming"]->Fill(time);
	  if(process==1){
	    nPhotTiming_wls++;
	    averageTiming_wls+=time;
	    averageZ_wls+=Z;
	  }else if(process==2){
	    nPhotTiming_scint++;
	    averageTiming_scint+=time;
	    averageZ_scint+=Z;
	  }else if(process==3){
	    nPhotTiming_cher++;
	    averageTiming_cher+=time;
	    averageZ_cher+=Z;
	  }
	}
      }
      histos_["timeArrival_avg"]->Fill(averageTiming/nPhotTiming);
      histos_["ZTimeArrival_avg"]->Fill(averageZ/nPhotTiming);
      
      histos_["timeArrival_avg_wls"]->Fill(averageTiming_wls/nPhotTiming_wls);
      histos_["ZTimeArrival_avg_wls"]->Fill(averageZ_wls/nPhotTiming_wls);
      
      histos_["timeArrival_avg_scint"]->Fill(averageTiming_scint/nPhotTiming_scint);
      histos_["ZTimeArrival_avg_scint"]->Fill(averageZ_scint/nPhotTiming_scint);
      
      histos_["timeArrival_avg_cher"]->Fill(averageTiming_cher/nPhotTiming_cher);
      histos_["ZTimeArrival_avg_cher"]->Fill(averageZ_cher/nPhotTiming_cher);
   }


   fitHisto(histos_["timeArrival_avg"],resValueTime,resValueTimeErr);
   fitHisto(histos_["time_frac50"],resValueTime_frac50,resValueTimeErr_frac50);
   if(DOSHAPING)    fitHisto(histos_["time_frac50_shaped"],resValueTime_frac50_shaped,resValueTimeErr_frac50_shaped);
   drawHistos();

   TCanvas wave_canvas;
   histos_["waveform_total"]->Draw();
   histos_["waveform_scint"]->SetLineColor(kRed);
   histos_["waveform_scint"]->Draw("same");
   histos_["waveform_cher"]->SetLineColor(kBlue);
   histos_["waveform_wls"]->SetLineColor(kViolet);
   histos_["waveform_cher"]->Draw("same");
   histos_["waveform_wls"]->Draw("same");
   wave_canvas.SaveAs(outDir_+"waveform.png");
   wave_canvas.SaveAs(outDir_+"waveform.pdf");

   meanValueTime->Write("meanValueTime");
   meanValueTimeErr->Write("meanValueTimeErr");

   resValueTime->Write("resValueTime");
   resValueTimeErr->Write("resValueTimeErr");

   resValueTime_frac50->Write("resValueTime_frac50");
   resValueTimeErr_frac50->Write("resValueTimeErr_frac50");

   resValueTime_frac50_shaped->Write("resValueTime_frac50_shaped");
   resValueTimeErr_frac50_shaped->Write("resValueTimeErr_frac50_shaped");


   outFile->Write();
   outFile->Close();

}


void Analyzer::fitHisto(TH1F* histo, TVectorD* res, TVectorD* resErr){
//-----------------fit with cruijff ------------------------
  double peakpos = histo->GetBinCenter(histo->GetMaximumBin());
  double sigma = histo->GetRMS();

  double fitmin;
  double fitmax;
  
  
  fitmin = peakpos-4*sigma;
  fitmax = peakpos+4*sigma;
  
  RooRealVar x("x","deltaT", fitmin, fitmax);
  RooDataHist data("data","dataset with x",x,RooFit::Import(*histo) );

  RooRealVar meanr("meanr","Mean",peakpos+sigma,peakpos-3*sigma, peakpos+3*sigma);
  RooRealVar widthL("widthL","#sigmaL",sigma , 0, 5*sigma);
  RooRealVar widthR("widthR","#sigmaR",sigma , 0, 5*sigma);
  RooRealVar alphaL("alphaL","#alpha",5.08615e-02 , 0., 1.);
  RooRealVar alphaR("alphaR","#alpha",5.08615e-02, 0., 1.);
  int ndf;

  RooPlot* frame;

  RooCruijff fit_fct("fit_fct","fit_fct",x,meanr,widthL,widthR,alphaL,alphaR); ndf = 5;
  fit_fct.fitTo(data);
  
  frame = x.frame("Title");
  frame->SetXTitle("time [ns]");
  std::string ytitle = Form("Events");
  frame->SetYTitle(ytitle.c_str());
  
  data.plotOn(frame);  //this will show histogram data points on canvas 
  fit_fct.plotOn(frame);//this will show fit overlay on canvas  

  double rms,rmsErr;
  rms = (widthL.getVal()+widthR.getVal())/2;
  rmsErr = 0.5*sqrt(widthL.getError()*widthL.getError()+widthR.getError()*widthR.getError());

  TCanvas* cans = new TCanvas();
  cans->cd();
  frame->Draw();
  TLegend* lego = new TLegend(0.57, 0.75, 0.89, 0.9); 
  lego->SetTextAlign(32);
  lego->SetTextSize(0.036);
  lego->AddEntry(  (TObject*)0 ,Form("#mu = %.0f #pm %.0f ps", meanr.getVal()*1.e3, meanr.getError()*1.e3), "");
  lego->AddEntry(  (TObject*)0 ,Form("#sigma = %.0f #pm %.0f ps", rms*1.e3, rmsErr*1.e3), "");

  meanValueTime[0]=meanr.getVal()*1.e3;
  meanValueTimeErr[0]=meanr.getError()*1.e3;

  res[0]=rms*1.e3;
  resErr[0]=rmsErr*1.e3;


  lego->SetFillColor(0);
  lego->Draw("same");
  
  TPaveText* pave = DrawTools::getLabelTop_expOnXaxis(energy_+" Electron Beam");
  pave->Draw("same");

  cans->SaveAs(outDir_+histo->GetName()+"_cruijff_fit.png");
  cans->SaveAs(outDir_+histo->GetName()+"_cruijff_fit.pdf");



}



