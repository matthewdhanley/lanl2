// inputs should just be a 3 digit combo or the word 'reset'
 
// pin names (global)
  const int sw1 = 10; // switch 1
  const int sw2 = 11; // switch 2
  const int sw3 = 12; // switch 3
  const int rset = 13; // reset switch
  const int en = 9; // ENABLE toggle control
  const int slp = 8; // Sleep toggle control
  const int dir = 7; // direction control
  const int st1 = 6; // step 1 pwm
  const int st2 = 5; // step 2 pwm
  const int st3 = 4; // step 3 pwm

int st1ct = 0; // initializes reset function counters
int st2ct = 0;
int st3ct = 0;

// global constants
const int rpr = 2048; // Number of steps in a revolution, must be even
const int cyc = 2; // half the period for the pwm 

void setup() {
  // setup code here, runs once:
pinMode(st3,OUTPUT); // stepper motor 3
pinMode(st2,OUTPUT); // stepper motor 2
pinMode(st1,OUTPUT); // stepper motor 1
pinMode(dir,OUTPUT); // direction toggle
pinMode(slp,OUTPUT); // sleep (HIGH is on)
pinMode(en,OUTPUT); // ENABLE (LOW is on)
pinMode(sw1,INPUT); // switch 1 for step 1
pinMode(sw2,INPUT); // switch 2 for step 2
pinMode(sw3,INPUT); // switch 3 for step 3
pinMode(rset,INPUT); // reset switch for all motors

Serial.begin(115200); // connect to serial port
// Serial.println("Input a 3 digit combination (no delimiters)"); // show the string I want to parse
}

void loop() {
  // Serial reading function:
while (Serial.available()>0){
String instring = Serial.readString(); // reads serial input
  //Serial.println("Input read");
    if(instring == "reset"){ // if it reads 'reset' it does this
      //Serial.println(instring.substring(0,5)); // shows that 'reset' is read
      //Serial.println("Motors will begin spinning shortly, please wait until 'Reset done' \nis shown to enter another combo");
      digitalWrite(dir,HIGH);
      digitalWrite(en,LOW);
      digitalWrite(slp,HIGH);
      for (int i=1; i<=rpr*4;i++){ // for loop limits the number of clicks to 8
        if(st1ct >0){
          digitalWrite(st1,HIGH); // turns led one on
          st1ct = st1ct-1; // counter - 1
        }
        if(st2ct >0){
          digitalWrite(st2,HIGH); // turns led 2 on
          st2ct = st2ct-1; // counter -1
        }
        if(st3ct >0){
          digitalWrite(st3,HIGH); // turns led 3 on
          st3ct = st3ct-1; // counter - 1
        }
        delay(cyc);
        // turns all the leds off
      digitalWrite(st1,LOW);
      digitalWrite(st2,LOW);
      digitalWrite(st3,LOW);
      if(st1ct==0 && st2ct ==0 && st2ct==0){
        // if largest combo # is smaller than 8, exits early
        break;
      }
      delay(cyc); // delay so you can see the blinks
    }
  st1ct = 0; // initializes reset function counters
  st2ct = 0;
  st3ct = 0;
  digitalWrite(dir,LOW); // indicates resetting is done
  digitalWrite(en,HIGH);
  digitalWrite(slp,LOW);
  Serial.println("Reset done \n \n");
 // Serial.println("Enter another combo or type 'reset' to reset to original position");
    
  }
  else {
    // the main function that reads number inputs
  //Serial.println(instring.substring(0,3));
  //Serial.println("Motors will begin spinning shortly, please wait until 'done' \nis shown to enter another combo");
  // Parsing lines
  String blink1 = instring.substring(0,1); // first digit
  int BA = blink1.toInt(); // saves as int
  st1ct = BA*rpr/2; // reset counter for led 1
  String blink2 = instring.substring(1,2); // 2nd digit
  int BB = blink2.toInt(); // saves as int
  st2ct = BB*rpr/2; // reset counter for led 2
  String blink3 = instring.substring(2,3); // 3rd digit
  int BC = blink3.toInt(); // saves as int
  st3ct = BC*rpr/2; // reset counter for led 3
  // comment back in to see individual steps
  //Serial.println("blink1");
  //Serial.println(blink1);
  //Serial.println("blink2");
  //Serial.println(blink2);
  //Serial.println("blink3");
  //Serial.println(blink3);
BA = BA*rpr/2;
BB = BB*rpr/2;
BC = BC*rpr/2;
    digitalWrite(dir,LOW);
    digitalWrite(en,LOW);
    digitalWrite(slp,HIGH);
  for (int i=1; i<=rpr*4;i++){ // limits the number of blinks to 8, and turns them all on/off at basically the same time
    if(BA >0){ // led 1 blinking progress
      digitalWrite(st1,HIGH);
      BA = BA-1; // counter
    }
    if(BB >0){ // led 2 blinking progress
      digitalWrite(st2,HIGH);
      BB = BB-1; // counter
    }
    if(BC >0){ // led 3 blinking progress
      digitalWrite(st3,HIGH);
      BC = BC-1; // counter
    }
    delay(cyc);
  digitalWrite(st1,LOW);
  digitalWrite(st2,LOW);
  digitalWrite(st3,LOW);
  if(BA==0 && BB ==0 && BC==0){
    break; // exits loop early if the largest combo digit is less than 8
  }
  delay(cyc);
  }
    digitalWrite(en,LOW);
    digitalWrite(slp,LOW);
  Serial.println("Done \n");
  //Serial.println("Enter another combo or type 'reset' to reset to original position \n");

}
}
digitalWrite(slp,LOW);
}
