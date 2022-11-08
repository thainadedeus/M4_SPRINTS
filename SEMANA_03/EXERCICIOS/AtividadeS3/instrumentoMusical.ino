https://wokwi.com/projects/347788772429005396
int listadeLeds[4] = {3,10,15,18};
int buttonSave = 45;
int save = LOW;
int buttonClean = 47;
int clean = LOW;
int sensorLuz = 40;
int arrayLuzes[50] = {};
int posicaoInicial = 0;
int Buzzer = 6;
int conversaoSensor(int value, int min, int max) {
  int converted = 0;
  int a = value - min;
  float b = max - min;
  converted = float((a / b)*15);
  return converted;
}
void setup() {
  Serial.begin(115200);
  for (int i = 0; i<4; i++){
  pinMode(listadeLeds[i], OUTPUT);
  }
  pinMode(buttonSave, INPUT_PULLUP);
  pinMode(buttonClean, INPUT_PULLUP);
  pinMode(Buzzer, OUTPUT);
  pinMode(sensorLuz, INPUT);
}
void loop() {
  Serial.println("LDR" + analogRead (sensorLuz));
  save = digitalRead(buttonSave);
  if (save == LOW){
    sensorLuz = conversaoSensor(analogRead(4),64,4063);
    Serial.println(sensorLuz);
    int acender[4]= {0,0,0,0};
    for (int i = 0; i<4; i++){
      acender[i] = (1&sensorLuz>>i);
      if (acender[i] == 1){
        digitalWrite(listadeLeds[i],HIGH);
      }
    }
  tone(Buzzer,100+(150*sensorLuz),3000);
  arrayLuzes[posicaoInicial] = sensorLuz;
  posicaoInicial += 1;
  delay(2500);
    for (int i = 0; i<4; i++){
      digitalWrite(listadeLeds[i],LOW);
    }
  }
  clean = digitalRead(buttonClean);
  if (clean == LOW){
    int acender_2[4]= {0,0,0,0};
    for (int h = 0; h< posicaoInicial; h++){
      sensorLuz = arrayLuzes[h];
      Serial.println(sensorLuz);
      for (int i = 0; i<4; i++){
        acender_2[i] = (1&sensorLuz>>i);
        if (acender_2[i] == 1){
          digitalWrite(listadeLeds[i],HIGH);
        }
      }
      tone(Buzzer,(100+(150*arrayLuzes[h])),3000);
      arrayLuzes[h] = 0;
      delay(5000);
      for (int i = 0; i<4; i++){
        digitalWrite(listadeLeds[i],LOW);
          }
    }
    posicaoInicial = 0;
  }
}











