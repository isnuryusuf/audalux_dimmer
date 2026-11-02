# audalux_dimmer

> Custom dimmer controller for the Audalux Reef LED, driven by an LCD keypad shield and an RTC DS1302.

![Status](https://img.shields.io/badge/status-Work%20In%20Progress-yellow)

> ⚠️ **Disclaimer**: This is a DIY project. Use it at your own risk. Any 220 V mains work must follow local safety regulations and be verified by a qualified person.

## Features

- **Jam + reminder jam**: the clock keeps running after a power failure (DS1302 + EEPROM), so schedules are not lost when the unit resets.
- **Setting schedule** (on/off time per schedule, stored in EEPROM):
  - Sunrise Start / Stop
  - Sunglight Start / Stop
  - Sunset Start / Stop
  - Moontime Start / Stop
- **Setting intensity per schedule** — 4 stages A > B > C > D, each 0–83 %.
- **Display**:
  - Current time
  - Running schedule intensity
  - Active schedule (`*`) and the next schedule (`+`)
- **Settings menu** (LCD keypad): set RTC time, schedule times, and intensity stages.

### Example schedule log

```text
00:58:41.929 -> - Run SunriseA + Intens: 26% + Delay: 30
01:59:12.013 -> - Run SunriseB + Intens: 28% + Delay: 30
00:59:41.929 -> - Run SunriseC + Intens: 26% + Delay: 30
01:00:12.013 -> - Run SunriseD + Intens: 28% + Delay: 30
01:00:42.098 -> - Run SunlightA + Intens: 36% + Delay: 30
01:01:12.062 -> - Run SunlightB + Intens: 48% + Delay: 30
01:01:42.142 -> - Run SunlightC + Intens: 56% + Delay: 30
01:02:12.151 -> - Run SunlightD + Intens: 64% + Delay: 30
01:02:42.208 -> - Run SunsetA + Intens: 48% + Delay: 30
01:03:12.276 -> - Run SunsetB + Intens: 36% + Delay: 30
01:03:42.294 -> - Run SunsetC + Intens: 28% + Delay: 30
01:04:12.377 -> - Run SunsetD + Intens: 28% + Delay: 30
01:04:42.477 -> - Run MoontimeA + Intens: 24% + Delay: 30
01:05:12.523 -> - Run MoontimeB + Intens: 22% + Delay: 30
01:05:42.589 -> - Run MoontimeC + Intens: 20% + Delay: 30
01:06:12.640 -> - Run MoontimeD + Intens: 18% + Delay: 30
```

## Bahan-bahan / Hardware

- [Audalux LED](https://www.tokopedia.com/tj168/lampu-sorot-lampu-hias-ikan-laut-lampu-coral-biru-50-w-kabel-2-m)
- [Arduino Uno](https://www.tokopedia.com/rajacell/arduinoo-uno-r3-smd-high-quality-atmega328-ch340g-5v-16mhz-dev-board-uno-r3-board)
- [LCD Keypad Shield 16x2](https://www.tokopedia.com/rajacell/lcd-keypad-shield-arduino-uno-mega-1602-blue-kualitas-no1)
- [RTC DS1302](https://www.tokopedia.com/rajacell/rtc-ds1302-battery-cr3032-real-time-clock-module-for-arduinoo)
- [220 V to DC power switching / power supply module](https://www.tokopedia.com/kedaianekabarang/9v-500ma-4-5w-switching-power-supply-module-modul-ac-dc-adaptor)
- [Robodyn AC Dimmer](https://www.tokopedia.com/kyware/ac-light-dimmer-robotdyn-module-1-channel-220v-110v-logic-5v-3-3v)
- [Power Socket + Switch IEC 320 C14 220V 250V 10A](https://www.tokopedia.com/rajacell/power-socket-saklar-iec-320-c14-220v-250v-10a-colokan-listrik-3-pin)
- [Kabel AWG 22](https://www.tokopedia.com/rajacell/kabel-awg-22-awg22-serabut-tembaga-putih-eceran-1meter-jumper-cable-kuning)
- [Socket / soket cover AC 2 way outlet bakelit](https://www.tokopedia.com/grosirlegend/socket-soket-cover-ac-2-way-outlet-bakelit)
- [Kabel Komputer-Kabel Power](https://www.tokopedia.com/586shop/kabel-komputer-kabel-power-cpu-pc-kabel-magicom-1-8m-ful)

## Sketch pins (main)

| Signal | Pin |
| --- | --- |
| Dimmer output | 3 |
| LCD RS / E | 8 / 9 |
| LCD data D4–D7 | 4 / 5 / 6 / 7 |
| Keypad (analog) | A0 |
| RTC DS1302 SCLK / IO / CE | A3 / A2 / A1 |
| Relays (currently unused) | 10 / 11 / 12 / 13 |

> The relay pin `#define`s were originally all `2` (a copy-paste error) and collided with the `zerocross` pin. They are left unconnected until the relay driver is added; map them to your actual relay board before wiring.

## Setup / How to use

1. Upload `yusuf_audalux.ino` to the Arduino Uno.
2. **Set time**: press `SELECT` > UP (TIME SETTING) and enter the current time. The RTC date is fixed to the default value (day 10 / month 1 / year 2014 by design) — only the time can be changed from the menu.
3. **Set schedules**: press `SELECT` > DOWN (SCHED SETTING) for Sunrise, Sunglight, Sunset, and Moontime on/off times.
4. **Set intensity**: press `SELECT` > DOWN (INTS SETTING) for the A > B > C > D stages of each schedule.
5. Power the dimmer through the Robodyn AC dimmer module.

## Demo


![Audalux Dimmer Demo](https://img.youtube.com/vi/7hPapCJz-5I/hqdefault.jpg)

<a href="https://youtu.be/7hPapCJz-5I" target="_blank">Open the demo on YouTube ↗</a>

## Photos

<img src="https://github.com/isnuryusuf/audalux_dimmer/assets/5492467/ebcd8834-74fa-4541-93c9-def7004bf52f" width="40%">
<img src="https://github.com/isnuryusuf/audalux_dimmer/assets/5492467/102e2a54-974a-401e-86f9-6e9bc1298642" width="30%">
<img src="https://github.com/isnuryusuf/audalux_dimmer/assets/5492467/10edff56-1b4a-495d-8fae-05f7eedf6025" width="30%">
<img src="https://github.com/isnuryusuf/audalux_dimmer/assets/5492467/4c9ecb7e-5fcb-40fb-b326-0215b342362b" width="30%">
<img src="https://github.com/isnuryusuf/audalux_dimmer/assets/5492467/c37b0997-68fb-4cd8-8dae-32a4faa88beb" width="30%">

## Diagram

<svg viewBox="0 0 1200 640" xmlns="http://www.w3.org/2000/svg" width="100%" height="auto">
  <rect width="1200" height="640" fill="#fafafa"/>
  <!-- AC INPUT POWER SECTION (left) -->
  <rect x="8" y="20" width="380" height="590" rx="10" fill="#1e1f1e" stroke="#3a3535" stroke-width="2"/>
  <text x="198" y="34" text-anchor="middle" fill="#8fd38f" font-size="15" font-weight="bold" letter-spacing="1">AC INPUT (220 V)</text>
  <rect x="14" y="72" width="150" height="40" rx="8" fill="#2a2727" stroke="#5a5252" stroke-width="1.5"/>
  <text x="89" y="96" text-anchor="middle" fill="#cfd6da" font-size="11" font-weight="bold">IEC 320 C14</text>
  <text x="89" y="110" text-anchor="middle" fill="#8f8a8a" font-size="8">AC OUTLET</text>
  <rect x="14" y="122" width="150" height="34" rx="5" fill="#2a2727" stroke="#5a5252" stroke-width="1.5"/>
  <text x="89" y="146" text-anchor="middle" fill="#cfd6da" font-size="10" font-weight="bold">POWER SWITCH</text>
  <rect x="14" y="170" width="150" height="80" rx="6" fill="#232020" stroke="#4a4545" stroke-width="1.5"/>
  <text x="89" y="202" text-anchor="middle" fill="#8fd38f" font-size="10" font-weight="bold">AC INPUT BUS</text>
  <text x="89" y="218" text-anchor="middle" fill="#8f8a8a" font-size="9">(+):220 V &middot; (&minus;):GND</text>
  <rect x="14" y="266" width="150" height="70" rx="6" fill="#232020" stroke="#4a4545" stroke-width="1.5"/>
  <text x="89" y="290" text-anchor="middle" fill="#8fd38f" font-size="10" font-weight="bold">9 V DC PSU</text>
  <text x="89" y="304" text-anchor="middle" fill="#8f8a8a" font-size="9">(5 V / 9 V out)</text>
  <rect x="14" y="350" width="150" height="60" rx="6" fill="#232020" stroke="#4a4545" stroke-width="1.5"/>
  <text x="89" y="374" text-anchor="middle" fill="#8fd38f" font-size="10" font-weight="bold">5 V REGULATOR</text>
  <text x="89" y="388" text-anchor="middle" fill="#8f8a8a" font-size="9">(7805)</text>
  <rect x="14" y="426" width="150" height="140" rx="10" fill="#241f1f" stroke="#4a4545" stroke-width="2"/>
  <text x="89" y="462" text-anchor="middle" fill="#8fd38f" font-size="13" font-weight="bold">ARDUINO UNO</text>
  <text x="89" y="480" text-anchor="middle" fill="#8f8a8a" font-size="9">(ATmega328P)</text>
  <text x="89" y="496" text-anchor="middle" fill="#8f8a8a" font-size="9">+5V &middot; GND &middot; RESET</text>
  <rect x="34" y="506" width="112" height="44" rx="8" fill="#261f1f" stroke="#5a6a7a" stroke-width="1.5"/>
  <text x="90" y="528" text-anchor="middle" fill="#cfd6da" font-size="10" font-weight="bold">20 PIN HEADER</text>
  <!-- CONTROL BOARD -->
  <rect x="812" y="20" width="380" height="590" rx="10" fill="#1e1f1e" stroke="#3a3535" stroke-width="2"/>
  <text x="1002" y="34" text-anchor="middle" fill="#8fd38f" font-size="13" font-weight="bold" letter-spacing="1">CONTROL</text>
  <rect x="852" y="60" width="200" height="100" rx="10" fill="#241f1f" stroke="#5a6a7a" stroke-width="2"/>
  <text x="952" y="100" text-anchor="middle" fill="#8fd38f" font-size="12" font-weight="bold">LCD 16&times;2</text>
  <text x="952" y="116" text-anchor="middle" fill="#8f8a8a" font-size="9">HD44780</text>
  <text x="952" y="130" text-anchor="middle" fill="#8f8a8a" font-size="9">RS=8 &middot; E=9</text>
  <text x="952" y="144" text-anchor="middle" fill="#8f8a8a" font-size="9">D4=4 D5=5</text>
  <text x="952" y="158" text-anchor="middle" fill="#8f8a8a" font-size="9">D6=6 D7=7</text>
  <rect x="882" y="170" width="136" height="60" rx="8" fill="#2a2727" stroke="#5a6a7a" stroke-width="1.5"/>
  <text x="950" y="196" text-anchor="middle" fill="#cfd6da" font-size="10" font-weight="bold">LCD KEYPAD</text>
  <text x="950" y="210" text-anchor="middle" fill="#8f8a8a" font-size="9">SELECT &middot; UP &middot; DOWN</text>
  <text x="950" y="224" text-anchor="middle" fill="#8f8a8a" font-size="9">LEFT &middot; RIGHT</text>
  <rect x="862" y="250" width="176" height="44" rx="6" fill="#232020" stroke="#5a6a7a" stroke-width="1.5"/>
  <text x="950" y="274" text-anchor="middle" fill="#8fd38f" font-size="10" font-weight="bold">KEYPAD ROW</text>
  <text x="950" y="288" text-anchor="middle" fill="#8f8a8a" font-size="9">&rarr; Pins 1&ndash;6</text>
  <rect x="832" y="316" width="240" height="120" rx="10" fill="#232020" stroke="#5a6a7a" stroke-width="2"/>
  <text x="952" y="362" text-anchor="middle" fill="#8fd38f" font-size="13" font-weight="bold">DS1302 RTC</text>
  <text x="952" y="378" text-anchor="middle" fill="#8f8a8a" font-size="9">realtime clock</text>
  <text x="952" y="394" text-anchor="middle" fill="#8f8a8a" font-size="9">VCC&Aring;5 &middot; GND&Aring;4</text>
  <text x="952" y="408" text-anchor="middle" fill="#8f8a8a" font-size="9">SCLK&Aring;3 &middot; IO&Aring;2 &middot; CE&Aring;1</text>
  <!-- ROBODYN DIMMER -->
  <rect x="200" y="320" width="760" height="220" rx="12" fill="#232020" stroke="#4a4545" stroke-width="2"/>
  <text x="580" y="344" text-anchor="middle" fill="#8fd38f" font-size="14" font-weight="bold">ROBODYN AC LIGHT DIMMER</text>
  <text x="580" y="360" text-anchor="middle" fill="#8f8a8a" font-size="9">U1 &middot; Triac phase-cut dimmer</text>
  <text x="580" y="374" text-anchor="middle" fill="#8f8a8a" font-size="9">Logic: +5 V / GND &middot; Zero-Cross</text>
  <rect x="400" y="390" width="80" height="28" rx="4" fill="#d0ff90" stroke="#8f8a8a" stroke-width="1.5"/>
  <text x="440" y="408" text-anchor="middle" fill="#5a5252" font-size="9" font-weight="bold">D3&larr;dimmer in</text>
  <rect x="400" y="420" width="80" height="28" rx="4" fill="#d0ff90" stroke="#8f8a8a" stroke-width="1.5"/>
  <text x="440" y="438" text-anchor="middle" fill="#5a5252" font-size="9" font-weight="bold">D2&larr;zero</text>
  <text x="440" y="458" text-anchor="middle" fill="#8f8a8a" font-size="8">(&mu;C digital out)</text>
  <rect x="220" y="450" width="400" height="80" rx="8" fill="#2a2727" stroke="#5a6a7a" stroke-width="2"/>
  <text x="420" y="474" text-anchor="middle" fill="#8fd38f" font-size="11" font-weight="bold">RELAYS (unwired)</text>
  <text x="420" y="488" text-anchor="middle" fill="#8f8a8a" font-size="9">relay1=10 &middot; relay2=11</text>
  <text x="420" y="502" text-anchor="middle" fill="#8f8a8a" font-size="9">relay3=12 &middot; relay4=13</text>
  <rect x="660" y="460" width="280" height="60" rx="8" fill="#1e1f1e" stroke="#5a6a7a" stroke-width="1.5"/>
  <text x="800" y="490" text-anchor="middle" fill="#8fd38f" font-size="11" font-weight="bold">LIGHT (Audalux LED)</text>
  <text x="800" y="504" text-anchor="middle" fill="#8f8a8a" font-size="9">220 V AC via contacts</text>
  <line x1="660" y1="490" x2="800" y2="490" stroke="#4a4545" stroke-width="1"/>
  <circle cx="660" cy="490" r="6" fill="#ffd080" stroke="#8f8a8a" stroke-width="1"/>
  <text x="660" y="490" text-anchor="middle" fill="#5a5252" font-size="9" font-weight="bold">LED</text>
  <rect x="200" y="530" width="760" height="50" rx="8" fill="#2a2727" stroke="#5a6a7a" stroke-width="1.5"/>
  <text x="580" y="556" text-anchor="middle" fill="#8f8a8a" font-size="9">
    <tspan fill="#cfd6da" font-weight="bold">Pins:</tspan> A0=Keypad &middot; A1=CE &middot; A2=IO &middot; A3=SCLK &middot; A4=GND &middot; A5=VCC &middot; D2=zero &middot; D3=dimmer &middot; D4-7=LCD &middot; D10-13=relays
  </text>
</svg>



## References

1. https://www.youtube.com/watch?v=BhQWOv10Oag
2. https://circuitdigest.com/microcontroller-projects/ac-phase-angle-control-for-light-dimmers-and-motor-speed-control-using-555-timer-and-pwm-control
