// VMK Technical Power
//Line Follower Robot Using Arduino and L298N Motor Driver                                                                 
 int IN1 = 6;
 int IN2 = 7;
 int IN3 = 8;
 int IN4 = 9;
int motorSpeed = 0;

//Define IR1 and IR2 Sensors
 int IR1 = A0;
 int IR2 = A1;

//Define Sensors Values
int IR1Val = analogRead(IR1);
int IR2Val = analogRead(IR2); 

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
}

  void Trial()
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }

  void loop () {
    if (analogRead(IR1)<150){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      }
    
    else  {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      }
      
     if(analogRead(IR2)<150){
       digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      
    }

    else  {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
     
      
    }
   Serial.print(analogRead(IR1));
   Serial.print("");
   Serial.println(analogRead(IR2));
   
  }


  


 
