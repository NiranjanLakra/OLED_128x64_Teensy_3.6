#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

/////////////////////////////////////////////////////////////
const byte ROWS=6;
const byte COLS=3;

int UD=0;            // position of rectangular box
int menu_set=0;      // menu item number
int cursor_id=0;     // Cursor POS
int temp=0;          // value for dash_effect
int x=0;             // Initial X value
int y=0;             // Initial y value
int z=0;             // Initial z value

char keys[ROWS][COLS]=
{
  {'M','U','B'},
  {'L','O','R'},
  {'.','D','0'},
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'}
};
byte rowPins[ROWS] = {2,3,4,5,6,7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8,9,10}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

/////////////////////////////////////////////////////////////
#define OLED_RESET -1
#define PAUSE 1000
#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH  128 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/////////////////////////////////////////////////////////////
void setup()   
{     
  Serial.begin(9600);          
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.fillScreen(0);
  display.display(); 
}
String Main_Menu2[4][5][5]=
{
  {{"WIFI","SCAN","ATCK","SERV","NETT"},{5,6,7,8,9},{10,11,12,13,14},{15,16,17,18,19},{20,21,22,23,24}},
  {{"RFAT","RFSC","ATCK","BLST","JAMM"},{30,31,32,33,34},{35,36,37,38,39},{40,41,42,43,44},{9,9,9,9,9}},
  {{"CARA","PHOB","ATTK","IGNI","KILL"},{25,46,47,48,49},{50,51,52,53,54},{55,56,57,58,59},{9,9,9,9,9}},
  {{"BUNY","SYST","ARCH","MEAN","PALD"},{65,66,67,68,69},{70,71,72,73,74},{75,76,77,78,79},{9,9,9,9,9}}
};

/////////////////////////////////////////////////////////////   
int cursor_pp=0;
void line_drawer(int c, int f)
{
  display.setTextColor(c);
  display.setCursor(f,5);              //36, 74
  display.print("-");
  delay(20);
  display.display();
  display.setCursor(f,20);
  display.print("-");
  delay(20);
  display.display();
  display.setCursor(f,35);
  display.print("-");
  delay(20);
  display.display();
  display.setCursor(f,50);
  display.print("-");
  display.display();
}
int cursor_p=0;
int line_p=0;
void dash_drawer(int p,int c, int d)
{
  if(temp>0)
  {
    display.setTextColor(0);
    display.setCursor(c,temp);         //////////////////// cursor pos 30,68
    display.print("-");
    display.drawLine(d,8,73,d,0);      //////////////////// line pos 35,73
    display.display();
  }
  display.setTextColor(1);
  display.setCursor(c,p+5);            //////////////////// cursor pos 30,68
  display.print("-");
  temp=p+5;
  display.drawLine(d,8,d,53,1);       //////////////////// line pos 35,73
  delay(20);
  display.display();
}

void line_functions()
{
  line_drawer(0,cursor_pp);
  dash_drawer(UD,cursor_p,line_p);
  line_drawer(1,cursor_pp);
}
void rect_drawup(int p)
{
  display.setTextColor(1);
  display.setTextSize(1);
  display.drawRect(p,3+UD,27,11,1);
  display.drawRect(p,18+UD,27,11,0);
  display.display();
}
void rect_drawdown(int j)
{
  display.setTextColor(1);
  display.setTextSize(1);
  display.drawRect(j,3+UD,27,11,1);
  display.drawRect(j,3+UD-15,27,11,0);
  display.display();
}
int array_id=0;      // current menu (in 3 Dimension)
int pos1=0;

void up_down(char KEY)
{
  if(KEY=='U' && array_id>0)
  {
    if(UD>0)
    {
      UD-=15; 
      rect_drawup(pos1);
      if(pos1!=79)
      {
        line_functions();
      }
    }
    if(cursor_id>0)
    {
      cursor_id-=1;
    }
    else
    {
      
    }
  }
  else if(KEY=='D' && array_id>0)
  {
    if(UD<45)
    {
      UD+=15;
      rect_drawdown(pos1);
      if(pos1!=79)
      {
        line_functions();
      }
    }
    if(cursor_id<=2)
    {
      cursor_id+=1;
    }
    else
    {

      
    }
}
}

