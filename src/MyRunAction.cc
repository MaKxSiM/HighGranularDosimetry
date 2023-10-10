#include "MyRunAction.hh"
#include "G4RunManager.hh"
#include "G4PrimaryVertex.hh"
#include "G4AccumulableManager.hh"

MyRunAction::MyRunAction()
{
  auto man = G4AnalysisManager::Instance();

  CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine);
  //CLHEP::HepRandom::setTheSeed(time(NULL));
  CLHEP::HepRandom::setTheSeed((unsigned)clock()); 

  G4RunManager::GetRunManager()->SetPrintProgress(0);

  man->SetVerboseLevel(0);
  man->SetNtupleMerging(true);
// Fluences for all particles, for a given particle easy to get taking a projection on a particle type

  man->CreateNtuple("Fluences", "Fluences");
  man->CreateNtupleIColumn("Event");
  man->CreateNtupleDColumn("X");
  man->CreateNtupleDColumn("Y");
  man->CreateNtupleDColumn("Zsurf");
  man->CreateNtupleDColumn("Energy");
  man->CreateNtupleIColumn("particle_id");
  man->CreateNtupleSColumn("particle_name");
  man->CreateNtupleSColumn("material_name_end");
  man->FinishNtuple(0);

// Differential energy for the primary particle (step will be an input parameter)

  man -> CreateNtuple("dEdz","dEdz");
  man->CreateNtupleDColumn("Edep_MeV");
  man->CreateNtupleDColumn("Step");
  man->CreateNtupleDColumn("Z");
  man->CreateNtupleDColumn("En");
  man->CreateNtupleIColumn("Event");
  man->FinishNtuple(1);

  man->CreateNtuple("Dose_in_volume_N", "Dose_in_volume_N");
  man->CreateNtupleDColumn("Edep_MeV");
  man->CreateNtupleIColumn("VolumeId");
  man->CreateNtupleIColumn("Event");
  man->CreateNtupleDColumn("dose");
  man->CreateNtupleDColumn("X");
  man->CreateNtupleDColumn("Y");
  man->CreateNtupleDColumn("Z");
  man->FinishNtuple(2);

  man->CreateNtuple("Produced particles", "Produced particles");
  man->CreateNtupleDColumn("En");
  man->CreateNtupleSColumn("Particle_Name");
  man->CreateNtupleIColumn("Particle_Id");
  man->CreateNtupleDColumn("X");
  man->CreateNtupleDColumn("Y");
  man->CreateNtupleDColumn("Z");
  man->CreateNtupleDColumn("Distance_fr_pr_vertex");
  man->FinishNtuple(3);

}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{

    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->OpenFile("output.root");


    // set printing event number per each event
}


void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}
