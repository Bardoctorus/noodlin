#include "WavetableGen.h"

void WavetableGen::_bind_methods() {
    godot::ClassDB::bind_method(D_METHOD("createStandardWavetable", "type"), &WavetableGen::createStandardWavetable);
    godot::ClassDB::bind_method(D_METHOD("sine", "i"), &WavetableGen::sine);
    godot::ClassDB::bind_method(D_METHOD("sawUp", "i"), &WavetableGen::sawUp);
    godot::ClassDB::bind_method(D_METHOD("sawDown", "i"), &WavetableGen::sawDown);
    godot::ClassDB::bind_method(D_METHOD("square", "i"), &WavetableGen::square);
    godot::ClassDB::bind_method(D_METHOD("triangle", "i"), &WavetableGen::triangle);
    godot::ClassDB::bind_method(D_METHOD("createCustomWavetable", "values"), &WavetableGen::createCustomWavetable);
    godot::ClassDB::bind_method(D_METHOD("setWavetableLength", "length"), &WavetableGen::setWavetableLength);
    godot::ClassDB::bind_method(D_METHOD("getWavetableLength"), &WavetableGen::getWavetableLength);
  

}

Array WavetableGen::createStandardWavetable(int type) {
    Array GeneratedTable;
    for (size_t i = 0; i < wavetableLength; i++)
    {
        switch(type)
        {
            case 0:
                GeneratedTable.append(sine(i));
            break;
            case 1:
            break;
            case 2:
            break;
            case 3:
            break;
            default:
            break;

        }
    }
    return GeneratedTable;
    

}
float WavetableGen::sine(int i) {
    return sinf(Math_TAU * ((float)i / wavetableLength));

}
float WavetableGen::sawUp(int i) {
    return 0;

}
float WavetableGen::sawDown(int i) {
    return 0;

}
float WavetableGen::square(int i) {
    return 0;

}
float WavetableGen::triangle(int i) {
    return 0;

}

Array WavetableGen::createCustomWavetable(Array values) {
    Array a;
    return a;
}

void WavetableGen::setWavetableLength(int length) {
    wavetableLength = length;
}
int WavetableGen::getWavetableLength() const {
    return wavetableLength;
}