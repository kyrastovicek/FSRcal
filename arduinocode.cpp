// mahi includes
#include <Mahi/Gui.hpp>  // MAHI libraries for GUI functionality
#include <Mahi/Util.hpp> // MAHI libraries for clock, logging, and other functionality

// standard library includes
#include <thread>        // std::thread
#include <random>        // std::random_device
#include <string>
#include <iostream>
#include <fstream>      // for data collection into csv
#include <algorithm>
#include <windows.h>


class Arduino {
public: 
    Arduino(const char* portName) : portName_(portName) {}


        void setupCommunication(){
            // Open serial port
            hSerial = CreateFile(portName_, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hSerial == INVALID_HANDLE_VALUE) {
                DWORD dwError = GetLastError();
                if (dwError == ERROR_FILE_NOT_FOUND) {
                    LOG(mahi::util::Info) <<"Serial port does not exist";
                } else {
                    LOG(mahi::util::Info) <<"Error opening serial port. Error code: " << dwError;
                }
            return;
            }

            // Set serial parameters
            DCB dcbSerialParams = { 0 };
            dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
            dcbSerialParams.BaudRate = CBR_9600;
            dcbSerialParams.ByteSize = 8;
            dcbSerialParams.StopBits = ONESTOPBIT;
            dcbSerialParams.Parity = NOPARITY;

            if (!SetCommState(hSerial, &dcbSerialParams)) {
                LOG(mahi::util::Info) << "Error setting serial port parameters" ;
                CloseHandle(hSerial);
                return;
            }
        }

        //sending a char variable to the arduino
        // void sendSerialData(const char* data) {
        //     DWORD bytesWritten;
        //     if (!WriteFile(hSerial, data, strlen(data), &bytesWritten, NULL)) {
        //     LOG(mahi::util::Info) << "Error writing to serial port" ;
        //     }
        // }
        void sendSerialData(const void* data, size_t dataSize) {
            DWORD bytesWritten;
            if (!WriteFile(hSerial, data, dataSize, &bytesWritten, NULL)) {
                LOG(mahi::util::Info) << "Error writing to serial port" ;
            }
        }
        void sendByte(int byteData) {
            uint8_t dataToSend = static_cast<uint8_t>(byteData);
            sendSerialData(&dataToSend, sizeof(dataToSend));
        }

private:
    const char* portName_;
    HANDLE hSerial;

};
