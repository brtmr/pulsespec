#include <LiquidCrystal.h>
#define LENGTH 16
#define EMPTYCHAR B00010000
#define BAR_ROW   0B11011

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
byte single_character[8];
int counter;
char signal[LENGTH];
char remainig[LENGTH+1];
boolean redraw;
boolean found;

/* creates a character set of 8 bars of different height */
void setup(){
  Serial.begin(9600);
  int i,j;
  for (i=0; i<8; i++){
    for (j=0; j<8; j++){
      single_character[j] = (8-(j+1))>i ? 0 : BAR_ROW;
    }
    lcd.createChar(i, single_character);
    delay(10);
  }
  lcd.begin(LENGTH, 2);
  counter = 0;
}

void loop(){
  redraw = false;
  while (Serial.available() >= LENGTH){
    found = Serial.findUntil("\x10","?");
  }
  if (found) {
    redraw =(Serial.readBytes(signal,LENGTH)==LENGTH);
  }
  for (int i=0; i<LENGTH; i++) {
    draw_bar(signal[i],i);
  }

}

void draw_bar(int height, int col){
  height = height % 16;
  int lower = height<=7 ? height : 7;
  int upper = height>7 ? (height-8) : (-1);
  lcd.setCursor(col,1);
  lcd.write(byte(lower));

  lcd.setCursor(col,0);
  if (upper>=0){
    lcd.write(byte(upper));
  } 
  else {
    lcd.write(byte(EMPTYCHAR));
  }
}
