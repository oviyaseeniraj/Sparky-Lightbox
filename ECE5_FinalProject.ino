#include <PS2Keyboard.h>
#include <RGBmatrixPanel.h>
using namespace std;

const int DataPin = 4;
const int IRQpin =  3;
#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

PS2Keyboard keyboard;
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);
String str = "";

void setup() {
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("Keyboard Test:");
  
//  matrix.begin();
//  matrix.fillScreen(matrix.Color333(0, 0, 0));
//  matrix.setTextSize(1);
//  matrix.setTextWrap(true);
//  matrix.setCursor(2, 2);
//  matrix.print("HI! ENTER");
//  matrix.setCursor(2, 12);
//  matrix.print ("TEXT ON");
//  matrix.setCursor(2, 22);
//  matrix.print("KEYBOARD:");
//  delay (5000);
//  matrix.fillScreen(matrix.Color333(0, 0, 0));
//  matrix.setCursor(2, 2);
}

void loop() {
  if (keyboard.available()) {
    
    // read the next key
    char c = keyboard.read();
    if (c == PS2_DELETE)
    {
      String strCopy = "";
       for (int i = 0; i < str.length()-1; i++)
       {
        strCopy = strCopy+str[i];
       }
       str = strCopy;
    }
    else if (c == PS2_ENTER)
    {
      printMatrix(str);
    }
    else
    {
      Serial.print(c);
     str = str + c;
    }
  }
}

void printMatrix(String str)
{
  
  matrix.begin();
  if (str == "circles")
  {
    circles();
    str = "";
  }
  else if (str == "x")
  {
    matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(0, 7, 0));
    delay(300);
    matrix.drawRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(7, 7, 0));
    delay(300);
    matrix.drawLine(0, 0, matrix.width()-1, matrix.height()-1, matrix.Color333(7, 0, 0));
    matrix.drawLine(matrix.width()-1, 0, 0, matrix.height()-1, matrix.Color333(7, 0, 0));
    delay(500);
  }
  else if (str == "flashing")
  {
    matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(7, 0, 0));
    delay(300);
    matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(7, 7, 0));
    delay(300);
    matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(0, 7, 0));
    delay(300);
    matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(0, 0, 7));
    delay(300);
    matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(7, 0, 7));
    delay(300);
  }
  else if (str.substring(0,3) == "red")
  {
    matrix.setTextColor(matrix.Color333(7,0,0));
    matrix.print(str.substring(3, str.length()) + " ");
    str = "";
  }
  else if (str.substring(0,6) == "yellow")
  {
    matrix.setTextColor(matrix.Color333(7,4,0));
    matrix.print(str.substring(6, str.length()) + " ");
    str = "";
  }
  else if (str.substring(0,5) == "green")
  {
    matrix.setTextColor(matrix.Color333(0,7,0));
    matrix.print(str.substring(5, str.length()) + " ");
    str = "";
  }
  else if (str.substring(0,4) == "blue")
  {
    matrix.setTextColor(matrix.Color333(0,0,7));
    matrix.print(str.substring(4, str.length()) + " ");
    str = "";
  }
  else if (str.substring(0,6) == "purple" || str.substring(0,6) == "violet")
  {
    matrix.setTextColor(matrix.Color333(7,0,7));
    matrix.print(str.substring(6, str.length()) + " ");
    str = "";
  }
  else
  {
    matrix.print(str + " ");
    str = "";
  }
  loop();
}

void circles()
{
  matrix.drawCircle(10, 10, 10, matrix.Color333(0, 0, 7));
  delay(500);
  matrix.fillCircle(40, 21, 10, matrix.Color333(7, 0, 7));
  delay(500);
}
