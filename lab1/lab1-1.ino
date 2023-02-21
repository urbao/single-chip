int Led[5]={8, 9, 10, 11, 12};

void setup(){
    for(int i=0;i<5;i++){
        pinMode(Led[1], OUTPUT);
    }
}

void Loop(){
    // Add code to achieve Marquee LED
    // LED ON order: 8, 9, 10, 11, 12, 12, 11, 10, 9, 8
}

