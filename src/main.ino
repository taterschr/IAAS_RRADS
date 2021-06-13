#include <Arduino.h>
#include <NMEAGPS.h>
#include <Streamers.h>
#include <GPSport.h>
#include <TimeLib.h>

static gps_fix  fix;
static NMEAGPS  gps;
#define DEBUG_ON
#define UTC_OFFSET 6



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial1.begin(9600);
  Serial.println("init");


}
float lat, lng, alt, batV;
int gpsDay, gpsMonth, gpsYear, gpsHour, gpsMinute, gpsSecond;
int sats, gpsTime, rHumidity, pressure_mbar;


void loop() {
  // put your main code here, to run repeatedly:
  getGPS();       // gets gps position


}



void getGPS(){
  while (gps.available( gpsPort )) {
    fix = gps.read();
    lat = fix.latitude();
    lng = fix.longitude();
    alt = fix.altitude();
    sats = fix.satellites;
    time_t t = fix.dateTime+946684800 - (UTC_OFFSET*3600);
    setTime(t);
    gpsDay = day();
    gpsMonth = month();
    gpsYear = year();
    gpsHour = hour();
    gpsMinute = minute();
    gpsSecond = second();

    #ifdef DEBUG_ON
      Serial.print("GPS: ");
      trace_all(Serial, gps, fix );
    #endif
  }
}
