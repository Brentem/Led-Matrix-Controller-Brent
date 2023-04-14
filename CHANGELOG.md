# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## 0.1.0

### Added
* ESP8266 can read button input.
* ESP8266 can turn led on for 1 second.
* Arduino can make corner of Led Matrix red or blue.
* Serial communication between Arduino and ESP8266.
  * ESP8266 buttons pressed send "Option1" or "Option2".
  * Arduino received "Option1" or "Option2" send "ACK".
  * ESP8266 receives "ACK" and turns led on for 1 second.
