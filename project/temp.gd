extends Node2D

var wavet = WavetableGen.new()
var w: Array


func _ready():
	print(w.size())
	print(w)
	
	wavet.setWavetableLength(64)
	w = wavet.createStandardWavetable(0)
	print(w.size())
	print(w)

	pass
