#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#define BLACK 0x0000
#define BRBLUE 0x95FF
#define RED 0xF800
#define PINK 0xFC38
#define WHITE 0xFFFF
MCUFRIEND_kbv tft;

int TS_LEFT=136,TS_RT=907,TS_TOP=139,TS_BOT=942;

//XP=8,XM=A2,YP=A3,YM=9

TouchScreen ts=TouchScreen(8,A3,A2,9,300);

TSPoint tp;

uint16_t xpos,ypos;
uint8_t mainIn;
uint8_t EggState;
uint32_t HrT,MnT,ScT,HrDT;
uint32_t PlusT;
uint32_t millisCalc;
uint32_t timerCalc;
uint32_t acc=71950;
uint32_t HrST,MnST,ScST;
boolean timer=0;

void EggDisplay()
{
  if(acc<72000)EggState=0;
  else if(acc>=72000 && acc<144000)EggState=1;
  else if(acc>=144000)EggState=2;
  tft.setTextSize(1);
  tft.setCursor(0, 90);
  tft.setTextColor(BLACK);
  switch(EggState)
  {
    case 0:
    {
      tft.println(" +++++");
      tft.println(" ## +");
      tft.println(" #### +");
      tft.println(" ##### +");
      tft.println(" +## ####");
      tft.println(" + ######");
      tft.println(" + ######");
      tft.println(" + ###+");
      tft.println(" + +/");
      tft.println(" +### +//");
      tft.println(" ##### +//");
      tft.println(" /### ++///");
      tft.println(" //+++++////");
      tft.println(" /////////"); 
      break;
    }
    
    case 1:
    {
      tft.println("\n\n ++++");
      tft.println(" ####+");    
      tft.println(" +## ++#");    
      tft.println(" + ###");    
      tft.println(" + ###");    
      tft.println(" + ##+");    
      tft.println(" + +/");   
      tft.println(" +### +//");   
      tft.println(" ##### +//");    
      tft.println(" /### ++///");    
      tft.println(" //+++++////");    
      tft.println(" /////////");    
      break;
    }
    
//    case 2:
//    {
//      tft.println("\n\n\n\n\n\n\n ++ ++ +++");    
//      tft.println(" + ++####/");
//      tft.println(" +### #+//");    
//      tft.println(" ##### +//");    
//      tft.println(" /### ++///");    
//      tft.println(" //+++++////");    
//      tft.println(" /////////");    
//      break;    
//    }
  }
}

void timeCalc()
{
  PlusT%=86400;
  millisCalc=((millis()/1000)+PlusT)%86400;
  MnT=millisCalc/60%60;
  HrT=millisCalc/3600;
  ScT=millisCalc%60;
}

void touchSensing()
{
  tp = ts.getPoint();
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  if (tp.z > 50 && tp.z < 1000)
  {
    xpos = map(tp.y, TS_BOT, TS_TOP, 0, tft.width());
    ypos = map(tp.x, TS_LEFT, TS_RT, 0, tft.height());
  }
  Serial.print(xpos);
  Serial.print(" ");
  Serial.println(ypos);
}

