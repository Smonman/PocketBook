# PocketBook

A small project for a one-word-at-a-time-e-book-reader.

This is intended to be run on a [Raspberry Pi Pico W (RP2040)](https://www.raspberrypi.com/documentation/microcontrollers/pico-series.html#pico1), however, both the Wi-Fi module and the Bluetooth module are currently not in use.
The intended display is the [Waveshare Pico LCD 2](https://www.waveshare.com/wiki/Pico-LCD-2).

## Architecture

Since the Pico does not have external memory, all required data is stored directly on the chip.
To persist data between boot cycles, flash memory is used.
To this end, [littlefs](https://github.com/littlefs-project/littlefs) is used through the [pico-lfs](https://github.com/tjko/pico-lfs) interface.

### Data

However, the actual data that is displayed (i.e. the e-book content) is not stored using the file system.
Rather, for the sake of simplicity, the data is compiled into the project through the `content.c` source file.
This `content.c` is expected to have the following skeleton:

```c
#include "content.h"
const char content[] = ""; // <-- place content here
const size_t content_length = sizeof(content) - 1;
```

To automatically generate such a file from a content text file, take a look at tools like [bin2c](https://github.com/adobe/bin2c).

The format of the content is simple.
As of now, it is expected to only contain ASCII characters, using other characters may lead to faults.
Each word or token (an atomic element that is displayed at once) is expected to be terminated by a new line character (`\n`).
Take a look at [PocketWords](https://github.com/Smonman/PocketWords) if you want to automatically generate a valid list of words from an e-book file.

The `content` content is expected to be mapped to flash memory, no specific linker files are given.

### LCD Access

The LCD screen is controled using the Waveshares's own demo code (See the [Wiki to download the Demo files](https://www.waveshare.com/wiki/Pico-LCD-2#Demo_Download)).
Part of the files are located under `lib/Config`, `lib/Fonts`, `lib/GUI`, `lib/infrared` and `lib/LCD`.

## Develop

This project was set up and developed using the [Raspberry Pi Pico](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico) extension in Visual Studio Code.
To build, flash and run the code, take a look at the tasks defined in `.vscode/tasks.json`.
