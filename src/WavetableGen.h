#pragma once

#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/ref_counted.hpp"


using namespace godot;

class WavetableGen : public RefCounted {
    GDCLASS(WavetableGen, RefCounted)

    protected:
        static void _bind_methods();
        int wavetableLength;


    public:
        Array createStandardWavetable(int type);
        float sine(int i);
        float sawUp(int i);
        float sawDown(int i);
        float square(int i);
        float triangle(int i);

        Array createCustomWavetable(Array values);

        void setWavetableLength(int length);
        int getWavetableLength() const;


        

};