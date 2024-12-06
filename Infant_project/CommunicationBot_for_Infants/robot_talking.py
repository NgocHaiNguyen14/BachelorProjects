import pyttsx3

robot_brain=" i love you so much"

robot_mouth = pyttsx3.init()
robot_mouth.say(robot_brain)
robot_mouth.runAndWait()