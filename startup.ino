const byte IN1 = 3;		// Motor A
const byte IN2 = 4;
const byte ENA = 5;		
 
const byte IN3 = 7;		// Motor B
const byte IN4 = 8;
const byte ENB = 6;		
 
int speed;			
 
void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
 
  speed = 100; 
}

void loop() {
  analogWrite(ENA, speed);	//PWM	
  analogWrite(ENB, speed);		
 
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
}
 
void backward()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);	
}
 
void turnLeft()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);	
}
 
void turnRight()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}
 
void stop()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}
