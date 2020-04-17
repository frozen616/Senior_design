#include <SparkFun_I2C_GPS_Arduino_Library.h> //Use Library Manager or download here: https://github.com/sparkfun/SparkFun_I2C_GPS_Arduino_Library
I2CGPS myI2CGPS; //Hook object to the library
#include <SoftwareSerial.h>

#include <TinyGPS++.h> //From: https://github.com/mikalhart/TinyGPSPlus
TinyGPSPlus gps; //Declare gps object
int kph = 0;

#include <WiseChipHUD.h>

WiseChipHUD myHUD;
long meters;
int inches = 0;





void setup()
{
  delay(1000);
  
    //HUD CODE BELOW
    myHUD.begin();
    // Begin the Serial at 115200 Baud
  Serial.begin(115200);
  
   myHUD.clearAll(); // Clears all of the segments



delay(1000);
  
  
  

  if (myI2CGPS.begin() == false)
  {
    Serial.println("Module failed to respond. Please check wiring.");
    while (1); //Freeze!
  }
  Serial.println("GPS module found!");
}

void loop()
{
  
  while (myI2CGPS.available()) //available() returns the number of new bytes available from the GPS module
  {
    gps.encode(myI2CGPS.read()); //Feed the GPS parser
  }
  printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);

  Serial.println(kph);
   
 
  

  /************************* Compass Group *************************/
  myHUD.compassCircle(0); // 0 = All Off; 1-8 = All Off Except Selected; 9 = All On; 10-17 = All On Except Selected
  myHUD.compassArrows(0); // 0 = All Off; 1-8 = All Off Except Selected; 9 = All On; 10-17 = All On Except Selected
  //myHUD.setHeading(188);  // Max 199

  /************************* Radar Detector Group *************************/
  myHUD.radarDetector(0); // 0 = No Radar Gun Icon; 1 = Radar Gun Only; 2-8 = meters Meter
  myHUD.setRadarDistance(kph,1); // Max 999    
  myHUD.radarDistanceUnits(0); // 0 = Blank; 1 = "m" 

  /************************* Destination/Waypoint Group *************************/
  myHUD.flag(0); // 0 = Blank; 1 = flag icon 
  //myHUD.setDestinationDistance(888,2); // Max 999
  myHUD.destinationDistanceUnits(0); // 0 = Blank; 1 = "h"; 2 = "m"; 3 = "km"
  myHUD.H01(0); // 0 = Blank; 1 = "h"

  /************************* Exit Group *************************/
  myHUD.leftTunnel(0); // 0 = Blank; 1 = Tunnel; Also try leftRoad();
  myHUD.middleTunnel(0); // 0 = Blank; 1 = Tunnel; Also try middleRoad();
  myHUD.rightTunnel(0); // 0 = Blank; 1 = Tunnel; Also try rightRoad();

  /************************* Navigation Group *************************/
  myHUD.nav_Group(0); // 0 = Entire Nav Group Off; 1 = Entire Nav Group On
  //myHUD.setTurnDistance(888,1); // Max 999
  myHUD.turnDistanceUnits(0); // 0 = Blank; 1 = "m"; 2 = "km"
   //Turn Groups:
   //nav_KeepLeft(1);
   //nav_TurnLeft(1);
   //nav_HardLeft(1);
   //nav_UTurnLeft(1);
   //nav_ContinueStraight(1);
   //nav_KeepRight(1);
   //nav_TurnRight(1);
   //nav_HardRight(1);
   //nav_UTurnRight(1);

  /************************* Call Group *************************/
  myHUD.setCallIcon(0); // 0 = Blank; 1 = Outline; 2 = Outline + Phone Icon; 3 = All Segments

  /************************* TPMS Group *************************/
  myHUD.tirePressureAlert(0); // 0 = Blank; 1 = "TPMS"; 2 = "TIRE"; 3 = All Segments
  //myHUD.setTirePressure(88,1); // Max 99

  /************************* Speedometer Group *************************/
  //myHUD.setSpeedometer(0); // Max 199
  //myHUD.speedometerUnits(1); // 0 = Blank; 1 = "km/h"

  




delay(100);
  
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i){
      Serial.println(' ');}
    kph = val;
  }
 }
