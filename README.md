# lodestar
Lodestar is a small scale electric demonstrator for the belly-flop and tail-sitting control algorithms necessary for SpaceX's Starship.

This project is being undertaken by Shihao Cao and Govind Chari

## Setup

This project is setup within VSCode and leverages the PlatformIO extension heavily. This project also borrows a lot of framework code from the Cornell Space Systems Design Studio project: Pathfinder for Autonomous Navigation (PAN).

Link to PAN repo:
https://github.com/pathfinder-for-autonomous-navigation

## FAQ / Fixes
Error:
> error: there are no arguments to 'isnan' that depend on a template parameter, so a declaration of 'isnan' must be available

If you run into a isnan() definition error in utility/vector.h in the Adafruit BNO_055 library within the .pio folder, change `#include <math.h>` to `#include <cmath>` and `isnan()` to `std::isnan()`within the utility/vector.h file.