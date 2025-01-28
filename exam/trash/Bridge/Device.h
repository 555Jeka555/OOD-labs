#ifndef EXAM_DEVICE_H
#define EXAM_DEVICE_H

class Device {
public:
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual void setVolume(int volume) = 0;
    virtual ~Device() = default;
};

#endif //EXAM_DEVICE_H
