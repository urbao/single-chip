int Led[5]={8, 9, 10, 11, 12};
int curr_Led_idx=0; // This's the current operated LED index in array of Led[]

void setup(){
    for(int i=0;i<5;i++){
        pinMode(Led[i], OUTPUT);
    }
}

void Loop(){
    // Add code to achieve Marquee LED
    // LED ON order: 8, 9, 10, 11, 12, 12, 11, 10, 9, 8
    // Following assign the operating LED index
    for(int i=0;;i++){
        if(i%10==0 || i%10==9)
            curr_Led_idx=0;
        else if(i%10==1 || i%10==8)
            curr_Led_idx=1;
        else if(i%10==2 || i%10==7)
            curr_Led_idx=2;
        else if(i%10==3 || i%10==6)
            curr_Led_idx=3;
        else
            curr_Led_idx=4;
    }
    // Start controlling LED
    // First turn on, and wait for 500ms
    digitalWrite(Led[curr_Led_idx], HIGH);
    delay(500);
    // And, turn off, also wait for 500ms
    digitalWrite(Led[curr_Led_idx], LOW);
    delay(500);

}

