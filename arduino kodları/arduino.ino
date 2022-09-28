#include <Servo.h>
#include "Wire.h"
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

Servo ustservo;
Servo altservo;


void setup() {
  // put your setup code here, to run once:
    tcs.begin();

  Serial.begin(9600);
  ustservo.attach(9);
  altservo.attach(8);
  
 
}
bool isEnabled = false;

void Red()
{
  Serial.println("RED");
}

void Green()
{
  Serial.println("GREEN");
}
void  Blue()
{
    Serial.println("BLUE");
}
void  Pink()
{
    Serial.println("YELLOW");
}
void  Orange()
{
    Serial.println("ORANGE");
}
void  Brown()
{
    Serial.println("BROWN");
}
void Fail()
{
      Serial.println("FAIL");

}
void loop() {
  if(Serial.available())
   {
      String str = Serial.readString();
    
    if(str == "START")
    {
      isEnabled = true;
    }
    if(str == "STOP")
    {
      isEnabled = false;
    }
   }

   if(isEnabled)
   {
     Idle();
        delay(760);

     ReadState();
        delay(1250);

     uint16_t clearcol, red, green, blue;
     tcs.getRawData(&red, &green, &blue, &clearcol);
    
     float average = (red+green+blue)/3;

     float r = red/average;
     float g = green/average;
     float b = blue/average;

  
         

       if(r > 0.95 && r < 1.17  &&  g > 1.34 && g < 1.54  &&  b > 0.51 && b < 0.60)
       {
         Ayarla(1); // green
         Green();

         //AD 1.05 1.42 0.55 0
         //D 1.02 1.42 0.55 0

         //105 139 55 0
         //96 151 53 0
       }else
       if(r > 1.66 && r < 1.87  && g > 0.65 && g < 0.87  && b > 0.44 && b < 0.54)
       {
         Ayarla(0); // Kırmızı
         Red();

         //174 77 49 0
         //173 78 49 0

         //189 68 45 0

         //175 78 50 0

         //181 75 47 0

         //168 85 53 0
         //171 80 51 0
         //174 82 50 0
         //1.69 0.83 0.53 0
       }else
      if(r > 0.66  && r < 1.00  && g > 1.10 && g < 1.17  && b > 0.94 && b < 1.20)
      {
        Ayarla(2); //Mavi
        Blue();

        //80 113 113 0
       // 69 117 119 0
      }else
        if(r > 1.64 && r < 1.90   && g > 0.76 && g < 0.94  && b > 0.36 && b < 0.48)
       {
         Ayarla(3); // Turuncu
         Orange();
         //181 83 40 0
         //167 89 43 0
         //177 83 40 0

         //170 91 44 0

         //180 80 41 0

         //188 77 38 0
       }
       else
         if(r > 1.43 && r < 1.54   && g > 1.04 && g < 1.22  && b > 0.33 && b < 0.46)
       {
         Ayarla(4); // Yellow
         Pink();
       }
        else
         if(r > 1.36 && r < 1.50   && g > 0.95 && g < 1.12  && b > 0.50 && b < 0.65)
       {
         Ayarla(5); // Brown
         Brown();
         //146 100 58 0
       }else 
       {
         
       //  isEnabled = false;
      //   Fail();
       }


      //1.49 1.13 0.40 0 sarı
      // 1.42 1.00 0.58 0 kahverengi
      //1.71 0.87 0.42 turuncu
     //D 1.78 0.84 0.41 0


       /*Kırmızı
         
1.81 0.74 0.45 0
1.69 0.83 0.50 0
1.82 0.72 0.46 0
1.72 0.83 0.50 0
1.69 0.81 0.50 0
1.82 0.74 0.47 0

YESIL

1.08 1.41 0.57 0
1.02 1.44 0.54 0
1.05 1.42 0.55 0
1.08 1.37 0.55 0


MAVI

0.93 1.13 1.00 0
0.87 1.13 1.03 0
0.97 1.13 0.97 0
0.83 1.14 1.07 0

SARI

1.49 1.12 0.39 0
1.48 1.15 0.39 0
1.49 1.13 0.40 0

TURUNCU
1.76 0.84 0.41 0
1.74 0.87 0.43 0
1.73 0.86 0.43 0
1.68 0.89 0.43 0

KAHVERENGI

1.41 1.04 0.59 0
1.44 1.04 0.59 0
1.44 1.04 0.56 0
1.43 1.04 0.57 0

       */

        delay(1700);

     EndState();

     //rengi oku
     delay(400);
   }
  
}

void Idle()
{
  
  for(int i = 30 ; i < 120; i++)
  {
     ustservo.write(i);
    delay(10);
  }
}
void ReadState()
{
  for(int i = 120; i > 55; i--)
  {
     ustservo.write(i);
     delay(10);

  }

}
void EndState()
{
   for(int i = 55; i > 30; i--)
  {
     ustservo.write(i);
     delay(10);

  }


}

void Ayarla(int _color)
{
   switch(_color)
   {
     case 0:
     altservo.write(40); // red
     break;
     case 1:
     altservo.write(60); // green
     break;
      case 2:
     altservo.write(80); // blue
     break;

      case 3:
     altservo.write(100); // orange
     break;
      case 4:
     altservo.write(120); // pink
     break;
      case 5:
     altservo.write(130); // brown
     break;
   }
}
