//
// Created by zelenyy on 8/5/20.
//

#ifndef THUNDERSTORM_SIMULATION_PUBLIC_UTILS_HH
#define THUNDERSTORM_SIMULATION_PUBLIC_UTILS_HH

#include "G4SystemOfUnits.hh"
#include <ctime>
#include <iostream>
#include <string>

struct Settings{
    long seed = -1;
    G4double height = 10.0*CLHEP::kilometer;
    G4double length = 500.0*CLHEP::meter;
    G4double field = 0.0;
    G4double cut = 0.05*CLHEP::MeV;

    bool disableGamma = false;
    bool disablePositron = true;

    std::string output = "thunderstorm";
};

class Logger {
public:

    static Logger* instance(){
        static Logger logger;
        return  &logger;
    }

    ~Logger(){};

    void print(std::string message){
        *clog << getTimeString() << " " << message << std::endl << std::flush;
    };

    std::string getTimeString() {
        time_t secondsTemp = time(NULL);
        tm *timeinfo = localtime(&secondsTemp);
        std::string time(asctime(timeinfo));
        time.pop_back();
        return "[" + time + "]" ;
    };

    void setOutput(std::ostream* stream){clog = stream;};

private:
    Logger(){
        clog = &std::cout;
    };
    Logger(Logger const&);
    Logger& operator=(Logger const&);
    std::ostream* clog;
};


#endif //THUNDERSTORM_SIMULATION_PUBLIC_UTILS_HH
