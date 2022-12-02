//
// Created by zelenyy on 8/5/20.
//

#ifndef THUNDERSTORM_SIMULATION_PUBLIC_PHYSICSLIST_HH
#define THUNDERSTORM_SIMULATION_PUBLIC_PHYSICSLIST_HH


#include <G4EmStandardPhysics.hh>
#include "G4EmStandardPhysics_option4.hh"
#include "G4VModularPhysicsList.hh"
#include "Settings.hh"

class PhysicsList: public G4VModularPhysicsList
{
public:
    PhysicsList(){
//        auto emPhys = new G4EmStandardPhysics_option4();
        auto emPhys = new G4EmStandardPhysics();
        RegisterPhysics(emPhys);
    };
    ~PhysicsList() override = default;
};

#endif //THUNDERSTORM_SIMULATION_PUBLIC_PHYSICSLIST_HH
