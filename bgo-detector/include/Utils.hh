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
    G4double size = 15.0*CLHEP::millimeter;
    G4double length = 15.0*CLHEP::millimeter;
    G4String material = "G4_BGO";
    std::string output = "deposit.txt";

};

class Logger {
public:

    static Logger* instance(){
        static Logger logger;
        return  &logger;
    }

    ~Logger()= default;

    void print(const std::string& message){
        *clog << getTimeString() << " " << message << std::endl << std::flush;
    };

    static std::string getTimeString() {
        time_t secondsTemp = time(nullptr);
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
    Logger(Logger const&) = delete;
    Logger& operator=(Logger const&) = delete;
    std::ostream* clog;
};


#endif //THUNDERSTORM_SIMULATION_PUBLIC_UTILS_HH
