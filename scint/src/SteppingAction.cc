/////////////////////////////////////////////////////////////////////////
//
//
//
// This class collects information at three different levels: 
// 1 - Energy deposited in the sensitive volume (LaBr3 crystal)
// 2 - Number of photons absorbed by the photocathode (or just generated!)
// 3 - Time at which each photon is absorbed
//
// This information is passed to the Event Action Class via 
// the eventAction pointer
//
/////////////////////////////////////////////////////////////////////////

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "G4SteppingManager.hh"
#include "G4ThreeVector.hh"
#include "G4RunManager.hh"

#include "fstream"
#include "iomanip"

using namespace std;	 

SteppingAction::SteppingAction(EventAction* EvAct)
:eventAction(EvAct)
{ }

SteppingAction::~SteppingAction()
{ }

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
	const G4String currentPhysicalName 
    = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName();



    //}
	
	// check if the photon is absorbed in the sensitive volume
    if (currentPhysicalName == "Detector"){
        //const G4String ProcessName =
        //aStep -> GetPostStepPoint() -> GetProcessDefinedStep() -> GetProcessName();
        //if (ProcessName == "OpAbsorption"){
            //eventAction->Energy=aStep->GetPreStepPoint()->GetKineticEnergy();
             //if (FinalEdep>0.) eventAction->Energy=FinalEdep;
        eventAction->X_coor=aStep->GetPreStepPoint()->GetPosition().getX();
        eventAction->Y_coor=aStep->GetPreStepPoint()->GetPosition().getY();
        eventAction->Z_coor=aStep->GetPreStepPoint()->GetPosition().getZ();
        eventAction->Radius=aStep->GetPreStepPoint()->GetPosition().getR();
        eventAction->angle_Phi=aStep->GetPreStepPoint()->GetPosition().getPhi();
        eventAction->angle_Theta=aStep->GetPreStepPoint()->GetPosition().getTheta();


            //eventAction->nAbsPhotons++;
			
            //eventAction->absTime = aStep -> GetPreStepPoint() -> GetGlobalTime();
        //}
	}
}

