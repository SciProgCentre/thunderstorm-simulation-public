//
// Created by zelenyy on 8/14/20.
//

#ifndef THUNDERSTORM_SIMULATION_PUBLIC_RUNACTION_HH
#define THUNDERSTORM_SIMULATION_PUBLIC_RUNACTION_HH

#include "G4UserRunAction.hh"
#include "Utils.hh"
#include "Output.hh"
#include "fstream"

class RunAction : public G4UserRunAction{
private:
    Settings* settings;

public:

    RunAction(Settings* settings) : settings(settings){};

    void BeginOfRunAction(const G4Run *aRun) override;

    void EndOfRunAction(const G4Run *aRun) override;

private:
    void printSettingsInLog();

};

void RunAction::BeginOfRunAction(const G4Run *aRun) {
    G4UserRunAction::BeginOfRunAction(aRun);
    printSettingsInLog();

}

void RunAction::EndOfRunAction(const G4Run *aRun) {
    G4UserRunAction::EndOfRunAction(aRun);
}

void RunAction::printSettingsInLog() {
    auto logger = Logger::instance();
    std::string text = "Start run with ";
    logger->print(text + "size = " + std::to_string(settings->size/CLHEP::millimeter) + " mm" );
}

#endif //THUNDERSTORM_SIMULATION_PUBLIC_RUNACTION_HH
