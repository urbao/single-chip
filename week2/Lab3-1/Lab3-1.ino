const int SEG_COM[4] = {10, 11, 12, 13};  //控制線
const int SEG_data[10][8] = {{1, 1, 1, 1, 1, 1, 0, 0},  //"0"  //資料線
                       {0, 1, 1, 0, 0, 0, 0, 0},  //"1"
                       {1, 1, 0, 1, 1, 0, 1, 0},  //"2"
                       {1, 1, 1, 1, 0, 0, 1, 0},  //"3"
                       {0, 1, 1, 0, 0, 1, 1, 0},  //"4"
                       {1, 0, 1, 1, 0, 1, 1, 0},  //"5"
                       {1, 0, 1, 1, 1, 1, 1, 0},  //"6"
                       {1, 1, 1, 0, 0, 0, 0, 0},  //"7"
                       {1, 1, 1, 1, 1, 1, 1, 0},  //"8"
                       {1, 1, 1, 0, 0, 1, 1, 0}};  //"9"


int disp[4] = {2, 0, 2, 3};  //欲顯示數字

void setup() {
  for(int i=2; i<=13; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);  //共陽極
  }
}

void loop() {
  for(int i=0; i<=3; i++){  //個、十、百、千位數
    digitalWrite(SEG_COM[i], LOW);  //觸發第i位數顯示數字
    SEG_Drive(disp[i]);  //資料線寫入數值
    delay(5);
    digitalWrite(SEG_COM[i], HIGH);  //結束觸發第i位數
  }
}

void SEG_Drive(int number){  //將字元變數從SEG_data[][]找到相對應的位置，並寫入a~g中
  for(int i = 2; i<10; i++)
  {
    // i: pin腳
    // number: 要顯示的數字
    // pos: 亮的位置
    int pos = i-2;
    digitalWrite(i,SEG_data[number][pos]);
  }
}
