#include <DetectorConstruction.hh>
#include <PrimaryGeneratorAction.hh>
#include <G4VisManager.hh>
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>
#include <G4UImanager.hh>
#include <random>
#include "G4RunManager.hh"
#include "Settings.hh"
#include "ActionInitialization.hh"
#include "PhysicsList.hh"

long init_seed(){
    std::random_device rd;
    std::uniform_int_distribution<long> uid(0, LONG_MAX);
    return uid(rd);
}

void read_to_settings(char* filename, Settings* settings){
    std::fstream file;
    file.open(filename, std::ios::in);
    std::string line;

    std::getline(file, line, ' ');
    settings->seed = std::stol(line);
    std::getline(file, settings->output, ' ');

    std::getline(file, line, ' ');
    settings->att_position_z = std::stod(line);
    std::getline(file, line, ' ');
    settings->att_radius = std::stod(line);
    std::getline(file, line, ' ');
    settings->att_length = std::stod(line);
    std::getline(file, settings->att_material, ' ');

    std::getline(file, line, ' ');
    settings->scnt_position_z = std::stod(line);
    std::getline(file, line, ' ');
    settings->scnt_radius = std::stod(line);
    std::getline(file, line, ' ');
    settings->scnt_length = std::stod(line);
    std::getline(file, settings->scnt_material, ' ');

    std::getline(file, line, ' ');
    settings->wall = line == "true";

}

int main(int argc, char **argv) {
    auto settings = new Settings;
    if (argc > 1){
        read_to_settings(argv[1], settings);
    }

    // Get the pointer to the User Interface manager
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    long seed = (settings->seed == -1) ? init_seed() : settings->seed;
    CLHEP::HepRandom::setTheSeed(seed);



    G4RunManager *runManager = new G4RunManager;
    runManager->SetUserInitialization(new DetectorConstruction(settings));
    runManager->SetUserInitialization(new PhysicsList());
    runManager->SetUserInitialization(new ActionInitialization());
    runManager->Initialize();

    // Process macro or start UI session
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
    return 0;
}



