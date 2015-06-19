#include <wiringPi.h>
#include <stdlib.h>
#define DISTANCE 360
#define NOTURN 0
#define AFTERRIGHT 1
#define AFTERLEFT 2

unsigned int count=0,direction=0;
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
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    digitalWrite(in5,HIGH);
    digitalWrite(in6,LOW);
    digitalWrite(in7,HIGH);
    digitalWrite(in8,LOW);
}

void turnLeft(int in1,int in2,int in3,int in4,int in5,int in6,int in7,int in8)
{
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    digitalWrite(in5,HIGH);
    digitalWrite(in6,LOW);
    digitalWrite(in7,HIGH);
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


struct region{
        char up=0;
        char left=0; 
        char right=0;
        char back=0;
        char state = 0; //0=unknown 1=free 2=obstacle;
};

typedef struct car{
        volatile float x;// car position
        volatile float y;
        char mode;          // running mode,0:first run
        char direction; // 0:North 1:East 2:South 3:West
}CAR;

void detect(){
        unsigned int timeLeft,timeRight,timeLLeft,timeRRight;

        trigger(0);
        timeLeft = pulseIn(1,HIGH,500000);
        currentLeft = distance(timeLeft);
                                 
        trigger(2);  
        timeRight = pulseIn(3,HIGH,500000);
        currentRight = distance(timeRight);

        trigger(4);
        timeLLeft = pulseIn(5,HIGH,500000);
        currentLLeft = distance(timeLLeft);
                                                                    
        trigger(6);  
        timeRRight = pulseIn(7,HIGH,500000);
        currentRRight = distance(timeRRight);
                                                                                        
}

void init(){
        car.x=1;
        car.y=1;
        car.direction = 0;
        map[0][0].state = free;
        int i,j;
        for(i=0;i<X;i++){
                for(j=0;j<Y;j++){
                         if(j==0||i==0||i==X||j=={
                                map[i][j] = 2;                                                                                  }
                                                                                                
                }
        }
}

void update_map(CAR car){
        //¶ZÂ´«º⦨³æ
        unsigned int Leftunit = currentLeft/unit;
        unsigned int Rightunit = currentRight/unit;
        unsigned int LLeftunit = currentLLeft/unit;
        unsigned int RRightunit = currentRRight/unit;
        unsigned int Frontunit;

        //§PÂ«e¤襪or¥k¸û¨ú
        if(rightunit>leftunit)  
                Frontunit = Leftunit;
        else
                Frontunit = Rightunit;

        //®ھڳæ¡A¨M©w«e«ᥪ¥kstate
        if(Leftunit==0 && currentLLeft!=0)      //currentLLeft=0 ¶W¹L¥i´ú½d³òí¤U­ӳæµL»Ùªª«
                map[car.x][car.y].left = 2;
        else
                map[car.x][car.y].left = 1;

        if(Rightunit==0 && currentRRight!=0)
                map[car.x][car.y].right = 2;
        else
                map[car.x][car.y].right = 1;

        if(Frontunit==0 && (currentLeft!=0 || currentRight!=0))
                map[car.x][car.y].up = 2;
        else
                map[car.x][car.y].up = 1;

        if(car.direction==0)
                map[car.x][car.y].back = map[car.x][car.y-1].state;
        else if(car.direction==2)
                map[car.x][car.y].back = map[car.x][car.y+1].state;
}

        //globalÅ¼Æ
        unsigned int unit 1 ;                   //³æ¤j¤p
        volatile unsigned int currentLeft,currentRight,currentLLeft,currentRRight;

        CAR car;

        int X 256;
        int Y 128;      
        struct region map[X][Y];

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
     timeLeft = pulseIn(1,HIGH,50000);
     distLeft = distance(timeLeft);
     if(distLeft >0)
     {
         currentLeft=distLeft;
     }

     trigger(2);
     timeRight = pulseIn(3,HIGH,50000);
     distRight = distance(timeRight);
     if(distRRight >0)
     {
         currentRight=distRight;
     }

     trigger(4);
     timeLLeft = pulseIn(5,HIGH,50000);
     distLLeft = distance(timeLLeft);
     if(distLLeft >0)
     {
         currentLLeft=distLLeft;
     }

     trigger(6);
     timeRRight = pulseIn(7,HIGH,50000);
     distRRight = distance(timeRRight);
     if(distRRight >0)
     {
         currentRRight=distRRight;
     }


     if (currentLeft>DISTANCE && currentRight >DISTANCE)
     {
        if (currentLLeft>DISTANCE && currentRRight >DISTANCE)
        {
           forward(8,9,10,11,12,13,14,15);
        }
        else if(currentLLeft<=DISTANCE && currentRRight <=DISTANCE)
        {
            forward(8,9,10,11,12,13,14,15);
        }
        else if (currentLLeft<=DISTANCE && currentRRight >DISTANCE)
        {
            turnRight(8,9,10,11,12,13,14,15);
            direction=AFTERRIGHT;
        }
        else
        {
            turnLeft(8,9,10,11,12,13,14,15);
            direction=AFTERLEFT;
        }
     }
     else if(currentLeft<=DISTANCE && currentRight <=DISTANCE)
     {
        if (currentLLeft>DISTANCE && currentRRight >DISTANCE)
        {
             switch (direction)
             {
                 case AFTERRIGHT:
                    turnLeft(8,9,10,11,12,13,14,15);
                    break;
                 case AFTERLEFT:
                    turnRight(8,9,10,11,12,13,14,15);
                    break;
                 default:
                    turnRight(8,9,10,11,12,13,14,15);                    
             }
        }
        else if(currentLLeft<=DISTANCE && currentRRight <=DISTANCE)
        {
            backward(8,9,10,11,12,13,14,15);
        }
        else if (currentLLeft<=DISTANCE && currentRRight >DISTANCE)
        {
            turnRight(8,9,10,11,12,13,14,15);
        }
        else
        {
            turnLeft(8,9,10,11,12,13,14,15);
        }
     }
     else if (currentLeft<=DISTANCE && currentRight >DISTANCE)
     {
        if (currentLLeft>DISTANCE && currentRRight >DISTANCE)
        {
             switch (direction)
             {
                 case AFTERRIGHT:
                    turnLeft(8,9,10,11,12,13,14,15);
                    break;
                 case AFTERLEFT:
                    turnRight(8,9,10,11,12,13,14,15);
                    break;
                 default:
                    turnRight(8,9,10,11,12,13,14,15);                    
             }
        }
        else if(currentLLeft<=DISTANCE && currentRRight <=DISTANCE)
        {
            backward(8,9,10,11,12,13,14,15);
        }
        else if (currentLLeft<=DISTANCE && currentRRight >DISTANCE)
        {
            turnRight(8,9,10,11,12,13,14,15);
        }
        else
        {
            turnLeft(8,9,10,11,12,13,14,15);
        }
     }
     else
     {
        if (currentLLeft>DISTANCE && currentRRight >DISTANCE)
        {
              switch (direction)
             {
                 case AFTERRIGHT:
                    turnLeft(8,9,10,11,12,13,14,15);
                    break;
                 case AFTERLEFT:
                    turnRight(8,9,10,11,12,13,14,15);
                    break;
                 default:
                    turnRight(8,9,10,11,12,13,14,15);                    
             }
        }
        else if(currentLLeft<=DISTANCE && currentRRight <=DISTANCE)
        {
            backward(8,9,10,11,12,13,14,15);
        }
        else if (currentLLeft<=DISTANCE && currentRRight >DISTANCE)
        {
            turnRight(8,9,10,11,12,13,14,15);
        }
        else
        {
            turnLeft(8,9,10,11,12,13,14,15);
        }
     }
     printf("distLeft: %d distRight: %d distLLeft: %d distRRight: %d count zero: %d\n",distLeft,distRight,distLLeft,distRRight,count);
     delay(100); 
  }
  return 0 ;
}
