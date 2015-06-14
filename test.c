#include <wiringPi.h>
#include <stdlib.h>

void trigger()
{
    digitalWrite (0, HIGH) ; 
    delayMicroseconds (50) ;
    digitalWrite (0,  LOW) ;
}

unsigned int pluseIn(int pin, int value, unsigned int timeout)
{
   unsigned int wait=micros(); 
   for(;;)
   {
       if (micros() - wait >= timeout)
       {
            return 0;
       }
       if (digitalRead(1)==value)
      {
          unsigned int start=micros();
          for(;;)
          {
               if (digitalRead(1)!=value)
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

int main (void)
{
  wiringPiSetup () ;
  pinMode (0, OUTPUT) ;
  pinMode (1, INPUT) ;
  for(;;)
  {
     unsigned int time;
     unsigned int dist;

     trigger();
     time = pluseIn(1,HIGH,500000);
     dist = distance(time);
     printf("dist: %d\n",dist);
     delay (1000);
  }
  return 0 ;
}