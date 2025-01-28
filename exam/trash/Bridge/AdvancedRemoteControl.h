#ifndef EXAM_ADVANCEDREMOTECONTROL_H
#define EXAM_ADVANCEDREMOTECONTROL_H

#include "RemoteControl.h"

class AdvancedRemoteControl : public RemoteControl {
public:
    explicit AdvancedRemoteControl(Device* device) : RemoteControl(device) {}

    void mute() {
        if (device) {
            device->setVolume(0); // Устанавливаем громкость на 0
        }
    }
};

#endif //EXAM_ADVANCEDREMOTECONTROL_H
