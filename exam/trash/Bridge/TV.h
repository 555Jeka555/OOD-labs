#ifndef EXAM_TV_H
#define EXAM_TV_H

#include "Device.h"
#include "iostream"

class TV : public Device {
public:
    void enable() override {
        std::cout << "TV is enabled" << std::endl;
    }

    void disable() override {
        std::cout << "TV is disabled" << std::endl;
    }

    void setVolume(int volume) override {
        std::cout << "TV volume set to " << volume << std::endl;
    }
};

#endif //EXAM_TV_H
