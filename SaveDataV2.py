# Importing Libraries 
import serial 
import time 
import csv
import keyboard

def collect_data(arduino_call):
    voltageData = []

    print("Waiting for Instron...\n")
    # arduino_call.write(b'0')

    while True:
        line = arduino_call.readline().decode('utf-8').strip()
        # print(line)
        if line == "GO":
            print("Trigger received\n")
            break

    while True:
        try:
            line = arduino_call.readline().decode('utf-8').strip()
            
            if line:
                try:
                    # Split line into float values
                    values = [float(v.strip()) for v in line.strip().split(',')]
                    
                    if 1 <= len(values) <= 2:
                        voltageData.append(values)
                        # print(f"Received: {values}")
                    else:
                        print(f"Unexpected number of values: {line}")
                        
                except ValueError:
                    print(f"Invalid data received: {line}")
            
            if keyboard.is_pressed("space"):
                break

        except KeyboardInterrupt:
            print("\nData collection interrupted.")
            break

    return voltageData




if __name__ == "__main__":

    # setting up connection to arduino
    portNum = input("Enter Port:")

    try:
        arduino = serial.Serial(port=portNum, baudrate=115200, timeout=.1) 
        print(f"Connected to port {portNum}\n")
    except:
        print("Please check the arduino port\n")
        exit()

    while True:

        filename = input("Which resistance are we workin with and what iteration?")

        if filename.lower() == " exit":
            print("\nGood Job Collecting Data")
            break

        filename += ".csv"
        print(f"\nNow creating file: {filename}")

        voltageData = collect_data(arduino)

        with open(filename, mode='w', newline='') as file:
            dataWriter = csv.writer(file)
            dataWriter.writerows(voltageData)


