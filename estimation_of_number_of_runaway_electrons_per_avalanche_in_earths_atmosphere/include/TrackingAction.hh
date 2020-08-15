//
// Created by zelenyy on 8/14/20.
//

#ifndef THUNDERSTORM_SIMULATION_PUBLIC_TRACKINGACTION_HH
#define THUNDERSTORM_SIMULATION_PUBLIC_TRACKINGACTION_HH

#include "G4UserTrackingAction.hh"

class TrackingAction : public G4UserTrackingAction {
private:
    Settings* settings;
    CloudList* data;
public:

    TrackingAction(Settings* settings, CloudList* data) : settings(settings), data(data){};

    void PreUserTrackingAction(const G4Track *track) override;

    void PostUserTrackingAction(const G4Track *track) override;

public:
};

void TrackingAction::PreUserTrackingAction(const G4Track *track) {
    G4UserTrackingAction::PreUserTrackingAction(track);
    data->addTrack(track);
}

void TrackingAction::PostUserTrackingAction(const G4Track *track) {
    G4UserTrackingAction::PostUserTrackingAction(track);
}

#endif //THUNDERSTORM_SIMULATION_PUBLIC_TRACKINGACTION_HH
