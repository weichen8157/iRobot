const byte IN1 = 0;		// Motor A
const byte IN2 = 1;
const byte ENA = 2;		
 
const byte IN3 = 3;		// Motor B
const byte IN4 = 4;
const byte ENB = 5;		

const byte IN5 = 6;		// Motor C	
const byte IN6 = 7;
const byte ENC = 8;	

const byte IN7 = 9;		// Motor D
const byte IN8 = 10;
const byte END = 11;	

int speed;			
 
void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
 
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(ENC, OUTPUT);
 
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
  pinMode(END, OUTPUT);
  
  speed = 100; 
}

void loop() {
  analogWrite(ENA, speed);	//PWM	
  analogWrite(ENB, speed);
  analogWrite(ENC, speed);	//PWM	
  analogWrite(END, speed);				
 
  forward(); 		
  delay(5000);		
  backward();		  
  delay(5000);		
  turnLeft();		
  delay(5000);		
  turnRight();		
  delay(5000);		
 
  stop();
  delay(6000);		
 
  speed += 40;			// speed up
  if (speed >= 240) {	
    speed = 100;
  }
}

void forward()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    digitalWrite(IN5, HIGH);
    digitalWrite(IN6, LOW);
    digitalWrite(IN7, HIGH);
    digitalWrite(IN8, LOW);   	
}
 
void backward()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    digitalWrite(IN5, LOW);
    digitalWrite(IN6, HIGH);
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, HIGH);    	
}
 
void turnLeft()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);	
    digitalWrite(IN7, HIGH);
    digitalWrite(IN8, LOW);
    digitalWrite(IN5, LOW);
    digitalWrite(IN6, LOW);    
}
 
void turnRight()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, LOW);
    digitalWrite(IN5, HIGH);
    digitalWrite(IN6, LOW);   
}
 
void stop()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(IN5, LOW);
    digitalWrite(IN6, LOW);
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, LOW);    
}