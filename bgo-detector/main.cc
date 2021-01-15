#include <DetectorConstruction.hh>
#include <PrimaryGeneratorAction.hh>
#include <G4VisManager.hh>
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>
#include <G4UImanager.hh>
#include <random>
#include <dlfcn.h>
#include "G4RunManager.hh"
#include "Utils.hh"
#include "ActionInitialization.hh"
#include "PhysicsList.hh"
#include "fstream"
#include "Messenger.hh"

long init_seed(){
    std::random_device rd;
    std::uniform_int_distribution<long> uid(0, LONG_MAX);
    return uid(rd);
}

int main(int argc, char **argv) {
    auto settings = new Settings;
    auto messenger = new Messenger(settings);

    // Get the pointer to the User Interface manager
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if (argc > 1){
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    std::ofstream* flog = new std::ofstream;
    flog->open("bgo.log");
    auto logger = Logger::instance();
    logger->setOutput(flog);
    time_t seconds = time(NULL);

    long seed = (settings->seed == -1) ? init_seed() : settings->seed;
    CLHEP::HepRandom::setTheSeed(seed);


    G4RunManager *runManager = new G4RunManager;
    runManager->SetUserInitialization(new DetectorConstruction(settings));
    runManager->SetUserInitialization(new PhysicsList(settings));
    runManager->SetUserInitialization(new ActionInitialization(settings));
    runManager->SetNumberOfAdditionalWaitingStacks(4);
    runManager->Initialize();





    // Process macro or start UI session
    //
    if (argc > 2) {
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[2];
        UImanager->ApplyCommand(command + fileName);
    } else {
        G4VisManager *visManager = new G4VisExecutive;
        visManager->Initialize();
        // interactive mode
        G4UIExecutive *ui =  new G4UIExecutive(argc, argv);
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
        delete visManager;
    }


    delete runManager;
    time_t secondsEnd = time(NULL);
    logger->print("Time of simulation in seconds: " + std::to_string(secondsEnd - seconds));
    logger->print("The end.");
    flog->close();
    return 0;
}



