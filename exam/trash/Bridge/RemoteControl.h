#ifndef EXAM_REMOTECONTROL_H
#define EXAM_REMOTECONTROL_H

#include "Device.h"

class RemoteControl {
protected:
    Device* device; // Ссылка на реализацию

public:
    explicit RemoteControl(Device* device) : device(device) {}

    void togglePower() {
        if (device) {
            device->enable();
        } else {
            device->disable();
        }
    }

    void volumeUp() {
        if (device) {
            device->setVolume(10); // Увеличиваем громкость
        }
    }

    virtual ~RemoteControl() = default;
};

#endif //EXAM_REMOTECONTROL_H
