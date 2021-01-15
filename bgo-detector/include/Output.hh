//
// Created by zelenyy on 14.08.2020.
//

#ifndef THUNDERSTORM_SIMULATION_PUBLIC_OUTPUT_HH
#define THUNDERSTORM_SIMULATION_PUBLIC_OUTPUT_HH

#include "iostream"
#include "G4Track.hh"




template <class T>
class ProtoWrapper{
protected:
    T* protoList = nullptr;
    std::ostream* out;
    int count = 0;
    void write(){
        if (protoList != nullptr){
            long size = protoList->ByteSizeLong();
            if (size != 0){
                out->write(reinterpret_cast<char*>(&size), sizeof size);
                protoList->SerializeToOstream(out);
                protoList->Clear();
                count = 0;
            }

        }
    }

public:

    explicit ProtoWrapper()= default;

    virtual void initializeRun(std::ostream* out){
        this->out = out;
        if (protoList != nullptr){
            delete protoList;
        }
        protoList = new T;
    }

    virtual void initializeEvent(int eventID){

    }

    virtual void addTrack(const G4Track* track){
        count++;
        if (count > 100000){
            write();
        }
    };

    virtual void finishEvent(){
        write();
    }

    virtual void finishRun(){
        write();
    }
};

#endif //THUNDERSTORM_SIMULATION_PUBLIC_OUTPUT_HH
