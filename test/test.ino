#define LED1 6
#define LED2 5
#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4

#define TRANS1 17
#define TRANS2 18
#define TRANS3 19

void setup()
{
  // put your setup code here, to run once:
  
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(BUTTON3,INPUT);
  
  pinMode(TRANS1,OUTPUT);
  pinMode(TRANS2,OUTPUT);
  pinMode(TRANS3,OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  
  if(digitalRead(BUTTON1)==HIGH)
  {
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,LOW);
    
    digitalWrite(TRANS1,HIGH);
    digitalWrite(TRANS2,LOW);
    digitalWrite(TRANS3,LOW);
  }
  else if(digitalRead(BUTTON2)==HIGH)
  {
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    
    digitalWrite(TRANS1,LOW);
    digitalWrite(TRANS2,HIGH);
    digitalWrite(TRANS3,LOW);
  }
  else if(digitalRead(BUTTON3)==HIGH)
  {
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,HIGH);
    
    digitalWrite(TRANS1,LOW);
    digitalWrite(TRANS2,LOW);
    digitalWrite(TRANS3,HIGH);
  }
}
