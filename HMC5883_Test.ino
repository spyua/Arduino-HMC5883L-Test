#include <Wire.h> 
#include <math.h> 

//0011110b, I2C 7bit address of HMC5883
#define address 0x1E 

int x,y,z; //triple axis data
double angle;

void setup(){
  //Initialize Serial and I2C communications
  Serial.begin(9600);
  Wire.begin();
  //HMC5883 Init
  HMC5883_Init();
}

void loop(){
  Read_HMC5883_Data();
  Print_HMC5883_Data();
  delay(250);
}

void Read_HMC5883_Data()  
{
  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }
  angle= atan2((double)y,(double)x) * (180/3.14159265) + 180;
}

void Print_HMC5883_Data() {
  //Print out values of each axis
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.print(z);
  Serial.print("  A: ");
  Serial.println(angle);
}

void HMC5883_Init() {
   //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
}



