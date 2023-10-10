# MedPhys_pBi

A. How to run
  1. Create a build directory
  mkdir MedPhys_pBi-build

  2. Go there
  cd MedPhys_pBi-build

  3. Run cmake  pointing to install directory of Geant4 and the source of project
  cmake -DGeant4_DIR=/your_path_to/Geant4/geant4-v11.0.3-install/lib/Geant4-11.0.3 /your_path_to_the source_the_project/MedPhys_pBi

  4. make
  
  6. Running in interactive mode
     ./RunGun
    
     In GUI set commands for example
     /control/verbose 2
     /tracking/verbose 2
     /gun/particle proton
     /gun/energy 230 MeV
     /run/beamOn 10
 
  Enjoy!
  
#### Future plans 

Now working with devs. Next goal: make multithreading work properly. If implemented correctly, as I understand, all "t*." files should combine into a single output file. Right now this file is produced but cannot be openned (hint buildformaster() method in ActionInitiallization.cc).   
