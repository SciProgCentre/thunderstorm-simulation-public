//
// Created by zelenyy on 8/5/20.
//

#ifndef THUNDERSTORM_SIMULATION_PUBLIC_STACKINGACTION_HH
#define THUNDERSTORM_SIMULATION_PUBLIC_STACKINGACTION_HH


#include <G4UserStackingAction.hh>
#include <G4SystemOfUnits.hh>
#include "G4Track.hh"
#include "Utils.hh"

class StackingAction : public G4UserStackingAction {
public:
    StackingAction(Settings* settings);
    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track *aTrack) override;

private:
    Settings* settings;
    double cut = 0.05*CLHEP::MeV;
};


#endif //THUNDERSTORM_SIMULATION_PUBLIC_STACKINGACTION_HH
