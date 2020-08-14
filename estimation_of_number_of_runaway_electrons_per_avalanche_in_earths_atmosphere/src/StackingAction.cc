//
// Created by zelenyy on 8/5/20.
//

#include "StackingAction.hh"
#include "G4Gamma.hh"
#include <G4Electron.hh>
#include <G4Positron.hh>

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track *aTrack) {
    if (aTrack->GetParentID() == 0){
        return fUrgent;
    }

    if (aTrack->GetKineticEnergy() < cut){
        return fKill;
    }


    if (aTrack->GetDefinition() == G4Gamma::Definition()){
        if (settings->disableGamma){
            return fKill;
        }
        else if (aTrack->GetKineticEnergy() < 0.08*MeV){
            return fUrgent;
        }
        else if (aTrack->GetKineticEnergy() < 0.5*MeV){
            return fWaiting_1;
        }
        else{
        return fWaiting_2;
        }
    }
    else if (aTrack->GetDefinition() == G4Electron::Definition()){
        if (aTrack->GetKineticEnergy() < 0.08 * MeV) {
            return fWaiting;
        } else{
            return fWaiting_3;
        }
    }
    else if (aTrack->GetDefinition() == G4Positron::Definition()){
        if (settings->disablePositron){
            return fKill;
        }
        else {
            return fWaiting_4;
        }
    }

    return G4UserStackingAction::ClassifyNewTrack(aTrack);
}

StackingAction::StackingAction(Settings *settings) : settings(settings){

}
