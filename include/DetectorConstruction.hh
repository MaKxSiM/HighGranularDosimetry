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


#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4UserLimits.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4PVPlacement.hh"
#include "G4HumanPhantomMaterial.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;

/// Detector construction class to define materials and geometry.


class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction() override;

    G4VPhysicalVolume* Construct() override;

    std::vector<G4VPhysicalVolume*> GetScoringVolumes() const { return fScoringVolumes; }

// Detector parameters


    const G4double cell_size_XY = 0.1*cm, cell_size_Z = 1.0*cm;
    const G4double env_sizeXY = 6*cm, env_sizeZ = 8*cm;
    //const G4double sc_vol_st = 1.0*cm;
    const G4ThreeVector pos2 = G4ThreeVector(0, 0, 0.0*cm);
    G4double world_sizeXY = 1.2*env_sizeXY;
    G4double world_sizeZ  = 1.2*env_sizeZ;

//========platic A-150-tissue  with incorporated Bi particles =======================
    const G4String env_mat_name = "G4_WATER";
    const G4String world_mat_name = "G4_AIR";
    const G4String Admixture_name = "G4_Bi";
    //const G4String Tissue_name = "G4_A-150_TISSUE";
    const G4String Tissue_name = "soft_tissue"; //soft tissues from G4HumanPhantomMaterial

    const G4String TissueWithAdmixture_name = "TissueWithAdmixture";

    //G4double  rho_tissue= 1.00*g/cm3; //this is just water
    G4double  rho_tissue= 0.9869*g/cm3; //soft tissue
    G4double  rho_admix = 9.79*g/cm3;
    G4double admix_c = 10000*mg/L; //concetration in  mg per Litre ++ as per Kolobov++++
    //G4double admix_c = 3000000*mg/L; //half of the plate from Bi  ++++test++++
    //G4double admix_c = 9790000*mg/L; //100% of the plate from Bi  ++++test++++

    G4Material* TissueWithAdmixture;
    G4Material* Tissue;
    G4Material* Admixture;
  //  G4Material* soft;
//==================================================================================




//

    //G4Material* shape2_mat;

    G4Material* env_mat;
    G4Material* world_mat;
    G4LogicalVolume* logicEnv,*logicWorld,*logicShape2,*logictempl,*logictemp_pl_plate;
    G4VPhysicalVolume* physEnv;
    G4bool checkOverlaps = true;
    std::vector<G4double> vPos_X;
    std::vector<G4double> vPos_Y;
    std::vector<G4double> vPos_Z;


  private:
    G4UserLimits* fStepLimit = nullptr;
    void ConstructScoringVolumes();

  protected:
    std::vector<G4VPhysicalVolume*> fScoringVolumes {};
    G4int N_vol;
};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
