#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Fonts/FreeSansBold12pt7b.h>

#define TFT_CS 30
#define TFT_DC 32

struct Color {
  int r;
  int g;
  int b;
};

// basic state controllers
int theme = 0;
int inApp = 0;
bool isPlaying = true;

// holds RGB for available themes
Color availableThemes[5][4] = {{{40, 40, 40}, {24, 24, 24}, {64, 64, 64}, {255, 255, 255}},
  {{248, 249, 250}, {173, 181, 189}, {222, 226, 230}, {0, 0, 0}},
  {{189, 224, 254}, {205, 180, 219}, {162, 210, 255}, {255, 255, 255}},
  {{58, 90, 64}, {52, 78, 65}, {88, 129, 87}, {218, 215, 205}},
  {{197, 55, 204}, {255, 69, 69}, {170, 42, 170}, {255, 219, 131}}
};

#define BG display.color565(availableThemes[theme][0].r, availableThemes[theme][0].g, availableThemes[theme][0].b)
#define ACCENT_ONE display.color565(availableThemes[theme][1].r, availableThemes[theme][1].g, availableThemes[theme][1].b)
#define ACCENT_TWO display.color565(availableThemes[theme][2].r, availableThemes[theme][2].g, availableThemes[theme][2].b)
#define HIGHLIGHT display.color565(availableThemes[theme][3].r, availableThemes[theme][3].g, availableThemes[theme][3].b)


Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC);

// menu states
int menuPos[2] = {0, 0};
int menuLimits[5][2] = {{0, 0}, {2, 1}, {0, 3}, {1, 3}, {0, 0}};
int mainMenuIconPos[6][2] = {{40, 100}, {130, 100}, {210, 100}, {40, 180}, {130, 180}, {210, 180}};
int settingsIconPos[4][2] = {{15, 15}, {24, 63}, {24, 112}, {24, 161}};
int customizeIconPos[7][2] = {{15, 15}, {24, 53}, {176, 53}, {24, 108}, {176, 108}, {24, 163}, {176, 163}};
int contributionIconPos[2] = {15, 15};

