// define your settings here
#define LED_COUNT 1

#define BUTTON_PIN 2

#define RED_PIN 3
#define GREEN_PIN 5
#define BLUE_PIN 6

#define BAUD_RATE 115200

#define CONNECTION_TIMEOUT 12000

#define MODE_STATIC 0
#define MODE_CONNECTED 1

struct Color {
  int r;
  int g;
  int b;
};

Color leds[LED_COUNT];

int mode = MODE_STATIC;

bool on = false;

unsigned long chaneStateMillis = 0;

struct Color staticColor;

void setup() {
  pinMode(BUTTON_PIN, INPUT);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  staticColor.r = staticColor.g = staticColor.b = 255;

  for (int i = 0; i < LED_COUNT; i++) {
    setColor(i, 0, 0, 0);
  }

  Serial.begin(BAUD_RATE);

  delay(400);

  syncLeds();
}

void loop() {
  readPhysicalInput();

  readSerial();

  checkConnection();

  syncLeds();
}

unsigned long connectionTimeoutTime = 0;

void checkConnection() {
  if (millis() > connectionTimeoutTime && mode == MODE_CONNECTED) {
    mode = MODE_STATIC;
  }
}

int getValueMultiplier() {
  unsigned long timeDiff = millis() - chaneStateMillis;

  if (timeDiff > 255) {
    timeDiff = 255;
  }

  if (on) {
    return timeDiff;
  } else {
    return 255 - timeDiff;
  }
}

String* splitString(String data, char delimiter, int& numSubstrings) {
  numSubstrings = 1;
  for (int i = 0; i < data.length(); i++) {
    if (data.charAt(i) == delimiter) {
      numSubstrings++;
    }
  }

  String* substrings = new String[numSubstrings];
  int currentIndex = 0;
  int startIndex = 0;
  int endIndex = data.indexOf(delimiter);

  while (endIndex > 0) {
    substrings[currentIndex] = data.substring(startIndex, endIndex);
    currentIndex++;
    startIndex = endIndex + 1;
    endIndex = data.indexOf(delimiter, startIndex);
  }

  substrings[currentIndex] = data.substring(startIndex);

  return substrings;
}

void readPhysicalInput() {
  static bool wasDown = false;

  bool isDown = !digitalRead(BUTTON_PIN);

  if (isDown != wasDown) {
    wasDown = isDown;

    if (isDown) {
      setOn(!on);
    }
  }
}

void setOn(bool value) {
  if (on == value) {
    return;
  }

  on = value;
  chaneStateMillis = millis();
}

void readSerial() {
  if (!Serial.available()) {
    return;
  }

  markConnection();

  executeCommands(Serial.readStringUntil('\n'));
}

void executeCommands(String commands) {
  int numSubstrings = 0;
  String* substrings = splitString(commands, ';', numSubstrings);

  for (int i = 0; i < numSubstrings; i++) {
    executeCommand(substrings[i]);
  }

  delete[] substrings;
}

void executeCommand(String command) {
  if (command == "ping") {
    Serial.println("pong");
  } else {
    int numSubstrings = 0;
    String* substrings = splitString(command, ' ', numSubstrings);

    if (substrings[0] == "led") {
      int index = substrings[1].toInt();
      int r = substrings[2].toInt();
      int g = substrings[3].toInt();
      int b = substrings[4].toInt();

      setColor(index, r, g, b);
    } else if (substrings[0] == "mode") {
      mode = substrings[1].toInt();
    } else if (substrings[0] == "on") {
      setOn(substrings[1].toInt());
    }

    delete[] substrings;
  }
}

void syncLeds() {
  int mult = getValueMultiplier();

  for (int i = 0; i < LED_COUNT; i++) {
    struct Color color;

    switch (mode) {
      case MODE_STATIC:
        color = staticColor;
        break;
      case MODE_CONNECTED:
        color = leds[i];
        break;
    }


    analogWrite(RED_PIN, color.r * mult / 255);
    analogWrite(GREEN_PIN, color.g * mult / 255);
    analogWrite(BLUE_PIN, color.b * mult / 255);
  }
}

void setColor(int led, int r, int g, int b) {
  struct Color color;

  color.r = r;
  color.g = g;
  color.b = b;

  leds[led] = color;
}

void markConnection() {
  connectionTimeoutTime = millis() + CONNECTION_TIMEOUT;
}