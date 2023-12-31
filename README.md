# audalux_dimmer - Work In Progress - WIP
# DISSCLAIMER: AT YOUR OWN RISK!!

# Foto Sample Prototype
<img src="https://github.com/isnuryusuf/audalux_dimmer/assets/5492467/ebcd8834-74fa-4541-93c9-def7004bf52f" width=40%>

<img src="https://github.com/isnuryusuf/audalux_dimmer/assets/5492467/102e2a54-974a-401e-86f9-6e9bc1298642" width=30%>

<img src="https://github.com/isnuryusuf/audalux_dimmer/assets/5492467/10edff56-1b4a-495d-8fae-05f7eedf6025)" width=30%>

<img src="https://github.com/isnuryusuf/audalux_dimmer/assets/5492467/4c9ecb7e-5fcb-40fb-b326-0215b342362b" width=30%>

<img src="https://github.com/isnuryusuf/audalux_dimmer/assets/5492467/c37b0997-68fb-4cd8-8dae-32a4faa88beb" width=30%>

# Demo
https://youtu.be/7hPapCJz-5I


# Diagram
![image](https://github.com/isnuryusuf/audalux_dimmer/assets/5492467/a9ebe972-4b32-41c0-a27d-1056b8dc2876)


# Features:
- Setting Jam dan reminder Jam (jam tidak ter-reset kalo mati)
- Setting Schedule
  - Sunrise Start: jam:menit
  - Sunrise Stop: jam:menit
  - Sunglight Start: jam:menit
  - Sunglight Stop: jam:menit
  - Sunset Start: jam:menit
  - Sunset Stop: jam:menit
  - Moontime Start: jam:menit
  - Moontime Stop: jam:menit
- Setting Intensitas masing2
  - Sunrise: A > B > C >D
  - SunriseA: xx %
  - SunriseB: xx %
  - SunriseC: xx %
  - SunriseD: xx %
  - Dst
- Display
  - Status Schedule
  - Persentasi schedule yang berjalan
  - Jam
- Example Schedule log
```
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
  
Bahan-bahan:
- [Audalux LED](https://www.tokopedia.com/tj168/lampu-sorot-lampu-hias-ikan-laut-lampu-coral-biru-50-w-kabel-2-m)
- [Arduino Uno](https://pages.github.com](https://www.tokopedia.com/rajacell/arduinoo-uno-r3-smd-high-quality-atmega328-ch340g-5v-16mhz-dev-board-uno-r3-board)/)
- [LCD Keypad Shield 16x2](https://www.tokopedia.com/rajacell/lcd-keypad-shield-arduino-uno-mega-1602-blue-kualitas-no1)
- [RTC DS1302](https://www.tokopedia.com/rajacell/rtc-ds1302-battery-cr3032-real-time-clock-module-for-arduinoo)
- [220v to 9v Power Switching](https://www.tokopedia.com/kedaianekabarang/9v-500ma-4-5w-switching-power-supply-module-modul-ac-dc-adaptor)
- [Robodyn AC Dimmer](https://www.tokopedia.com/kyware/ac-light-dimmer-robotdyn-module-1-channel-220v-110v-logic-5v-3-3v)
- [Power Socket + Saklar IEC 320 C14 220V 250V 10A](https://www.tokopedia.com/rajacell/power-socket-saklar-iec-320-c14-220v-250v-10a-colokan-listrik-3-pin)
- [Kabel AWG 22 awg22 ](https://www.tokopedia.com/rajacell/kabel-awg-22-awg22-serabut-tembaga-putih-eceran-1meter-jumper-cable-kuning)
- [Socket soket cover AC 2 way outlet bakelit](https://www.tokopedia.com/grosirlegend/socket-soket-cover-ac-2-way-outlet-bakelit)
- [Kabel Komputer-Kabel Power](https://www.tokopedia.com/586shop/kabel-komputer-kabel-power-cpu-pc-kabel-magicom-1-8m-ful)


Referensi
  - [1] https://www.youtube.com/watch?v=BhQWOv10Oag
  - [2] https://circuitdigest.com/microcontroller-projects/ac-phase-angle-control-for-light-dimmers-and-motor-speed-control-using-555-timer-and-pwm-control
