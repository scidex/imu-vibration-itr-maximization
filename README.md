# Threshold-based Information Transfer System with IMU, EMG and vibrotactile motors

## What does the system do?

This repository can be used for transmitting data between rooms via local WLAN networks using an IMU for encoding and four vibrotactile motors for decoding. Optionally, an EMG can be used for error correction to increase the accuracy of the system. In experimental trials maximal information transfer rates of above 100 bit per minute and more than 99% accuracy were achieved in trials optimizing for one of both performance measurements at a time.

## Which hardware is needed?

Encoding Subsystem:
1. ESP32E
2. IMU
3. EMG (optional)
4. USB connector (1x)
5. wires (7x)

Decoding Subsystem:
1. ESP32
2. Vibrotactile motors (4x)
3. capacitor (0.1uF / 100nF) (4x)
4. 1N4001 diode (4x)
5. resistor (1kOhm) (4x)
6. 2N2222 transistor (4x)
7. wires (10x)

Full System:
1. Local WLAN Router

## How can I set the system up?

1. Connect the

## File index

- decoder.ino: Decoder, runs udpServer board, i.e ESP32

- encoder.ino: Encoder: runs udpClient board, i.e ESP32E

- System_Analysis.ipynb:  is the jupyter notebook for all the data analysis

- performance_calculation.py: Utils for calculating ITR and accuracy

## Additional resources

Data can be found here: https://syncandshare.lrz.de/getlink/fi3AynGppD5jvn7uEdVXA3Yp/

Authors: Ahmed Almijbari, Nathan van Beelen, Bertram Fuchs and Runfeng Lyu
