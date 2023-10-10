{

  gROOT->Reset();
  //gStyle->SetOptStat(0);
  //gStyle->SetOptTitle(0);
  gStyle->SetOptFit(0);
  gStyle->SetLabelFont(42);
  gStyle->SetTitleFont(42);

  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadTopMargin(0.1);//!!
  gStyle->SetPadBottomMargin(0.12);//!!

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  //gPad->SetLogy();
  //TGaxis::SetMaxDigits(3);
  double TextSizeScale = 1.0;

  struct GraphAttr {
  	int colour;
  	int marker;
  	float width;
  	float size;
  	char  ModelName[100];
  	char option[20];
  };


  GraphAttr ModelAttr[] = {
  	{ 4, 21, 2.0, 1.2, "protons", "" },
  	{ 3, 33, 2.0, 1.5, "neutrons", "same" },
  	{ 2, 34, 2.0, 1.5, "electrons", "same" },
  	{ 45, 29, 2.0, 1.6, "photons", "same" },
    { 5, 29, 2.0, 1.6, "alpha", "same" },
  };

  vector<int> PIDofInterest;
  PIDofInterest.push_back(2212);   //proton
  PIDofInterest.push_back(2112);   //neutron
  PIDofInterest.push_back(11);     //electron
  PIDofInterest.push_back(22);     //gamma
  PIDofInterest.push_back(1000020040);  //alpha


   //TFile *f = new TFile("~/Programs/Geant4/WorkTest/MedPhys-v3/MedPhys_pBi-build/output.root");
   //TFile *f = new TFile("~/Programs/Geant4/WorkTest/MedPhys-v4/MedPhys_pBi-build/output_woAct.root");
  // TFile *f = new TFile("~/Programs/Geant4/WorkTest/MedPhys-v4/MedPhys_pBi-build/output_wAct.root");
//TFile *f = new TFile("~/Programs/Geant4/WorkTest/MedPhys-v4/MedPhys_pBi-build/output_100MeV_100mg.root");
  //////////TFile *f = new TFile("~/Programs/Geant4/WorkTest/MedPhys-v4/MedPhys_pBi-build/output_100MeV_0mg.root");
   //TFile *f = new TFile("~/Programs/Geant4/WorkTest/MedPhys-v4/MedPhys_pBi-build/output_100MeV_250mg_e01mev.root");
  // TFile *f = new TFile("~/Programs/Geant4/WorkTest/MedPhys-v4/MedPhys_pBi-build/output.root");

  //////////TFile *f2 = new TFile("~/Programs/Geant4/WorkTest/MedPhys-v4/MedPhys_pBi-build2/output.root");
  // TFile *f2 = new TFile("~/Programs/Geant4/WorkTest/MedPhys-v4/MedPhys_pBi-build/output_100MeV_1000mg.root");
   //TFile *f2 = new TFile("~/Programs/Geant4/WorkTest/MedPhys-v4/MedPhys_pBi-build/output_100MeV_3kg.root");
//======================= low-e stduies ========================================
  // TFile *f = new TFile("~/Programs/Geant4/WorkTest/MedPhys-v4/MedPhys_pBi-build2/output_ref_250eV_0mg_v2.root");
   //TFile *f2 = new TFile("~/Programs/Geant4/WorkTest/MedPhys-v4/MedPhys_pBi-build2/output_ref_250eV_10000mg_v2.root");
//==============================================================================

//TFile *f = new TFile("/home/maxim/Programs/Geant4/WorkTest/MedPhys-v4/MedPhys_pBi-build2/output.root");
//TFile *f2 = new TFile("/home/maxim/Programs/Geant4/WorkTest/MedPhysG11.1_v1/MedPhys_pBi-build/output.root");

TFile *f = new TFile("/home/maxim/Programs/Geant4/WorkTest/MedPhysG11.1_v1/MedPhys_pBi-build/output_soft_0mg.root");
TFile *f2 = new TFile("/home/maxim/Programs/Geant4/WorkTest/MedPhysG11.1_v1/MedPhys_pBi-build/output_soft_10000mg.root");



c4 = new TCanvas("c4", "Produced particle", 960, 720);

//===================== histograms for energy spectra ==========================
TH1F *hParticle1 = new TH1F("hParticle1","Electron energy",100,0,0.001);
TH1F *hParticle2 = new TH1F("hParticle2","Gamma energy",200,0,0.02);
TH1F *hParticle3 = new TH1F("hParticle3","Alfa energy",100,0,10);
TH1F *hParticle4 = new TH1F("hParticle4","Neutron energy",100,0,10);

TH1F *hParticle1_2 = new TH1F("hParticle1_2","Electron energy",100,0,0.001);
TH1F *hParticle2_2 = new TH1F("hParticle2_2","Gamma energy",200,0,0.02);
TH1F *hParticle3_2 = new TH1F("hParticle3_2","Alfa energy",100,0,10);
TH1F *hParticle4_2 = new TH1F("hParticle4_2","Neutron energy",100,0,10);
//==============================================================================

//===================== partilce densities =====================================
TH1F *hDensityProfile1 = new TH1F("hDensityProfile1","Electron density", 120,0,120);
TH1F *hDensityProfile2 = new TH1F("hDensityProfile2","Gamma density", 120,0,120);
TH1F *hDensityProfile3 = new TH1F("hDensityProfile3","Alfa density", 120,0,120);
TH1F *hDensityProfile4 = new TH1F("hDensityProfile4","Neutron density", 120,0,120);

TH1F *hDensityProfile1_2 = new TH1F("hDensityProfile1_2","Electron density", 120,0,120);
TH1F *hDensityProfile2_2 = new TH1F("hDensityProfile2_2","Gamma density", 120,0,120);
TH1F *hDensityProfile3_2 = new TH1F("hDensityProfile3_2","Alfa density", 120,0,120);
TH1F *hDensityProfile4_2 = new TH1F("hDensityProfile4_2","Neutron density", 120,0,120);
//==============================================================================

TTree *t4 = (TTree*)f->Get("Produced particles");
double Dist, Energy;
int particle_id;
char ParticleName[100];
t4->SetBranchAddress("Distance_fr_pr_vertex",&Dist);
t4->SetBranchAddress("Particle_Name",&ParticleName);
t4->SetBranchAddress("En",&Energy);
t4->SetBranchAddress("Particle_Id",&particle_id);

int nentries4 = (int)t4->GetEntries();
for (int i=0; i<nentries4; i++) {
//for (int i=0; i<10000; i++) {
  t4 -> GetEntry(i);

     if (particle_id == 11){
       if(Dist>=50 && Dist<60) hParticle1->Fill(Energy);
       hDensityProfile1->Fill(Dist);
     }
     if (particle_id == 22){
       if(Dist>=50 && Dist<60)
       hParticle2->Fill(Energy);
       hDensityProfile2->Fill(Dist);
     }
     if (particle_id == 1000020040){
       if(Dist>=50 && Dist<60) hParticle3->Fill(Energy);
       hDensityProfile3->Fill(Dist);
     }
     if (particle_id == 2112){
       if(Dist>=50 && Dist<60) hParticle4->Fill(Energy);
       hDensityProfile4->Fill(Dist);
     }
}

TTree *t4_2 = (TTree*)f2->Get("Produced particles");

t4_2->SetBranchAddress("Distance_fr_pr_vertex",&Dist);
t4_2->SetBranchAddress("Particle_Name",&ParticleName);
t4_2->SetBranchAddress("En",&Energy);
t4_2->SetBranchAddress("Particle_Id",&particle_id);

int nentries4_2 = (int)t4_2->GetEntries();
for (int i=0; i<nentries4_2; i++) {
//for (int i=0; i<10000; i++) {
  t4_2 -> GetEntry(i);

     if (particle_id == 11){
       if(Dist>=50 && Dist<60) hParticle1_2->Fill(Energy);
       hDensityProfile1_2->Fill(Dist);
     }
    if (particle_id == 22){
      if(Dist>=50 && Dist<60)
       hParticle2_2->Fill(Energy);
       hDensityProfile2_2->Fill(Dist);
     }
     if (particle_id == 1000020040){
      if(Dist>=50 && Dist<60) hParticle3_2->Fill(Energy);
      hDensityProfile3_2->Fill(Dist);
     }
     if (particle_id == 2112){
       if(Dist>=50 && Dist<60) hParticle4_2->Fill(Energy);
       hDensityProfile4_2->Fill(Dist);
     }

}




c4->Divide(2,2);

c4->cd(1);
hParticle1->GetXaxis()->SetTitle("Energy, MeV");
hParticle1->SetLineColor(kBlue);
hParticle1->Draw();
hParticle1_2->SetLineColor(kRed);
hParticle1_2->Draw("same");

TLegend* legend = new TLegend(0.50, 0.65, 0.7, 0.80);//
legend->SetTextSize(0.036);
legend->SetTextFont(42);
legend->SetHeader("Concentration:","C");
legend->AddEntry(hParticle1, "c_{Bi} = 0", "l");
legend->AddEntry(hParticle1_2, "c_{Bi} = 1000mg/l", "l");
legend->SetFillColor(kWhite);
legend->SetLineColor(kWhite);
legend->Draw();



c4->cd(2);
hParticle2->GetXaxis()->SetTitle("Energy, MeV");
hParticle2->SetLineColor(kBlue);
hParticle2->Draw();
hParticle2_2->SetLineColor(kRed);
hParticle2_2->Draw("same");

c4->cd(3);
hParticle3->GetXaxis()->SetTitle("Energy, MeV");
hParticle3->SetLineColor(kBlue);
hParticle3->Draw();
hParticle3_2->SetLineColor(kRed);
hParticle3_2->Draw("same");

c4->cd(4);
hParticle4->GetXaxis()->SetTitle("Energy, MeV");
hParticle4->SetLineColor(kBlue);
hParticle4->Draw();
hParticle4_2->SetLineColor(kRed);
hParticle4_2->Draw("same");





c5 = new TCanvas("c5", "Produced particle", 960, 720);

//getinng maximun for first histrgram and makins some offset by multiplying by 1.2
double max_y_plot[4];
max_y_plot[0] = 1.2*std::max(hDensityProfile1->GetMaximum (), hDensityProfile1_2->GetMaximum ());
max_y_plot[1] = 1.2*std::max(hDensityProfile2->GetMaximum (), hDensityProfile2_2->GetMaximum ());
max_y_plot[2] = 1.2*std::max(hDensityProfile3->GetMaximum (), hDensityProfile3_2->GetMaximum ());
max_y_plot[3] = 1.2*std::max(hDensityProfile4->GetMaximum (), hDensityProfile4_2->GetMaximum ());

c5->Divide(2,2);
c5->cd(1);
hDensityProfile1->GetXaxis()->SetTitle("depth, mm");
hDensityProfile1->Draw();

hDensityProfile1->GetYaxis()->SetRangeUser(0,  max_y_plot[0]);
hDensityProfile1->GetXaxis()->SetTitle("depth, mm");
hDensityProfile1->SetLineColor(kBlue);
hDensityProfile1->Draw();
hDensityProfile1_2->SetLineColor(kRed);
hDensityProfile1_2->Draw("same");

TLegend* legend2 = new TLegend(0.20, 0.65, 0.4, 0.80);//
legend2->SetTextSize(0.036);
legend2->SetTextFont(42);
legend2->SetHeader("Concentration:","C");
legend2->AddEntry(hParticle1, "c_{Bi} = 0", "l");
legend2->AddEntry(hParticle1_2, "c_{Bi} = 1000mg/l", "l");
legend2->SetFillColor(kWhite);
legend2->SetLineColor(kWhite);
legend2->Draw();


TLine *line1a = new TLine(50,0,50,max_y_plot[0]);
line1a->SetLineWidth(2);
line1a->SetLineColor(kGray);
line1a->Draw();
TLine *line1b = new TLine(60,0,60,max_y_plot[0]);
line1b->SetLineWidth(2);
line1b->SetLineColor(kGray);
line1b->Draw();


c5->cd(2);
hDensityProfile2->GetYaxis()->SetRangeUser(0,  max_y_plot[1]);
hDensityProfile2->GetXaxis()->SetTitle("depth, mm");
hDensityProfile2->SetLineColor(kBlue);
hDensityProfile2->Draw();
hDensityProfile2_2->SetLineColor(kRed);
hDensityProfile2_2->Draw("same");

TLine *line2a = new TLine(50,0,50,max_y_plot[1]);
line2a->SetLineWidth(2);
line2a->SetLineColor(kGray);
line2a->Draw();
TLine *line2b = new TLine(60,0,60,max_y_plot[1]);
line2b->SetLineWidth(2);
line2b->SetLineColor(kGray);
line2b->Draw();


c5->cd(3);
hDensityProfile3->GetYaxis()->SetRangeUser(0,  max_y_plot[2]);
hDensityProfile3->GetXaxis()->SetTitle("depth, mm");
hDensityProfile3->SetLineColor(kBlue);
hDensityProfile3->Draw();
hDensityProfile3_2->SetLineColor(kRed);
hDensityProfile3_2->Draw("same");

TLine *line3a = new TLine(50,0,50,max_y_plot[2]);
line3a->SetLineWidth(2);
line3a->SetLineColor(kGray);
line3a->Draw();
TLine *line3b = new TLine(60,0,60,max_y_plot[2]);
line3b->SetLineWidth(2);
line3b->SetLineColor(kGray);
line3b->Draw();

c5->cd(4);
hDensityProfile4->GetYaxis()->SetRangeUser(0,  max_y_plot[3]);
hDensityProfile4->GetXaxis()->SetTitle("depth, mm");
hDensityProfile4->SetLineColor(kBlue);
hDensityProfile4->Draw();
hDensityProfile4_2->SetLineColor(kRed);
hDensityProfile4_2->Draw("same");

TLine *line4a = new TLine(50,0,50,max_y_plot[3]);
line4a->SetLineWidth(2);
line4a->SetLineColor(kGray);
line4a->Draw();
TLine *line4b = new TLine(60,0,60,max_y_plot[3]);
line4b->SetLineWidth(2);
line4b->SetLineColor(kGray);
line4b->Draw();




}
