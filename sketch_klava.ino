// '''

// 0 — 200, яркое дневное освещение
// 200 — 150, приглушенный свет
// 150 — 800, сумерки
// 800 — 1023, темнота

// '''

// Порты моторов
#define M5 A5     // сироп
#define M3 A3     //вода
#define M4 A4     // сок

// подключение клавиатуры
#include <Keypad.h>
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {   {'1', '2', '3', 'A'},   {'4', '5', '6', 'B'},   {'7', '8', '9', 'C'},   {'*', '0', '#', 'D'} };
byte rowPins[ROWS] = {9, 8, 7, 6};  
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
byte currentIndex;
// подключение мотора
#define in1 10
#define in2 11
#define in3 12
#define in4 13

//  датчики света
uint8_t  PIN_violet = A0;   
uint8_t  PIN_green = A1; 
uint16_t LUM_violet;  
uint16_t LUM_green;  

// время работы мотора
long steps_50_ml = 2304;
long steps_80_ml = 3687;
long steps_30_ml = 1382;
long steps_35_ml = 1613;

long steps_45_ml = 2344;
long steps_10_ml = 483;
long steps_40_ml = 2083;
long steps_50_mlO = 2604;
long steps_20_ml = 966;



int dl = 11;  

// список напитков
char inputDigits[5];  


void oneStep(){
  digitalWrite(M3,LOW);
  digitalWrite(M4,LOW);
  digitalWrite(M5,LOW);

  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH);
  delay(dl);

  digitalWrite(in1, HIGH); 
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW);
  delay(dl);

  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW);
  delay(dl);

  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, HIGH);
  delay(dl);
}

void setup() {
    Serial.begin(9600);

    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(M3, OUTPUT);
    pinMode(M5, OUTPUT);
    pinMode(M4, OUTPUT);

    digitalWrite(M3,LOW);
    digitalWrite(M5,LOW);
    digitalWrite(M4,LOW);

    inputDigits[0] = '0';
    inputDigits[1] = '0';
    inputDigits[2] = '0';
    inputDigits[3] = '0';
    inputDigits[4] = '0';
    currentIndex = 0;

    Serial.println("System ready");
}


void loop() {
  char key = keypad.getKey();
  if (key) {
    delay(100);
    if (currentIndex < 4) {
      if (key == '1' ||key == '2' || key == '3' || key == '4' || key == '5' || key == '6' ) {
        inputDigits[currentIndex] = key;
        Serial.print("Нажата кнопка: ");
        Serial.println(key);
      } 
      else {
        inputDigits[currentIndex] = '0';
        Serial.print("Нажата кнопка______ : ");
        Serial.println(key);
        currentIndex = 4;       }

      currentIndex++;
      if (currentIndex >= 4) {
        Serial.print("Полученный список: ");
        for (byte i = 0; i < 4; i++) {
          Serial.print(inputDigits[i]);
          Serial.print(" ");
        }
        Serial.println();
        Engine_init(inputDigits);
        currentIndex = 0;
        inputDigits[0] = '0';
        inputDigits[1] = '0';
        inputDigits[2] = '0';
        inputDigits[3] = '0';
        inputDigits[4] = '0';
      }     }     } 
}

void Engine_init(char *inputDigits){
  LUM_violet = 140;
  while(LUM_violet < 150){
    LUM_violet = analogRead(PIN_violet);
    Serial.println(LUM_violet);
    oneStep();
    Serial.print("motor_init working__");
  }
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW);
  Serial.println(" ");
  Serial.println("motor_init_finished");
  Serial.println("______запускаем наливание напитков");
  pour_drinks(inputDigits);
}

