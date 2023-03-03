#include <Keypad.h>   //引用Keypad函式庫
#include <Password.h> //引用Password函式庫
#define KEY_ROWS 4    //按鍵模組的列數
#define KEY_COLS 4    //按鍵模組的行數

//Keypad設定
const byte colPins[4] = {7, 8, 9, 10};
const byte rowPins[4] = {3, 4, 5, 6};
const char keymap[KEY_ROWS][KEY_COLS] = { {'1','2','3','A'}, 
                                          {'4','5','6','B'}, 
                                          {'7','8','9','C'},
                                          {'*','0','#','D'} };
Keypad myKeypad = Keypad(makeKeymap(keymap),rowPins,colPins,KEY_ROWS,KEY_COLS);

// initialize random number for answer
String ans=""; // used to store the real answer
String input=""; // used to temp. store user input
int a_count=0; // used to store value of A & B counts
int b_count=0;
bool win_already=true; // check if user win or not(initialize to true: generate passwd in the beginning)
bool matched[4]={0}; // checked if the ans bit is matched to another input bit

void setup(){
  Serial.begin(9600);
  randomSeed(analogRead(0)); // used randomSeed(so the random number can be really random)
}

void loop(){
  if(win_already==true)ans=String(random(10000));
  win_already=false;
  Serial.print("Answer: ");
  Serial.println(ans);

  // make sure password is 4 digit
  while(ans.length()!=4){
    ans="0"+ans;
  }
  // get a 4 digit input
  while(input.length()!=4){
    char key=myKeypad.getKey();
    if(key)input+=String(key);
  }

  // print out user input, so user can see their input
  Serial.println(input);

  if(input.length()==4){
    // checking `a` counts
    for(int i=0;i<4;i++){
      if(ans[i]==input[i]){
        a_count++;
        matched[i]=1;
      }
    }

    // Start checking
    // first, checking `b` counts
    for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
        if(input[i]==ans[j]&&matched[j]!=1&&i!=j){
          b_count++;
          matched[j]=1;
        }
      }
    }
    
    // print out result
    Serial.print(a_count);
    Serial.print("A");
    Serial.print(b_count);
    Serial.println("B");
  
    // check if win
    if(a_count==4){
      Serial.println("You win!");
      win_already=true; // if win, reset the whole game
    }
    // reset all inputs, so next time user input can be update
    input="";
    b_count=0;
    a_count=0;
    for(int i=0;i<4;i++)matched[i]=0;
  }

}
