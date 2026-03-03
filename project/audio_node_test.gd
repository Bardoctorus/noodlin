extends AudioNodeTest


var prevtime
var nowtime
var ms_elapsed
var seconds_alive = 0
var thisName





func _ready():
	print("This Name: ", getTestName())
	print("Change Me Init: ", changeMe)
	changeMe = "I've Changed"
	print("Change Me Init: ", changeMe)
	play()
	print("godot side audio gen: ",get_stream_playback())
	printsPlayback(get_stream_playback())

	prevtime = 0
	pass
	
func _process(_delta):
	nowtime = Time.get_ticks_msec()

	
	if (nowtime - prevtime >= 1000):
		incrementSeconds()
		seconds_alive = getSecondsElapsed()
		#print("seconds alive: ", seconds_alive)
		prevtime = nowtime
	
