#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // setup address of LCD I2C

// print out in LCD screen function
// parameter: [cols, rows, info]
void printout(int cols, int rows, String info){
    lcd.setCursor(cols, rows);
    lcd.print(info);
}

void setup(){
    // lcd initialization
    lcd.init();
    lcd.backlight();
    // print out the info
    printout(3, 0, "Second Group");
    printout(1, 1, "has four members");
    Serial.begin(115200); // set up port number
    for(int i=0;i<2;i++){
        // blink twice
        lcd.noBacklight();
        delay(1000);
        lcd.backlight();
        delay(1000);
    }
    lcd.clear();// clear the screen of LCD
    printout(3, 0, "Use Serial");
    printout(5, 1, "Monitor");
}

void loop(){
    if(Serial.available()){
        lcd.clear(); // clear the screen
        String tmp=Serial.readString();
        if(tmp.length()>2){ // since readString() function will also read the newline character
            printout(0,0,"Input too long");
        }
        else{
          int num=tmp.toInt();
          switch(num){
              case 1:
                  printout(0,0,"E24094198");
                  break;
              case 2:
                  printout(0,0,"E24094130");
                  break;
              case 3:
                  printout(0,0,"E24094164");
                  break;
              case 4:
                  printout(0,0,"E24091069");
                  break;
              default:
                  printout(0,0,"Wrong Input");
                  break;
            } 
        }
    }
}
