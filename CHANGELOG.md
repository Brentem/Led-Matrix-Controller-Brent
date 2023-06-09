# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## 0.3.0 - 09/06/2023

### Added
* Arduino: SimpleRowDrawer class.\
  * Contains logic that is responsible for loading data and driving the clock signal.
* Arduino: SimpleMatrixDrawer class.
  * Contains logic that is responsible for address, OE and Lat signals.
* Arduino: MatrixTimer class.
  * Timer class that contains function pointer to function that gives back time in milliseconds or microseconds.
* Arduino: my_gpio.
  * My own GPIO drivers.

### Removed
* Arduino: LedMatrixDriver class.

## 0.2.0 - 26/05/2023

### Added
* Arduino Led Matrix Driver that can drive the first row of the led matrix to blue.

### Removed
* Arduino code for serial communication.

## 0.1.0 - 17/04/2023

### Added
* ESP8266 can read button input.
* ESP8266 can turn led on for 1 second.
* Arduino can make corner of Led Matrix red or blue.
* Serial communication between Arduino and ESP8266.
  * ESP8266 buttons pressed send "Option1" or "Option2".
  * Arduino received "Option1" or "Option2" send "ACK".
  * ESP8266 receives "ACK" and turns led on for 1 second.
