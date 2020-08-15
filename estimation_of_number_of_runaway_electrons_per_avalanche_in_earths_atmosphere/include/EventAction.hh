//
// Created by zelenyy on 14.08.2020.
//

#ifndef THUNDERSTORM_SIMULATION_PUBLIC_EVENTACTION_HH
#define THUNDERSTORM_SIMULATION_PUBLIC_EVENTACTION_HH

#include "G4UserEventAction.hh"

class EventAction : public G4UserEventAction{
private:
    Settings* settings;
    CloudList* data;
public:

    EventAction(Settings* settings, CloudList* data) : settings(settings), data(data){};

    void BeginOfEventAction(const G4Event *anEvent) override {
        G4UserEventAction::BeginOfEventAction(anEvent);
        data->initializeEvent(anEvent->GetEventID());
    }

    void EndOfEventAction(const G4Event *anEvent) override {
        G4UserEventAction::EndOfEventAction(anEvent);
        data->finishEvent();
    }

public:

};

#endif //THUNDERSTORM_SIMULATION_PUBLIC_EVENTACTION_HH
