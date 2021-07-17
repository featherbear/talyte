# Talyte

> An [OBS](https://obsproject.com/) tally light for the M5StickC IoT device.  

---

## Usage

> Note: Talyte requires [obs-websocket](https://github.com/Palakis/obs-websocket) installed on the computer running [OBS](https://obsproject.com/).

You can use Talyte as a standalone program, or as an API (write your own program, OBS tally integration is done for you).

### TalyteStandalone - Talyte as a software

* Open the `src/main.cpp` and edit the `ssid`, `password`, `OBS_HOST`, and `OBS_PORT` variables to match your configuration.  
  * If you would like to set a default program for Talyte to observe, modify the `defaultProgram` variable as well.
* Compile and upload the code
  * This project uses [PlatformIO](https://platformio.org/) as the build framework, however you can use whatever build chain you like

#### Usage

**Setup**

Whilst the device is on the Connecting screen (during startup), press the [M5] button to enter the setup mode. The wireless network and IP address to connect to are displayed on the LCD screen.

Once connected, you can configure the network and tally settings on the webpage.

![](https://featherbear.cc/blog/uploads/screely-1626514386767.png)

**Views**

```
/--Tally
|
\--Info
    + Source        |<
    + Device        |< Pages
    + Link Assign   |<
```

* `[M5] button` - Switch views
* `Alt button` - Switch pages

To select a new program to link Talyte to, go to the Link Assign page and hold the `Alt button` for _6 seconds_.


### TalyteClient - Talyte as a library

> idk import the header file i guess...

---

## Extra | Talyte Assistant

[Talyte Assistant](https://github.com/featherbear/talyte-assistant) is a WebSockets proxy to reduce the amount of traffic that Talyte receives, thus making Talyte perform more optimally.

---

## License

This software is licensed under the MIT license, as can be viewed [here](LICENSE.md).  