////////////////////////////////////////////////////////
int bp=0;
void blank_space(int k)
{
  display.fillRect(k,3,27,56,0); ///43
}
int temp1=0;
int temp12=0;
int temp2=0;
int temp22=0;
void key_handler(char KEY)
{
  if (KEY=='M')
  {
  display.setTextColor(1);
  display.setTextSize(1);
  if(array_id==0)
  {
    menu_handler(x,y,z,array_id);
    pos1=3;
    bp=43;
    cursor_p=30;
    line_p=35;
    cursor_pp=36;
    rect_drawup(pos1);
    line_functions();
    array_id+=1;
    menu_handler(x,y,z,array_id);
  }
  else if(array_id==1)
  {
    temp1=cursor_id;
    temp12=UD;
    menu_handler(x,y,z,array_id);
    pos1=41;
    bp=81;
    cursor_p=68;
    line_p=73;
    cursor_pp=74;
    rect_drawup(pos1);
    line_functions();
    array_id+=1;
    menu_handler(x,y,z,array_id);
  }
  else if(array_id==2)
  {
    temp22=UD;
    menu_handler(x,y,z,array_id);
    pos1=79;
    rect_drawup(pos1);
    line_functions();
  }
  Serial.print("\narray_id=");
  Serial.print(array_id);
  }
  if (KEY=='B' && array_id>0)
  {
  display.setTextColor(1);
  display.setTextSize(1);
  array_id-=1;
  if(array_id==0)
  {
    UD=temp12;
    menu_handler(x,y,z,array_id);
    pos1=3;
    bp=41;
    cursor_p=30;
    line_p=35;
    cursor_pp=36;
    blank_space(bp);
    rect_drawup(pos1);
    blank_space(bp);
    line_functions();
    array_id+=1;
    menu_handler(x,y,z,array_id);
  }
  else if(array_id==1)
  {
    bp=41;
    blank_space(bp);
    UD=temp22;
    menu_handler(x,y,z,array_id);
    pos1=41;
    
    cursor_p=68;
    line_p=73;
    cursor_pp=74;
    bp=81;
    blank_space(bp);
    rect_drawup(pos1);
    line_functions();
    array_id+=1;
    menu_handler(x,y,z,array_id);
    array_id-=1;
  }}
  else if(KEY=='U' || KEY=='D')
  {
    if(pos1!=79)
    {
      blank_space(bp);
      up_down(KEY);
      menu_handler(x,y,z,array_id);
    }
    else
    {
      up_down(KEY);
    }
  }
  else
  {
    
  }
  
}

////////////////////////////////////////////////////////
int j;
int t2=0;
void menu_handler(int x, int y, int z, int arr)   
{
  if(arr==0)
  {
    for(int i=0; i<4; i++)// value of x will change
    {
      display.setCursor(5,5+(i*15));
      display.print(Main_Menu2[i][y][z]);
    }
    display.display();
  } 
   if(arr==1)
  {
    j=0;
//    display.setTextColor(1);
//    display.setTextSize(1);
    for(int i=1; i<=5; i++)// value of z will change
    {
      display.setCursor(43,5+(j*15));
      display.print(Main_Menu2[cursor_id][y][i]);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
      j+=1;
    }
    display.display();
    t2=cursor_id;
  }
  if(arr==2)
  {
    j=0;
    for(int l=1; l<=5; l++)// value of x will change
    {
      display.setCursor(81,5+(j*15));
      display.print(Main_Menu2[t2][l][cursor_id]);
      j+=1;
    }
    display.display();
  } 
}

void loop()
{
  
  char key = keypad.getKey();
  if (key != NO_KEY)
  {
    key_handler(key);
  }
}
