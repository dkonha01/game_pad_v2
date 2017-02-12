// Number of buttons on the gamepad
#define NUM_BUTTONS    12

// Button pins
#define B       0
#define A       1
#define X       2
#define Y       3
#define START   4
#define SELECT  5
#define RIGHT   6
#define UP      7
#define DOWN    8
#define LEFT    9
#define LTRIG   A2
#define RTRIG   A3

// Used for marking flags 
static uint8_t flags[NUM_BUTTONS] = {0};

// The pins corresponding to button flags
const uint8_t buttonPins[NUM_BUTTONS] = {
   B, A, X, Y,
   START, SELECT,
   RIGHT, UP,
   DOWN, LEFT,
   LTRIG, RTRIG
};

// The HID messages corresponding to button pins
// Can be changed to different HID messages
const uint8_t buttonFunctions[NUM_BUTTONS] = {
  'B', 'A', 'X', 'Y',  // Normal right thumb buttons
  PAUSE, PLAY,  // START and SELECT buttons
  KEY_RIGHT_ARROW, KEY_UP_ARROW,  // RIGHT and UP on d-pad
  KEY_DOWN_ARROW, KEY_LEFT_ARROW,  // DOWN and LEFT on d-pad
  REWIND, STOP  // LEFT TRIGGER and RIGHT TRIGGER
};

void setup() 
{
  //Enable HID library for Bean+
  BeanHid.enable();

  // Set all used pins as inputs
  pinMode(B, INPUT);
  pinMode(A, INPUT);
  pinMode(X, INPUT);
  pinMode(Y, INPUT);
  pinMode(START, INPUT);
  pinMode(SELECT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(LTRIG, INPUT);
  pinMode(RTRIG, INPUT);
}

void loop() 
{
  for (int i = 0; i < NUM_BUTTONS; i++)
  {
       // For each button, check if the state has changed
    uint8_t buttonState = digitalRead(buttonPins[i]);
    if (buttonState != flags[i])
    {
      // Hold/release the corresponding button accordingly
      if (buttonState == 1)
      {
        BeanHid.holdKey(buttonFunctions[i]);
      }
      else if (buttonState == 0)
      {
        BeanHid.releaseKey(buttonFunctions[i]);
      }
      // Update the last known button state for later use
      flags[i] = buttonState;
    }
  }

   AccelerationReading accel = Bean.getAcceleration();

  int16_t x = accel.xAxis;
  int16_t y = accel.yAxis;
  int16_t z = accel.zAxis;

  // Add a deadzone. If Bean is reasonabally flat, don't move the mouse pointer
  if (abs(x) < 23){
    x = 0;
  }
  if (abs(y) < 23) {
    y = 0;
  }
  
  // we want to map the movements to reasonable values.
  // This constrains the accelerometer to -20 to 20.
 //int16_t acclx = map(x, -60, 60, -20, 20);
 //int16_t accly = map(y, -60, 60, 20, -20);

  if ((x+y) > 87) { 

  
  BeanHid.sendKey(KEY_RIGHT_ARROW);

  delay(13); 
    
  }
  else {
  

    
  }
}
