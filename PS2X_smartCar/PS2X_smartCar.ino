#include <PS2X_lib.h>  // for v1.6

/** ATMEGA328p */
#define PS2_DAT 12
#define PS2_CMD 11
#define PS2_SEL 10
#define PS2_CLK 13

int pwm1 = 6;
int pwm2 = 10;
int pwm3 = 11;
int pwm4 = 9;

int io_0 = A0;
int io_1 = A1;
int io_2 = A2;
int io_3 = A3;

int io_4 = 2;
int io_5 = 3;
int io_6 = 4;
int io_7 = 5;

#define pressures true
#define rumble true

PS2X ps2x;  // create PS2 Controller Class

int error = 0;
byte type = 0;
byte vibrate = 0;

// 全局变量用于控制电机的PWM调速占空比
int motorSpeed = 130;

// Reset func
void (*resetFunc)(void) = 0;

void setup() {

  Serial.begin(9600);

  delay(500);  //added delay to give wireless ps2 module some time to startup, before configuring it

  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  if (error == 0) {
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  } else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Unknown Controller type found ");
      break;
    case 1:
      Serial.println("DualShock Controller found ");
      break;
    case 2:
      Serial.println("GuitarHero Controller found ");
      break;
    case 3:
      Serial.println("Wireless Sony DualShock Controller found ");
      break;
  }

  // 初始化为输出口
  pinMode(io_0, OUTPUT);
  pinMode(io_1, OUTPUT);
  pinMode(io_2, OUTPUT);
  pinMode(io_3, OUTPUT);

  pinMode(io_4, OUTPUT);
  pinMode(io_5, OUTPUT);
  pinMode(io_6, OUTPUT);
  pinMode(io_7, OUTPUT);

  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(pwm3, OUTPUT);
  pinMode(pwm4, OUTPUT);
}

// 停机
void STOP() {
  pinMode(io_0, LOW);
  pinMode(io_1, LOW);
  pinMode(io_2, LOW);
  pinMode(io_3, LOW);

  pinMode(io_4, LOW);
  pinMode(io_5, LOW);
  pinMode(io_6, LOW);
  pinMode(io_7, LOW);

  pinMode(pwm1, 0);
  pinMode(pwm2, 0);
  pinMode(pwm3, 0);
  pinMode(pwm4, 0);
}

// PWM调速前进
void RUN() {
  digitalWrite(io_0, HIGH);
  digitalWrite(io_1, LOW);
  digitalWrite(io_2, HIGH);
  digitalWrite(io_3, LOW);

  digitalWrite(io_4, HIGH);
  digitalWrite(io_5, LOW);
  digitalWrite(io_6, HIGH);
  digitalWrite(io_7, LOW);

  analogWrite(pwm1, motorSpeed);
  analogWrite(pwm2, motorSpeed);
  analogWrite(pwm3, motorSpeed);
  analogWrite(pwm4, motorSpeed);
}

// PWM调速后退
void BACK() {
  digitalWrite(io_0, LOW);
  digitalWrite(io_1, HIGH);
  digitalWrite(io_2, LOW);
  digitalWrite(io_3, HIGH);

  digitalWrite(io_4, LOW);
  digitalWrite(io_5, HIGH);
  digitalWrite(io_6, LOW);
  digitalWrite(io_7, HIGH);

  analogWrite(pwm1, motorSpeed);
  analogWrite(pwm2, motorSpeed);
  analogWrite(pwm3, motorSpeed);
  analogWrite(pwm4, motorSpeed);
}

// 右转
void RIGHT() {
  digitalWrite(io_0, HIGH);
  digitalWrite(io_1, LOW);
  digitalWrite(io_2, HIGH);
  digitalWrite(io_3, LOW);

  digitalWrite(io_4, LOW);
  digitalWrite(io_5, HIGH);
  digitalWrite(io_6, LOW);
  digitalWrite(io_7, HIGH);

  analogWrite(pwm1, motorSpeed);
  analogWrite(pwm2, motorSpeed);
  analogWrite(pwm3, motorSpeed);
  analogWrite(pwm4, motorSpeed);
}

// 左转
void LEFT() {
  digitalWrite(io_0, LOW);
  digitalWrite(io_1, HIGH);
  digitalWrite(io_2, LOW);
  digitalWrite(io_3, HIGH);

  digitalWrite(io_4, HIGH);
  digitalWrite(io_5, LOW);
  digitalWrite(io_6, HIGH);
  digitalWrite(io_7, LOW);

  analogWrite(pwm1, motorSpeed);
  analogWrite(pwm2, motorSpeed);
  analogWrite(pwm3, motorSpeed);
  analogWrite(pwm4, motorSpeed);
}

/** 平移方法 */
void Translation(uint8_t io_values, uint8_t speed) {
  digitalWrite(io_0, (io_values >> 7) & 0x01);
  digitalWrite(io_1, (io_values >> 6) & 0x01);
  digitalWrite(io_2, (io_values >> 5) & 0x01);
  digitalWrite(io_3, (io_values >> 4) & 0x01);
  digitalWrite(io_4, (io_values >> 3) & 0x01);
  digitalWrite(io_5, (io_values >> 2) & 0x01);
  digitalWrite(io_6, (io_values >> 1) & 0x01);
  digitalWrite(io_7, io_values & 0x01);

  analogWrite(pwm1, speed);
  analogWrite(pwm2, speed);
  analogWrite(pwm3, speed);
  analogWrite(pwm4, speed);
}

