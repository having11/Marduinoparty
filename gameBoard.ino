/* pin assignments:
 * LCD RS: 12, LCD E: 13, LCD 4: 5,LCD 5: 4, LCD 6: 3, LCD 7: 2
 * Button Left: 6, Button Middle: 7, Button Right: 8, Servo Player 1: 9, Servo Player 2: 10, Servo Player 3: 11
 * LED Left: A3, LED Middle: A2, LED Right: A1
 */
 #include <Servo.h>
 #include <LiquidCrystal.h>

 String playerNames[3]={"","",""};
 int spaces[3] = {0,0,0};
 int points[3]={0,0,0};
 const int servo_pin[3] = {9,10,13};
 int serNum = 0;
 int playerNum = 0;
 String SerialMessage1="";
 String SerialMessage2="";
 int LEDR = A1;
 int LEDM = A2;
 int LEDL = A3;
 long roll = 0;
 int pageNum = 0;
 int buttonL = 7;
 int buttonM = 6;
 int buttonR = 8;
 int buttonLState = 0;
 int buttonMState = 0;
 int buttonRState = 0;
 
 LiquidCrystal lcd(12,11,5,4,3,2);
 Servo servo[3];
 
void setup() {
  for(int x=0;x<3;x++){
    servo[x].attach(servo_pin[x]);
  }
  randomSeed(analogRead(0));
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.print("Ready");
for(int x=0;x<3;x++){
  servo[x].write(0);
}
welcomeScreen();
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonLState = digitalRead(buttonL);
  buttonMState = digitalRead(buttonM);
  buttonRState = digitalRead(buttonR);
  if(buttonLState == 1){
    if(pageNum==1){
      pageNum=2;
    }
    else{
    pageNum = 1;
    }
  }
  else if(buttonMState==1){
    if(pageNum<11){
      if(pageNum==2){
        pageNum=1;
      }
      else if(pageNum==1){
        pageNum=3;
      }
      else{
    pageNum += 1;
      }
    }
  }
  else if(buttonRState==1){
    if (pageNum>0 && pageNum<5){
      pageNum-=1;
    }
  }
  
  
switch(pageNum){
  case 0:
  welcomeScreen();
  break;
  case 1:
  mainMenu();
  break;
  case 2:
  menu();
  break;
  case 3:
  playerNumber();
  break;
  case 4:
  names();
  break;
  case 5:
  readyGo();
  break;
  case 6:
  for(int x=0;x<playerNum;x++){
    if(x==0){
      analogWrite(LEDL, 150);
    }
    else if(x==1){
      analogWrite(LEDM,150);
    }
    else if(x==2){
      analogWrite(LEDR,150);
    }
    dieRoll(x);
  }
  pageNum=7;
  break;
  case 7:
  minigame();
  pageNum=8;
  break;
  case 8:
  ranking();
  pageNum=9;
  break;
  case 9:
  again();
  break;
  case 10:
  gameOver();
  break;
}
delay(500);
}


void welcomeScreen(){
  lcd.begin(16,2);
lcd.write("Hi! Press button");
lcd.setCursor(0,1);
lcd.write("to start playing");
}
void mainMenu(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Menu   Go   Back");
  lcd.setCursor(0,1);
  lcd.write(" -     -     -");
}

void menu(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Use phone to");
  lcd.setCursor(0,1);
  lcd.print("select options");
}
void playerNumber(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Player number?");
  scrollLED();
  lcd.setCursor(0,1);
  lcd.print("Use Phone");
  Serial.print("Player Number");
  while(!Serial.available()){
    delay(10);
    scrollLED();
  }
  while(Serial.available()){
  SerialMessage1 = Serial.readStringUntil('*');
  if(SerialMessage1=="Player"){
    serNum=Serial.parseInt();
    playerNum=serNum;
    if(playerNum==1){
      analogWrite(LEDL,150);
      delay(500);
      allOff();
      analogWrite(LEDL,150);
      delay(500);
      allOff();
      analogWrite(LEDL,150);
      delay(500);
      allOff();
    }
    else if(playerNum==2){
      analogWrite(LEDL,150);
      analogWrite(LEDM,150);
      delay(500);
      allOff();
      analogWrite(LEDL,150);
      analogWrite(LEDM,150);
      delay(500);
      allOff();
      analogWrite(LEDL,150);
      analogWrite(LEDM,150);
      delay(500);
      allOff();
    }
    else if(playerNum==3){
      analogWrite(LEDL,150);
      analogWrite(LEDM,150);
      analogWrite(LEDR,150);
      delay(500);
      allOff();
      analogWrite(LEDL,150);
      analogWrite(LEDM,150);
      analogWrite(LEDR,150);
      delay(500);
      allOff();
      analogWrite(LEDL,150);
      analogWrite(LEDM,150);
      analogWrite(LEDR,150);
      delay(500);
      allOff();
    }
    pageNum=4;
  }
  else{
  delay(20);
  }
  }
}
void names(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Points reset");
  lcd.setCursor(0,1);
  lcd.print("Enter names");
  for(int x=0;x<playerNum;x++){
    if(x==0){
      analogWrite(LEDL, 150);
    }
    else if(x==1){
      analogWrite(LEDM,150);
    }
    else if(x==2){
      analogWrite(LEDR,150);
    }
  Serial.print("Name");
  while(!Serial.available()){
    delay(10);
  }
  while(Serial.available()){
    SerialMessage1 = Serial.readStringUntil('*');
    if(SerialMessage1=="Names"){
      SerialMessage2=Serial.readStringUntil('#');
      playerNames[x] = SerialMessage2;
    }
    delay(10);
    }
    allOff();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(playerNames[x]);
    lcd.print(", you");
    lcd.setCursor(0,1);
    lcd.print("are player ");
    lcd.print(x+1);
  }
  Serial.println(playerNames[0]);
  Serial.println(playerNames[1]);
  Serial.println(playerNames[2]);
  pageNum=5;
}

