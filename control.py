import RPi.GPIO as GPIO
import time
import face3
import paho.mqtt.client as mqtt
import json
from picamera import PiCamera
import requests
import json
import base64
#import door
#import buzzer
#import light
# 169.234.19.8
#scp control.py pi@169.234.19.8:
MotionSensor = 12
door = 26
buzzer = 25
temperature = 24
GPIO.setmode(GPIO.BCM)
GPIO.setup(door,GPIO.OUT)
GPIO.setup(buzzer,GPIO.OUT)
GPIO.setup(temperature,GPIO.OUT)
GPIO.setup(MotionSensor, GPIO.IN)
ip = "54.219.185.67"
url = 'http://54.219.185.67/uploadphoto.php'
# The callback for when the client receives a CONNACK response from the server.


def OpenDoor(door):
    GPIO.output(door, GPIO.HIGH)
    time.sleep(2)
    GPIO.output(door, GPIO.LOW)

def closeDoor(door):
    GPIO.output(door, GPIO.LOW)
    time.sleep(2)
    GPIO.output(door, GPIO.HIGH)


def BuzzerAlarm(buzzer):
    GPIO.output(buzzer, GPIO.HIGH)

def BuzzerCalm(buzzer):
    GPIO.output(buzzer, GPIO.LOW)

def checkTemperature(temperature):
    return GPIO.input(temperature)

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("/home/home1") #subscribe to corresponding channel (same with the id(unique) of Pi)

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))
    message = json.loads(msg.payload)
    if (message['Type'] == "ViewPhoto"):
        #TO-DO: Require camera to take picture.
        camera = PiCamera()
        camera.start_preview()
        camera.capture('/home/pi/Desktop/viewphoto.jpg')
        camera.stop_preview()
        camera.close()
        image =  open('/home/pi/Desktop/viewphoto.jpg','rb')
        image_read = image.read()
        image_64 = base64.encodestring(image_read)
        payload = {"Homename":"home1","Image":image_64}
        r=requests.post(url, data=json.dumps(payload))         
    if message['Type'] == "OpenDoor":
        door.OpenDoor()
        pass;
    if message['Type'] == "SendAlert":
        buzzer.alarm()
        pass;
    if message['Type'] == "TurnOnLight":
        light.TurnOn()
        pass;
    if message['Type'] == "TurnOffLight":
        light.TurnOff()
        pass;
    if message['Type'] == "HomeStatus":
        url = 'http://54.219.185.67/refreshstatus.php'
        pass


if __name__ == '__main__':  

    
    client = mqtt.Client()
    
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect(ip, 1883, 60)
    
    # Blocking call that processes network traffic, dispatches callbacks and
    # handles reconnecting.
    # Other loop*() functions are available that give a threaded interface and a
    # manual interface.
    client.loop_start()
    #GPIO.setmode(GPIO.BOARD)
    
    flag=0

    try:

        while True:
            print "motion sensor is : ",   GPIO.input(MotionSensor)
            if GPIO.input(MotionSensor)==0:
                print "nobody"
                flag=0
                time.sleep(0.5)
            if GPIO.input(MotionSensor)==1:
                print "somebody here"
                if flag==0:
                    print "camera on"
                    face3.StartFaceDetection()
                    time.sleep(10)
                    OpenDoor(26)
                    BuzzerAlarm(25)
                    time.sleep(2)
                    BuzzerCalm(25)
                    closeDoor(26)
                flag = 1 
                time.sleep(5)
            if checkTemperature()>60:
                OpenDoor(26)
                BuzzerAlarm(25)
                time.sleep(5)
                BuzzerCalm(25)

    except KeyboardInterrupt:
        GPIO.cleanup()
        client.loop_stop()
        print "all cleanup"

