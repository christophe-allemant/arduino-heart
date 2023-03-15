#include <UTFT.h>

// Initialize Font and screen data
extern uint8_t SmallFont[];
UTFT myGLCD(ITDB32WD,38,39,40,41); 

// Initialize position data
int xA=0;
int yA=0;

int xB=0;
int yB=0;

int screenX=0;
int screenY=0;

int centerY=0;
int interation=0;

void setup() {
  // Initialize serial port
  // Serial.begin(9600);

  // pinMode(8, INPUT); // Setup for leads off detection LO +
  // pinMode(9, INPUT); // Setup for leads off detection LO -

  // Init screen display and font
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  
  // Get size on the screen
  screenX=myGLCD.getDisplayXSize();
  screenY=myGLCD.getDisplayYSize();
  
  // Vertical middle of the screen
  centerY=screenY/2;

  //start on middle
  yA = centerY;
  yB = centerY;
}

void loop() {
  
  // Get position of horizontal point
  // Modify the millis/20 to change the zoom on X
  xA=int((int(millis()/20)-(screenX*interation)));
  
  // If dot is external to screen size
  if(xA>screenX){
    // Clear screen
    myGLCD.clrScr();
    // Add iterate to calculate value
    interation+=1;
    //Reset point position
    xA=0 ;
    xB=0;
    yA=centerY;
    yB=centerY;
  }
   
  // Get value of pulsation and position on screen
  if((digitalRead(8) == 1)||(digitalRead(9) == 1)){
    // If there is no data, display at the middle of the screen
    yA=centerY;    
  }
  else{
    // Display the pulsatile value of heart
    // modify the analogRead(A0)/10 to change the zoom on Y
    yA = int(analogRead(A0)/10) + int(centerY/2);
  }
    
  //Print data on screen
  myGLCD.setColor(0,255,0);
  myGLCD.drawLine(xA,yA,xB,yB);
  
  //Save old points
  xB=xA;
  yB=yA;
  
  //Wait before next step
  delay(100);
}
