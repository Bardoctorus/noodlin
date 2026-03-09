extends AudioNodeTest

@export_range(1, 10) var NumberOfOscillators: int

@export_range(40.0,10000.0) var Frequency = 440.0
var samplerate: float = 44100.0
var wavetable
var baseControl := BaseController.new()
var playback: AudioStreamPlayback = null
@export var DetuneAmount = "DetuneAmount"
@export var LFOFreq = "LFOFreq"
@export var LFOAmount = "LFOAmount"
var modify: Dictionary[String,float]

var Sine: String = "Sine"
var SawUp: String = "SawUp"
var SawDown: String = "SawDown"
var Square: String = "Square"
var Triangle: String = "Triangle"
var Voices
var RandOscs: Array
func _ready():
	Voices = [Sine,SawUp,SawDown,Square,Triangle]
	for i in randi_range(2,12):
		RandOscs.push_back(Voices.pick_random())
	baseControl.init(samplerate,RandOscs)
	RandOscs.clear()
	Voices = [Square, Triangle, Square, Triangle,SawDown,SawUp]
	play()
	playback = get_stream_playback()
	pass
	
func _process(_delta):
	baseControl.process(playback)
	pass

#-UI-#

func _on_amp_slider_value_changed(value):
	%ampvalue.text = str(value)
	#csynth.updateAmplitude(value)
	baseControl.setAmplitude(value)
	pass # Replace with function body.
func _on_freq_slider_value_changed(value):
	%freqvalue.text = str(value)
	#csynth.updateFrequency(value)
	baseControl.setFrequency(value)
	pass # Replace with function body.
func _on_detune_slider_value_changed(value):
	%detunevalue.text = str(value)
	modify[DetuneAmount]=value;
	baseControl.updateModifiers(modify)
	#csynth.updateDetune(value)
func _on_powerbutton_toggled(toggled_on):
	if(toggled_on):
		baseControl.start()
		pass
	if(!toggled_on):
		baseControl.stop()
		pass
	#csynth.isPlaying(toggled_on)
func _on_gatebutton_button_down():
	RandOscs.clear()
	for i in randi_range(2,12):
		RandOscs.push_back(Voices.pick_random())
	baseControl.update(samplerate,RandOscs)
	var f = %"freq slider".value
	_on_freq_slider_value_changed(f)
		
	
	#csynth.gateTriggered(true)
	%holdbutton.button_pressed = false
func _on_gatebutton_button_up():
	pass
	#csynth.gateTriggered(false)
func _on_holdbutton_toggled(_toggled_on):
	
	pass
	#csynth.gateTriggered(toggled_on)
func _on_attackslider_value_changed(value):
	%attackval.text = str(value)
	#csynth.updateAttack(value*samplerate)
	
func _on_decayslider_value_changed(value):
	%decayval.text = str(value)
	#csynth.updateDecay(value*samplerate)
func _on_sustainslider_value_changed(value):
	%sustainval.text = str(value)
	#csynth.updateSustain(value)
func _on_releaseslider_value_changed(value):
	%releaseval.text = str(value)
	#csynth.updateRelease(value*samplerate)
func _on_lfoamountslider_value_changed(value):
	%lfoamountval.text = str(value)
	modify[LFOAmount]=value;
	baseControl.updateModifiers(modify)


	#csynth.updateLfoAmount(value)
func _on_lfofreqslider_value_changed(value):
	#if lfomultactive:
		#value*=lfomultiplier
	%lfofreqval.text = str(value)
	modify[LFOFreq]=value;
	baseControl.updateModifiers(modify)

func _on_lfox_4_button_toggled(_toggled_on):
	#lfomultactive = toggled_on
	#print(lfomultactive)
	var ting = %lfofreqslider.value
	_on_lfofreqslider_value_changed(ting)
	


func _on_option_button_item_selected(index):
	var o = %OptionButton.get_item_text(index)
	samplerate = float(o)
	stop()
	play()
	print(index, " : ", o)
	pass # Replace with function body.
