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
/// \file SteppingAction.cc
/// \brief Implementation of the B1::SteppingAction class

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "MyRunAction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MySteppingAction::MySteppingAction(MyRunAction* runAc ,EventAction* eventAction)
:fRunAction(runAc),
 fEventAction(eventAction)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MySteppingAction::~MySteppingAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void MySteppingAction::UserSteppingAction(const G4Step* step)
{
  // collect energy deposited in this step

  G4double edepStep = step->GetTotalEnergyDeposit();
  G4Track* mytrack = step -> GetTrack ();
  G4double xi, yi, zi, xi_post, yi_post, zi_post, En, stepdist, xpr, ypr, zpr , zdist_fluence_pre, zdist_fluence_post;
  G4int i_z_dEdx,i_p_dEdx;
  G4int i_z_fluence,i_p_fluence;

  G4AnalysisManager *man = G4AnalysisManager::Instance();

  xi = step->GetPreStepPoint()->GetPosition().x();
  yi = step->GetPreStepPoint()->GetPosition().y();
  zi=  step->GetPreStepPoint()->GetPosition().z();

  xi_post = step->GetPostStepPoint()->GetPosition().x();
  yi_post = step->GetPostStepPoint()->GetPosition().y();
  zi_post = step->GetPostStepPoint()->GetPosition().z();

  xpr = fEventAction->xprime;
  ypr = fEventAction->yprime;
  zpr = fEventAction->zprime;


  zdist_fluence_pre = zi - zpr ;
  zdist_fluence_post = zi_post - zpr ;

  stepdist = sqrt( (xi-xi_post)*(xi-xi_post) + (yi-yi_post)*(yi-yi_post) + (zi-zi_post)*(zi-zi_post) );


  i_z_fluence = int(zdist_fluence_pre/fRunAction->stepforfluence);
  i_p_fluence = int(zdist_fluence_post/fRunAction->stepforfluence);
  En = step->GetPreStepPoint()->GetKineticEnergy()/CLHEP::MeV;

  if (mytrack->GetTrackID() == 1){
    if (fEventAction->distdEdx<fRunAction->MaxZ) {
        i_z_dEdx = int(fEventAction->distdEdx/fRunAction->stepfordEdz);
        fEventAction->vdEdz.at(i_z_dEdx) = fEventAction->vdEdz.at(i_z_dEdx) + edepStep;
        fEventAction->distdEdx+= stepdist;
        i_p_dEdx = int(fEventAction->distdEdx/fRunAction->stepfordEdz);
        if (i_p_dEdx != i_z_dEdx ) fEventAction->vEn.at(i_z_dEdx) = En;
    };
  };

  if (i_z_fluence != i_p_fluence){
    int ismaller,ibigger;
    if (G4RunManager::GetRunManager()->GetCurrentEvent()){
      if (i_z_fluence<i_p_fluence){
        ismaller = i_z_fluence;
        ibigger = i_p_fluence;
      } else
      {
        ismaller = i_p_fluence;
        ibigger = i_z_fluence;
      };
      for (int i=ismaller; i<ibigger;i++){
        if(En>0.00){ //keeping only fluences for particles with  Energy >10 keV
        man->FillNtupleIColumn(0,0,G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID());
        man->FillNtupleDColumn(0,1,xi);
        man->FillNtupleDColumn(0,2,yi);
        man->FillNtupleDColumn(0,3,i*fRunAction->stepforfluence);
        man->FillNtupleDColumn(0,4,En);
        man->FillNtupleIColumn(0,5,mytrack->GetDefinition()->GetPDGEncoding());
        man->FillNtupleSColumn(0,6,mytrack->GetDefinition()->GetParticleName());
        man->FillNtupleSColumn(0,7,mytrack->GetMaterial()->GetName());
        man->AddNtupleRow(0);
       }
      }
    }
  };

  G4VPhysicalVolume* volume  = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  if (fScoringVolumes.size() == 0) {
      const DetectorConstruction* detConstruction = static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
      fScoringVolumes = detConstruction->GetScoringVolumes();
  };

  for (uint i = 0; i<fScoringVolumes.size(); i++){
    if (volume == fScoringVolumes.at(i)){
        fEventAction->AddEdep(edepStep,i);
    };
    if (volume->GetMotherLogical()){
      if ((volume->GetMotherLogical()->GetName() != "World") && (volume->GetMotherLogical()->GetName() == fScoringVolumes.at(i)->GetLogicalVolume()->GetName())){
          fEventAction->AddEdep(edepStep,i);
      };
    };
  };

}