void readyGo(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("      Ready?");
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);
}
for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position right:
    lcd.scrollDisplayRight();
    // wait a bit:
    delay(150);
  }
  delay(500);
  lcd.clear();
  lcd.print("GO!");
  delay(500);
  pageNum=6;
}

void dieRoll(int playerTurn){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(playerNames[playerTurn]);
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("You rolled a:");
  lcd.setCursor(0,1);
  roll = random(1,4);
  lcd.print(roll);
  delay(1000);
  spaces[playerTurn] += roll;
  servo[playerTurn].write(spaces[playerTurn] * 6);
  allOff();
}
void minigame(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Time for a");
  lcd.setCursor(0,1);
  lcd.print("minigame!");
  for(int x=0;x<playerNum;x++){
    if(x==0){
      analogWrite(LEDL, 150);
    }
    else if(x==1){
      analogWrite(LEDM,150);
    }
    else if(x==2){
      analogWrite(LEDR,150);
    }
  while(!Serial.available()){
    delay(10);
  }
  while(Serial.available()){
    SerialMessage1 = Serial.readStringUntil('*');
    if(SerialMessage1=="Points"){
      serNum=Serial.parseInt();
      points[x] += serNum;
    }
    delay(10);
    }
    delay(1200);
    allOff();
  }
  lcd.clear();
  lcd.setCursor(0,0);
  delay(3000);
  for(int x=0;x<playerNum;x++){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(playerNames[x]);
    lcd.setCursor(0,1);
    lcd.print("You have: ");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(points[x]);
    lcd.setCursor(0,1);
    lcd.print("points!");
    delay(1000);
  }
}

void ranking(){
  lcd.clear();
  lcd.setCursor(0,0);
  if((points[0]>points[1]) && (points[0]>points[2])){
    analogWrite(LEDL,150);
    lcd.print(playerNames[0]);
    lcd.setCursor(0,1);
    lcd.print("is in first!");
  }
  else if((points[1]>points[0]) && (points[1]>points[2])){
    analogWrite(LEDM,150);
    lcd.print(playerNames[1]);
    lcd.setCursor(0,1);
    lcd.print("is in first!");
  }
  else if((points[2]>points[0]) && (points[2]>points[1])){
    analogWrite(LEDR,150);
    lcd.print(playerNames[2]);
    lcd.setCursor(0,1);
    lcd.print("is in first!");
  }
  delay(2000);
  allOff();
}

void again(){
  bool won = false;
  lcd.clear();
  lcd.setCursor(0,0);
  for(int x=0;x<playerNum;x++){
    if(spaces[x]>=30){
      won = true;
      lcd.print(playerNames[x]);
      lcd.setCursor(0,1);
      lcd.print("has won with");
      delay(2000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(points[x]);
      lcd.print("!");
      delay(3000);
      pageNum=10;
    }
  }
  if(won==false){
    lcd.print("Rolling again!");
    delay(1000);
    pageNum=6;
  }
  }


void gameOver(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Well done!");
  lcd.setCursor(0,1);
  lcd.print("Game over.");
}

void scrollLED(){
  analogWrite(LEDL,150);
  delay(300);
  allOff();
  analogWrite(LEDM,150);
  delay(300);
  allOff();
  analogWrite(LEDR,150);
  delay(300);
  allOff();
}

void allOff(){
  analogWrite(LEDL, 0);
  analogWrite(LEDM, 0);
  analogWrite(LEDR, 0);
}