// Mecanum-右平移
void Translation_Right() {
  Translation(0b00110011, motorSpeed);
}

// Mecanum-左平移
void Translation_Left() {
  Translation(0b11001100, motorSpeed);
}

// Mecanum-右上平移
void Translation_Right_Up() {
  Translation(0b10000001, motorSpeed);
}

// Mecanum-右下平移
void Translation_Right_Down() {
  Translation(0b01111110, motorSpeed);
}

// Mecanum-左上平移
void Translation_Left_Up() {
  Translation(0b10000001, motorSpeed);
}

// Mecanum-左下平移
void Translation_Left_Down() {
  Translation(0b01111110, motorSpeed);
}

void loop() {

  if (error == 1) {  //skip loop if no controller found
    resetFunc();
  }

  if (type == 2) {        //Guitar Hero Controller
    ps2x.read_gamepad();  //read controller

    if (ps2x.ButtonPressed(GREEN_FRET))
      Serial.println("Green Fret Pressed");
    if (ps2x.ButtonPressed(RED_FRET))
      Serial.println("Red Fret Pressed");
    if (ps2x.ButtonPressed(YELLOW_FRET))
      Serial.println("Yellow Fret Pressed");
    if (ps2x.ButtonPressed(BLUE_FRET))
      Serial.println("Blue Fret Pressed");
    if (ps2x.ButtonPressed(ORANGE_FRET))
      Serial.println("Orange Fret Pressed");

    if (ps2x.ButtonPressed(STAR_POWER))
      Serial.println("Star Power Command");

    if (ps2x.Button(UP_STRUM))  //will be TRUE as long as button is pressed
      Serial.println("Up Strum");
    if (ps2x.Button(DOWN_STRUM))
      Serial.println("DOWN Strum");

    if (ps2x.Button(PSB_START))  //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if (ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");

    if (ps2x.Button(ORANGE_FRET)) {  // print stick value IF TRUE
      Serial.print("Wammy Bar Position:");
      Serial.println(ps2x.Analog(WHAMMY_BAR), DEC);
    }
  } else {                              //DualShock Controller
    ps2x.read_gamepad(false, vibrate);  //read controller and set large motor to spin at 'vibrate' speed

    if (ps2x.Button(PSB_START))  //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if (ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");

    if (ps2x.Button(PSB_PAD_UP)) {  //will be TRUE as long as button is pressed
      Serial.print("Up held this hard: ");
      RUN();
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    }
    if (ps2x.Button(PSB_PAD_RIGHT)) {
      Serial.print("Right held this hard: ");
      LEFT();
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
    if (ps2x.Button(PSB_PAD_LEFT)) {
      Serial.print("LEFT held this hard: ");
      RIGHT();
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }
    if (ps2x.Button(PSB_PAD_DOWN)) {
      Serial.print("DOWN held this hard: ");
      BACK();
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }

    vibrate = ps2x.Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
    if (ps2x.NewButtonState()) {        //will be TRUE if any button changes state (on to off, or off to on)
      if (ps2x.Button(PSB_L3))
        Serial.println("L3 pressed");
      if (ps2x.Button(PSB_R3))
        Serial.println("R3 pressed");

      if (ps2x.Button(PSB_L2)) {
        Translation_Left();
        Serial.println("L2 pressed");
      }

      if (ps2x.Button(PSB_R2)) {
        Serial.println("R2 pressed");
      }

      if (ps2x.Button(PSB_TRIANGLE)) {
        Serial.println("Triangle pressed");
        
        // 加速
        motorSpeed += 1;
        if (motorSpeed > 255)
          motorSpeed = 255;
        Serial.print("Current PWM Speed: ");
        Serial.println(motorSpeed);
      }
    }

    if (ps2x.NewButtonState(PSB_CROSS)) {
      Serial.println("X just changed");

      // 减速
      motorSpeed -= 1;
      if (motorSpeed <= 125)
        motorSpeed = 125;
      Serial.print("Current PWM Speed: ");
      Serial.println(motorSpeed);

    }  //will be TRUE if button was JUST pressed OR released
    
    if (ps2x.ButtonPressed(PSB_CIRCLE)) {
      Serial.println("Circle just pressed");

    }  //will be TRUE if button was JUST pressed

    if (ps2x.ButtonReleased(PSB_SQUARE)) {
      Serial.println("Square just released");
      
    }  //will be TRUE if button was JUST released


    if (ps2x.Button(PSB_L1)) {  //print stick values if either is TRUE
      Serial.print("PSB_L1 Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC);  //Left stick, Y axis. Other options: LX, RY, RX
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC);
      Serial.print("");

      // 左移
      Translation_Left();

    } else if (ps2x.Button(PSB_R1)) {
      Serial.print("PSB_R1 Stick Values:");
      Serial.print(ps2x.Analog(PSS_RY), DEC);
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC);
      Serial.print("");

      // 右移
      Translation_Right();
    }
  }
  delay(50);
}
