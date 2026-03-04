extends Node

class_name Util

enum WaveTables{Sine,Square,Saw,Triangle}

func fillWaveTable(type: WaveTables = Util.WaveTables.Sine, wavetablesize:int = 64) -> Array:
	var wavetableArray: Array[float] = []
	match(type):
		WaveTables.Sine:
			for i in wavetablesize:
				wavetableArray.push_back(sin(TAU * (i as float / wavetablesize)))
			print("Generated Sine wavetable of length ", wavetablesize)
		WaveTables.Square:
			for i in wavetablesize:
				i = 1.0 if (sin(TAU * i as float / wavetablesize) >= 0.0) else -1.0
				wavetableArray.push_back(i) 
			print("Generated Square wavetable of length ", wavetablesize)
		WaveTables.Saw:
			for i in wavetablesize:
				wavetableArray.push_back(2.0 * (i as float / wavetablesize) - 1.0)
			print("Generated Saw wavetable of length ", wavetablesize)
		WaveTables.Triangle:
			for i in wavetablesize:
				wavetableArray.push_back(1 - absf((i as float / wavetablesize)- 0.5) *4)
			print("Generated Triangle wavetable of length ", wavetablesize)
		_:
			print("Invalid Wavetable Type: You shouldn't be able to get here you fucked up")
	
	return wavetableArray
