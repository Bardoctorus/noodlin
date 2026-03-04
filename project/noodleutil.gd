extends Node

class_name Util

enum WaveTables{Sine,Square,Saw,Triangle}

func fillWaveTable(wavetablesize:int, type: WaveTables) -> Array:
	var wavetableArray: Array[float] = []
	match(type):
		WaveTables.Sine:
			print("Sine")
		WaveTables.Square:
			print("Square")
		WaveTables.Saw:
			print("Saw")
		WaveTables.Triangle:
			print("triangle")
		_:
			print("default")
	
	return wavetableArray
