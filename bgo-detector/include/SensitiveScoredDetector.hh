//
// Created by zelenyy on 18.10.17.
//

#ifndef GEANT4_THUNDERSTORM_SENSITIVESCOREDDETECTOR_HH
#define GEANT4_THUNDERSTORM_SENSITIVESCOREDDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "iostream"
#include "fstream"
#include "vector"
#include "Utils.hh"

using namespace CLHEP;
using namespace std;

class G4Step;

class G4HCofThisEvent;

class G4TouchableHistory;



class SensitiveScoredDetector : public G4VSensitiveDetector {
public:
    SensitiveScoredDetector(G4String name, Settings *settings): fSettings(settings), G4VSensitiveDetector(name){
        fout = new std::ofstream;
        fout->open(settings->output,  std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);
        logger = Logger::instance();
    };

    void Initialize(G4HCofThisEvent *) override{
        deposit = 0.0;
    };

    G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) override{
        deposit += aStep->GetTotalEnergyDeposit();
    };

    void EndOfEvent(G4HCofThisEvent *) override{
        if (deposit > 0){
            (*fout) << deposit/MeV << endl;
        }

    };

    ~SensitiveScoredDetector(){
        if (fout != nullptr){
            fout->close();
        }
    }
private:
    Settings* fSettings;
    std::ofstream* fout;
    double deposit = 0.0;
    Logger* logger;
};


#endif //GEANT4_THUNDERSTORM_SENSITIVESCOREDDETECTOR_HH
