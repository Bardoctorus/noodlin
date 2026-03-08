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

WavetableGen::WavetableGen() {
    wavetableLength = 64;
}

WavetableGen::~WavetableGen() {
}


//todo make type human readable with enum or define
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
                GeneratedTable.append(sawUp(i));
            break;
            case 2:
                GeneratedTable.append(sawDown(i));
            break;
            case 3:
                GeneratedTable.append(square(i));
            break;
            case 4:
                GeneratedTable.append(triangle(i));
            break;
            default:
                GeneratedTable.append(0.0f);
                if(i == 0){
                print_line("Unknown standard wavetable type, zeroed table value returned");
                }
            

        }
    }
    return GeneratedTable;
    

}
float WavetableGen::sine(int i) {
    return sinf(Math_TAU * ((float)i / wavetableLength));

}
float WavetableGen::sawUp(int i) {
    return  2.0f * ((float)i / wavetableLength) - 1.0f;


}
float WavetableGen::sawDown(int i) {
    return 2.0f * ((wavetableLength-(float)i) / wavetableLength) - 1.0f;

}
float WavetableGen::square(int i) {
    return sinf(Math_TAU * ((float)i / wavetableLength)) >= 0.0 ? 1.0:-1.0;

}
float WavetableGen::triangle(int i) {
    return 1 - fabs(((float)i / wavetableLength)-0.5f) * 4;

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

