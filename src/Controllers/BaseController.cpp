#include "BaseController.h"

void BaseController::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("init", "_sampleRate", "_wavetableType", "_numOscillators"), &BaseController::init);
	godot::ClassDB::bind_method(D_METHOD("update", "_sampleRate", "_wavetableType", "_numOscillators"), &BaseController::update);
	godot::ClassDB::bind_method(D_METHOD("getAmplitude"), &BaseController::getAmplitude);
	godot::ClassDB::bind_method(D_METHOD("setAmplitude", "_amplitude"), &BaseController::setAmplitude);
	godot::ClassDB::bind_method(D_METHOD("getFrequency"), &BaseController::getFrequency);
	godot::ClassDB::bind_method(D_METHOD("setFrequency", "_frequency"), &BaseController::setFrequency);
	godot::ClassDB::bind_method(D_METHOD("updateModifiers", "modifiers"), &BaseController::updateModifiers);
	godot::ClassDB::bind_method(D_METHOD("isCurrentlyPlaying"), &BaseController::isCurrentlyPlaying);
	godot::ClassDB::bind_method(D_METHOD("start"), &BaseController::start);
	godot::ClassDB::bind_method(D_METHOD("stop"), &BaseController::stop);
	godot::ClassDB::bind_method(D_METHOD("process", "playback"), &BaseController::process);
}

BaseController::BaseController() {
	amplitude = 0.0f;
	frequency = 440.0f;
	currentlyPlaying = false;
}

BaseController::~BaseController() {
}

void BaseController::init(float _sampleRate, int _wavetableType, int _numOscillators) {
	//ugly as fuck but testing is testing.
	//in future init can be more selective over what it actually generates
	wavetableGen.instantiate();
	sineWavetable = wavetableGen->createStandardWavetable(0);
	sawUpWavetable = wavetableGen->createStandardWavetable(1);
	sawDownWavetable = wavetableGen->createStandardWavetable(2);
	squareWavetable = wavetableGen->createStandardWavetable(3);
	triangleWavetable = wavetableGen->createStandardWavetable(4);

	print_line("gen saw table:", sawDownWavetable);

	for (size_t i = 0; i < _numOscillators; i++) {
		Ref<Oscillator> oscInit;
		oscInit.instantiate();
		oscInit->reset(i, sawDownWavetable, _wavetableType, _sampleRate);
		oscillators.push_back(oscInit);
		print_line("instantiated osc: ", i);
	}
}

void BaseController::update(float _sampleRate, int _wavetableType, int _numOscillators) {
	if (currentlyPlaying)
		stop();

	for (size_t i = 0; i < _numOscillators; i++) {
		oscillators.clear();
		Ref<Oscillator> oscUpdate;
		oscUpdate.instantiate();
		oscUpdate->reset(i, sineWavetable, _wavetableType, _sampleRate);
        oscillators.push_back(oscUpdate);
	}
    print_line("updated: ",oscillators.size(),"oscillators now");
    start();
}

float BaseController::getAmplitude() const {
	return amplitude;
}

void BaseController::setAmplitude(float _amplitude) {
	amplitude = _amplitude;
}

float BaseController::getFrequency() const {
	return frequency;
}

void BaseController::setFrequency(float _frequency) {
	frequency = _frequency;
	for (size_t i = 0; i < oscillators.size(); i++) {
		Ref<Oscillator> osc = Ref<Oscillator>(Object::cast_to<Oscillator>(oscillators[i]));
		osc->setFrequency(frequency);
	}
}

void BaseController::updateModifiers(Dictionary modifiers) {
	
	Array parameter = modifiers.keys();
	for (size_t i = 0; i < parameter.size(); i++)
	{
		//switch here probably better
		if (parameter[i] == "DetuneAmount"){
			print_line("modifiers position " , i , parameter[i],": ",modifiers[parameter[i]]);
		}
		if (parameter[i] == "LFOFreq"){
			print_line("modifiers position " , i , parameter[i],": ",modifiers[parameter[i]]);
		}
		if (parameter[i] == "LFOAmount"){
			print_line("modifiers position " , i , parameter[i],": ",modifiers[parameter[i]]);
		}
	}
	print_line("modifers size: ",modifiers.size());
	
	
}

bool BaseController::isCurrentlyPlaying() const {
	return currentlyPlaying;
}

void BaseController::start() {
	for (size_t i = 0; i < oscillators.size(); i++) {
		Ref<Oscillator> osc = Ref<Oscillator>(Object::cast_to<Oscillator>(oscillators[i]));
		osc->start();
		currentlyPlaying = true;
	}
}

void BaseController::stop() {
	for (size_t i = 0; i < oscillators.size(); i++) {
		Ref<Oscillator> osc = Ref<Oscillator>(Object::cast_to<Oscillator>(oscillators[i]));
		osc->stop();
		currentlyPlaying = false;
	}
}

void BaseController::process(Ref<AudioStreamGeneratorPlayback> playback) {
	PackedVector2Array bbuffer;

	for (int i = 0; i < playback->get_frames_available(); ++i) {
		float sample = 0;
		for (size_t i = 0; i < oscillators.size(); i++) {
			Ref<Oscillator> osc = Ref<Oscillator>(Object::cast_to<Oscillator>(oscillators[i]));

			if (osc->isCurrentlyPlaying()) {
				sample += osc->getNextSample();
			}
		}

		bbuffer.push_back(Vector2(sample, sample));
	}
	playback->push_buffer(bbuffer);
}