void setup()
{
  Serial.begin(9600);
  tft.reset();
  int ID=tft.readID();
  tft.begin(ID);
  tft.setRotation(3);
  tft.fillScreen(BLACK);
  tft.setCursor(10, 100);
  tft.setTextSize(5);
  tft.setTextColor(WHITE);
  
  tft.print("Start");
  for(int i=0;i<4;i++)
  {
    delay(200);
    tft.print(".");
  }
  delay(200);
  tft.setTextSize(6);
  tft.print("!");
  delay(200);
  
  tft.invertDisplay(true);
  delay(200);
  
  main:
  
  tft.fillScreen(WHITE);
  tft.invertDisplay(false);
  tft.drawLine(220, 10,220,229,BLACK);
  tft.drawLine( 10, 40,209, 40,BLACK);
  tft.drawLine(231, 40,309, 40,BLACK);
  tft.drawLine( 10,100,209,100,BLACK);
  tft.drawLine(231,200,309,200,BLACK);
  tft.drawLine(25,140,210,140,BLACK);
  tft.drawLine(25,229,210,229,BLACK);
  tft.drawLine(25,140,25,229,BLACK);
  tft.drawLine(210,140,210,229,BLACK);
  tft.drawLine(15,150,30,150,BLACK);
  tft.drawLine(15,155,30,155,BLACK);
  tft.drawLine(15,170,30,170,BLACK);
  tft.drawLine(15,175,30,175,BLACK);
  tft.drawLine(15,190,30,190,BLACK);
  tft.drawLine(15,195,30,195,BLACK);
  tft.drawLine(15,210,30,210,BLACK);
  tft.drawLine(15,215,30,215,BLACK);
  
  tft.setTextColor(BRBLUE);
  tft.setCursor(20,105);
  tft.setTextSize(4);
  tft.print("SCHEDULE");
  
  tft.setCursor(0, 5);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.println(" Dont worry \n Be happy");
  
  //switch(DayT)
  //{
  //  case 1: tft.println(" Dont worry \n Be happy"); break;
  //  case 2: tft.println("Do your best You can be"); break;
  //  case 3: tft.println("Times never Stop"); break;
  //  case 4: tft.println("Nothing is Impossible"); break;
  //  case 5: tft.println("Cheer Up"); break;
  //}
  
  tft.setTextSize(3);
  tft.setCursor(226,10);
  tft.print("D-32");
  
  tft.setTextSize(1);
  tft.setCursor(226,65);
  tft.print("acc");
  
  tft.setTextSize(2);
  tft.print(" ");
  tft.setTextSize(1);
  tft.print(" h");
  
  tft.setTextSize(2);
  tft.print(" ");
  tft.setTextSize(1);
  tft.print(" m");
  
  tft.setTextSize(2);
  tft.setCursor(250,60);
  if(HrST<10)tft.print(" ");
  tft.print(HrST);
  
  tft.print(" ");
  if(MnST<10)tft.print(" ");
  tft.print(MnST);
  
  tft.setTextSize(2);
  tft.setCursor(230,210);
  tft.print("10.12");
  
  tft.setTextSize(1);
  tft.setCursor(295,222);
  tft.print("sat");
  
  EggDisplay();
  
  while(1)
  {
    timeCalc();
    if(HrT<12)
    {
      tft.setCursor(0,50);
      tft.setTextSize(2);
      tft.setTextColor(BLACK,BRBLUE);
      tft.println(" AM");
      tft.setTextColor(BLACK,WHITE);
      tft.println(" ");
      tft.println(" PM");
      
      if(HrT==0)HrDT=12;
      else HrDT=HrT;
    }
    
    else if(HrT>=12)
    {
      tft.setCursor(0,50);
      tft.setTextSize(2);
      tft.setTextColor(BLACK,WHITE);
      tft.println(" AM\n");
      tft.setTextColor(BLACK,BRBLUE);
      tft.println(" PM");
      
      if(HrT>12)HrDT=HrT-12;
      else HrDT=HrT;
    }
    
    tft.setTextColor(BLACK,WHITE);
    tft.setCursor(50,60);
    tft.setTextSize(4);
    tft.print(HrDT);
    if(HrDT<10)tft.print(" ");
    tft.print(":");
    if(MnT<10)tft.print(" ");
    tft.print(MnT);
    
    tft.setCursor(180,65);
    tft.setTextSize(3);
    if(ScT<10)tft.print(" ");
    tft.print(ScT);
    
    delay(50);
    
    touchSensing();
    
    if(tp.z>50&&tp.z<1000)
    {
      Serial.print(xpos);
      Serial.print(" ");
      Serial.println(ypos);
      if(xpos>32&&xpos<237&&ypos>42&&ypos<87)mainIn=1;
      else if(xpos>253&&xpos<330&&ypos>41&&ypos<190)mainIn=2;
      else if(xpos>31&&xpos<236&&ypos>104&&ypos<233)mainIn=3;
      else if(xpos>251&&xpos<333&&ypos>1&&ypos<28)mainIn=4;
      else if(xpos>251&&xpos<333&&ypos>211&&ypos<235)mainIn=5;
      else mainIn=0;
      if(mainIn!=0)break;
    }
  
  }
  
  tft.fillScreen(WHITE);
  
  switch(mainIn)
  {
    case 1:
    {
      tft.setTextSize(3);
      tft.setCursor(160,10);
      tft.setTextColor(BLACK);
      tft.print("Time Set");
      tft.drawLine(10,40,309,40,BLACK);
      
      tft.setCursor(0,75);
      tft.setTextSize(6);
      tft.setTextColor(RED);
      tft.println(" ^ ^\n\n Y Y");
      tft.fillRect(0,195,319,239,WHITE);
      
      while(1)
      {
        timeCalc();
        
        tft.setTextColor(BLACK,WHITE);
        tft.setCursor(40,110);
        tft.setTextSize(6);
        if(HrT<10)tft.print(" ");
        tft.print(HrT);
        tft.print(":");
        if(MnT<10)tft.print(" ");
        tft.print(MnT);
        
        tft.setCursor(240,125);
        tft.setTextSize(4);
        if(ScT<10)tft.print(" ");
        tft.print(ScT);
        
        delay(50);
        
        touchSensing();
        
        if(tp.z>50&&tp.z<1000)
        {
          if(PlusT<3600)PlusT+=86400;
          if(xpos<=30)goto main; 
          else if(xpos>30&&xpos<=150&&ypos<130)PlusT+=3600;
          else if(xpos>30&&xpos<=150&&ypos>=130)PlusT-=3600;
          else if(xpos>150&&xpos<=255&&ypos<130)PlusT+=60;
          else if(xpos>150&&xpos<=255&&ypos>=130)PlusT-=60;
          else if(xpos>255)PlusT-=ScT;
          
          delay(1);
        }
      }
    }
    
    case 2:
    {
      tft.fillScreen(WHITE);
      tft.drawLine(10,40,309,40,BLACK);
      tft.drawLine(10,200,309,200,BLACK);
      tft.setTextSize(3);
      
      tft.setCursor(130,10);
      tft.setTextColor(BLACK);
      tft.println("Study Mode");
      tft.setTextColor(RED);
      tft.print("\n\n\n\n\n\n\n reset");
      
      EggDisplay();
      
      while(1)
      {
        tft.setTextSize(3);
        tft.setCursor(50,65);
        if(timer==0)
        {
          tft.setTextColor(PINK,WHITE);
          tft.print(">");
          tft.print(" ");
          tft.setTextColor(RED,WHITE);
          tft.print("ll");
        }
        else if(timer==1)
        {
          tft.setTextColor(RED,WHITE);
          tft.print(">");
          tft.setTextColor(PINK,WHITE);
          tft.print(" ");
          tft.print("ll");
        }
        
        ScST=acc/10%60;
        MnST=(acc/600)%60;
        HrST=(acc/36000)%24;
        tft.setTextColor(BLACK,WHITE);
        tft.setTextSize(5);
        
        tft.setCursor(10,110);
        if(HrST<10)tft.print(" ");
        tft.print(HrST);
        tft.print(":");
        if(MnST<10)tft.print(" ");
        tft.print(MnST);
        tft.setTextSize(3);
        
        tft.setCursor(180,120);
        if(ScST<10)tft.print(" ");
        tft.print(ScST);
        
        touchSensing();
        
        if(tp.z>50&&tp.z<1000)
        {
          if(xpos<30)
          {
            timer=0;
            goto main;
          }
          else if(xpos>=30&&xpos<150&&ypos<=190)timer=1;
          else if(xpos>=150&&ypos<=190)timer=0;
          else if(xpos>=30&&ypos>190)acc=1;
        }
        if(timer==1)acc++;
        
        delay(49);
        
        if(acc%36000==0)
        {
          acc++;
          tft.fillRect(220,90,319,110,WHITE);
          
          EggDisplay();
        }
      }
    }
    
    case 3:
    {
      tft.setTextSize(3);
      tft.setCursor(160,10);
      tft.setTextColor(BLACK);
      tft.print("SCHEDULE");
      tft.drawLine(10,40,309,40,BLACK);
      
      while(1)
      {
        touchSensing();
        if(tp.z>50&&tp.z<1000)if(xpos<=30)goto main;
      }
    }
    
    case 4:
    {
      tft.setTextSize(3);
      tft.setCursor(220,10);
      tft.setTextColor(BLACK);
      tft.print("D-day");
      tft.drawLine(10,40,309,40,BLACK);
      
      while(1)
      {
        touchSensing();
        if(tp.z>50&&tp.z<1000)if(xpos<=30)goto main;
      }
    }
    
    case 5:
    {
      tft.setTextSize(3);
      tft.setCursor(230,10);
      tft.setTextColor(BLACK);
      tft.print("Date");
      tft.drawLine(10,40,309,40,BLACK);
      
      while(1)
      {
        touchSensing();
        if(tp.z>50&&tp.z<1000)if(xpos<=30)goto main;
      }
    }
  }
}

void loop(){}
