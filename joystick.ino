const int stepXPin = 2;
const int dirXPin = 5;

const int stepYPin = 3;
const int dirYPin = 6;

const int stepZPin = 4;
const int dirZPin = 7;

const int ledPin = 12;
const int buttonPin = 13;

const int joystickLowValue = 500;
const int joystickHighValue = 540;

const int vrx = A1;
const int vry = A0;

const int sleep = 2;
const int buttonSleep = 500;

bool zMode = false;

void setup() {  
  pinMode(stepXPin, OUTPUT);
  pinMode(dirXPin, OUTPUT);

  pinMode(stepYPin, OUTPUT);
  pinMode(dirYPin, OUTPUT);

  pinMode(stepZPin, OUTPUT);
  pinMode(dirZPin, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  digitalWrite(stepXPin, LOW);
  digitalWrite(dirXPin, HIGH);

  digitalWrite(stepYPin, LOW);
  digitalWrite(dirYPin, HIGH);

  digitalWrite(stepZPin, LOW);
  digitalWrite(dirZPin, HIGH);

  digitalWrite(ledPin, LOW);
}

void handleButtonPressed() {
  int buttonVal1 = digitalRead(buttonPin);

  if (buttonVal1 == LOW) {
    delay(buttonSleep);

    int buttonVal2 = digitalRead(buttonPin);;

    if (buttonVal1 == buttonVal2) {
      zMode = !zMode;
    }
  }
}

void doStep(int pin) {
  digitalWrite(pin, HIGH);
  delay(sleep);
  digitalWrite(pin, LOW);
}

void setDirection(int pin, int val) {
  if (val < joystickLowValue) {
    digitalWrite(pin, LOW);
  } else {
    digitalWrite(pin, HIGH);
  }
}

void setLed(bool on) {
  if (on) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void loop() {
  handleButtonPressed();
  setLed(zMode);

  int joystickX = analogRead(vrx);
  int joystickY = analogRead(vry);

  if (zMode) {
    setDirection(dirZPin, joystickY);
    delay(sleep);
    
    if (joystickY < joystickLowValue || joystickY > joystickHighValue) {
      doStep(stepZPin);
    }
  } else {
    setDirection(dirXPin, joystickX);
    setDirection(dirYPin, joystickY);

    delay(sleep);
    
    if (joystickX < joystickLowValue || joystickX > joystickHighValue) {
      doStep(stepXPin);
    }

    if (joystickY < joystickLowValue || joystickY > joystickHighValue) {
      doStep(stepYPin);
    }
  }

  delay(sleep);
}
