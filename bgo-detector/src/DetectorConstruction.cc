//
// Created by zelenyy on 8/5/20.
//

#include "DetectorConstruction.hh"
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>
#include <G4Box.hh>
#include <G4SDManager.hh>
#include "SensitiveScoredDetector.hh"
using namespace CLHEP;


DetectorConstruction::DetectorConstruction(Settings *settings) : settings(settings) {
}

G4VPhysicalVolume *DetectorConstruction::Construct() {
    G4bool checkOverlaps = true;
    G4NistManager *man = G4NistManager::Instance();
    double worldSize = 3 * max(settings->size, settings->length);
    G4Box *solidWorld = new G4Box("world", 0.5 * worldSize, 0.5 * worldSize, 0.5 * worldSize);
    auto vacuum = man->FindOrBuildMaterial("G4_Galactic");
    auto material = man->FindOrBuildMaterial(settings->material);
    auto logicWorld = new G4LogicalVolume(solidWorld, vacuum, "world");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "world",0, false, 0, checkOverlaps);

    double size = settings->size;
    G4Box *solidCube = new G4Box("bgo", 0.5 * size, 0.5 * size, 0.5 * settings->length);
    bgo_vol = new G4LogicalVolume(solidCube, material, "bgo");
    G4VPhysicalVolume *physCube = new G4PVPlacement(0, G4ThreeVector(), bgo_vol, "bgo", logicWorld, false, 0, checkOverlaps);


    return physWorld;
}

void DetectorConstruction::ConstructSDandField() {
    G4VUserDetectorConstruction::ConstructSDandField();
    G4SDManager *fSDM = G4SDManager::GetSDMpointer();
    auto det = new SensitiveScoredDetector("SensitiveScoredDetector", settings);
    fSDM->AddNewDetector(det);
    bgo_vol->SetSensitiveDetector(det);
    Logger::instance()->print("Create new detector: SensitiveScoredDetector");
}

