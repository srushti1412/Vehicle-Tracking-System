#include <Wire.h>
#include<MPU6050.h>
#include <SoftwareSerial.h>

SoftwareSerial sim(10, 11);   //(TX,RX)
int _timeout;
String _buffer;
String number = "+919130121960";


const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
float ax=0, ay=0, az=0, gx=0, gy=0, gz=0;


void setup() {
 Wire.begin();
 Wire.beginTransmission(MPU_addr);
 Wire.write(0x6B);  // PWR_MGMT_1 register
 Wire.write(0);     // set to zero (wakes up the MPU-6050)
 Wire.endTransmission(true);
 Serial.begin(9600);
 _buffer.reserve(50);
 Serial.println("System Started...");
 sim.begin(9600);
 delay(1000);
 pinMode(11, OUTPUT);
 
}

void loop() {
 mpu_read();
 ax = (AcX-2050)/16384.00;
 ay = (AcY-77)/16384.00;
 az = (AcZ-1947)/16384.00;

 //270, 351, 136 for gyroscope
 gx = (GyX+270)/131.07;
 gy = (GyY-351)/131.07;
 gz = (GyZ+136)/131.07;
 float Raw_AM = pow(pow(ax,2)+pow(ay,2)+pow(az,2),0.5);
 float AM = Raw_AM*10;  // as values are within 0 to 1 multiply by 10

 float GM = pow(pow(gx/2,2)+pow(gy,2)+pow(gz,2),0.5);
 
 Serial.print("ax : ");
 Serial.print(ax);
 Serial.print(", ay : ");
 Serial.print(ay);
 Serial.print(" ,az : ");
 Serial.println(az);
 Serial.print("AM : ");
 Serial.println(AM);

 Serial.print("gx : ");
 Serial.print(gx);
 Serial.print(", gy : ");
 Serial.print(gy);
 Serial.print(" ,gz : ");
 Serial.println(gz);
 Serial.print("GM : ");
 Serial.println(GM);

 if(AM>12 && GM>=30 && GM<=400)
 {
  Serial.println(AM);
  Serial.println("Fall Detected");
  SendMessage();
  if (Serial.available() > 0)
  {
    SendMessage();
  }
  if (sim.available() > 0)
    Serial.write(sim.read());
  digitalWrite(11,HIGH);
  delay(5000);
 }
 delay(200);
 digitalWrite(11,LOW);
 delay(200);
}
void mpu_read(){
 Wire.beginTransmission(MPU_addr);
 Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
 Wire.endTransmission(false);
 Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
 AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
 AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
 AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
 Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
 GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
 GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
 GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
 }
 void SendMessage()
{
  //Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  //Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "XYZ has met with an Accident at https://maps.google.com/?q=18.5310557728988,73.86584413793346";
  sim.println(SMS);
  Serial.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  _buffer = _readSerial();
}
String _readSerial() {
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
}
