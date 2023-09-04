# audalux_dimmer
# Work In Progress - WIP
# DISSCLAIMER: Use Your Own Risk!!!


<img src="https://github.com/isnuryusuf/audalux_dimmer/assets/5492467/ebcd8834-74fa-4541-93c9-def7004bf52f" width=40%>



Features:
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


Referensi
  - [1] https://www.youtube.com/watch?v=BhQWOv10Oag
  - [2] https://circuitdigest.com/microcontroller-projects/ac-phase-angle-control-for-light-dimmers-and-motor-speed-control-using-555-timer-and-pwm-control
