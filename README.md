# Threshold-based Information Transfer System with IMU, EMG and vibrotactile motors

## What does the system do?

This repository can be used for transmitting data between rooms via local WLAN networks using an IMU for encoding and four vibrotactile motors for decoding. Optionally, an EMG can be used for error correction to increase the accuracy of the system. In experimental trials maximal information transfer rates of above 100 bit per minute and more than 99% accuracy were achieved in trials optimizing for one of both performance measurements at a time.

## Which hardware is needed?

Encoding Subsystem:
1. ESP32E
2. IMU ICM-20948
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

1. Connect the IMU as follows:
 (figure credits: Neuro-Inspired Systems Engineering Course @ TUM)

![](https://github.com/scidex/imu-vibration-itr-maximization/blob/main/figures/IMUsetup.png?raw=true)

2. Connect the EMG as follows:
 (figure credits: Neuro-Inspired Systems Engineering Course @ TUM)

![](https://github.com/scidex/imu-vibration-itr-maximization/blob/main/figures/EMGsetup.png?raw=true)

3. Connect the first two vibrotactile motors as follows:
 (figure credits: Neuro-Inspired Systems Engineering Course @ TUM)

![](https://github.com/scidex/imu-vibration-itr-maximization/blob/main/figures/VIBRATORSsetup.png?raw=true)

Now connect the third and fourth motors analogously to the second one. Don't forget to set the correct pins in the decoding.ino file!

4. Set an IP-address which is not yet occupied in the local WLAN network. Di this in the encoder.ino file.

5. Run the decoder.ino file after the encoder has been pushed to the device.

6. Open the Arduino monitor on the laptop running on the decoder side and set the baud rate to 500000. This enables feedback for the encoder.

7. Now you are ready to go!

## How can I encode and decode numbers now?

### Encoding

Fix a paper to a table and draw the following figure onto the paper.

<img src="https://github.com/scidex/imu-vibration-itr-maximization/blob/main/figures/encoding_sketch.jpeg?raw=true" width="400" height="570">

The encoding works as follows:

1: 90 degrees, range: 67.5 to 112.5
2: 45 degrees, range: 22.5 to 67.5
3: 0 degrees, range: -22.5 (or 337.5) to 22.5
4: 315 degrees, range: 292.5 to 337.5
5: 270 degrees, range: 247.5 to 292.5
6: 225 degrees, range: 202.5 to 247.5
7: 180 degrees, range: 157.5 to 202.5
8: 135 degrees, range: 112.5 to 157.5

- For encoding the numbers 1-8 make fast movements away from the origin to the number written on the paper and back to the origin.

- For encoding a 9 lift the IMU vertically and move it back to the origin.

- For encoding a 0 rotate the IMU around the z-axis and return to the initial rotation angle.

- Optionally, you can reset the last sent number by flexing your arm. Note that only the last number can be reset.

The following figure shows the encoding scheme in 3D:

![](https://github.com/scidex/imu-vibration-itr-maximization/blob/main/figures/3D_encoding.png?raw=true)

### Decoding

For decoding, place the vibrators according to the connection to your microcontroller onto the table. According to the encoding, the vibrators will now vibrate with a delay of one encoded number. You can either decode using acoustic and visual; or tactile sensory feedback. Note that in our trials combined auditory and visual feedback performed best.

The decoding scheme is shown in the following figure:

<img src="https://github.com/scidex/imu-vibration-itr-maximization/blob/main/figures/decoding.png?raw=true" width="291" height="600">

Let's look at two examples:

- If a '1' is being sent, only the rightmost vibrotactile motor will vibrate. Hence, you can write down a 1.
- If all vibrotactile motors vibrate, you can write down the number 9.

It will take a couple of minutes until you learn the decoding. If the decoding is too fast for you, you can set the delay to 2000ms. If you are getting faster, you can try a delay of 1500ms or even 1250ms.


#### And - the last step: ENJOY THE SYSTEM!

## File index

- decoder.ino: Decoder, runs udpServer board, i.e ESP32

- encoder.ino: Encoder: runs udpClient board, i.e ESP32E

- System_Analysis.ipynb:  is the jupyter notebook for all the data analysis

- performance_calculation.py: Utils for calculating ITR and accuracy

## Additional resources

Data can be found here: https://syncandshare.lrz.de/getlink/fi3AynGppD5jvn7uEdVXA3Yp/

Authors: Ahmed Almijbari, Nathan van Beelen, Bertram Fuchs and Runfeng Lyu
