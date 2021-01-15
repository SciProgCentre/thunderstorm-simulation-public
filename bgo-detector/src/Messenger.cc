//
// Created by zelenyy on 8/10/20.
//

#include <G4UIcmdWithABool.hh>
#include "Messenger.hh"

Messenger::Messenger(Settings *settings) : settings(settings){
    npm = new G4UIdirectory(root_path.c_str());
    thunderstorm = new G4UIdirectory(thunderstorm_path.c_str());

    seed = new G4UIcmdWithAnInteger(seed_path.c_str(), this);
    seed->SetGuidance("Set seed for random engine");
    seed->SetParameterName("seed", true);
    seed->SetDefaultValue(0);


    size = new G4UIcmdWithADoubleAndUnit(size_path.c_str(), this);
    size->SetGuidance("Set size of cube");
    size->SetParameterName("size", false);
    size->SetDefaultUnit("mm");



}

void Messenger::SetNewValue(G4UIcommand *command, G4String newValue) {
    if (command == seed){
        settings->seed = seed->GetNewIntValue(newValue);
    }
     else if (command == size){
        settings->size = size->GetNewDoubleValue(newValue);
    }
    else {
        G4UImessenger::SetNewValue(command, newValue);
    }

}
