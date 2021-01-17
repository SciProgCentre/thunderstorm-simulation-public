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
    std::string seed_path = root_path + "seed";
    std::string size_path = thunderstorm_path + "size";
    std::string length_path = thunderstorm_path + "length";

    G4UIdirectory * npm;
    G4UIdirectory * thunderstorm;

    G4UIcmdWithAnInteger *seed;
    G4UIcmdWithADoubleAndUnit* size;
    G4UIcmdWithADoubleAndUnit* length;

};


#endif //THUNDERSTORM_SIMULATION_PUBLIC_MESSENGER_HH
