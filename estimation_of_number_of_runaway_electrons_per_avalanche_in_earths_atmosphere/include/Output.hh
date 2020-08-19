//
// Created by zelenyy on 14.08.2020.
//

#ifndef THUNDERSTORM_SIMULATION_PUBLIC_OUTPUT_HH
#define THUNDERSTORM_SIMULATION_PUBLIC_OUTPUT_HH

#include "iostream"
#include "thunderstorm.pb.h"
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

class CloudList : public ProtoWrapper<thunderstorm::CloudList>{
public:
    void initializeEvent(int eventID) override {
        ProtoWrapper::initializeEvent(eventID);
        protoList->set_eventid(eventID);
    }

    void addTrack(const G4Track *track) override {
        auto data = protoList->add_cloud();
        data->set_id(track->GetTrackID());
        data->set_parent_id( track->GetParentID());
        data->set_particle( track->GetDefinition()->GetPDGEncoding());
        data->set_energy(track->GetKineticEnergy() / CLHEP::MeV);
        const G4ThreeVector &momentumDir = track->GetMomentumDirection();
        const G4ThreeVector &position = track->GetPosition();
        data->set_theta(momentumDir.getTheta() / CLHEP::radian);
        data->set_radius(position.perp() / CLHEP::meter);
        data->set_z(position.getZ() / CLHEP::meter);
        data->set_time(track->GetGlobalTime() / CLHEP::ns);
        ProtoWrapper::addTrack(track);
    }
};

#endif //THUNDERSTORM_SIMULATION_PUBLIC_OUTPUT_HH
