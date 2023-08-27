#include <RBDdimmer.h>
#include "LiquidCrystal.h"
#include <EEPROM.h>
#include <virtuabotixRTC.h>
//#include "RTClib.h"

//#define USE_SERIAL  SerialUSB
#define USE_SERIAL  Serial
#define outputPin  3
#define zerocross  2 // for boards with CHANGEBLE input pins

/* ================================================== */
/* DEF Functions                                      */
/* ================================================== */
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int lcd_key     = 0;
int adc_key_in  = 0;

//dimmerLamp dimmer(outputPin, zerocross); //initialase port for dimmer for ESP8266, ESP32, Arduino due boards
dimmerLamp dimmer(outputPin); //initialase port for dimmer for MEGA, Leonardo, UNO, Arduino M0, Arduino Zero

int outVal = 0;
int SunRi1;
int SunRi2;
int SunRi3;
int SunRi4;
int SunLi1;
int SunLi2;
int SunLi3;
int SunLi4;
int SunSe1;
int SunSe2;
int SunSe3;
int SunSe4;
int MoonTi1;
int MoonTi2;
int MoonTi3;
int MoonTi4;

// relay pins
#define relay1      2
#define relay2      2
#define relay3      2
#define relay4      2

// define pins of RTC module
#define rtcVCC      A5
#define rtcGND      A4
#define rtcSCLK     A3
#define rtcIO       A2
#define rtcCE       A1

// creation of RTC object
virtuabotixRTC myRTC(rtcSCLK, rtcIO, rtcCE);

// keypad definitions
#define btnRIGHT    0
#define btnUP       1
#define btnDOWN     2
#define btnLEFT     3
#define btnSELECT   4
#define btnNONE     5

// mode definitions
#define modeSETUP   1
#define modeNORMAL  2
int mode = 1; // set default mode

// EEPROM adrressing
#define adr1ON    2
#define adr1OF    4
#define adr2ON    6
#define adr2OF    8
#define adr3ON    10
#define adr3OF    12
#define adr4ON    14
#define adr4OF    16

#define adr1ON2    102
#define adr1OF2    104
#define adr2ON2    106
#define adr2OF2    108
#define adr3ON2    110
#define adr3OF2    112
#define adr4ON2    114
#define adr4OF2    116

int eepromMin = 0;
int eepromHour = 0;
int eepromHourON = 0;
int eepromHourOF = 0;
int eepromMinON = 0;
int eepromMinOF = 0;

int eepromMin2 = 0;
int eepromHour2 = 0;
int eepromHourON2 = 0;
int eepromHourOF2 = 0;
int eepromMinON2 = 0;
int eepromMinOF2 = 0;

int testDimmer = 0;

/* ================================================== */
/* SETUP                                  */
/* ================================================== */
void setup() {
  // jadikan semua digital pin sbg output
  /*for (int i = 0; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  */
  // activate RTC module 
  pinMode(rtcVCC,  OUTPUT);
  pinMode(rtcGND,  OUTPUT);
  pinMode(rtcSCLK, OUTPUT);
  pinMode(rtcIO,   OUTPUT);
  pinMode(rtcCE,   OUTPUT);
  digitalWrite(rtcVCC, HIGH);
  digitalWrite(rtcGND, LOW);
  delay(500);

  /*
  //moontime
  EEPROM.write(100, 24);
  //sunrise
  EEPROM.write(101, 26);
  EEPROM.write(102, 28);
  EEPROM.write(103, 30);
  EEPROM.write(104, 32);
  EEPROM.write(105, 34);
  EEPROM.write(106, 36);
  EEPROM.write(107, 38);
  EEPROM.write(108, 40);
  EEPROM.write(109, 42);
  EEPROM.write(110, 46);
  EEPROM.write(111, 58);
  //sunlight
  EEPROM.write(201, 64);
  EEPROM.write(202, 84);
  //sunset
  EEPROM.write(301, 26);
  EEPROM.write(302, 28);
  EEPROM.write(303, 30);
  EEPROM.write(304, 32);
  EEPROM.write(305, 34);
  EEPROM.write(306, 36);
  EEPROM.write(307, 38);
  EEPROM.write(308, 40);
  EEPROM.write(309, 42);
  EEPROM.write(310, 46);
  EEPROM.write(311, 58);
  */

  //debuging mode
  USE_SERIAL.begin(9600); 
  dimmer.begin(NORMAL_MODE, ON); //dimmer initialisation: name.begin(MODE, STATE) 
  USE_SERIAL.println("Audalux Reef LED ");
  //USE_SERIAL.println("Set value");

  lcd.begin(16, 2);              // start the library
  //lcd.setCursor(0, 0);
  //lcd.print("Audalux Reef LED"); 
}

