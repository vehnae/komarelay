# KomaRelay

An Arduino sketch for controlling a relay board with AC connections. This means that we use two relays per socket to cut off both the live and neutral connections at the same time. The sketch includes a serial interface using [NMEA commands](http://www.hhhh.org/wiml/proj/nmeaxor.html).

## Configuration

Edit *KomaRelay.ino* and define the number of relays and the digital pins they are connected into. By default the relay #4 (R4) is connected to the LED pin (13) for testing. If you plan to use multiple boards you should also update the board name to be unique.

## Command set

### TEST

Queries the board name and version number. This message is also sent automatically when the serial port is opened.

Example: `$TEST*16`  
Response: `$KOMARELAY,VER=1.0*34`

### STATUS

Queries the current status of the relays.

Example: `$STATUS*14`  
Response: `$STATUS,R1=OFF,R2=OFF,R3=OFF,R4=ON*5E`

### SET

Toggles one or more relays.

Example: `$SET,R1=ON,R4=ON*47`  
Response: `$SET,OK*6A`  
Errors: `$SET,ERR*2B` (parse error)
