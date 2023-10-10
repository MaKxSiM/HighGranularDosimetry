#ifndef PhysicsList_h

#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "QBBC.hh"

#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//class PhysicsList: public G4VModularPhysicsList
class PhysicsList: public QBBC
{

public:

  PhysicsList();

 ~PhysicsList() override;

public:

  void SetCuts() override;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
