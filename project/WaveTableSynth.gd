extends Node

#The c++ script will need to take:
	#number of oscillators -> pass to oscillator instantiation function and store
	#wavetable, samplerate, starting freq, detune -> call init on each stored osc, set freq + detune
	#frequency updates -> set freq + detune
	#Start/stop -> calls osc start/stop
	
