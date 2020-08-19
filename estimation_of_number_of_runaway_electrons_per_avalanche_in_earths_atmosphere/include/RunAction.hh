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
    CloudList* data;
    std::ofstream* fout;
public:

    RunAction(Settings* settings, CloudList* data) : settings(settings), data(data){};

    void BeginOfRunAction(const G4Run *aRun) override;

    void EndOfRunAction(const G4Run *aRun) override;

private:
    void printSettingsInLog();

};

void RunAction::BeginOfRunAction(const G4Run *aRun) {
    G4UserRunAction::BeginOfRunAction(aRun);
    printSettingsInLog();
    fout = new std::ofstream;
    fout->open(settings->output,  std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);
    data->initializeRun(fout);

}

void RunAction::EndOfRunAction(const G4Run *aRun) {
    G4UserRunAction::EndOfRunAction(aRun);
    data->finishRun();
    fout->close();
}

void RunAction::printSettingsInLog() {
    auto logger = Logger::instance();
    std::string text = "Start run with ";
    logger->print(text + "field = " + std::to_string(settings->field/ (CLHEP::kilovolt/CLHEP::meter)) + "kV/m" );
}

#endif //THUNDERSTORM_SIMULATION_PUBLIC_RUNACTION_HH