void printSpace(int val)
{
  if ((val / 100) == 0) USE_SERIAL.print(" ");
  if ((val / 10) == 0) USE_SERIAL.print(" ");
}
/* ================================================== */
/* END SETUP                                          */
/* ================================================== */


/* ================================================== */
/* LOOP                                               */
/* ================================================== */
void loop() {

  lcd.setCursor(0, 0); 
  lcd.print("JAM ");
  lcd.setCursor(4, 0);
    // tampilkan jam:menit:detik di tengah
  displayTime();

  // tampilkan intensitas yang berjalan
  lcd.setCursor(13, 0); 
  lcd.print(dimmer.getPower());
  if (outVal <= 9) {
    lcd.print("% ");
  } else if (outVal >= 10 && outVal <= 99) {
    lcd.print("%");
  }
  lcd.print("%");

  // set & tampilkan status schedule berdasarkan data eeprom
  // * = Sedang berjalan, + = akan berjalan di hari yg sama, b = scheduler berjalan next day
  lcd.setCursor(0, 1); 
  lcd.print("R:");
  // 2, 1
  relayAction(adr1ON, adr1OF, 2, relay1);
  lcd.setCursor(4, 1); 
  lcd.print("L:");
  // 6, 1
  relayAction(adr2ON, adr2OF, 6, relay2);
  lcd.setCursor(8, 1); 
  lcd.print("S:");
  // 10, 1
  relayAction(adr3ON, adr3OF, 10, relay3);
  lcd.setCursor(12, 1); 
  lcd.print("M:");
  // 14, 1
  relayAction(adr4ON, adr4OF, 14, relay4);

  // jika user menekan tombol SELECT, masuk menu setting
  // set Schedule Audalux sunrise, sunlight, sunset, moontime
  if (read_LCD_buttons() == btnSELECT) {
    while (read_LCD_buttons() == btnSELECT);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("UP. TIME SETTING");
    lcd.setCursor(0, 1);
    lcd.print("DN. SCHE SETTING");
    while (read_LCD_buttons() == btnNONE);
    if (read_LCD_buttons() == btnUP) {
      while (read_LCD_buttons() == btnUP);
      setRTC();   // jika user menekan tombol UP, masuk menu setting RTC/jam
    }
    else if (read_LCD_buttons() == btnDOWN) {
      while (read_LCD_buttons() == btnDOWN);
      setPin();   // jika user menekan tombol DOWN, masuk menu setting SCHED
    }
    else if (read_LCD_buttons() == btnRIGHT) {
      while (read_LCD_buttons() == btnRIGHT);
      lcd.clear();
    }
  }

  // set intensitas LED sunrise, sunlight, sunset, moontime
  if (read_LCD_buttons() == btnLEFT) {
    while (read_LCD_buttons() == btnLEFT);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RI. BACK");
    lcd.setCursor(0, 1);
    lcd.print("DN. INTS SETTING");
    while (read_LCD_buttons() == btnNONE);
    if (read_LCD_buttons() == btnUP) {
      while (read_LCD_buttons() == btnUP);
      lcd.clear();
    }
    else if (read_LCD_buttons() == btnDOWN) {
      while (read_LCD_buttons() == btnDOWN);
      setIntense();   // jika user menekan tombol DOWN, masuk menu setting intensitas
    }
    else if (read_LCD_buttons() == btnRIGHT) {
      while (read_LCD_buttons() == btnRIGHT);
      lcd.clear();
    }
  }
}

