extends Node2D

var wavet = WavetableGen.new()
var w: Array


func _ready():
	print(w.size())
	print(w)
	
	for i in range(6):
		w = wavet.createStandardWavetable(i)
		print(w.size())
		print(w)

	pass
