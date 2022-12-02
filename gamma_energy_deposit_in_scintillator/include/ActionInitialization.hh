//
// Created by zelenyy on 8/5/20.
//

#ifndef THUNDERSTORM_SIMULATION_PUBLIC_ACTIONINITIALIZATION_HH
#define THUNDERSTORM_SIMULATION_PUBLIC_ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "Settings.hh"

class ActionInitialization : public G4VUserActionInitialization{
public:
    void Build() const override {
        auto gps = new PrimaryGeneratorAction();
        SetUserAction(gps);
    }
};

#endif //THUNDERSTORM_SIMULATION_PUBLIC_ACTIONINITIALIZATION_HH
