#include "PhysicsList.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4NuclideTable.hh"
//#include "HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronInelasticQBBC.hh"
#include "QBBC.hh"

#include "G4HadronPhysicsINCLXX.hh"
#include "G4IonElasticPhysics.hh"
#include "G4IonPhysicsXS.hh"
#include "G4IonINCLXXPhysics.hh"
#include "G4StoppingPhysics.hh"

#include "G4EmStandardPhysics_option3.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

#include "G4StepLimiterPhysics.hh"

// below is the group of  customized physics lists
//#include "GammaNuclearPhysics.hh"
//#include "GammaNuclearPhysicsLEND.hh"
//#include "ElectromagneticPhysics.hh"
//#include "RadioactiveDecayPhysics.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//G4VModularPhysicsList* physicsList = new QBBC;
//physicsList->SetVerboseLevel(1); // ?
//physicsList->RegisterPhysics(new G4StepLimiterPhysics()); //!!!!!!!!!!!!!!!
//physicsList->RegisterPhysics(new G4RadioactiveDecayPhysics);
//runManager->SetUserInitialization(physicsList);
// new implimentation of physics physicsList
//:G4VModularPhysicsList()

PhysicsList::PhysicsList()
:QBBC()

{

  G4int verb = 1;
  SetVerboseLevel(verb);
  // mandatory for G4NuclideTable

  //
  RegisterPhysics(new G4StepLimiterPhysics()); //!!!

  const G4double meanLife = 1*nanosecond, halfLife = meanLife*std::log(2);

  G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(halfLife);


  //RegisterPhysics( new G4HadronPhysicsINCLXX(verb));

  // Ion Elastic scattering
  //////////////RegisterPhysics( new G4IonElasticPhysics());

  // Ion Inelastic Physics
  //RegisterPhysics( new G4IonPhysicsXS());
  ////RegisterPhysics( new G4IonINCLXXPhysics(verb));


  // Gamma-Nuclear Physics
  ////RegisterPhysics( new GammaNuclearPhysicsLEND("gamma"));

  // EM physics
  ////RegisterPhysics(new G4EmStandardPhysics_option3(verb));


  // Radioactive Decay
  RegisterPhysics(new G4RadioactiveDecayPhysics());

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::~PhysicsList()

{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetCuts()

{
  // G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(10*eV, 1*GeV);
  // SetCutValue(0*mm, "proton");
  // SetCutValue(10*km, "e-");
  // SetCutValue(10*km, "e+");
  // SetCutValue(10*km, "gamma");

}
