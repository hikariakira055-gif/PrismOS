#include <LiquidCrystal.h>
#include <math.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

/*const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);*/

char aff[4][3] = {"INS", "PA1", "PA2", "PIN"};

//--------------------------------------------------------------

static int number_of_digit(int __template__){

  int iterator = 1;

  while(__template__ > 1){
    __template__ = __template__ / 10;
    iterator++;
  }

  return (iterator);

}


static int power(int a, int b){

  int summ = 1;

  for (int i = 0; i < b; i++){
    summ *= a;
  }

  return (summ);
  
}

int bit_to_dec(int binary){

  int __int__ = 0;
  float __t_number = 0;
  int __int_t__ = 0;
  int auxiliary_number = 0;
  int tmp = 0;
  __t_number = binary;
  for (int i = 0; i < number_of_digit(binary); i++){
    __t_number /= 10;
    
    auxiliary_number = (int)__t_number;

    printf("%f - %d = %f --> *10 = %f\n", __t_number, auxiliary_number, (__t_number - auxiliary_number), (__t_number - auxiliary_number)*10);

    tmp = (__t_number - auxiliary_number)*10 + 0.1;

    if(tmp < 0.6){
      __int__ = 0;
    }else{
      __int__ = 1;
    }
    

    printf("i - %d\n", __int__);
    
    __int_t__ = __int_t__ + (__int__ *  (power(2, i)));

    printf("(%d * 2 ^ %d = %d)\n", __int__, i, (__int__ * (power(2, i))));   

    __t_number = auxiliary_number;
    
  }

  return (__int_t__);

}


//------------------------------------------------------------------


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

int RAM[64];
int ITM[64][3];

int ITM_ID = 0;
int tmp_itm = 0;

void loop() {
  
  lcd.setCursor(8, 1);

  if(a0() == 1){
    delay(250);
    if(it != 3){ 
      
      it++;
    }else{
      
      it = 0;
    }
    
  }

  if(a0() == 5){ // select W_MODE
    delay(250);

    ITM[ITM_ID][0] = ins;
    ITM[ITM_ID][1] = pa1;
    ITM[ITM_ID][2] = pa2;

    ITM_ID++;

    lcd.clear();

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
    

  }else if(it == 3){ // execute

    if(a0() == 4){ // clear the section
      delay(250);
      
      lcd.clear();
    }

    if(a0() == 2 && tmp_itm < 64){ // up
      tmp_itm++;
      delay(500);
      lcd.clear();
      
    } else if(a0() == 3 && tmp_itm > 0){ // down
      tmp_itm--;
      delay(500);
      lcd.clear();
    }

    lcd.setCursor(0, 1);
    lcd.print(tmp_itm);

    lcd.setCursor(3, 1);
    lcd.print(bit_to_dec(ITM[tmp_itm][0]));

    lcd.setCursor(7, 1);
    lcd.print(bit_to_dec(ITM[tmp_itm][1]));

    lcd.setCursor(11, 1);
    lcd.print(bit_to_dec(ITM[tmp_itm][2]));

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