// check schedule dan action
void relayAction(int adrON, int adrOF, int pos, int pin) {
 
  //fungsi ds1302
  myRTC.updateTime();
  int MinToday = (myRTC.hours * 60) + myRTC.minutes; //jam sekarang jadi total menit
  int MinEprON = (EEPROM.read(adrON) * 60) + EEPROM.read(adrON + 1); //jam+menit start dalam menit untuk semua schedule
  int MinEprOF = (EEPROM.read(adrOF) * 60) + EEPROM.read(adrOF + 1); //jam+menit stop dalam menit untuk semua schedule

  //cuma buat debug
  /*
  Serial.print(now.hour());
  Serial.print('\n');
  Serial.print(now.minute());
  Serial.print('\n');
  Serial.print(MinToday);
  delay(1000);
  Serial.print('\n');
  Serial.print(MinEprON);
  delay(1000);
  Serial.print('\n');
  Serial.print(MinEprOF);
  delay(1000);
  Serial.print('\n');
  */
  
  lcd.setCursor(pos, 1);
  if (MinEprON == MinEprOF) {  // jika start-stop sama berarti tidak dipake
    lcd.print(" "); //tidak ada schedule di set
    //digitalWrite(pin, LOW);
    Serial.print('No-schedule');
  }
  else if (MinEprON < MinEprOF) { // kondisi ON terjadi di hari yg sama, contoh start 01:00, stop 02:00
    if ((MinEprON <= MinToday) && (MinEprOF > MinToday)) {
      lcd.print("*");
      //digitalWrite(pin, LOW);
      dimmer.setPower(20);
     }
    else {
      lcd.print("+");
      //digitalWrite(pin, HIGH);
      //sunRiseValue();
      //sunLightValue();
      //sunSetValue();
      moonLightValue();
      //testDimmer = EEPROM.read(adr4ON2);
      //dimmer.setPower(testDimmer);
      //dimmer.setPower(84);
      int durationSched = (MinEprON * 3600) - (MinEprOF * 3600);
      //Serial.print('durationSched');
      //Serial.print('\n');
      //Serial.print(MinEprON);
      //Serial.print('\n');
      //Serial.print(MinEprOF);
      //Serial.print('\n');
      //delay(durationSched);
      //delay(1000); 
      
     }
  }
  else if (MinEprON > MinEprOF) {  // kondisi ON terjadi sampai besoknya
    if ((MinEprON >= MinToday) || (MinEprOF < MinToday)) {
      lcd.print("b");
      //digitalWrite(pin, LOW);
      dimmer.setPower(40);
    }
    else {
      lcd.print("-");
      //digitalWrite(pin, HIGH);
      dimmer.setPower(50);
    }
  }
}
/* ================================================== */
/* END LOOP                                    */
/* ================================================== */

/* ================================================== */
/* SETUP Functions                                    */
/* ================================================== */

void setRTC() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TIME SETTING");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CURRENT ");
  setupShowValue(myRTC.hours, myRTC.minutes, 0);

  lcd.setCursor(0, 1);
  lcd.print("NEW ");

  myRTC.updateTime();
  setupShowValue(myRTC.hours, myRTC.minutes, 1);
  setupShowValue2(myRTC.hours, myRTC.minutes, 1);
  while (read_LCD_buttons() == btnNONE);
  setupChooseValueSetRTC(myRTC.hours, myRTC.minutes, 1);
  lcd.setCursor(0,0);
  lcd.print("SETTINGS SAVED   ");
  delay(1000);
  lcd.clear();
}
/* ================================================== */
/* END LOOP                                           */
/* ================================================== */


