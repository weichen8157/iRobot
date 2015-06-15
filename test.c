#include <wiringPi.h>
#include <stdlib.h>
unsigned int count=0;
unsigned int currentLeft,currentRight,currentLLeft,currentRRight;

/*dimension
Width: 16 cm
Length: 24 cm
ratio 2:3
*/

void trigger(int pin)
{
    digitalWrite (pin, HIGH) ;
    delayMicroseconds (20) ;
    digitalWrite (pin,  LOW) ;
}

unsigned int pulseIn(int pin, int value, unsigned int timeout)
{
   unsigned int wait=micros();
   for(;;)
   {
       if (micros() - wait >= timeout)
       {
            count++;
            return 0;
       }
       if (digitalRead(pin)==value)
       {
          unsigned int start=micros();
          for(;;)
          {
               if (digitalRead(pin)!=value)
               {
                   return micros()-start;
               }
          }
       }
   }
}

unsigned int distance(unsigned int t)
{
   return t*34/200;
}

void forward(int in1,int in2,int in3,int in4,int in5,int in6,int in7,int in8)
{
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    digitalWrite(in5,HIGH);
    digitalWrite(in6,LOW);
    digitalWrite(in7,HIGH);
    digitalWrite(in8,LOW);
}

void backward(int in1,int in2,int in3,int in4,int in5,int in6,int in7,int in8)
{
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    digitalWrite(in5,LOW);
    digitalWrite(in6,HIGH);
    digitalWrite(in7,LOW);
    digitalWrite(in8,HIGH);
}

void turnRight(int in1,int in2,int in3,int in4,int in5,int in6,int in7,int in8)
{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    digitalWrite(in5,LOW);
    digitalWrite(in6,LOW);
    digitalWrite(in7,HIGH);
    digitalWrite(in8,LOW);
}

void turnLeft(int in1,int in2,int in3,int in4,int in5,int in6,int in7,int in8)
{
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    digitalWrite(in5,HIGH);
    digitalWrite(in6,LOW);
    digitalWrite(in7,LOW);
    digitalWrite(in8,LOW);
}

void stop(int in1,int in2,int in3,int in4,int in5,int in6,int in7,int in8)
{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    digitalWrite(in5,LOW);
    digitalWrite(in6,LOW);
    digitalWrite(in7,LOW);
    digitalWrite(in8,LOW);
}

int main (void)
{
  wiringPiSetup () ;
  pinMode (0, OUTPUT) ;//Ultrasonic 1
  pinMode (1, INPUT) ;
  pinMode (2, OUTPUT) ;//Ultrasonic 2
  pinMode (3, INPUT) ;
  pinMode (4, OUTPUT) ;//Ultrasonic 3
  pinMode (5, INPUT) ;
  pinMode (6, OUTPUT) ;//Ultrasonic 4
  pinMode (7, INPUT) ;

  pinMode (8,OUTPUT);//Motor 1
  pinMode (9,OUTPUT);
  pinMode (10,OUTPUT);//Motor 2
  pinMode (11,OUTPUT);
  pinMode (12,OUTPUT);//Motor 3
  pinMode (13,OUTPUT);
  pinMode (14,OUTPUT);//Motor 4
  pinMode (15,OUTPUT);
  stop(8,9,10,11,12,13,14,15);

  for(;;)
  {
     unsigned int timeLeft,timeRight,timeLLeft,timeRRight;
     unsigned int distLeft,distRight,distLLeft,distRRight;

     trigger(0);
     timeLeft = pulseIn(1,HIGH,500000);
     distLeft = distance(timeLeft);
     if(distLeft >0)
     {
         currentLeft=distLeft;
     }

     trigger(2);  
     timeRight = pulseIn(3,HIGH,500000);
     distRight = distance(timeRight);
     if(distRRight >0)
     {
         currentRight=distRight;
     }

     trigger(4);
     timeLLeft = pulseIn(5,HIGH,500000);
     distLLeft = distance(timeLLeft);
     if(distLLeft >0)
     {
         currentLLeft=distLLeft;
     }

     trigger(6);  
     timeRRight = pulseIn(7,HIGH,500000);
     distRRight = distance(timeRRight);
     if(distRRight >0)
     {
         currentRRight=distRRight;
     }

     if(currentLeft<=240 && currentRight <=240 && currentRRight <=240 && currentRRight <=240)
     {
         backward(8,9,10,11,12,13,14,15);
     }
     else if (currentLeft>240 && currentRight >240)
     {
         forward(8,9,10,11,12,13,14,15);
     }
     else if (currentLeft<=240 && currentRRight >240)
     {
         turnRight(8,9,10,11,12,13,14,15);
     }
     else if (currentRight<=240 && currentLLeft >240)
     {
         turnLeft(8,9,10,11,12,13,14,15);
     }
     printf("distLeft: %d distRight: %d count zero: %d\n",distLeft,distRight,count);
     delay (1000);
  }
  return 0 ;
}
