#ifndef __SONARIMPL__
#define __SONARIMPL__

#include "Sonar.h"

class SonarImpl : public Sonar
{
    private:
        float distance;
        float temperature;
        float sound_speed;
        int trig_pin;
        int echo_pin;

    public:
        SonarImpl(const int trig_pin, const int echo_pin, const float temperature);
        void sync();
        float getDistance();
};

#endif