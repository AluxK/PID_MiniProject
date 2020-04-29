//const means that these values will not change during runtime
const int FSR_Pin = A5;
const int LED_Effect1 = 12;
const int LED_Effect2 = 8;
const int LED_Audio_Sim = 6; 
const int Button_Pin = 2;
int buttonState = 0;
int buttonLastState = 0;
int state = 0;
int brightness = 0;
float FSR_Value = 0;

void setup() {
  //Opens up the Serial connection, and sets the datarate to be 9600
  Serial.begin(9600);
  //specify the task that each pin will do.
  pinMode(LED_Effect1, OUTPUT);
  pinMode(LED_Effect2, OUTPUT);
  pinMode(LED_Audio_Sim, OUTPUT);
  pinMode(Button_Pin, INPUT);
  pinMode(FSR_Pin, INPUT);
}

void loop() {
  //read the current state of the button
  buttonState = digitalRead(Button_Pin);

  //if the last state is different from the current, then:
  if (buttonState != buttonLastState && buttonState == HIGH) {
    //if state is below two, add one and print the value. else set it to 0.
    if (state < 2) {
      state++;
      Serial.print("S: ");
      Serial.println(state);
    } else {
      state = 0;
      Serial.print("S: ");
      Serial.println(state);
    }
    changedState(state);
  }
  
  //load in the state of the button, to compare with future button states.
  buttonLastState = buttonState;
  
  //Read FSR value and print it.
  FSR_Value = analogRead(FSR_Pin);
  Serial.print("F: ");
  Serial.println(FSR_Value);
  
  //change the brightness of the LED, depending on the value read from the FSR
  if(FSR_Value >=25){
  digitalWrite(LED_Audio_Sim, HIGH);
  }
  else
  {
    digitalWrite(LED_Audio_Sim, LOW);
  }
}

//changes which LED is on, depending on the value of the state verible. 
void changedState(int state){
  switch(state){
    case 1:
    digitalWrite(LED_Effect1, HIGH);
    digitalWrite(LED_Effect2, LOW);
    break;
    case 2:
    digitalWrite(LED_Effect1, LOW);
    digitalWrite(LED_Effect2, HIGH);
    break;
    default:
    digitalWrite(LED_Effect1, LOW);
    digitalWrite(LED_Effect2, LOW);
    break;
  }
}
