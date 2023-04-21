const int led_pin = 13;

void setup(){
    Serial.begin(115200);
    pinMode(led_pin, OUTPUT);  
    
    // disable all interrupts
    noInterrupts();
    // TCCR1A Reset
    TCCR1A=0; 
    // TCCR1B Reset
    TCCR1B=0; 
    // load timer
    TCNT1=0;
    // set compare value by OCR1?
    OCR1A=31250;
    // 256 prescaler
    TCCR1B|=(1<<CS12);
    // set CTC mode by TCCR1?
    //enable  Timer1 compare interrupt mode by TIMSK?
    TIMSK1|=(1<<OCIE1A);
    //enable  interrupt 
    interrupts();
}

void loop(){                   
    Serial.println(TCNT1);
}

ISR(TIMER1_COMPA_vect){
    //create a ISR() to control the routine of Timer1 interrupt and led toggled.
    TCNT1=0;
    digitalWrite(led_pin, !digitalRead(led_pin));
}
