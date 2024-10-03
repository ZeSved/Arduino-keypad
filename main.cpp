#include <Keyboard.h>

int rows[2] = {2, 3};
int columns[3] = {5, 6, 7};

String actions[2][3] = {
  {"Coding for life", "B", "C"},
  {"D", "E", "F"}
};

int currentRow = 3;
int lastPressed[2] = {0, 0};

void setup() {
  for (int row : rows) {
    pinMode(row, OUTPUT);
  }

  for (int col : columns) {
    pinMode(col, INPUT);
  }

  Keyboard.begin();
}

void loop() {
  if (currentRow == 2) {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    currentRow = 3;
  } else {
    digitalWrite(3, LOW);
    digitalWrite(2, HIGH);
    currentRow = 2;
  }

  for (int c : columns) {
    if (digitalRead(c) == HIGH && (currentRow != lastPressed[0] || c != lastPressed[1])) {
      Keyboard.print(actions[currentRow - 2][c - 5]);
      delay(100);
      Keyboard.releaseAll();
      lastPressed[0] = currentRow;
      lastPressed[1] = c;
    }
  }

  if (digitalRead(lastPressed[1]) == LOW && currentRow == lastPressed[0]) {
    lastPressed[0] = 0;
    lastPressed[1] = 0;
  }
}