void setPin() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SCHED SETTING");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sunris ON");
  eepromHour = EEPROM.read(adr1ON);
  eepromMin = EEPROM.read(adr1ON + 1);
  if (eepromHour >= 24) eepromHour = 0;
  if (eepromMin  >= 60) eepromMin  = 0;
  setupShowValue(eepromHour, eepromMin, 0);
  while (read_LCD_buttons() == btnNONE);
  setupChooseValue(eepromHour, eepromMin, adr1ON, 0);

  lcd.setCursor(0, 1);
  lcd.print("Sunris OFF");
  eepromHour = EEPROM.read(adr1OF);
  eepromMin = EEPROM.read(adr1OF + 1);
  if (eepromHour >= 24) eepromHour = 0;
  if (eepromMin  >= 60) eepromMin  = 0;
  setupShowValue(eepromHour, eepromMin, 1);
  while (read_LCD_buttons() == btnNONE);
  setupChooseValue(eepromHour, eepromMin, adr1OF, 1);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sunlig ON");
  eepromHour = EEPROM.read(adr2ON);
  eepromMin = EEPROM.read(adr2ON + 1);
  if (eepromHour >= 24) eepromHour = 0;
  if (eepromMin  >= 60) eepromMin  = 0;
  setupShowValue(eepromHour, eepromMin, 0);
  while (read_LCD_buttons() == btnNONE);
  setupChooseValue(eepromHour, eepromMin, adr2ON, 0);

  lcd.setCursor(0, 1);
  lcd.print("Sunlig OFF");
  eepromHour = EEPROM.read(adr2OF);
  eepromMin = EEPROM.read(adr2OF + 1);
  if (eepromHour >= 24) eepromHour = 0;
  if (eepromMin  >= 60) eepromMin  = 0;
  setupShowValue(eepromHour, eepromMin, 1);
  while (read_LCD_buttons() == btnNONE);
  setupChooseValue(eepromHour, eepromMin, adr2OF, 1);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sunset ON");
  eepromHour = EEPROM.read(adr3ON);
  eepromMin = EEPROM.read(adr3ON + 1);
  if (eepromHour >= 24) eepromHour = 0;
  if (eepromMin  >= 60) eepromMin  = 0;
  setupShowValue(eepromHour, eepromMin, 0);
  while (read_LCD_buttons() == btnNONE);
  setupChooseValue(eepromHour, eepromMin, adr3ON, 0);

  lcd.setCursor(0, 1);
  lcd.print("Sunset OFF");
  eepromHour = EEPROM.read(adr3OF);
  eepromMin = EEPROM.read(adr3OF + 1);
  if (eepromHour >= 24) eepromHour = 0;
  if (eepromMin  >= 60) eepromMin  = 0;
  setupShowValue(eepromHour, eepromMin, 1);
  while (read_LCD_buttons() == btnNONE);
  setupChooseValue(eepromHour, eepromMin, adr3OF, 1);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moon ON");
  eepromHour = EEPROM.read(adr4ON);
  eepromMin = EEPROM.read(adr4ON + 1);
  if (eepromHour >= 24) eepromHour = 0;
  if (eepromMin  >= 60) eepromMin  = 0;
  setupShowValue(eepromHour, eepromMin, 0);
  while (read_LCD_buttons() == btnNONE);
  setupChooseValue(eepromHour, eepromMin, adr4ON, 0);

  lcd.setCursor(0, 1);
  lcd.print("Moon OFF");
  eepromHour = EEPROM.read(adr4OF);
  eepromMin = EEPROM.read(adr4OF + 1);
  if (eepromHour >= 24) eepromHour = 0;
  if (eepromMin  >= 60) eepromMin  = 0;
  setupShowValue(eepromHour, eepromMin, 1);
  while (read_LCD_buttons() == btnNONE);
  setupChooseValue(eepromHour, eepromMin, adr4OF, 1);

}

