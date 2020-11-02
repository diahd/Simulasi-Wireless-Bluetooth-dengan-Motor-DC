//Sistem Embedded. Simulasi Bluetooth dengan Proteus

#define in1 6
#define in2 7
#define enA 9

#define pbsPin 2
#define potPin A0

int rotDirection = 0;
int pressed = false;

String motion;

void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(pbsPin, INPUT);
  //Set initial rotation direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  Serial.println("Silakan ketik 'w' untuk memutar, 's' untuk berhenti.");
}

void loop() {
 
  while (Serial.available()==0){}
  
  motion = Serial.readString();
  if(motion=="w"){  
    int potVal = analogRead(potPin); //Read potentiometer value
    int pwmOutput = map(potVal,0,1023,0,255); //Mapping
    analogWrite(enA, pwmOutput); //Send PWM signal to L298N Enable Pin
    
   //Read button - Debounce
    if(digitalRead(pbsPin)==true){
      pressed = !pressed;
    }
    while (digitalRead(pbsPin)==true);
    delay(20);

    //if button pressed - change rotation direction
    if (pressed == true &rotDirection == 0){
      Serial.println("Berbalik arah.");
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      rotDirection =1;
      delay(20);
    }
    //if button is pressed - change rotation direction
    if(pressed == false & rotDirection ==1){
      Serial.println("Berbalik arah.");
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      rotDirection = 0;
      delay(20);
    }
  }

  if (motion=="s"){
    Serial.println("Berhenti.");
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    delay(20);
  }
}
