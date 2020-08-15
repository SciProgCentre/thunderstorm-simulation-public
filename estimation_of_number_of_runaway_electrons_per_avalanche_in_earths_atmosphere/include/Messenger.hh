//
// Created by zelenyy on 8/10/20.
//

#ifndef THUNDERSTORM_SIMULATION_PUBLIC_MESSENGER_HH
#define THUNDERSTORM_SIMULATION_PUBLIC_MESSENGER_HH


#include <G4UImessenger.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4UIcmdWithAnInteger.hh>
#include "G4UImessenger.hh"
#include "Utils.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"



class Messenger : public G4UImessenger {
private:
    Settings* settings;
public:
    explicit Messenger(Settings* settings);

    void SetNewValue(G4UIcommand *command, G4String newValue) override;
private:
    std::string root_path = "/npm/";
    std::string thunderstorm_path = root_path + "thunderstorm/";
    std::string field_path = thunderstorm_path + "field";
    std::string height_path = thunderstorm_path + "height";
    std::string length_path = thunderstorm_path + "length";
    std::string cut_path = thunderstorm_path + "cut";
    std::string seed_path = thunderstorm_path + "seed";
    std::string disable_gamma_path = thunderstorm_path + "gamma";
    std::string disable_positron_path = thunderstorm_path + "positron";



    G4UIdirectory * npm;
    G4UIdirectory * thunderstorm;

    G4UIcmdWithAnInteger *seed;
    G4UIcmdWithABool* gamma;
    G4UIcmdWithABool* positron;
    G4UIcmdWithADoubleAndUnit* field;
    G4UIcmdWithADoubleAndUnit* height;
    G4UIcmdWithADoubleAndUnit* length;
    G4UIcmdWithADoubleAndUnit* cut;
};


#endif //THUNDERSTORM_SIMULATION_PUBLIC_MESSENGER_HH
