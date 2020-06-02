# lodestar
Lodestar is a small scale electric demonstrator for the belly-flop and tail-sitting control algorithms necessary for SpaceX's Starship.

This project is being undertaken by Shihao Cao and Govind Chari

## Setup

This project is setup within VSCode and leverages the PlatformIO extension heavily. This project also borrows a lot of framework code from the Cornell Space Systems Design Studio project: Pathfinder for Autonomous Navigation (PAN).

Link to PAN repo:
https://github.com/pathfinder-for-autonomous-navigation

### Installations

You will need the latest Teensyduino, and a compatible version of Arduino.

You will need VSCode and the Platformio extension.

## Uploading Code

This command will upload the current flight software stack.
This project assumes you have a Teensy 3.6 plugged in.
```
pio run -e flight -t upload
```

You can replace the `flight` environment with your own enviorment as configured in `platformio.ini`.

The below environment is linked to the `your_target.cpp` file.
```
pio run -e your_target -t upload
```

You can check your code compiles without uploading through:
```
pio run -e your_target
```

For more information, google `pio run`, and change the `platformio.ini` accordingly.

## Groundstation

To start the Flask server that reads from either hardline serial or the 915 MHz Telemetry Radio:
```
cd web/flask
. start
```

To start the ground station website:
```
cd web/gs
npm start
```

## FAQ / Fixes
Error:
> error: there are no arguments to 'isnan' that depend on a template parameter, so a declaration of 'isnan' must be available

If you run into a isnan() definition error in utility/vector.h in the Adafruit BNO_055 library within the .pio folder, change `#include <math.h>` to `#include <cmath>` and `isnan()` to `std::isnan()`within the utility/vector.h file.