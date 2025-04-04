# Importing Libraries 
import serial 
import time 
import csv
import keyboard

def collect_data(arduino_call):

    # empty list for voltage values over time
    # print(f"Sending to {arduino_call}\n")

    voltageData = []

    while True:
        try:
            # Read data from serial, decode, and strip unwanted characters
            line = arduino.readline().decode('utf-8').strip()
            
            if line:
                try:
                    voltage = float(line)  # Convert to float
                    voltageData.append([voltage])  # Store as a list (for CSV writing)
                    # print(f"Voltage: {voltage}")  # Display current reading
                except ValueError:
                    print(f"Invalid data received: {line}")  # Handle non-numeric data
            
            # Check if user wants to stop data collection
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


