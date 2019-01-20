#include <Plotter.h>
#include <RF24.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!
#include <nRF24L01.h>

RF24 radio(7, 8);
Plotter p;
const byte rxAddr[6] = "00001";

typedef struct data {
  sensors_vec_t a, g;
};

float acc_x,acc_y,acc_z,gyro_x,gyro_y,gyro_z;


void setup()
{
  //while (!Serial);
  //Serial.begin(9600);
  p.Begin(); // start plotter
  radio.begin();
  radio.openReadingPipe(0, rxAddr);
  
  radio.startListening();
  
  
  p.AddTimeGraph( "Some title of a graph", 500, "label for x", acc_x );

  
  //Serial.println("CLEARDATA");
  //Serial.println("LABEL,Time,Timer(ms),Ax(m/s^2),Ay(m/s^2),Az(m/s^2),Gx(dps),Gy(dps),Gz(dps)");
}

void loop()
{
  if (radio.available())
  {
   struct data recieve_data;
   radio.read(&recieve_data, sizeof(recieve_data));

   //Serial.print("DATA,TIME,TIMER,");
      
   //Serial.print(recieve_data.a.x); Serial.print(",");
   //Serial.print(recieve_data.a.y); Serial.print(",");  
   //Serial.print(recieve_data.a.z); Serial.print(",");  

   //Serial.print(recieve_data.g.x); Serial.print(",");
   //Serial.print(recieve_data.g.y); Serial.print(",");
   //Serial.print(recieve_data.g.z); Serial.println("");
  acc_x = recieve_data.a.x;
  p.Plot();


  }
}
