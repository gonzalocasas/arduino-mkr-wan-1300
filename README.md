# Getting Started with Arduino MKR WAN 1300

[![Say Thanks!](https://img.shields.io/badge/Say%20Thanks-!-1EAEDB.svg)](https://saythanks.io/to/gonzalocasas)

> Minimal getting started examples to connect the Arduino MKR WAN 1300 to [The Things Network](https://thethingsnetwork.org)

  <img alt="Arduino MKR WAN 1300" src="images/arduino-mkr-wan-1300.jpg" width="500">

## Setup your environment

Make sure you have an updated version of [Arduino IDE](https://www.arduino.cc/en/Main/Software) installed.  
_You could run these examples on the Arduino Web Editor also, but the screenshots are from the desktop client._

* Install board definitions

  Go to `Tools` -> `Boards` -> `Board manager`, search for `MKR`, and install the `Arduino SAMD Boards` package.
  
  <img alt="Boards manager" src="images/board-manager.jpg" width="500">

* Install LoRaWAN library

  Go to `Sketch` -> `Include Library` -> `Manage Libraries..`, search for `MKRWAN`, and install it.

  <img alt="Library manager" src="images/library-manager.jpg" width="500">

## Connect to The Things Network

1. [Check coverage](#check-coverage)
2. [Plug the antenna](#plug-the-antenna)
3. [Provision the device](#provision-the-device)
4. [Sending our first message](#sending-our-first-message)
5. [A real use case: GPS tracker](#gps-tracker)

### Check coverage

In order to connect, you will need to be in range of a gateway of [The Things Network](https://www.thethingsnetwork.org/). Check the [world map](https://www.thethingsnetwork.org/map) to see if your local community already has gateways, and if not, consider installing one!

While you're there, also make sure you [have an account on The Things Network](https://account.thethingsnetwork.org/register).

### Plug the antenna

Always make sure you have the antenna plugged to your Arduino before powering it up.

### Provision the device

In order to send messages to the network, you need to register it on The Things Network, but before we do that, we need to find out its `Device EUI` (identifier):

  1. Plug your Arduino to your computer
  2. Select the correct `Board` and `Port` on the Arduino IDE menu
  3. Open the first sketch of this repository: [`mkrwan_01_get_deveui`](/mkrwan_01_get_deveui/)
  4. Update (if needed) the `lora_band region` variable according to your region.
  5. Open the [**serial monitor**](https://www.arduino.cc/en/Guide/Environment#toc12) and upload the sketch to your Arduino.
  6. The serial monitor will print the `Device EUI`, **keep this at hand**.

  <img alt="Device EUI" src="images/01_get_deveui.jpg" width="500">

  7. Now, go to [The Things Network Console](https://console.thethingsnetwork.org/applications)
  8. Add a new `Application`
  9. Register a new `Device` giving it a ID of your liking and paste the `Device EUI` that we got on Step 5.

  <img alt="Register new device" src="images/register-device.jpg" width="500">

### Sending our first message

Once the device is registered on the network, we can start sending data:

  1. Open the second sketch of this repository: [`mkrwan_02_hello_world`](/mkrwan_02_hello_world/)
  2. Update (if needed) the `lora_band region` variable according to your region.
  3. On the second tab (`arduino_secrets.h`), paste the `appEui` and `appKey` values for your device. You can copy & paste it verbatim from the bottom of the device page on The Things Network Console (section `EXAMPLE CODE`).

  <img alt="Device keys" src="images/paste-keys.jpg" width="500">

  4. Upload the sketch to your Arduino.
  5. If everything is in order, you will see messages coming through in the `Data` tab of The Things Network Console.

  <img alt="Data tab" src="images/data-tab.jpg" width="500">


> Q: Wait! Why do I see payload = `68 69` instead of `hi`?
> 
> A: That's HEX for `hi`. That's because you should not be sending strings over LoRaWAN, you have to optimize the air time usage sending as much a compact payload as possible.

Check [Working with Bytes](https://www.thethingsnetwork.org/docs/devices/bytes.html) for more details about optimizing your payload.

### GPS Tracker

Now for a more complete application, let's build a GPS tracker node! For this example, you need to get a GPS module. I am using [u-blox PAM-7Q](https://www.u-blox.com/en/product/pam-7q-module) but also tested it with the more widely available u-blox NEO series.

#### Wiring GPS module

The wiring of the module is trivial:

| Arduino pin | GPS pin     |
|-------------|-------------|
| `GND`       | `GND` (`3`) |
| `VCC`       | `VCC` (`4`) |
| `RX` (`13`) | `TX` (`2`)  |
| `TX` (`14`) | `RX` (`1`)  |

#### Configuring libraries

You will also need to install the [TinyGPS++ library](https://github.com/mikalhart/TinyGPSPlus/releases). Download it as ZIP, then go to `Sketch` -> `Include Library` -> `Add .ZIP Library` and select it.

#### Configuring payload format

We will use a binary payload based on [TTN Mapper](https://ttnmapper.org) reference, so we need to add a `decoder` payload format function to [The Things Network Console](https://console.thethingsnetwork.org/applications) (as described in the [documentation](https://www.thethingsnetwork.org/docs/devices/bytes.html)).

Go to the `Applications` tab in [The Things Network Console](https://console.thethingsnetwork.org/applications), select `Payload Formats` and copy & paste the following `decoder` function:

```javascript
// Author:
// Copyright (c) 2016 JP Meijers
// Apache License, Version 2.0, http://www.apache.org/licenses/LICENSE-2.0
// https://github.com/jpmeijers/RN2483-Arduino-Library
function Decoder(bytes, port) {
  // Decode an uplink message from a buffer
  // (array) of bytes to an object of fields.
  var decoded = {};
  // if (port === 1) decoded.led = bytes[0];
  decoded.lat = ((bytes[0]<<16)>>>0) + ((bytes[1]<<8)>>>0) + bytes[2];
  decoded.lat = (decoded.lat / 16777215.0 * 180) - 90;
  decoded.lon = ((bytes[3]<<16)>>>0) + ((bytes[4]<<8)>>>0) + bytes[5];
  decoded.lon = (decoded.lon / 16777215.0 * 360) - 180;
  var altValue = ((bytes[6]<<8)>>>0) + bytes[7];
  var sign = bytes[6] & (1 << 7);
  if(sign)
  {
    decoded.alt = 0xFFFF0000 | altValue;
  }
  else
  {
    decoded.alt = altValue;
  }
  decoded.hdop = bytes[8] / 10.0;
  return decoded;
}
```

#### Flashing your Arduino

We are all set to update our Arduino, the steps are almost identical to the previous example:

  1. Open the third sketch of this repository: [`mkrwan_03_gps_tracker`](/mkrwan_03_gps_tracker/)
  2. Update (if needed) the `lora_band region` variable according to your region.
  3. On the second tab (`arduino_secrets.h`), paste the `appEui` and `appKey` values for your device. You can copy & paste it verbatim from the bottom of the device page on The Things Network Console (section `EXAMPLE CODE`).
  4. Upload the sketch to your Arduino.
  5. On start, the node will join the network and try to get a GPS fix. This usually takes up to a minute. **NOTE:** You will need to be outdoors for the GPS module to get a location.
  6. Check the `Serial Monitor` to see the progress.
  7. If all went well, you can now check the `Data` tab in the console to see GPS data coming in.
  8. Optionally, configure the [TTN Mapper integration](https://www.thethingsnetwork.org/docs/applications/ttnmapper/) and have your node contribute to the mapping efforts of the community.

Fantastic! And now, how do I see my GPS traces on a map like this?

  <img alt="Boards manager" src="images/bike-tracker.jpg" width="500">

Check [this sample web app](https://github.com/gonzalocasas/ttn-live-tracker)!

---

## License

This content is licensed under the MIT License, see the [LICENSE](LICENSE) file for details.

## Contributing

1. Fork it (<https://github.com/gonzalocasas/arduino-mkr-wan-1300>)
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create a new Pull Request :D

## Credits

Examples loosely based on [Arduino MKRWAN library](https://www.arduino.cc/en/Tutorial/MKRWANLoraSendAndReceive).

Check the [reference documentation](https://www.arduino.cc/en/Reference/MKRWAN) of the library for additional options.
