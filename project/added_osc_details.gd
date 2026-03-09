extends HBoxContainer

@export var OscTypeLabel: Label
@export var WeightLabel: Label


func setType(oscType):
	OscTypeLabel.text = oscType
	
func setWeight(weight):
	WeightLabel.text = str(weight)
	


func _on_removebutton_button_down():
	queue_free()
	pass
