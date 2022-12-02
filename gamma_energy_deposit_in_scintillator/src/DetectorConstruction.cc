//
// Created by zelenyy on 8/5/20.
//

#include "DetectorConstruction.hh"
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>
#include <G4Box.hh>
#include <G4SDManager.hh>
#include <G4Tubs.hh>
#include "SensitiveScoredDetector.hh"
using namespace CLHEP;


DetectorConstruction::DetectorConstruction(Settings *settings) : settings(settings) {
}

G4VPhysicalVolume *DetectorConstruction::Construct() {
    G4bool checkOverlaps = true;
    G4NistManager *man = G4NistManager::Instance();
    double worldSize = 4 * settings->scnt_position_z;
    G4Box *solidWorld = new G4Box("world", 0.5 * worldSize, 0.5 * worldSize, 0.5 * worldSize);
    auto vacuum = man->FindOrBuildMaterial("G4_Galactic");
    auto detMaterial = man->FindOrBuildMaterial(settings->scnt_material);
    auto attMaterial = man->FindOrBuildMaterial(settings->att_material);
    auto lead = man->FindOrBuildMaterial("G4_Pb");

    auto logicWorld = new G4LogicalVolume(solidWorld, vacuum, "world");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "world",0, false, 0, checkOverlaps);

    if (settings->att_length != 0.0){
        auto *solidAtt = new G4Tubs("att", 0.0, settings->att_radius, 0.5*settings->att_length, 0.0, twopi);
        auto logAtt = new G4LogicalVolume(solidAtt, attMaterial, "bgo");
        G4VPhysicalVolume *physAtt = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, settings->att_position_z), logAtt, "att", logicWorld, false, 0, checkOverlaps);
    }


    auto *solidScnt = new G4Tubs("scnt", 0.0, settings->scnt_radius, 0.5*settings->scnt_length, 0.0, twopi);
    det_vol = new G4LogicalVolume(solidScnt, detMaterial, "scnt");
    G4VPhysicalVolume *physCube = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, settings->scnt_position_z), det_vol, "scnt", logicWorld, false, 0, checkOverlaps);

    if (settings->wall){
        auto solidWall = new G4Tubs("wall", 0.0, settings->scnt_radius, 0.5*settings->scnt_length, 0.0, twopi);
        auto logWall = new G4LogicalVolume(solidWall, attMaterial, "bgo");
        G4VPhysicalVolume *physWall = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, settings->scnt_position_z+settings->scnt_length), logWall, "att", logicWorld, false, 0, checkOverlaps);

    }
    return physWorld;
}

void DetectorConstruction::ConstructSDandField() {
    G4VUserDetectorConstruction::ConstructSDandField();
    G4SDManager *fSDM = G4SDManager::GetSDMpointer();
    auto det = new SensitiveScoredDetector("SensitiveScoredDetector", settings);
    fSDM->AddNewDetector(det);
    det_vol->SetSensitiveDetector(det);
}
