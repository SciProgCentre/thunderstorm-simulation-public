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

    gamma = new G4UIcmdWithABool(disable_gamma_path.c_str(), this);
    positron = new G4UIcmdWithABool(disable_positron_path.c_str(), this);
    gamma->SetParameterName("flag", false);
    positron->SetParameterName("flag", false);

    height = new G4UIcmdWithADoubleAndUnit(height_path.c_str(), this);
    height->SetGuidance("Set height of cloud");
    height->SetParameterName("height", false);
    height->SetDefaultUnit("m");

    field = new G4UIcmdWithADoubleAndUnit(field_path.c_str(), this);
    field->SetGuidance("Set uniform Z-field in cloud");
    field->SetParameterName("field", false);
    field->SetDefaultUnit("kV/m");

    length = new G4UIcmdWithADoubleAndUnit(length_path.c_str(), this);
    length->SetGuidance("Set length of cloud");
    length->SetParameterName("length", false);
    length->SetDefaultUnit("m");

    cut = new G4UIcmdWithADoubleAndUnit(cut_path.c_str(), this);
    cut->SetGuidance("Set minimal energy of particle");
    cut->SetParameterName("cut", false);
    cut->SetDefaultUnit("MeV");

}

void Messenger::SetNewValue(G4UIcommand *command, G4String newValue) {
    if (command == seed){
        settings->seed = seed->GetNewIntValue(newValue);
    } else if (command == gamma){
        settings->disableGamma = not gamma->GetNewBoolValue(newValue);
    } else if (command == positron){
        settings->disablePositron = not positron->GetNewBoolValue(newValue);
    } else if (command == field){
        settings->field = field->GetNewDoubleValue(newValue);
    }else if (command == field){
        settings->field = field->GetNewDoubleValue(newValue);
    }else if (command == height){
        settings->height = height->GetNewDoubleValue(newValue);
    }else if (command == length){
        settings->length = length->GetNewDoubleValue(newValue);
    }else if (command == cut){
        settings->cut = cut->GetNewDoubleValue(newValue);
    } else {
        G4UImessenger::SetNewValue(command, newValue);
    }

}
