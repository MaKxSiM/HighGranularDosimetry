{

  gROOT->Reset();
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetOptFit(0);
  gStyle->SetLabelFont(42);
  gStyle->SetLabelFont(42);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleFont(42);

  gStyle->SetPadLeftMargin(0.08);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadTopMargin(0.03);//!!
  gStyle->SetPadBottomMargin(0.12);//!!

//  gStyle->SetPadBottomMargin(0.21);//!!

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
  //1000020040//alfa


  // TFile *f = new TFile("~/Programs/Geant4/WorkTest/GIT/MedPhys_pBi-build/output_210MeV_step5mkm.root");
   //TFile *f = new TFile("~/Programs/Geant4/WorkTest/MedPhys-v2/MedPhys_pBi-build/gamma_25.root");
   TFile *f1 = new TFile("~/Programs/Geant4/WorkTest/MedPhys-v3/MedPhys_pBi-build/output_190.root");
   TFile *f2 = new TFile("~/Programs/Geant4/WorkTest/MedPhys-v3/MedPhys_pBi-build/output_230.root");

/*
c4 = new TCanvas("c4", "Produced particle", 1400, 720);

TH1F *hParticle1 = new TH1F("hParticle","Produced particle",150,0,150);
TH1F *hParticle2 = new TH1F("hParticle2","Produced particle",150,0,150);

TTree *t4 = (TTree*)f1->Get("Produced particles");
double Dist;
char ParticleName[100];
t4->SetBranchAddress("Distance_fr_pr_vertex",&Dist);
t4->SetBranchAddress("Particle_Name",&ParticleName);

int nentries4 = (int)t4->GetEntries();
for (int i=0; i<nentries4; i++) {
//for (int i=0; i<10000; i++) {
  t4 -> GetEntry(i);
  //if(Dist>201 && Dist<210){
  if(Dist>11 && Dist<20){
     hParticle1->Fill(ParticleName, 1);
  }
}


TTree *t5 = (TTree*)f2->Get("Produced particles");
double Dist2;
char ParticleName2[100];
t5->SetBranchAddress("Distance_fr_pr_vertex",&Dist2);
t5->SetBranchAddress("Particle_Name",&ParticleName2);

int nentries5 = (int)t5->GetEntries();
for (int i=0; i<nentries5; i++) {
//for (int i=0; i<10000; i++) {
  t5 -> GetEntry(i);
  //if(Dist2>201 && Dist2<210){
 if(Dist2>11 && Dist2<20){
     if(strcmp(ParticleName2," ")!=0)hParticle2->Fill(ParticleName2, 1);
  }
}


hParticle1->SetLineWidth(2);
hParticle1->SetLineColor(kBlue);
hParticle1->LabelsOption(">","X");
hParticle1->Draw();

hParticle2->SetLineWidth(2);
hParticle2->LabelsOption(">","X");
hParticle2->SetLineColor(kRed);
hParticle2->Draw("same");

TLegend* legend = new TLegend(0.65, 0.70, 0.80, 0.85);//
legend->SetTextSize(0.036);
legend->SetTextFont(42);
//legend->SetHeader("Particle fluences","C");
legend->AddEntry(hParticle1, "E_{beam} = 190 MeV", "l");
legend->AddEntry(hParticle2, "E_{beam} = 230 MeV", "l");
legend->SetFillColor(kWhite);
legend->SetLineColor(kWhite);
legend->Draw();
*/

//====================================================================
TTree *t1 = (TTree*)f1->Get("Fluences");
double X, Y, Zsurf, Energy;
int particle_id;
char particle_name[50];
int Event;

t1->SetBranchAddress("X",&X);
t1->SetBranchAddress("Y",&Y);
t1->SetBranchAddress("Zsurf",&Zsurf);
t1->SetBranchAddress("Energy",&Energy);
t1->SetBranchAddress("particle_id",&particle_id);
t1->SetBranchAddress("particle_name",&particle_name);
//t1->SetBranchAddress("Event",&Event);

TH1F *hSpectrum1  = new TH1F("hFluence","Fluence (z)",200,0,100);
TH1F *hSpectrum2  = new TH1F("hFluence","Fluence (z)",200,0,100);

int nentries = (int)t1->GetEntries();
for (int i=0; i<nentries; i++) {
//for (int i=0; i<30; i++) {
  t1 -> GetEntry(i);

  if(Zsurf>=200 && Zsurf<=202 )if(particle_id == 2212)hSpectrum1 -> Fill(Energy);

  //if(strcmp(particle_name, "alpha") == 0 ) hFluence[4] -> Fill(Zsurf);
  //if(strcmp(particle_name, "alpha") == 0 ) cout<< particle_name << "   PDG ID = "<< particle_id <<endl;
}

c1 = new TCanvas("c1", "c1", 960, 720);


hSpectrum1->GetYaxis()->SetTickLength(0.02);
hSpectrum1->GetYaxis()->SetNdivisions(505);
hSpectrum1->GetXaxis()->CenterTitle();
hSpectrum1->GetYaxis()->CenterTitle();
hSpectrum1->GetXaxis()->SetTitle("Energy, GeV");
//hDoze->GetYaxis()->SetTitle("Dose, Gy");
hSpectrum1->GetYaxis()->SetTitle("N");
//hFluence[0] ->GetYaxis()->SetTitleSize(0.045*TextSizeScale);
//hSpectrum1 ->GetYaxis()->SetRangeUser(0, 3);
hSpectrum1->GetYaxis()->SetTitleOffset(1.2);
hSpectrum1->GetXaxis()->SetTitleSize(0.045*TextSizeScale);
hSpectrum1->GetXaxis()->SetTitleOffset(1.0);
hSpectrum1->GetYaxis()->SetLabelSize(0.04*TextSizeScale);
hSpectrum1->GetXaxis()->SetLabelSize(0.04*TextSizeScale);

hSpectrum1 -> Draw();


}
