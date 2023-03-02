#define ROW 30
#define COLUMN 5

int Led[COLUMN] = {8, 9, 10, 11, 12};
int pos[ROW][COLUMN] = {{0,0,0,0,0},
                        {1,0,0,0,0},
                        {0,1,0,0,0},
                        {0,0,1,0,0},
                        {0,0,0,1,0}, 
                        {0,0,0,0,1},
                        {1,0,0,0,1},
                        {0,1,0,0,1},
                        {0,0,1,0,1},
                        {0,0,0,1,1}, 
                        {1,0,0,1,1},
                        {0,1,0,1,1},
                        {0,0,1,1,1},
                        {1,0,1,1,1},
                        {0,1,1,1,1},
                        {1,1,1,1,1},
                        {1,1,1,1,0},
                        {1,1,1,0,1},
                        {1,1,1,0,0}, 
                        {1,1,0,1,0}, 
                        {1,1,0,0,1},
                        {1,1,0,0,0},   
                        {1,0,1,0,0}, 
                        {1,0,0,1,0}, 
                        {1,0,0,0,1},
                        {1,0,0,0,0},     
                        {0,1,0,0,0},   
                        {0,0,1,0,0}, 
                        {0,0,0,1,0}, 
                        {0,0,0,0,1},                
                       };//30種輸出形式

void setup() {
  for(int i=0; i<COLUMN; i++)
    pinMode(Led[i], OUTPUT);
}

void loop() {
  for(int i=0;i<ROW;i++)
  {
    for(int j=0;j<COLUMN;j++)
    {
      if(pos[i][j]==1)
      digitalWrite(Led[j],HIGH); //燈亮
      else
      digitalWrite(Led[j],LOW);  //燈暗
    }
    delay(500);
  }
}