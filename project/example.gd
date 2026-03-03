extends Node

var aud = AudioStreamPlayer.new()

func _ready() -> void:
	var example := ExampleClass.new()
	example.print_type(example)
	addting()


func addting():
	add_child(aud)
	pass
