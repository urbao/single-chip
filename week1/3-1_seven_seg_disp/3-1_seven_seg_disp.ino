const int SEG_COM[4] = {10, 11, 12, 13};  // Control number-digit pin number
const int SEG_data[10][8] = {{1, 1, 1, 1, 1, 1, 0, 0},  //"0"  // Data
                       {0, 1, 1, 0, 0, 0, 0, 0},  //"1"
                       {1, 1, 0, 1, 1, 0, 1, 0},  //"2"
                       {1, 1, 1, 1, 0, 0, 1, 0},  //"3"
                       {0, 1, 1, 0, 0, 1, 1, 0},  //"4"
                       {1, 0, 1, 1, 0, 1, 1, 0},  //"5"
                       {1, 0, 1, 1, 1, 1, 1, 0},  //"6"
                       {1, 1, 1, 0, 0, 0, 0, 0},  //"7"
                       {1, 1, 1, 1, 1, 1, 1, 0},  //"8"
                       {1, 1, 1, 0, 0, 1, 1, 0}};  //"9"

int disp[4] = {2, 0, 2, 3};  // The number desired to display

void setup() {
  for(int i=2; i<=13; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);  // Common anode(All connected to HIGH(VDD source))
  }
}

void loop() {
// Since the SEG_COM can only control display of one digit at a time
// so, we use iteration to repeat set display number
  for(int i=0; i<=3; i++){  // Run through all different digit
    digitalWrite(SEG_COM[i], LOW); // When LOW, means loop is closed(connected to GND) 
    SEG_Drive(disp[i]);  // Write data based on the disp[]
    delay(5);
    digitalWrite(SEG_COM[i], HIGH);  // When HIGH, means loop is short(connected to HIGH)
  }
}

void SEG_Drive(char number){
    // Choose the corresponding number desired to display
    // and assign the a~dp value to 7-segment display
    // number: also he same to element index of SEG_data[]
    for(int i=0;i<8;i++){ // run through all the a~dp to set pin status 
        // since the pin of 'a' is 2,'b' is 3, and so on, so digitalWrite the pin of 'i+2'
        // assign the corresponding value to pin
        digitalWrite(i+2, SEG_data[number][i]);
    }
}
