//
// Created by zelenyy on 8/5/20.
//

#ifndef THUNDERSTORM_SIMULATION_PUBLIC_DETECTORCONSTRUCTION_HH
#define THUNDERSTORM_SIMULATION_PUBLIC_DETECTORCONSTRUCTION_HH


#include <G4VUserDetectorConstruction.hh>
#include "G4LogicalVolume.hh"
#include <G4Material.hh>
#include "Utils.hh"





class DetectorConstruction : public G4VUserDetectorConstruction {
private:
    Settings* settings;
    G4LogicalVolume* cloud;
public:
    explicit DetectorConstruction(Settings* settings);

    G4VPhysicalVolume *Construct() override;

    void ConstructSDandField() override;

    static G4double countDensity(G4double height);

    static G4double countPressure(G4double height);

    static G4double countTemperature(G4double height);

    static G4Material *createAirForHeight(G4double height);

};


#endif //THUNDERSTORM_SIMULATION_PUBLIC_DETECTORCONSTRUCTION_HH
