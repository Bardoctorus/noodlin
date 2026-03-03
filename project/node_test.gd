extends NodeTest


var starttime
var nowtime
var ms_elapsed
var seconds_alive:int = 0
var thisName





func _ready():
	print("This Name: ", getTestName())
	print("Change Me Init: ", changeMe)
	changeMe = "I've Changed"
	print("Change Me Init: ", changeMe)

	starttime = Time.get_ticks_msec()
	pass
	
func _process(delta):
	nowtime = Time.get_ticks_msec()
	ms_elapsed = nowtime - starttime
	if (ms_elapsed % 1000 == 0):
		incrementSeconds()
		seconds_alive = getSecondsElapsed()
		
		if(seconds_alive % 10 == 0):
			print(seconds_alive)
	pass
