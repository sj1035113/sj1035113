//i2c及tz master測 成功
//  X測 成功
//  Y測 成功 檔案於J25E
//  Z測 成功
#include <Wire.h>

#include <Unistep2.h>
Unistep2 SX1(4, 5, 6, 7, 4096, 950);
Ultrasonic USX1(3, 2);
Ultrasonic USY(11, 10);
Ultrasonic USZ(9, 8);
int coordinate[2][3]= {{20,0,21},
                       {4,0,19}};
int X=0;
int OX; //初始位子
int MX; //移動至距離
int NX; //目前位子
int WX; //判斷正負
int AX;
int Y=1;
int OY=0;
int MY;
int NY=100;
int WY;
int Z=2;
int OZ=0;
int MZ;
int NZ;
int WZ;
int AZ;
int TZ=5;
int NTZ;
int correctX=0;
int correctY=0;
int correctZ=0;
int correctTZ=0;
int data=100;
void sendtopz(){
  while(correctTZ<=3){     
  data=USZ.read();
  NTZ=data;
  Wire.beginTransmission(1);
  Wire.write(data);
  Wire.endTransmission();
  delay(3);
  Serial.println(data);
  if(NTZ<=TZ+1){
      correctTZ++;
    }
  }     
}
void moveX(){
  Serial.println("start");
  AX=OX+1;
  WX=coordinate[AX][X]
    -coordinate[OX][X];
  MX=coordinate[AX][X];
  Serial.println(WX);
  Serial.println(MX);     
  if(WX<0){
    while(correctX<=3){         //轉速要快一點的話，i值調高，單次移動加大:相反得延遲也會增加
      NX=USX1.read();
      for(int i=0;i<100;i++){
        SX1.run();
        SX1.move(10);
      }
      if(NX<=MX){
        correctX++;
      }
    }
  }
  if(WX>0){
    while(correctX<=3){         //轉速要快一點的話，i值調高，單次移動加大:相反得延遲也會增加
      NX=USX1.read();
      for(int i=0;i<100;i++){
        SX1.run();
        SX1.move(-10);
      }
      if(NX>=MX){
        Serial.println("FINISH");
        correctX++;
      }
    }
  }
  SX1.stop();
  Serial.println("LFINISH");
  correctX=0;
  OX++;  
}
void sendz(){
  AZ=OZ+1;
  MZ=coordinate[AZ][Z];
  while(correctZ<=3){         //轉速要快一點的話，i值調高，單次移動加大:相反得延遲也會增加
    Serial.println(data);    
    data=USZ.read();
    NZ=data;
    Wire.beginTransmission(1);
    Wire.write(data);
    Wire.endTransmission();
    delay(3);       
    if(NZ>=MZ){
      correctZ++;
    }
  }
  OZ++;
}
     

void setup(){ 
Wire.begin(); //I2C位址與連線設定，主端不用設 
Serial.begin(9600);
sendtopz();
moveX();
sendz();
} 

void loop(){ 
  //sendtopz();
  
  //moveX();
} 
