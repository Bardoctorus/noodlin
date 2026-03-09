extends MarginContainer

@export var GuiAddedOscList: VBoxContainer
@export var GuiAddedOsc: PackedScene
@export var SynthConfigDropdown: OptionButton
@export var UserWeightFeedback: Label

var selectedOsc: String
var userWeight: float





func _on_ynth_config_add_osc_button_button_down():
	print("Osc: ", selectedOsc," Weight: ", userWeight, " - ", typeof(userWeight))
	var newOsc = GuiAddedOsc.instantiate()
	newOsc.call("setType", selectedOsc)
	newOsc.call("setWeight", userWeight)
	GuiAddedOscList.add_child(newOsc)
	

func _on_ynth_config_osc_wave_dropdown_item_selected(index):
	selectedOsc = SynthConfigDropdown.get_item_text(index)




func _on_ynth_config_osc_weight_box_value_changed(value):
	userWeight = value
	UserWeightFeedback.text = str(value)
	
