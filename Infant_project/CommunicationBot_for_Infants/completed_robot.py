import pyttsx3
import speech_recognition
import webbrowser
from datetime import date
import datetime
import os

def speak_bye(voice = "Goodbye Mr Hai"):
    robot_mouth = pyttsx3.init()
    robot_mouth.say(voice)
    robot_mouth.runAndWait()

def open_application(text):
    if "code block" in text:
        speak("Openning CodeBlocks ")
        os.startfile('C:\\Program Files\\CodeBlocks\\codeblocks.exe')

i = 1
now = datetime.datetime.now()
x = int(now.strftime("%H"))
if 0 <= x < 5:
    robot_braintime = "It is too late now, you should sleep"
elif 5 <= x < 12:
    robot_braintime = "good morning Mr Hai, have a good day"
elif 12 <= x < 19:
    robot_braintime = "good afternoon Mr Hai"
elif 19 <= x < 24:
    robot_braintime = "good night Mr Hai"
print(robot_braintime)
robot_mouth = pyttsx3.init()
robot_mouth.say(robot_braintime)
robot_mouth.runAndWait()

while True:

    # phan truyen data cho robot
    robot_ear = speech_recognition.Recognizer()
    with speech_recognition.Microphone() as mic:
        print("Robot: I'm listening")
        audio = robot_ear.listen(mic, phrase_time_limit=3)
    try:
        you = robot_ear.recognize_google(audio)
    except:
        you = "repeat"

    print("....")

    # phan cho robot brain upgrade data
    open_application(you)
    if "hello" in you:
        robot_brain = "hello"
    elif "bye" in you:
        robot_brain = "Goodbye Mr Hai"
        robot_mouth = pyttsx3.init()
        robot_mouth.say(robot_brain)
        robot_mouth.runAndWait()
        break
    elif "today" in you:
        today = date.today()
        robot_brain = today.strftime("%B %d,%Y")
    elif "now" in you:
        robot_brain = "it is %a hour and %a minute " % (now.hour, now.minute)

    elif "play music" in you:
        webbrowser.open('https://www.youtube.com/watch?v=GQ4F9k4USfA&list=RDGQ4F9k4USfA&start_radio=1&t=3')
        break
    elif "shut down" in you:
        os.system('shutdown -s')
    elif "restart" in you:
        speak_bye("Your computer is about to restart")
        os.system('shutdown -r')
    elif "turn off" in you:
        speak_bye("Turning off your computer, goodbye")
        break
    else:
        robot_brain = "i can not hear you, can you repeat "
        i = i + 1
        if i == 4:
            break

    # phan noi ra robot brain
    print(robot_brain)
    robot_mouth = pyttsx3.init()
    robot_mouth.say(robot_brain)
    robot_mouth.runAndWait()
