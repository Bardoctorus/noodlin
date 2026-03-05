extends AudioNodeTest


var prevtime
var nowtime
var ms_elapsed
var seconds_alive = 0
var thisName

var util = Util.new()

@export var WavetableType: Util.WaveTables
@export_range(1, 4) var NumberOfOscillators: int
@export_range(0, 10) var DetuneAmount
var samplerate = 44100.0
var wavetable
var csynth = CppWavetableSynth.new()


func _ready():
	
	
	
	wavetable = util.fillWaveTable(WavetableType)
	print(wavetable)
	csynth.initOscillators(samplerate, 440.0, wavetable,NumberOfOscillators)
	csynth.handleInput(true)
	prevtime = 0
	pass
	
func _process(_delta):
	nowtime = Time.get_ticks_msec()

	
	if (nowtime - prevtime >= 1000):
		incrementSeconds()
		seconds_alive = getSecondsElapsed()
		#print("seconds alive: ", seconds_alive)
		prevtime = nowtime
	
