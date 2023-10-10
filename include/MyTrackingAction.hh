#ifndef MyTrackingAction_h
#define MyTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class G4VPhysicalVolume;


/// Tracking action class
///

class EventAction;
class MyRunAction;

class MyTrackingAction : public G4UserTrackingAction
{
public:
  MyTrackingAction(MyRunAction *runaction,EventAction* eventAction);
  ~MyTrackingAction() override;

  // method from the base class
  void PreUserTrackingAction(const G4Track*) override;
//  void PostUserTrackingAction(const G4Track*) override;

private:
  MyRunAction* fRunAction = nullptr;
  EventAction* fEventAction = nullptr;
};

#endif
