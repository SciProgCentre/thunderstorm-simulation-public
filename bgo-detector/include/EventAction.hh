//
// Created by zelenyy on 14.08.2020.
//

#ifndef THUNDERSTORM_SIMULATION_PUBLIC_EVENTACTION_HH
#define THUNDERSTORM_SIMULATION_PUBLIC_EVENTACTION_HH

#include "G4UserEventAction.hh"

class EventAction : public G4UserEventAction{
private:
    Settings* settings;
public:

    EventAction(Settings* settings) : settings(settings){};

    void BeginOfEventAction(const G4Event *anEvent) override {
        G4UserEventAction::BeginOfEventAction(anEvent);
        if (anEvent->GetEventID() % 100000 == 0){
            Logger::instance()->print("Start event: " + std::to_string(anEvent->GetEventID()));
        }

    }

    void EndOfEventAction(const G4Event *anEvent) override {
        G4UserEventAction::EndOfEventAction(anEvent);

    }

public:

};

#endif //THUNDERSTORM_SIMULATION_PUBLIC_EVENTACTION_HH
