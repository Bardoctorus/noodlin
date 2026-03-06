extends AudioNodeTest


var prevtime
var nowtime
var ms_elapsed
var seconds_alive = 0
var thisName

var util = Util.new()

#@export var WavetableType: Util.WaveTables
@export_range(1, 10) var NumberOfOscillators: int
@export_range(0, 10) var DetuneAmount
@export_range(40.0,10000.0) var Frequency = 440.0
@export_enum("Saw", "Square", "Sine", "Triangle") var TableType:int
var samplerate = 44100.0
var wavetable
var csynth := CppWavetableSynth.new()
var playback

func _ready():
	
	
	#wavetable = util.fillWaveTable(WavetableType)
	#print(wavetable)
	
	csynth.initOscillators(samplerate, Frequency, TableType ,NumberOfOscillators, DetuneAmount)
	play()
	playback = get_stream_playback()
	prevtime = 0
	pass
	
func _process(_delta):
	
	csynth.render(playback)
	pass



	
#-UI-#

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
func _on_powerbutton_toggled(toggled_on):
	csynth.isPlaying(toggled_on)
func _on_gatebutton_button_down():
	csynth.gateTriggered(true)
	%holdbutton.button_pressed = false
func _on_gatebutton_button_up():
	csynth.gateTriggered(false)
func _on_holdbutton_toggled(toggled_on):
	csynth.gateTriggered(toggled_on)
func _on_attackslider_value_changed(value):
	%attackval.text = str(value)
	csynth.updateAttack(value*samplerate)
	
func _on_decayslider_value_changed(value):
	%decayval.text = str(value)
	csynth.updateDecay(value*samplerate)
func _on_sustainslider_value_changed(value):
	%sustainval.text = str(value)
	csynth.updateSustain(value)
func _on_releaseslider_value_changed(value):
	%releaseval.text = str(value)
	csynth.updateRelease(value*samplerate)


func _on_lfoamountslider_value_changed(value):
	%lfoamountval.text = str(value)
	csynth.updateLfoAmount(value)


func _on_lfofreqslider_value_changed(value):
	%lfofreqval.text = str(value)
	csynth.updateLfoFrequency(value)
