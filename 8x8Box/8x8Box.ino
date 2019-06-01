#include <MaxMatrix.h>
#include <SPI.h>
int DIN = ;   // DIN pin of MAX7219 module
int CLK = ;   // CLK pin of MAX7219 module
int CS = ;    // CS pin of MAX7219 module
int button = ;   // pin for the control button
int maxInUse = ;   //How many 8x8 led matrices will be in use
int switchState = 0;  //variable for the button's state
int modeState = 0;    //variable for the current mode
int hasRunM0 = 0;     //keep track of running display elements
int hasRunM1 = 1;     //keep track of running display elements
MaxMatrix m(DIN, CS, CLK, maxInUse);  //create a new MaxMatrix called m

//pattern for an empty heart
byte heartEmpty[] = {8,8,
                  B01100110,
                  B10011001,
                  B10000001,
                  B10000001,
                  B01000010,
                  B00100100,
                  B00011000,
                  B00000000
                 };
                 
//heart pattern filled in
byte heartFull[] = {8,8,
                  B01100110,
                  B11111111,
                  B11111111,
                  B11111111,
                  B01111110,
                  B00111100,
                  B00011000,
                  B00000000
                 };

//small filled in heart
byte heartSmallFull[] = {8,8,
                  B00000000,
                  B00100100,
                  B01111110,
                  B01111110,
                  B00111100,
                  B00011000,
                  B00000000,
                  B00000000
                 }; 

//the number 1
byte number1[] = {8,8,
                  B00011000,
                  B00101000,
                  B00001000,
                  B00001000,
                  B00001000,
                  B00001000,
                  B00001000,
                  B01111110
                 };

//the number 2                 
byte number2[] = {8,8,
                  B00111100,
                  B01000010,
                  B00000010,
                  B00000010,
                  B00000010,
                  B00111100,
                  B01000000,
                  B01111110
                 };

//animation for drawing a heart outline                            
void heartDraw(){
  m.setDot(1,3,true);
  delay(50);
  m.setDot(0,2,true);
  delay(50);
  m.setDot(0,1,true);
  delay(50);
  m.setDot(1,0,true);
  delay(50);
  m.setDot(2,0,true);
  delay(50);
  m.setDot(3,0,true);
  delay(50);
  m.setDot(4,1,true);
  delay(50);
  m.setDot(5,2,true);
  delay(50);
  m.setDot(6,3,true);
  delay(50);
  m.setDot(6,4,true);
  delay(50);
  m.setDot(5,5,true);
  delay(50);
  m.setDot(4,6,true);
  delay(50);
  m.setDot(3,7,true);
  delay(50);
  m.setDot(2,7,true);
  delay(50);
  m.setDot(1,7,true);
  delay(50);
  m.setDot(0,6,true);
  delay(50);
  m.setDot(0,5,true);
  delay(50);
  m.writeSprite(0,0,heartEmpty);
  delay(50);
}

//animation for erasing the heart outline
void heartClear(){
  m.setDot(1,3,false);
  delay(50);
  m.setDot(0,2,false);
  delay(50);
  m.setDot(0,1,false);
  delay(50);
  m.setDot(1,0,false);
  delay(50);
  m.setDot(2,0,false);
  delay(50);
  m.setDot(3,0,false);
  delay(50);
  m.setDot(4,1,false);
  delay(50);
  m.setDot(5,2,false);
  delay(50);
  m.setDot(6,3,false);
  delay(50);
  m.setDot(6,4,false);
  delay(50);
  m.setDot(5,5,false);
  delay(50);
  m.setDot(4,6,false);
  delay(50);
  m.setDot(3,7,false);
  delay(50);
  m.setDot(2,7,false);
  delay(50);
  m.setDot(1,7,false);
  delay(50);
  m.setDot(0,6,false);
  delay(50);
  m.setDot(0,5,false);
  delay(50);
  m.setDot(1,4,false);
  delay(50);
}

//a fade style filling for a heart.
//takes a boolean parameter f that will be set
//TRUE to fill the heart
//FALSE to empty the heart
void heartFadeFill(bool f){
  m.setDot(1,6,f);
  delay(20);
  m.setDot(1,5,f);
  m.setDot(2,6,f);
  delay(20);
  m.setDot(2,5,f);
  m.setDot(3,6,f);
  delay(20);
  m.setDot(2,4,f);
  m.setDot(3,5,f);
  delay(20);
  m.setDot(1,2,f);
  m.setDot(2,3,f);
  m.setDot(3,4,f);
  m.setDot(4,5,f);
  delay(20);
  m.setDot(1,1,f);
  m.setDot(2,2,f);
  m.setDot(3,3,f);
  m.setDot(4,4,f);
  delay(20);
  m.setDot(2,1,f);
  m.setDot(3,2,f);
  m.setDot(4,3,f);
  m.setDot(5,4,f);
  delay(20);
  m.setDot(3,1,f);
  m.setDot(4,2,f);
  m.setDot(5,3,f);
  delay(50);
}

//setup function
void setup() {
  pinMode(button, INPUT); //recieve input through the button pin
  m.init(); // MAX7219 initialization
  m.setIntensity(8); // initial led matrix intensity, 0-15
}

//runtime loop
void loop() {
  switchState = digitalRead(button);
  
  while (switchState == 1){ //button pressed
    if (modeState == 0){    //if mode 0
      modeState = 1;        //goto next mode
      m.clear();            //clear screen
      m.writeSprite(0,0,number2); //display the number 2
      delay(2000);          //wait
      break;
    }
    else if(modeState == 1){  //if mode 1
      modeState = 0;          //goto next mode
      m.clear();              //clear screen
      m.writeSprite(0,0,number1); //write the number 1
      delay(2000);            //wait
      break;
    }
  }
  while(switchState == 0){  //button not pressed
  if (modeState == 0){      //mode 0 animation, we will constantly be checking to see if the button is pressed to switch modes
    m.clear();
    if (digitalRead(button) == 1){
      break;
    }
    heartDraw();
    if (digitalRead(button) == 1){
      break;
    }
    heartClear();
    if (digitalRead(button) == 1){
      break;
    }
    heartDraw();
    if (digitalRead(button) == 1){
      break;
    }
    heartFadeFill(true);
    if (digitalRead(button) == 1){
      break;
    }
    heartFadeFill(false);
    if (digitalRead(button) == 1){
      break;
    }
    heartFadeFill(true);
    if (digitalRead(button) == 1){
      break;
    }
    delay(500);
    break;
    }
    else if (modeState == 1){ //mode 1 animation, we will constantly be checking to see if the button is pressed to switch modes
      m.writeSprite(0,0,heartFull);
      delay(1000);
      break;
    }
  }

}
