//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file EventAction.hh
/// \brief Definition of the B1::EventAction class

#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///

class MyRunAction;
class PrimaryGeneratorAction;

class EventAction : public G4UserEventAction
{
  public:
    EventAction(MyRunAction* runAction, PrimaryGeneratorAction* generatorAction);
    ~EventAction() override;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;

    void AddEdep(G4double edep, G4int i) { fEdepV.at(i) += edep; };

    G4double xprime, yprime, zprime, distdEdx;
    std::vector<G4double> vdEdz;
    std::vector<G4double> vEn;

    std::vector<G4double> InitializeZVector(G4double min, G4double max, G4double step);
    std::vector<G4double> InitializeEnVector(G4double min, G4double max, G4double step);
    std::vector<G4double> Initialize_EinVol_Vector(G4int N);

  private:
    MyRunAction* fRunAction = nullptr;
    PrimaryGeneratorAction* fGeneratorAction;
    std::vector<G4double> fEdepV;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
