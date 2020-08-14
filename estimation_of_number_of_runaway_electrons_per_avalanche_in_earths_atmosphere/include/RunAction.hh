//
// Created by zelenyy on 8/14/20.
//

#ifndef THUNDERSTORM_SIMULATION_PUBLIC_RUNACTION_HH
#define THUNDERSTORM_SIMULATION_PUBLIC_RUNACTION_HH

#include "G4UserRunAction.hh"
#include "Utils.hh"

class RunAction : public G4UserRunAction{
private:
    Settings* settings;
public:

    explicit RunAction(Settings* settings) : settings(settings){};

    void BeginOfRunAction(G4Run *aRun) override;

    void EndOfRunAction(G4Run *aRun) override;

};

void RunAction::BeginOfRunAction(G4Run *aRun) {
    G4UserRunAction::BeginOfRunAction(aRun);

}

void RunAction::EndOfRunAction(G4Run *aRun) {
    G4UserRunAction::EndOfRunAction(aRun);
}

#endif //THUNDERSTORM_SIMULATION_PUBLIC_RUNACTION_HH
