//
// Created by zelenyy on 8/5/20.
//

#ifndef THUNDERSTORM_SIMULATION_PUBLIC_PRIMARYGENERATORACTION_HH
#define THUNDERSTORM_SIMULATION_PUBLIC_PRIMARYGENERATORACTION_HH

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4GeneralParticleSource.hh>

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
private:
    G4GeneralParticleSource *particleSource;
public:
    PrimaryGeneratorAction(){
        particleSource = new G4GeneralParticleSource();
    };

    ~PrimaryGeneratorAction() override {
        delete particleSource;
    }

    void GeneratePrimaries(G4Event *anEvent) override {
        particleSource->GeneratePrimaryVertex(anEvent);
    }

};

#endif //THUNDERSTORM_SIMULATION_PUBLIC_PRIMARYGENERATORACTION_HH
