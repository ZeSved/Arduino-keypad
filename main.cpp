#include <Keyboard.h>

int rows[2] = {2, 3};
int columns[3] = {5, 6, 7};

//struct Commands {
//  boolean hasHex;
//  int hex;
//  String w;
//};

//Commands actions[2][3][8][3] = {
//  {
//    {
//      {false, 0, "https"}, 
//  {false, 0, ":"}, 
//  {true, 47, "null"}, 
//  {false, 0, "tenor.com"}, 
//  {false, 0, "/"}, 
//  {false, 0, "view"}, 
//  {false, 0, "/"}, 
//  {false, 0, "will-wood-ik-i-know-gif-13165299665569457587"}
//  }, 
//  {false, 0, "B"}, 
//  {false, 0, "C"}
//  },
//  {{false, 0, "D"}, {false, 0, "E"}, {false, 0, "F"}}
//};
String actions[2][3][21] = {
  {
    {
     "https", 
  ":", 
  "/", 
  "/", 
  "tenor.com", 
  "/", 
  "view", 
  "/", 
  "will", "+", "wood", "+", "ik", "+", "i", "+", "know", "+", "gif", "+", "13165299665569457587", 
  }, 
  {"B"}, 
  {"C"}
  },
  {{"D"}, {"E"}, {"F"}}
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
      for (int i = 0; i <= 20; i++) {
        //Commands act[3] = actions[currentRow - 2][c - 5][i];
        String act = actions[currentRow - 2][c - 5][i];

        if (act == "/") {
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('7');
          Keyboard.releaseAll();
        } else if (act == ":") {
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('.');
          Keyboard.releaseAll();
        } else if (act == "+") {
          //Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press(KEY_KP_MINUS);
          Keyboard.releaseAll();
        } else {
          Keyboard.print(act);
        }
        //if (act[0].hasHex == 1) {
        //  Keyboard.write(act[0].hex);
        //} else {
        //  Keyboard.print(act[0].w);
        //}
      }
      //
      //Keyboard.print("\n");
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
