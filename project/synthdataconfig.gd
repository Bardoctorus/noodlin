extends Node2D


#INIT AND UPDATE: float _sampleRate, int _wavetableType, int _numOscillators
# here we can add number of LFOs too


var SampleRate: float = 44100.0
var BitRate: int = 16
enum WAVETYPE {SINE, SAWUP, SAWDOWN, SQUARE, TRIANGLE}
@export var Wave: WAVETYPE

var Sine: String = "Sine"
var SawUp: String = "SawUp"
var SawDown: String = "SawDown"
var Square: String = "Square"
var Triangle: String = "Triangle"
var DetuneAmount: String = "DetuneAmount"
var LFOFreq: String = "LFOFreq"
var LFOAmount: String = "LFOAmount"


var Voices: Array[String]
var NumberOfLFOs: int = 1



func setVoices(voices):
	for v in voices:
		Voices.push_back(v)