void pour_drinks(char *inputDigits){
  Serial.println("запущена функция наливания");
  for (byte i = 0; i < 5; i++) {

    if (inputDigits[i] == '1'){
      Serial.print("запуск мотора с водой     ");
      delay(200);
      LUM_violet = 1000;
      for (long i = 0; i < steps_50_ml; i++) {
          LUM_violet =  analogRead(PIN_violet); 
          if (LUM_violet > 150){
            Serial.print(LUM_violet);
            Serial.println("  стакан стоит, вода течет");
            digitalWrite(M3,HIGH);
          } 
          else{
            while (LUM_violet < 150){    
              digitalWrite(M3,LOW);
              LUM_violet = analogRead(PIN_violet);
              Serial.print(LUM_violet);
              Serial.println("  убрали стакан, воды нет");  }}
      }
      digitalWrite(M3,LOW);
      Serial.print("напиток готов вкус_____ : ");
      Serial.println(inputDigits[i]);

      for (int i = 0; i < 100; i++) {
          oneStep();
          Serial.println("мотор вертится по приколу");
        }
      LUM_violet = 100;
      while (LUM_violet <150) {
        LUM_violet = analogRead(PIN_violet); 
        oneStep();
        Serial.println("мотор вертится пока светло");}
  
      Serial.println("Engite_next_cup проехал до след стакана  ");}


    if (inputDigits[i] == '2'){
        Serial.print("запуск мотора с сиропом     ");
        delay(200);
        LUM_violet = 1000;
        for (long i = 0; i < steps_10_ml; i++) {
            LUM_violet =  analogRead(PIN_violet); 
            if (LUM_violet > 150){
              Serial.print(LUM_violet);
              Serial.println("  стакан стоит, сироп течет");
              digitalWrite(M5,HIGH);
            } 
            else{
              while (LUM_violet < 150){    
                digitalWrite(M5,LOW);
                LUM_violet = analogRead(PIN_violet);
                Serial.print(LUM_violet);
                Serial.println("'  убрали стакан, сиропа нет'");  }}
        }
        digitalWrite(M5,LOW);
        Serial.print("напиток готов вкус_____ : ");
        Serial.println(inputDigits[i]);

        for (int i = 0; i < 100; i++) {
            oneStep();
            Serial.println("мотор вертится по приколу");
          }
        LUM_violet = 100;
        while (LUM_violet <150) {
          LUM_violet = analogRead(PIN_violet); 
          oneStep();
          Serial.println("мотор вертится пока светло");}
    
        Serial.println("Engite_next_cup проехал до след стакана  ");}


    if (inputDigits[i] == '3'){
        Serial.print("запуск мотора с соком     ");
        delay(200);
        LUM_violet = 1000;
        for (long i = 0; i < steps_40_ml; i++) {
            LUM_violet =  analogRead(PIN_violet); 
            if (LUM_violet > 150){
              Serial.print(LUM_violet);
              Serial.println("  стакан стоит, сок течет");
              digitalWrite(M4,HIGH);
            } 
            else{
              while (LUM_violet < 150){    
                digitalWrite(M4,LOW);
                LUM_violet = analogRead(PIN_violet);
                Serial.print(LUM_violet);
                Serial.println("'  убрали стакан, сока нет'");  }}
        }
        digitalWrite(M4,LOW);
        Serial.print("напиток готов вкус_____ : ");
        Serial.println(inputDigits[i]);

        for (int i = 0; i < 100; i++) {
            oneStep();
            Serial.println("мотор вертится по приколу");
          }
        LUM_violet = 100;
        while (LUM_violet <150) {
          LUM_violet = analogRead(PIN_violet); 
          oneStep();
          Serial.println("мотор вертится пока светло");}
    
        Serial.println("Engite_next_cup проехал до след стакана  ");}



    if (inputDigits[i] == '4'){
        Serial.print("запуск мотора с водой     ");
        delay(200);
        LUM_violet = 1000;
        for (long i = 0; i < steps_80_ml; i++) {
            LUM_violet =  analogRead(PIN_violet); 
            if (LUM_violet > 150){
              Serial.print(LUM_violet);
              Serial.println("  стакан стоит, водой течет");
              digitalWrite(M3,HIGH);
            } 
            else{
              while (LUM_violet < 150){    
                digitalWrite(M3,LOW);
                LUM_violet = analogRead(PIN_violet);
                Serial.print(LUM_violet);
                Serial.println("'  убрали стакан, воды нет'");  }}
        }
        digitalWrite(M3,LOW);


        Serial.print("запуск мотора с СИРОПОМ     ");
        for (long i = 0; i < steps_20_ml; i++) {
            LUM_violet =  analogRead(PIN_violet); 
            if (LUM_violet > 150){
              Serial.print(LUM_violet);
              Serial.println("  стакан стоит, сироп течет");
              digitalWrite(M5,HIGH);
            } 
            else{
              while (LUM_violet < 150){    
                digitalWrite(M5,LOW);
                LUM_violet = analogRead(PIN_violet);
                Serial.print(LUM_violet);
                Serial.println("'  убрали стакан, сиропа нет'");  }}
        }
        digitalWrite(M5,LOW);
        Serial.print("напиток готов вкус_____ : ");
        Serial.println(inputDigits[i]);

        for (int i = 0; i < 100; i++) {
            oneStep();
            Serial.println("мотор вертится по приколу");
          }
        LUM_violet = 100;
        while (LUM_violet <150) {
          LUM_violet = analogRead(PIN_violet); 
          oneStep();
          Serial.println("мотор вертится пока светло");}
    
        Serial.println("Engite_next_cup проехал до след стакана  ");}


    if (inputDigits[i] == '5'){
        Serial.print("запуск мотора с водой     ");
        delay(200);
        LUM_violet = 1000;
        for (long i = 0; i < steps_30_ml; i++) {
            LUM_violet =  analogRead(PIN_violet); 
            if (LUM_violet > 150){
              Serial.print(LUM_violet);
              Serial.println("  стакан стоит, сироп течет");
              digitalWrite(M3,HIGH);
            } 
            else{
              while (LUM_violet < 150){    
                digitalWrite(M3,LOW);
                LUM_violet = analogRead(PIN_violet);
                Serial.print(LUM_violet);
                Serial.println('  убрали стакан, воды нет');  }}
        }
        digitalWrite(M3,LOW);

        Serial.print("запуск мотора с соком     ");
        delay(200);
        LUM_violet = 1000;
        for (long i = 0; i < steps_50_ml; i++) {
            LUM_violet =  analogRead(PIN_violet); 
            if (LUM_violet > 150){
              Serial.print(LUM_violet);
              Serial.println("  стакан стоит, сок течет");
              digitalWrite(M4,HIGH);
            } 
            else{
              while (LUM_violet < 150){    
                digitalWrite(M4,LOW);
                LUM_violet = analogRead(PIN_violet);
                Serial.print(LUM_violet);
                Serial.println("'  убрали стакан, сока нет'");  }}
        }
        digitalWrite(M4,LOW);



        Serial.print("напиток готов вкус_____ : ");
        Serial.println(inputDigits[i]);

        for (int i = 0; i < 100; i++) {
            oneStep();
            Serial.println("мотор вертится по приколу");
          }
        LUM_violet = 100;
        while (LUM_violet <150) {
          LUM_violet = analogRead(PIN_violet); 
          oneStep();
          Serial.println("мотор вертится пока светло");}
    
        Serial.println("Engite_next_cup проехал до след стакана  ");}



    if (inputDigits[i] == '6'){
       Serial.print("запуск мотора с водой     ");
      delay(200);
      LUM_violet = 1000;
      for (long i = 0; i < steps_35_ml; i++) {
          LUM_violet =  analogRead(PIN_violet); 
          if (LUM_violet > 150){
            Serial.print(LUM_violet);
            Serial.println("  стакан стоит, вода течет");
            digitalWrite(M3,HIGH);
          } 
          else{
            while (LUM_violet < 150){    
              digitalWrite(M3,LOW);
              LUM_violet = analogRead(PIN_violet);
              Serial.print(LUM_violet);
              Serial.println("  убрали стакан, воды нет");  }}
      }
      digitalWrite(M3,LOW);

        Serial.print("запуск мотора с соком     ");
        delay(200);
        LUM_violet = 1000;
        for (long i = 0; i < steps_45_ml; i++) {
            LUM_violet =  analogRead(PIN_violet); 
            if (LUM_violet > 150){
              Serial.print(LUM_violet);
              Serial.println("  стакан стоит, сок течет");
              digitalWrite(M4,HIGH);
            } 
            else{
              while (LUM_violet < 150){    
                digitalWrite(M4,LOW);
                LUM_violet = analogRead(PIN_violet);
                Serial.print(LUM_violet);
                Serial.println("'  убрали стакан, сока нет'");  }}
        }
        digitalWrite(M4,LOW);
        Serial.print("запуск мотора с СИРОПОМ     ");
        for (long i = 0; i < steps_10_ml; i++) {
            LUM_violet =  analogRead(PIN_violet); 
            if (LUM_violet > 150){
              Serial.print(LUM_violet);
              Serial.println("  стакан стоит, сироп течет");
              digitalWrite(M5,HIGH);
            } 
            else{
              while (LUM_violet < 150){    
                digitalWrite(M5,LOW);
                LUM_violet = analogRead(PIN_violet);
                Serial.print(LUM_violet);
                Serial.println("'  убрали стакан, сиропа нет'");  }}
        }
        digitalWrite(M5,LOW);

        Serial.print("напиток готов вкус_____ : ");
        Serial.println(inputDigits[i]);

        for (int i = 0; i < 100; i++) {
            oneStep();
            Serial.println("мотор вертится по приколу");
          }
        LUM_violet = 100;
        while (LUM_violet <150) {
          LUM_violet = analogRead(PIN_violet); 
          oneStep();
          Serial.println("мотор вертится пока светло");}
    
        Serial.println("Engite_next_cup проехал до след стакана  ");}

        if (inputDigits[i] != '1' && inputDigits[i] != '2' && inputDigits[i] != '3' && inputDigits[i] != '4' && inputDigits[i] != '5' && inputDigits[i] != '6'){
            Serial.print("_____ НЕ напиток готов вкус_____ : ");
        Serial.println(inputDigits[i]);
        }




  }
  Serial.println("ЗАПУСК ВОЗВРАТА ");
  LUM_green = 100;
  currentIndex = 0;
  for (byte i = 0; i < 4; i++) {
    Serial.print("ВОЗВРАТ   ");
    Serial.println(i);

    if (currentIndex < 4){
       Serial.println("ВОЗВРАТ  первый иф ");
      if ((inputDigits[i] == '1' ||inputDigits[i] == '2' || inputDigits[i] == '3' || inputDigits[i] == '4' || inputDigits[i] == '5' || inputDigits[i] == '6' )) {
        LUM_green = 100;
        delay(1000);
        Serial.println("ВОЗВРАТ второй  иф ");
        while (LUM_green <150) {
          Serial.print(LUM_green);
          Serial.println("ВОЗВРАТ светло, крутится моторчик  иф");
          LUM_green = analogRead(PIN_green); 
          oneStep();}
        currentIndex ++;
        if (currentIndex < 4){
          while (LUM_green > 150) {
            LUM_green = analogRead(PIN_green); }
        }
      }
    }
    else{
      currentIndex = 5;
    }
  }

}






