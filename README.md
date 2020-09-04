
Under develompent... 

# Table of Contents

* [Description](#description)

* [Setup](#setup)

* [Team](#team)

* [License](#license)

# Description

KairOS is a simple open source embedded operating system based on [FreeRTOS](https://www.freertos.org) kernel, meant to be used on embedded devices.

## KairOS Files Architecture

The KairOS Architecture is arranged in the scheme showed below:

| drivers | > | hal | > | lib | > | res |
|:-------:|:--:|:---:|:--:|:---:|:--:|:---:|
| Code you wrote to run your hardware | | KairOS hardware Abstraction | | KairOS libraries | | KairOS Application Framework |

*The structure used may be changed in the future

## Setup

Comming soon...

## Peripherals

- Main chip: ESP32
  - Flash: 16MB
  - PSRAM: 8MB
  - SRAM: 520KiB

- Display: ST7789V (1.54 inch LCD with capacitive touch screen)
- PMU(Power Manager Unit): AXP202
- Triaxial Accelerometer: BMA423
- RTC PCF8563
- Vibration Motor
- Speaker
- Infra red sensor.

More info on [Lilygo TTGO T-Watch](https://translate.google.com/translate?hl=&sl=zh-CN&tl=en&u=https%3A%2F%2Flilygo-t-watch-document.readthedocs-hosted.com%2Fzh%2Flatest%2Findex.html&sandbox=1).

# Team

| <img src="https://github.com/Calebe94.png?size=200" alt="Edimar Calebe Castanho"> |
|:---------------------------------------------------------------------------------:|
| [Edimar Calebe Castanho (Calebe94)](https://github.com/Calebe94)                  |

## Contributing

Comming soon...

# License

All software is covered under [MIT License](https://opensource.org/licenses/MIT).

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