void setup() {
  Serial.begin(9600);
  delay(1000);
  for (int i = 3; i < 8; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  display.begin();
  delay(500);
  display.fillScreen(BG);
  display.setFont(&FreeSansBold12pt7b);
  display.setRotation(1);

  showStartMenu();

  while (!isButtonPressed());
  delay(50);

  inApp = 1;
  showMainMenu();
}

void loop() {
  if (isButtonPressed()) {
    int oldPos = getMenuIndex();
    int buttonClicked = determineButtonPressed();
    if (buttonClicked == 3) {
      showCorrectMenu();
      delay(150);
      return;
    }
    moveMenuPos(buttonClicked);
    int newPos = getMenuIndex(); // recall so it updates to the new pos

    // swaps which item is selected
    drawIcon(oldPos, false);
    drawIcon(newPos, true);

    while (!isButtonPressed());
    delay(50);
  }
  delay(100);
}

void showStartMenu() {
  clear();
  display.setCursor(0, 50);
  display.setTextColor(HIGHLIGHT);
  display.setTextSize(2);
  display.println("Walk-mini");
  display.setTextSize(1);
  display.setCursor(0, 150);
  display.println("Press button to begin");
  delay(100);
}

void showMainMenu() {
  clear();
  resetPos();

  display.fillRect(0, 0, 320, 90, ACCENT_ONE);
  display.setCursor(5, 25);
  display.setTextColor(HIGHLIGHT);
  display.setTextSize(1);
  display.println("Song Name");
  display.setCursor(5, 50);
  display.println("Artist");

  display.setCursor(135, 55);
  display.println("0:00");
  display.fillRect(250, 15, 45, 45, HIGHLIGHT);

  // progress bar
  display.fillRect(60, 80, 200, 5, HIGHLIGHT);
  display.fillCircle(160, 82, 8, HIGHLIGHT);

  for (int i = 0; i < 6; i++) {
    drawIcon(i, i == 0);
  }
}

void showSettings() {
  clear();
  resetPos();

  display.setTextSize(2);
  display.setCursor(80, 45);
  display.setTextColor(HIGHLIGHT);
  display.println("Settings");
  display.setTextSize(1);

  for (int i = 0; i < 4; i++) {
    drawIcon(i, i == 0);
  }
}

void showCustomizeMenu() {
  clear();
  resetPos();

  display.setTextSize(1);
  display.setCursor(100, 35);
  display.setTextColor(HIGHLIGHT);
  display.println("Customize");
  for (int i = 0; i < 7; i++) {
    drawIcon(i, i == 0);
  }
}

void showContributionsMenu() {
  clear();
  resetPos();

  drawIcon(0, 0 == 0);
  display.setCursor(15, 60);
  display.setTextColor(HIGHLIGHT);
  display.println("WalkMini: by nate/np3");
  display.setCursor(15, 100);
  display.println("HackClub: For Fallout");
  display.setCursor(15, 140);
  display.println("Mom & Dad: Support!");
  display.setCursor(15, 180);
  display.println("JLCPCB: PCB");
  display.setCursor(15, 220);
  display.println("You: For using Walkmini!");
}

void showBluetoothMenu() {
  clear();
  resetPos();

  display.setTextSize(2);
  display.setCursor(80, 45);
  display.setTextColor(HIGHLIGHT);
  display.println("Bluetooth");
  display.setTextSize(1);
  display.setCursor(15, 90);
  display.println("Devices Found:");
  
  // call for all bluetooth devices (await?), then use it for length of list
  int devicesFound = 2;
  for (int i = 0; i < devicesFound; i++) {
    display.fillRoundRect(15, 110 + (i*20), 272, 42, 3, ACCENT_TWO);
  }
}

// takes current position of the user and completes action
void showCorrectMenu() {
  if (inApp == 1 ) {
    switch (getMenuIndex()) {
      case 0:
        Serial.println("Restart");
        break;
      case 1:
        Serial.println(isPlaying ? "Pause" : "Resume");
        isPlaying = !isPlaying;
        drawIcon(getMenuIndex(), getMenuIndex()); // recall to change state
        break;
      case 2:
        Serial.println("Skip");
        break;
      case 3:
        Serial.println("Songs");
        break;
      case 4:
        Serial.println("Shuffle");
        break;
      case 5:
        Serial.println("Settings");
        inApp = 2;
        showSettings();
        break;
    }
  } else if (inApp == 2) {
    switch (getMenuIndex()) {
      case 0:
        inApp = 1;
        showMainMenu();
        break;
      case 1:
        inApp = 3;
        showCustomizeMenu();
        break;
      case 2:
        Serial.println("Bluetooth");
        break;
      case 3:
        inApp = 4;
        showContributionsMenu();
        break;
    }
  } else if (inApp == 3) {
    int ind = getMenuIndex();
    if (ind == 0) {
      inApp = 2;
      showSettings();
    } else if (ind == 6) {
      //add submit code
      inApp = 1;
      showMainMenu();
    } else {
      theme = ind - 1;
      showCustomizeMenu();
    }
  } else if (inApp == 4){ 
    if (getMenuIndex() == 0) {
        inApp = 2;
        showSettings();
    }
  } else if (inApp == 5) {
    if (getMenuIndex() == 0) {
      inApp = 2;
      showSettings();
    }
    // a case will have to be refresh bluetooth. all others will connect to the selected device.
  }
}



void clear() {
  display.fillScreen(BG);
}

void resetPos() {
  menuPos[0] = 0;
  menuPos[1] = 0;
}

int getMenuIndex() {
  if (inApp == 1) {
    return menuPos[1] * 3 + menuPos[0];
  } else if (inApp == 2) {
    return menuPos[1];
  } else if (inApp == 3) {
    if (menuPos[1] == 0) return 0;
    return menuPos[1] * 2 + menuPos[0] - 1;
  } else if (inApp == 4) {
    return 0;  
  }

  return 0;
}

bool isButtonPressed() {
  for (int i = 3; i < 8; i++) {
    if (digitalRead(i) == LOW) return true;
  }
  return false;
}

int determineButtonPressed() {
  for (int i = 3; i < 8; i++) {
    if (digitalRead(i) == LOW) return i;
  }
}

void moveMenuPos(int button) {
  if (inApp == 0)
    return;

  // moves menu pos, action button not programmed.
  switch (button) {
    case 3:
      break;
    case 4:
      menuPos[0]++;
      break;
    case 5:
      menuPos[0]--;
      break;
    case 6:
      menuPos[1]++;
      break;
    case 7:
      menuPos[1]--;
      break;
  }

  // swapping to other side if going over limits
  if (menuPos[0] < 0) {
    menuPos[0] = menuLimits[inApp][0];
  } else if (menuPos[0] > menuLimits[inApp][0]) {
    menuPos[0] = 0;
  } else if (menuPos[1] < 0) {
    menuPos[1] = menuLimits[inApp][1];
  } else if (menuPos[1] > menuLimits[inApp][1]) {
    menuPos[1] = 0;
  } if (inApp == 3 && menuPos[1] == 0) {
    menuPos[1] == 0;
  }
}

void redrawIcons(int prevPos[2], int curPos[2]) {
  display.fillRoundRect(prevPos[0], prevPos[1], 55, 55, 3, ACCENT_TWO);
  display.fillRoundRect(curPos[0], curPos[1], 55, 55, 3, HIGHLIGHT);
}

void drawIcon(int index, bool isSelected) {
  int pos[2] = {0, 0};
  uint16_t bg = isSelected ? HIGHLIGHT : ACCENT_TWO;
  uint16_t fg = isSelected ? ACCENT_TWO : HIGHLIGHT;
  if (inApp == 1) {
    pos[0] = mainMenuIconPos[index][0];
    pos[1] = mainMenuIconPos[index][1];
    display.fillRoundRect(pos[0], pos[1], 55, 55, 3, bg);

    switch (index) {
      case 0: // restart
        display.fillTriangle(pos[0] + 42, pos[1] + 45, pos[0] + 42, pos[1] + 10, pos[0] + 24, pos[1] + 27, fg);
        display.fillTriangle(pos[0] + 24, pos[1] + 45, pos[0] + 24, pos[1] + 10, pos[0] + 6, pos[1] + 27, fg);
        break;
      case 1: // pause + resume
        if (isPlaying) {
          display.fillTriangle(pos[0] + 8, pos[1] + 9, pos[0] + 8, pos[1] + 46, pos[0] + 46, pos[1] + 27, fg);
        } else {
          display.fillRect(pos[0] + 8, pos[1] + 9, 13, 37, fg);
          display.fillRect(pos[0] + 32, pos[1] + 9, 13, 37, fg);
        }
        break;
      case 2: // skip
        display.fillTriangle(pos[0] + 10, pos[1] + 45, pos[0] + 10, pos[1] + 10, pos[0] + 27, pos[1] + 27, fg);
        display.fillTriangle(pos[0] + 27, pos[1] + 45, pos[0] + 27, pos[1] + 10, pos[0] + 45, pos[1] + 27, fg);
        break;
      case 3: // songs
        display.fillRect(pos[0] + 6, pos[1] + 15, 15, 25, fg);
        display.fillTriangle(pos[0] + 45, pos[1] + 5, pos[0] + 45, pos[1] + 50, pos[0] - 10, pos[1] + 25, fg);
        display.fillRoundRect(40, 180, 6, 55, 3, bg); // hides triangle part that goes off button
        display.fillRect(0, 150, 40, 90, BG);
        break;
      case 4: // shuffle
        display.fillRect(pos[0] + 10, pos[1] + 15, 30, 5, fg);
        display.fillTriangle(pos[0] + 40, pos[1] + 8, pos[0] + 40, pos[1] + 27, pos[0] + 50, pos[1] + 17, fg);
        display.fillRect(pos[0] + 15, pos[1] + 40, 30, 5, fg);
        display.fillTriangle(pos[0] + 15, pos[1] + 33, pos[0] + 15, pos[1] + 52, pos[0] + 5, pos[1] + 40, fg);
        break;
      case 5: // settings
        display.fillRect(pos[0] + 10, pos[1] + 15, 35, 5, fg);
        display.fillCircle(pos[0] + 32, pos[1] + 17, 5, fg);
        display.fillRect(pos[0] + 10, pos[1] + 28, 35, 5, fg);
        display.fillCircle(pos[0] + 17, pos[1] + 30, 5, fg);
        display.fillRect(pos[0] + 10, pos[1] + 40, 35, 5, fg);
        display.fillCircle(pos[0] + 32, pos[1] + 42, 5, fg);
    }
  } else if (inApp == 2) {
    pos[0] = settingsIconPos[index][0];
    pos[1] = settingsIconPos[index][1];

    switch (index) {
      case 0:
        display.fillRoundRect(10, 10, 30, 30, 3, bg);
        display.fillTriangle(35, 15, 35, 35, 15, 25, fg);
        break;
      case 1:
        display.fillRoundRect(pos[0], pos[1], 272, 42, 3, bg);
        display.setTextColor(fg);
        display.setCursor(32, 90);
        display.println("Customize");
        break;
      case 2:
        display.fillRoundRect(pos[0], pos[1], 272, 42, 3, bg);
        display.setTextColor(fg);
        display.setCursor(32, 140);
        display.println("Bluetooth");
        break;
      case 3:
        display.fillRoundRect(pos[0], pos[1], 272, 42, 3, bg);
        display.setTextColor(fg);
        display.setCursor(32, 190);
        display.println("Contributions");
        break;
    }
  } else if (inApp == 3) {
    pos[0] = customizeIconPos[index][0];
    pos[1] = customizeIconPos[index][1];

    switch (index) {
      case 0:
        display.fillRoundRect(10, 10, 30, 30, 3, bg);
        display.fillTriangle(35, 15, 35, 35, 15, 25, fg);
        break;
      case 1:
        display.fillRoundRect(pos[0], pos[1], 120, 45, 3, bg);
        display.fillRoundRect(pos[0] + 15, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[0][0].r, availableThemes[0][0].g, availableThemes[0][0].b));
        display.fillRoundRect(pos[0] + 40, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[0][1].r, availableThemes[0][1].g, availableThemes[0][1].b));
        display.fillRoundRect(pos[0] + 65, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[0][2].r, availableThemes[0][2].g, availableThemes[0][2].b));
        display.fillRoundRect(pos[0] + 90, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[0][3].r, availableThemes[0][3].g, availableThemes[0][3].b));
        break;
      case 2:
        display.fillRoundRect(pos[0], pos[1], 120, 45, 3, bg);
        display.fillRoundRect(pos[0] + 15, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[1][0].r, availableThemes[1][0].g, availableThemes[1][0].b));
        display.fillRoundRect(pos[0] + 40, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[1][1].r, availableThemes[1][1].g, availableThemes[1][1].b));
        display.fillRoundRect(pos[0] + 65, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[1][2].r, availableThemes[1][2].g, availableThemes[1][2].b));
        display.fillRoundRect(pos[0] + 90, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[1][3].r, availableThemes[1][3].g, availableThemes[1][3].b));
        break;
      case 3:
        display.fillRoundRect(pos[0], pos[1], 120, 45, 3, bg);
        display.fillRoundRect(pos[0] + 15, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[2][0].r, availableThemes[2][0].g, availableThemes[2][0].b));
        display.fillRoundRect(pos[0] + 40, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[2][1].r, availableThemes[2][1].g, availableThemes[2][1].b));
        display.fillRoundRect(pos[0] + 65, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[2][2].r, availableThemes[2][2].g, availableThemes[2][2].b));
        display.fillRoundRect(pos[0] + 90, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[2][3].r, availableThemes[2][3].g, availableThemes[2][3].b));
        break;
      case 4:
        display.fillRoundRect(pos[0], pos[1], 120, 45, 3, bg);
        display.fillRoundRect(pos[0] + 15, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[3][0].r, availableThemes[3][0].g, availableThemes[3][0].b));
        display.fillRoundRect(pos[0] + 40, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[3][1].r, availableThemes[3][1].g, availableThemes[3][1].b));
        display.fillRoundRect(pos[0] + 65, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[3][2].r, availableThemes[3][2].g, availableThemes[3][2].b));
        display.fillRoundRect(pos[0] + 90, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[3][3].r, availableThemes[3][3].g, availableThemes[3][3].b));
        break;
      case 5:
        display.fillRoundRect(pos[0], pos[1], 120, 45, 3, bg);
        display.fillRoundRect(pos[0] + 15, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[4][0].r, availableThemes[4][0].g, availableThemes[4][0].b));
        display.fillRoundRect(pos[0] + 40, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[4][1].r, availableThemes[4][1].g, availableThemes[4][1].b));
        display.fillRoundRect(pos[0] + 65, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[4][2].r, availableThemes[4][2].g, availableThemes[4][2].b));
        display.fillRoundRect(pos[0] + 90, pos[1] + 15, 15, 15, 3, display.color565(availableThemes[4][3].r, availableThemes[4][3].g, availableThemes[4][3].b));
        break;
      case 6:
        display.fillRoundRect(pos[0], pos[1], 120, 45, 3, bg);
        display.setCursor(pos[0] + 17, pos[1] + 30);
        display.setTextSize(1);
        display.setTextColor(fg);
        display.println("Submit!");
        break;
    }
  } else if (inApp == 4) {
    pos[0] = customizeIconPos[index][0];
    pos[1] = customizeIconPos[index][1];

    display.fillRoundRect(10, 10, 30, 30, 3, bg);
    display.fillTriangle(35, 15, 35, 35, 15, 25, fg);
  }
}
