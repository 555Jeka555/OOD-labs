#include "TV.h"
#include "Radio.h"
#include "RemoteControl.h"
#include "AdvancedRemoteControl.h"

int main() {
    TV tv;
    Radio radio;

    RemoteControl basicRemote(&tv);
    basicRemote.togglePower(); // Включаем телевизор
    basicRemote.volumeUp();    // Увеличиваем громкость

    AdvancedRemoteControl advancedRemote(&radio);
    advancedRemote.togglePower(); // Включаем радио
    advancedRemote.mute();        // Выключаем звук

    return 0;
}