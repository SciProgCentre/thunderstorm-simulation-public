//
// Created by zelenyy on 8/5/20.
//

#ifndef THUNDERSTORM_SIMULATION_PUBLIC_UTILS_HH
#define THUNDERSTORM_SIMULATION_PUBLIC_UTILS_HH

#include "G4SystemOfUnits.hh"

using namespace CLHEP;

struct Settings{
    long seed = -1;
    std::string output = "deposit.bin";

    G4double att_position_z = 25*centimeter;
    G4double att_radius = 20.0*millimeter;
    G4double att_length = 0.0*millimeter;
    G4String att_material = "G4_Pb";

    G4double scnt_position_z = 50*centimeter;
    G4double scnt_radius = 20.0*millimeter;
    G4double scnt_length = 25.0*millimeter;
    G4String scnt_material = "G4_SODIUM_IODIDE";

    bool wall = true;

};



#endif //THUNDERSTORM_SIMULATION_PUBLIC_UTILS_HH
