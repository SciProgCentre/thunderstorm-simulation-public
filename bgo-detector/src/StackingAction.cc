//
// Created by zelenyy on 8/5/20.
//

#include "StackingAction.hh"
#include "G4Gamma.hh"
#include <G4Electron.hh>
#include <G4Positron.hh>

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track *aTrack) {
    if (aTrack->GetParentID() == 0){
        std::cout<<aTrack->GetKineticEnergy()/MeV<<std::endl;
        return fUrgent;
    }
    return G4UserStackingAction::ClassifyNewTrack(aTrack);
}

StackingAction::StackingAction(Settings *settings) : settings(settings){
}
