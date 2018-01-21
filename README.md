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


1. [Check coverage](#check-coverage)
2. [Plug the antenna](#plug-the-antenna)
3. [Provision the device](#provision-the-device)

### Check coverage

In order to connect, you will need to be in range of a gateway of [The Things Network](https://www.thethingsnetwork.org/). Check the [world map](https://www.thethingsnetwork.org/map) to see if your local community already has gateways, and if not, consider installing one!

While you're there, also make sure you [have an account on The Things Network](https://account.thethingsnetwork.org/register).

### Plug the antenna

Always make sure you have the antenna plugged to your Arduino before powering it up.

### Provision the device

In order to send messages to the network, you need to register it on The Things Network, but before we do that, we need to find out its `Device EUI` (identifier):

  1. Plug your Arduino to your computer
  2. Select the correct `Board` and `Port` on the Arduino IDE menu
  3. Open the first sketch of this repository: [`01_get_deveui`](/01_get_deveui/)
  4. Open the [**serial monitor**](https://www.arduino.cc/en/Guide/Environment#toc12) and upload the sketch to your Arduino
  5. The serial monitor will print the `Device EUI`, **keep this at hand**.

  <img alt="Device EUI" src="/images/01_get_deveui.jpg" width="500">

  6. Now, go to [The Things Network Console](https://console.thethingsnetwork.org/applications)
  7. Add a new `Application`
  8. Register a new `Device` giving it a ID of your liking and paste the `Device EUI` that we got on Step 5.

  <img alt="Register new device" src="/images/register-device.jpg" width="500">

