//
// Created by zelenyy on 8/5/20.
//

#include "DetectorConstruction.hh"
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>
#include <G4UniformElectricField.hh>
#include <G4EqMagElectricField.hh>
#include <G4DormandPrince745.hh>
#include <G4MagIntegratorDriver.hh>
#include <G4ChordFinder.hh>
#include "G4Tubs.hh"
#include "G4FieldManager.hh"

using namespace CLHEP;

namespace ISA {
    const G4double t0 = 288.15 * kelvin;
    const G4double temperatureGrad = -0.0065 * kelvin / m; //температурный градиент
    const G4double p0 = 101325 * pascal;
    const G4double g = 9.80665 * m / (s * s);
    const G4double M = 0.0289644 * kg / mole;
    const G4double R = 8.31447 * joule / (kelvin * mole);
};

DetectorConstruction::DetectorConstruction(Settings *settings) : settings(settings){
}

G4VPhysicalVolume *DetectorConstruction::Construct() {
    G4bool checkOverlaps = true;
    double worldSize = settings->length + 100*meter;
    G4Tubs* solidWorld = new G4Tubs("world", 0.0, 5.0*kilometer,0.5*worldSize, 0, twopi);
    auto material = createAirForHeight(settings->height);
    auto logicWorld = new G4LogicalVolume(solidWorld, material, "world");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "world",
            0, false, 0, checkOverlaps);

    double cloudSize = settings->length;
    G4Tubs* solidCloud = new G4Tubs("cloud", 0.0, 5.0*kilometer,0.5*cloudSize, 0, twopi);
    cloud = new G4LogicalVolume(solidCloud, material, "cloud");
    G4VPhysicalVolume *physCloud = new G4PVPlacement(0, G4ThreeVector(), cloud, "cloud",
                                                     logicWorld, false, 0, checkOverlaps);


    return physWorld;
}

void DetectorConstruction::ConstructSDandField() {
    G4VUserDetectorConstruction::ConstructSDandField();
    G4ElectricField *fEMfield = new G4UniformElectricField(
            G4ThreeVector(0.0, 0.0, settings->field));
    auto *equation = new G4EqMagElectricField(fEMfield);
    G4int nvar = 8;
    auto fStepper = new G4DormandPrince745(equation, nvar);
    auto *fieldManager = new G4FieldManager();
    cloud->SetFieldManager(fieldManager, true);
    fieldManager->SetDetectorField(fEMfield);
    G4double fMinStep;  // minimal step
    fMinStep = 0.01 * mm; // minimal step
    auto integrationDriver = new G4MagInt_Driver(
            fMinStep,
            fStepper,
            fStepper->GetNumberOfVariables()
    );
    auto fChordFinder = new G4ChordFinder(integrationDriver);
    fieldManager->SetChordFinder(fChordFinder);
}


G4double DetectorConstruction::countPressure(G4double height) {
    G4double temperature = countTemperature(height);
    G4double pressure = ISA::p0 * exp(-1 * ISA::M * ISA::g * height / (ISA::R * temperature));
    return pressure;
}

G4double DetectorConstruction::countDensity(G4double height) {
    G4double temperature = countTemperature(height);
    G4double pressure = countPressure(height);
    G4double density = pressure * ISA::M / (ISA::R * temperature);
    return density;
}

G4double DetectorConstruction::countTemperature(G4double height) {
    G4double temperature = ISA::t0 + ISA::temperatureGrad * height;
    return temperature;
}

G4Material *DetectorConstruction::createAirForHeight(G4double height) {
    G4NistManager *nistManager = G4NistManager::Instance();
    G4Material *air = nistManager->FindOrBuildMaterial("G4_AIR");
    const G4double density = countDensity(height);
    const G4double pressure = countPressure(height);
    const G4double temperature = countTemperature(height);
    std::string name = "_" + std::to_string((int) ceil(height / meter));
    Logger::instance()->print("airHeight" + name);
    Logger::instance()->print("Density: " + std::to_string(density / (kg / m3)) + " kg/m3");
    Logger::instance()->print("Pressure: " + std::to_string(pressure / pascal) + " pascal");
    Logger::instance()->print("Temperature: " + std::to_string(temperature / kelvin) + " kelvin");
    G4Material *airHeight = new G4Material("airHeight" + name, density, air,
                                           kStateGas, temperature, pressure);
    return airHeight;
}