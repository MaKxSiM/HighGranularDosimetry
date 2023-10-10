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
/// \file ActionInitialization.cc
/// \brief Implementation of the B1::ActionInitialization class

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "MyRunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "MyTrackingAction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyActionInitialization::MyActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyActionInitialization::~MyActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyActionInitialization::BuildForMaster() const
{
   MyRunAction* runAction = new MyRunAction();
   SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyActionInitialization::Build() const
{
  PrimaryGeneratorAction* generatorAction = new PrimaryGeneratorAction;
  SetUserAction(generatorAction);

  MyRunAction* runAction = new MyRunAction();
  SetUserAction(runAction);

  EventAction* eventAction = new EventAction(runAction,generatorAction);
  SetUserAction(eventAction);

  MyTrackingAction* trackingAction = new MyTrackingAction(runAction,eventAction);
  SetUserAction(trackingAction);

  SetUserAction(new MySteppingAction(runAction,eventAction));
}
