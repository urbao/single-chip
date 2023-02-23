const int SEG_COM[4] = {10, 11, 12, 13};  // Control digit pin number
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
int disp[4];  // Desired display number digit
int number = 0; // when the power ON, display starting from 0

void setup() {
  Serial.begin(9600);
  for(int i=2; i<=13; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);  // Common anode configuration
  }
}

void loop() {
    number_transfer(number);  // the disp value should be updated
    SEG_Drive(disp[4]); // use disp[4] array to setup proper value of seven-segment display
    // delay for 1 sec, then add 1 to display number
    delay(1000);
    number=number+1;
}

// Side-function that helps present nubmer
void number_transfer(int Num){ // transfer number into a four-digits array called 'disp[]'
   // Caution: needs to consider leading zero condition
    disp[0]=(Num/1000); // Thousand
    disp[1]=(Num/100%10); // Hundred
    disp[2]=(Num/10%10); // Ten digit
    disp[3]=(Num%10); // Single digits
}

void SEG_Drive(char number){
    for(int i=0;i<8;i++){ // run through all the a~dp to set pin status 
        // since the pin of 'a' is 2,'b' is 3, and so on, so digitalWrite the pin of 'i+2'
        // assign the corresponding value to pin
        digitalWrite(i+2, SEG_data[number][i]);
    }
}
