#ifndef EXAM_RADIO_H
#define EXAM_RADIO_H

#include "Device.h"
#include "iostream"

class Radio : public Device {
public:
    void enable() override {
        std::cout << "Radio is enabled" << std::endl;
    }

    void disable() override {
        std::cout << "Radio is disabled" << std::endl;
    }

    void setVolume(int volume) override {
        std::cout << "Radio volume set to " << volume << std::endl;
    }
};

#endif //EXAM_RADIO_H
