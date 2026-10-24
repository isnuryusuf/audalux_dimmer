# Copilot instructions

## Build, test, and lint

There are no repository-defined build, test, or lint scripts. The project is a single Arduino sketch, `yusuf_audalux.ino`, targeting an Arduino Uno (AVR).

With Arduino CLI installed, the AVR core and the `RBDdimmer` and `virtuabotixRTC` libraries available, compile the sketch with:

```sh
arduino-cli compile --fqbn arduino:avr:uno yusuf_audalux.ino
```

This is also the narrowest available compile check; there is no automated test suite or linter. `LiquidCrystal` and `EEPROM` are Arduino libraries used by the sketch.

## Architecture

The firmware runs from one `.ino` file. `setup()` initializes the DS1302 RTC, phase dimmer, serial logging, and 16x2 LCD. Each `loop()` reads the RTC, runs the lighting schedule, refreshes the LCD, and handles LCD keypad input for setting the clock, schedule times, and light intensities.

`runSchedule()` maps the current time into one of four configurable periods—Sunrise, Sunlight, Sunset, or Moontime. Each active period is divided into four elapsed-time stages (A–D); the corresponding stored intensity is sent to `RBDdimmer`. Schedules may cross midnight. `relayAction()` independently displays each period's active/upcoming status on the LCD.

## Hardware and code conventions

- The README describes an Arduino Uno, LCD keypad shield, DS1302 RTC, and RobotDyn AC dimmer. In the sketch, the dimmer output is pin 3, the zero-cross pin is 2, keypad input is analog pin A0, and the RTC is wired to A1–A5. The `relay1`–`relay4` macros currently all map to pin 2; do not assume they are separate relay outputs.
- Schedule and intensity settings are stored as individual EEPROM bytes in hour/minute pairs. Schedule start/end pairs occupy addresses 2–17; intensity pairs begin at 102 and occupy addresses 102–117. Keep these offsets and the UI's matching read/write paths consistent when changing persisted settings.
- The intensity address for a period points to its first stage; stages A–D use four consecutive bytes. The schedule progress calculation chooses the stage based on elapsed time, not fixed clock-hour boundaries.
- LCD button identities are determined by analog thresholds in `read_LCD_buttons()`. Menu handlers wait synchronously for button presses/releases, so changes to input handling should preserve the existing keypad-shield behavior.
- The README marks the prototype “at your own risk”; the dimmer controls mains-powered lighting. Treat hardware changes and testing accordingly.
