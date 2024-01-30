import serial

ser = serial.Serial('/dev/ttyAMA1', 115200)
print('serial connection opened')

while True:
	direction = raw_input()
	angle = raw_input()
	time = raw_input()
	command = direction + " " + angle + " " + time + ""
	ser.write(bytes(command))

ser.close()
print('serial connection closed')