void setIntense() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AUDALUX SETTING");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sunris 1>2");
  eepromHour2 = EEPROM.read(adr1ON2);
  eepromMin2 = EEPROM.read(adr1ON2 + 1);
  if (eepromHour2 >= 84) eepromHour2 = 0;
  if (eepromMin2  >= 84) eepromMin2  = 0;
  setupShowValue2(eepromHour2, eepromMin2, 0);
  while (read_LCD_buttons() == btnNONE);
  setupChooseValue2(eepromHour2, eepromMin2, adr1ON2, 0);

  lcd.setCursor(0, 1);
  lcd.print("Sunris 3>4");
  eepromHour2 = EEPROM.read(adr1OF2);
  eepromMin2 = EEPROM.read(adr1OF2 + 1);
  if (eepromHour2 >= 84) eepromHour2 = 0;
  if (eepromMin2  >= 84) eepromMin2  = 0;
  setupShowValue2(eepromHour2, eepromMin2, 1);
  while (read_LCD_buttons() == btnNONE);
  setupChooseValue2(eepromHour2, eepromMin2, adr1OF2, 1);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sunlig 1>2");
  eepromHour2 = EEPROM.read(adr2ON2);
  eepromMin2 = EEPROM.read(adr2ON2 + 1);
  if (eepromHour2 >= 84) eepromHour2 = 0;
  if (eepromMin2  >= 84) eepromMin2  = 0;
  setupShowValue2(eepromHour2, eepromMin2, 0);
  while (read_LCD_buttons() == btnNONE);
  setupChooseValue2(eepromHour2, eepromMin2, adr2ON2, 0);

  lcd.setCursor(0, 1);
  lcd.print("Sunlig 3>4");
  eepromHour2 = EEPROM.read(adr2OF2);
  eepromMin2 = EEPROM.read(adr2OF2 + 1);
  if (eepromHour2 >= 84) eepromHour2 = 0;
  if (eepromMin2  >= 84) eepromMin2  = 0;
  setupShowValue2(eepromHour2, eepromMin2, 1);
  while (read_LCD_buttons() == btnNONE);
  setupChooseValue2(eepromHour2, eepromMin2, adr2OF2, 1);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sunset 1>2");
  eepromHour2 = EEPROM.read(adr3ON2);
  eepromMin2 = EEPROM.read(adr3ON2 + 1);
  if (eepromHour2 >= 84) eepromHour2 = 0;
  if (eepromMin2  >= 84) eepromMin2  = 0;
  setupShowValue2(eepromHour2, eepromMin2, 0);
  while (read_LCD_buttons() == btnNONE);
  setupChooseValue2(eepromHour2, eepromMin2, adr3ON2, 0);

  lcd.setCursor(0, 1);
  lcd.print("Sunset 3>4");
  eepromHour2 = EEPROM.read(adr3OF2);
  eepromMin2 = EEPROM.read(adr3OF2 + 1);
  if (eepromHour2 >= 84) eepromHour2 = 0;
  if (eepromMin2  >= 84) eepromMin2  = 0;
  setupShowValue2(eepromHour2, eepromMin2, 1);
  while (read_LCD_buttons() == btnNONE);
  setupChooseValue2(eepromHour2, eepromMin2, adr3OF2, 1);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moon 1>2");
  eepromHour2 = EEPROM.read(adr4ON2);
  eepromMin2 = EEPROM.read(adr4ON2 + 1);
  if (eepromHour2 >= 84) eepromHour2 = 0;
  if (eepromMin2  >= 84) eepromMin2  = 0;
  setupShowValue2(eepromHour2, eepromMin2, 0);
  while (read_LCD_buttons() == btnNONE);
  setupChooseValue2(eepromHour2, eepromMin2, adr4ON2, 0);

  lcd.setCursor(0, 1);
  lcd.print("Moon 3>4");
  eepromHour2 = EEPROM.read(adr4OF2);
  eepromMin2 = EEPROM.read(adr4OF2 + 1);
  if (eepromHour2 >= 84) eepromHour2 = 0;
  if (eepromMin2  >= 84) eepromMin2  = 0;
  setupShowValue2(eepromHour2, eepromMin2, 1);
  while (read_LCD_buttons() == btnNONE);
  setupChooseValue2(eepromHour2, eepromMin2, adr4OF2, 1);

}

