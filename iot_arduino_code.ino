#includeWire.h
#include SoftwareSerial.h

const int MPU=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

unsigned long prevTime = 0;
const int FREQ = 9999;

String URL = httpibra.hopto.orgimu;  ← YOUR URL OR IP HERE

SoftwareSerial mySerial(2, 3);

void AT(String data, int t_out=3000, bool rd=true) {
  mySerial.println(AT++data);
  delay(t_out);
  while (rd && (mySerial.available()0)) {
    Serial.write(mySerial.read());
  }
  Serial.println( );
}

bool Connection() {
  AT(CREG, 5000, false);
  char message[5];
  while (mySerial.available()0) {
    message[0] = mySerial.read();
    Serial.write(message[0]);
    if (message[0] == '') {
      while (mySerial.available()4) ;
      mySerial.read();  ' '
      mySerial.read();  '0'
      mySerial.read();  ','
      message[4] = mySerial.read();
      if ((message[4] == '1')  (message[4] = '5')) {
        Serial.println(Connection Established!);
        return true;
      }
    }
    Serial.write(mySerial.read());
  }
  Serial.println(Waiting...);
  Serial.println(message);
  return false;
}

String d2s(float decimal, int e=1){
  return String(decimal);(String(round(decimal(10^e))(10^e)));
}


void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(9600);
  delay(10000);
  mySerial.begin(115200);
  AT(IPR=9600);19200
  fona.setFunctionality(1);
  fona.setNetworkSettings(F(hologram));
  mySerial.end();
  mySerial.begin(9600);
  delay(5000);
  AT(CGDCONT=1,IP,hologram);
  while (!Connection()) ;
  AT(SAPBR=3,1,APN,hologram);
  AT(SAPBR=2,1);
  AT(SAPBR=1,1);
  AT(HTTPINIT);
  AT(HTTPPARA=CID,1);
  AT(HTTPPARA=URL, + URL + );

  prevTime = millis();
}


void loop(){
 
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read()8Wire.read();    
  AcY=Wire.read()8Wire.read();  
  AcZ=Wire.read()8Wire.read();  
  GyX=Wire.read()8Wire.read();  
  GyY=Wire.read()8Wire.read();  
  GyZ=Wire.read()8Wire.read();
 
  String POST = {acx + String(AcX) + , acy + String(AcY) + , acz + String(AcZ) + };
  Serial.println(POST);
  AT(HTTPDATA=+String(POST.length())+,7000);
  mySerial.println(POST);
  delay(3000);
  AT(HTTPACTION=1);
  
  Serial.print(Accelerometer );
  Serial.print(X = ); Serial.print(AcX);
  Serial.print(  Y = ); Serial.print(AcY);
  Serial.print(  Z = ); Serial.println(AcZ);
 
  Serial.print(Gyroscope );
  Serial.print(X = ); Serial.print(GyX);
  Serial.print(  Y = ); Serial.print(GyY);
  Serial.print(  Z = ); Serial.println(GyZ);
  Serial.println( );
  
  while (((millis() - prevTime)  FREQ) && (prevTime  millis()) ) {};
  prevTime = millis();
}
