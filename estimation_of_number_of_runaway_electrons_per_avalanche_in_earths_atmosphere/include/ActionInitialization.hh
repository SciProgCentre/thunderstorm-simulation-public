//
// Created by zelenyy on 8/5/20.
//

#ifndef THUNDERSTORM_SIMULATION_PUBLIC_ACTIONINITIALIZATION_HH
#define THUNDERSTORM_SIMULATION_PUBLIC_ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "StackingAction.hh"
#include "RunAction.hh"
#include "TrackingAction.hh"
#include "EventAction.hh"

class ActionInitialization : public G4VUserActionInitialization{
private:
    Settings* settings;
public:
    explicit ActionInitialization(Settings* settings) : settings(settings){

    }

    void Build() const override {
        auto gps = new PrimaryGeneratorAction();
        SetUserAction(gps);
        auto stacking = new StackingAction(settings);
        SetUserAction(stacking);
        auto data = new CloudList();
        auto runAction = new RunAction(settings, data);
        SetUserAction(runAction);
        auto eventAction = new EventAction(settings, data);
        SetUserAction(eventAction);
        auto trackingAction = new TrackingAction(settings, data);
        SetUserAction(trackingAction);
    }
};

#endif //THUNDERSTORM_SIMULATION_PUBLIC_ACTIONINITIALIZATION_HH