void setupChooseValue(int HourNew, int MinNew, byte Address, byte Pos) {
  while (read_LCD_buttons() != btnSELECT) {
    if (read_LCD_buttons() == btnRIGHT) {
      if (HourNew < 23) {
        HourNew++;
      }
    }
    else if (read_LCD_buttons() == btnLEFT) {
      if (HourNew > 0) {
        HourNew--;
      }
    }
    else if (read_LCD_buttons() == btnUP) {
      if (MinNew < 59) {
        MinNew++;
      }
    }
    else if (read_LCD_buttons() == btnDOWN) {
      if (MinNew > 0) {
        MinNew--;
      }
    }
    setupShowValue(HourNew, MinNew, Pos);
    delay(150);
  }
  while (read_LCD_buttons() != btnNONE);  // tunggu sampai tombol rilis
  EEPROM.write(Address, HourNew);
  EEPROM.write(Address + 1, MinNew);
  delay(150);
}

void setupChooseValue2(int HourNew2, int MinNew2, byte Address2, byte Pos) {
  while (read_LCD_buttons() != btnSELECT) {
    if (read_LCD_buttons() == btnRIGHT) {
      if (HourNew2 < 84) {
        HourNew2++;
      }
    }
    else if (read_LCD_buttons() == btnLEFT) {
      if (HourNew2 > 0) {
        HourNew2--;
      }
    }
    else if (read_LCD_buttons() == btnUP) {
      if (MinNew2 < 84) {
        MinNew2++;
      }
    }
    else if (read_LCD_buttons() == btnDOWN) {
      if (MinNew2 > 0) {
        MinNew2--;
      }
    }
    setupShowValue2(HourNew2, MinNew2, Pos);
    delay(150);
  }
  while (read_LCD_buttons() != btnNONE);  // tunggu sampai tombol rilis
  EEPROM.write(Address2, HourNew2);
  EEPROM.write(Address2 + 1, MinNew2);
  delay(150);
}


void setupChooseValueSetRTC(int HourNew, int MinNew, byte Pos) {
  while (read_LCD_buttons() != btnSELECT) {
    if (read_LCD_buttons() == btnRIGHT) {
      if (HourNew < 23) {
        HourNew++;
      }
    }
    else if (read_LCD_buttons() == btnLEFT) {
      if (HourNew > 0) {
        HourNew--;
      }
    }
    else if (read_LCD_buttons() == btnUP) {
      if (MinNew < 59) {
        MinNew++;
      }
    }
    else if (read_LCD_buttons() == btnDOWN) {
      if (MinNew > 0) {
        MinNew--;
      }
    }
    setupShowValue(HourNew, MinNew, Pos);
    delay(150);
  }
  while (read_LCD_buttons() != btnNONE);  // tunggu sampai tombol rilis
  myRTC.setDS1302Time(00, MinNew, HourNew, 6, 10, 1, 2014); //detik, menit, jam, hari dalam seminggu, tanggal, bulan, tahun
  delay(150);
}

void setupShowValue(int Hour, int Min, int Pos) {
  lcd.setCursor(11, Pos);
  print2digits(Hour);
  lcd.print(":");
  print2digits(Min);
}

void setupShowValue2(int Hour, int Min, int Pos) {
  lcd.setCursor(11, Pos);
  print2digits(Hour);
  lcd.print(":");
  print2digits(Min);
}

/* ================================================== */
/* LCD Functions                                      */
/* ================================================== */
int read_LCD_buttons()
{
  adc_key_in = analogRead(0);       // read the value from the LCD

  if (adc_key_in > 1000) return btnNONE; 
  if (adc_key_in < 50)   return btnRIGHT;  
  if (adc_key_in < 150)  return btnUP; 
  if (adc_key_in < 300)  return btnDOWN; 
  if (adc_key_in < 500)  return btnLEFT; 
  if (adc_key_in < 850)  return btnSELECT;  
  return btnNONE;                // when all others fail, return this.
}

