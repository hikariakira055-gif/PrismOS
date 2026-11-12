#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

/*const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);*/

char aff[3][3] = {"INS", "PA1", "PA2"};

int nuber_of_diigt(int __template__){
  
}

int bit_to_dec(int binary){
  int __int__ = 0;
  int __t_number = 0;

  for (int i = 0; i < 4; i++){
    __t_number = (binary >> i);
    __t_number = (__t_number&1);
    __int__ = __int__ + (__t_number * (int)pow(2, i));
  }

  return (__int__);

}



//-------Screen and logiciel manipulation
int a0(void){ // keypad
  int x;
  x = analogRead(0);
  lcd.setCursor(10, 1);
  if (x < 60) {
    return (1); // right 
  } else if (x < 200) {
    return (2); // up 
  } else if (x < 400) {
    return (3); // down
  } else if (x < 600) {
    return (4); //left
  } else if (x < 800) {
    return (5); //select
  } else {
    return (6);
  }
}
void arcangel(){ // display

}
void angel(){

}

void setup() {
  lcd.cursor();
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 0);


  lcd.clear();
  
  
}

int it = 0;

int ins = 0;
int pa1 = 0;
int pa2 = 0;
int id = 0;

int ins_digit = 0;
int pa1_digit = 0;
int pa2_digit = 0;

int ITM[16][64];
int RAM[10][16];

void loop() {
  
  lcd.setCursor(8, 1);

  if(a0() == 1){
    delay(250);
    if(it != 2){ 
      
      it++;
    }else{
      
      it = 0;
    }
    
  }

  if(a0() == 5){ // select W_MODE
    delay(250);

  }
 
  if(it == 0){
    
    if(a0() == 4){ // clear the section
      delay(250);
      ins = 0b0000;
      ins_digit = 0;
      lcd.clear();
    }

    if(a0() == 2 && ins_digit < 4){ // 1
      ins = ins * 10 + 1;
      delay(500);
      ins_digit++;
    } else if(a0() == 3 && ins_digit < 4){ // 0
      ins = ins * 10;
      delay(500);
      ins_digit++;
      
    }


  }
  else if(it == 1){
  

    if(a0() == 4){ // clear the section
        delay(250);
        pa1 = 0b0000;
        pa1_digit = 0;
        lcd.clear();
      }

      if(a0() == 2 && pa1_digit < 4){ // 1
        pa1 = pa1 * 10 + 1;
        delay(500);
        pa1_digit++;
      } else if(a0() == 3 && pa1_digit < 4){ // 0
        pa1 = pa1 * 10;
        delay(500);
        pa1_digit++;
        
      }

  }
  else if(it == 2){
   

    if(a0() == 4){ // clear the section
      delay(250);
      pa2 = 0b0000;
      pa2_digit = 0;
      lcd.clear();
    }

    if(a0() == 2 && pa2_digit < 4){ // 1
      pa2 = pa2 * 10 + 1;
      delay(500);
      pa2_digit++;
    } else if(a0() == 3 && pa2_digit < 4){ // 0
      pa2 = pa2 * 10;
      delay(500);
      pa2_digit++;
      
    }


  }

  lcd.setCursor(0, 0);
  lcd.print(ins);

  lcd.setCursor(5, 0);
  lcd.print(pa1);

  lcd.setCursor(10, 0);
  lcd.print(pa2);

  lcd.setCursor(15, 0);
  lcd.print(it);

}
