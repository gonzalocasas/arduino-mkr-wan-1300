# Getting Started with the Arduino MKR WAN 1300

> Minimal getting started code to connect the Arduino MKR WAN 1300 to [The Things Network](https://thethingsnetwork.org)

## Setup your environment

Make sure you have an updated version of [Arduino IDE](https://www.arduino.cc/en/Main/Software) installed.  
_You could run these examples on the Arduino Web Editor also, but the screenshots are from the desktop client._

* Install board definitions:

  Go to `Tools` -> `Boards` -> `Board manager`, search for `MKR`, and install the `Arduino SAMD Boards` package.
  
  ![Boards manager](/images/board-manager.jpg)

* Install LoRaWAN library:

  Go to `Sketch` -> `Include Library` -> `Manage Libraries..`, search for `MKRWAN`, and install it.

  ![Library manager](/images/library-manager.jpg)
