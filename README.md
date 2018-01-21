# Getting Started with Arduino MKR WAN 1300

> Minimal getting started examples to connect the Arduino MKR WAN 1300 to [The Things Network](https://thethingsnetwork.org)

## Setup your environment

Make sure you have an updated version of [Arduino IDE](https://www.arduino.cc/en/Main/Software) installed.  
_You could run these examples on the Arduino Web Editor also, but the screenshots are from the desktop client._

* Install board definitions

  Go to `Tools` -> `Boards` -> `Board manager`, search for `MKR`, and install the `Arduino SAMD Boards` package.
  
  <img alt="Boards manager" src="/images/board-manager.jpg" width="500">

* Install LoRaWAN library

  Go to `Sketch` -> `Include Library` -> `Manage Libraries..`, search for `MKRWAN`, and install it.

  <img alt="Library manager" src="/images/library-manager.jpg" width="500">


## Connect to The Things Network

In order to connect, you will need to be in range of a gateway of [The Things Network](https://www.thethingsnetwork.org/). Check the [world map](https://www.thethingsnetwork.org/map) to see if your local community already has gateways, and if not, consider installing one!


