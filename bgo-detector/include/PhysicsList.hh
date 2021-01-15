//
// Created by zelenyy on 8/5/20.
//

#ifndef THUNDERSTORM_SIMULATION_PUBLIC_PHYSICSLIST_HH
#define THUNDERSTORM_SIMULATION_PUBLIC_PHYSICSLIST_HH


#include "G4EmStandardPhysics_option4.hh"
#include "G4VModularPhysicsList.hh"
#include "Utils.hh"

class PhysicsList: public G4VModularPhysicsList
{
public:
    PhysicsList(Settings* settings){
        auto opt4 = new G4EmStandardPhysics_option4();
        RegisterPhysics(opt4);
    };
    ~PhysicsList() override = default;
};

#endif //THUNDERSTORM_SIMULATION_PUBLIC_PHYSICSLIST_HH