void eeprom_write_int(int p_address, int p_value) {
  byte lowByte = ((p_value >> 0) & 0xFF);
  byte highByte = ((p_value >> 8) & 0xFF);

  EEPROM.write(p_address, lowByte);
  EEPROM.write(p_address + 1, highByte);
}

void eeprom_write_int2(int p_address2, int p_value2) {
  byte lowByte = ((p_value2 >> 0) & 0xFF);
  byte highByte = ((p_value2 >> 8) & 0xFF);

  EEPROM.write(p_address2, lowByte);
  EEPROM.write(p_address2 + 1, highByte);
}

unsigned int eeprom_read_int(int p_address) {
  byte lowByte = EEPROM.read(p_address);
  byte highByte = EEPROM.read(p_address + 1);

  return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}

unsigned int eeprom_read_int2(int p_address2) {
  byte lowByte = EEPROM.read(p_address2);
  byte highByte = EEPROM.read(p_address2 + 1);

  return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}

void displayTime() {

  myRTC.updateTime();
  print2digits(myRTC.hours);
  lcd.print(":");
  print2digits(myRTC.minutes);
  lcd.print(":");
  print2digits(myRTC.seconds);
}

void print2digits(int number) {
  if (number >= 0 && number < 10)
    lcd.print('0');
  lcd.print(number, DEC);
}


void sunRiseValue() {
/////////////////////////////////////////////////////
  SunRi1 = EEPROM.read(101);
  dimmer.setPower(SunRi1); // setPower(0-100%);

  {
    USE_SERIAL.print("lampValue -> ");
    printSpace(dimmer.getPower());
    USE_SERIAL.print(dimmer.getPower());
    USE_SERIAL.println("%");
  }
  /*
  lcd.setCursor(0, 0);
  lcd.print("Audalux Sunrise ");

  lcd.setCursor(0, 1);
  lcd.print("Setting: ");
  lcd.print(dimmer.getPower());
  if (outVal <= 9) {
    lcd.print("  ");
  } else if (outVal >= 10 && outVal <= 99) {
    lcd.print(" ");
  }
  lcd.print(" %");
  */
  //delay(500);
}


void sunLightValue() {
/////////////////////////////////////////////////////
  dimmer.setPower(84); // setPower(0-100%);

  {
    USE_SERIAL.print("lampValue -> ");
    printSpace(dimmer.getPower());
    USE_SERIAL.print(dimmer.getPower());
    USE_SERIAL.println("%");

  }
  /*
  lcd.setCursor(0, 0);
  lcd.print("Audalux Sunlight");

  lcd.setCursor(0, 1);
  lcd.print("Setting: ");
  lcd.print(dimmer.getPower());
  if (outVal <= 9) {
    lcd.print("  ");
  } else if (outVal >= 10 && outVal <= 99) {
    lcd.print(" ");
  }
  lcd.print(" %");
  */
  //delay(5000);
}

void sunSetValue() {
/////////////////////////////////////////////////////
  dimmer.setPower(46); // setPower(0-100%);

  {
    USE_SERIAL.print("lampValue -> ");
    printSpace(dimmer.getPower());
    USE_SERIAL.print(dimmer.getPower());
    USE_SERIAL.println("%");
  }
  /*
  lcd.setCursor(0, 0);
  lcd.print("Audalux Sunset  ");

  lcd.setCursor(0, 1);
  lcd.print("Setting: ");
  lcd.print(dimmer.getPower());
  if (outVal <= 9) {
    lcd.print("  ");
  } else if (outVal >= 10 && outVal <= 99) {
    lcd.print(" ");
  }
  lcd.print(" %");
  */
  //delay(1000);
/////////////////////////////////////////////////////
}

void moonLightValue() {
/////////////////////////////////////////////////////
  MoonTi1 = EEPROM.read(100);
  dimmer.setPower(MoonTi1); // setPower(0-100%);
  //delay(500);
/////////////////////////////////////////////////////
}
