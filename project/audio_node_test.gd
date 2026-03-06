extends AudioNodeTest


var prevtime
var nowtime
var ms_elapsed
var seconds_alive = 0
var thisName

var util = Util.new()

#@export var WavetableType: Util.WaveTables
@export_range(1, 4) var NumberOfOscillators: int
@export_range(0, 10) var DetuneAmount
@export_range(40.0,10000.0) var Frequency = 440.0
var samplerate = 44100.0
var wavetable
var csynth := CppWavetableSynth.new()
var playback

func _ready():
	
	
	#wavetable = util.fillWaveTable(WavetableType)
	#print(wavetable)
	
	csynth.initOscillators(samplerate, Frequency, 1 ,NumberOfOscillators, DetuneAmount)
	play()
	playback = get_stream_playback()
	prevtime = 0
	pass
	
func _process(_delta):
	csynth.render(playback)
	pass



	
	pass # Replace with function body.


func _on_amp_slider_value_changed(value):
	%ampvalue.text = str(value)
	csynth.updateAmplitude(value)
	pass # Replace with function body.


func _on_freq_slider_value_changed(value):
	%freqvalue.text = str(value)
	csynth.updateFrequency(value)
	pass # Replace with function body.


func _on_detune_slider_value_changed(value):
	%detunevalue.text = str(value)
	csynth.updateDetune(value)
	pass # Replace with function body.


func _on_powerbutton_toggled(toggled_on):
	csynth.handleInput(toggled_on)
	pass # Replace with function body.


func _on_gatebutton_button_down():
	pass # Replace with function body.


func _on_gatebutton_button_up():
	pass # Replace with function body.
