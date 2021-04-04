import serial
import json
import requests

#  MACOS
# ser = serial.Serial("/dev/cu.usbserial-14120", 9600)

# Raspberry Pi
ser = serial.Serial("/dev/ttyUSB0", 9600)


while 1:
    if ser.in_waiting > 0:
        try:
            line = ser.readline().decode("utf-8")
            jsonData = json.loads(line)
            if len(jsonData) == 5:
                id = str(jsonData["ID"])
                del jsonData["ID"]
                trashbinobj = {id: jsonData}

                url = "https://csc2006-smart-bin-default-rtdb.firebaseio.com/.json"
                payload = json.dumps(trashbinobj)
                headers = {"Content-Type": "application/json"}
                response = requests.request("PATCH", url, headers=headers, data=payload)

                print(response.text)

        except Exception as e:
            print(e)
