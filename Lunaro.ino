int ledPin[] = {3,5,6,9};
int pingPin[] = {4,7,10,12};
int echoPin[] = {2,8,11,13};
int sevenSegmentPin[] = {A0,A1,A2,A3,A4,A5}; //ef,b,c,d,a,g
int brightness[] = {30,30,30,30};
int distanceResult[4];
boolean isFirst = true;
void setup() {
  // put your setup code here, to run once:
  for(int a = 0; a< (sizeof(pingPin)/sizeof(pingPin[0])); a++){
    pinMode(ledPin[a],OUTPUT);
  }
  for(int a = 0; a<(sizeof(ledPin)/sizeof(ledPin[0])); a++){
    for(int value = 0; value >= brightness[a]; value++){
      analogWrite(ledPin[a], value);
      //delay(30);
    }
  }
  Serial.begin(9600);
}

void loop() {
  playCountDown();
  // put your main code here, to run repeatedly:
  
    long duration, inches, cm,start;

    for(int a = 0; a< (sizeof(pingPin)/sizeof(pingPin[0])); a++){ //ini untuk nembak per ping sensor
      pinMode(pingPin[a], OUTPUT);
      pinMode(echoPin[a], INPUT);
      
      digitalWrite(pingPin[a], LOW);
      delayMicroseconds(2);
      digitalWrite(pingPin[a], HIGH);
      delayMicroseconds(5);
      digitalWrite(pingPin[a], LOW);
      
      duration = pulseIn(echoPin[a], HIGH);
    
      inches = microsecondsToInches(duration);
      distanceResult[a] = microsecondsToCentimeters(duration);
      if(distanceResult[a] > 85) distanceResult[a] = 100;
      Serial.print("ini dari port = " );
      Serial.print(a);
      Serial.print(" = ");
      Serial.print(distanceResult[a]);
      Serial.print("cm");
      Serial.println();
      //brightness = 255-distanceresult, kalau distance result semakin besar, jarak asli semakin jauh, lampu mengecil ((100-distanceresult)*2)
      if((100-distanceResult[a])*2 >= brightness[a]){ //DR = 4 maka 100-4 = 96*2 = 192 > 30
        //kalau menjauh / semakin kecil
        Serial.print("port ");
        Serial.print(a);
        Serial.println("Meningkat");
        Serial.println("------------------");
        Serial.println("Progress");
        for(int value = brightness[a]; value <= (100-distanceResult[a])*2; value+=10){
          Serial.print("Port ");
          Serial.print(a);
          Serial.print(" brightness now = ");
          Serial.println(value);
          analogWrite(ledPin[a], value);
          //delay(5);
        }
      }
      else{
        Serial.print("port ");
        Serial.print(a);
        Serial.println("Menurun");
        Serial.println("------------------");
        Serial.println("Progress");
        //DR = 95 maka 100-95 = 5*2 = 10<192
        
        for(int value = brightness[a]; value >= (100-distanceResult[a])*2; value-= 10){
          
          Serial.print("Port ");
          Serial.print(a);
          Serial.print(" brightness now = ");
          Serial.println(value);
          analogWrite(ledPin[a], value);
          //delay(5);
        }
      }
      int index = compare();
      switch(index){
          case 0: 
          digitalWrite(sevenSegmentPin[0],1); 
          digitalWrite(sevenSegmentPin[1],0); 
          digitalWrite(sevenSegmentPin[2],0); 
          digitalWrite(sevenSegmentPin[3],1); 
          digitalWrite(sevenSegmentPin[4],0); 
          digitalWrite(sevenSegmentPin[5],0); 
          break;
          case 1: 
          digitalWrite(sevenSegmentPin[0],1);
          digitalWrite(sevenSegmentPin[1],0);
          digitalWrite(sevenSegmentPin[2],0);
          digitalWrite(sevenSegmentPin[3],0);
          digitalWrite(sevenSegmentPin[4],1);
          digitalWrite(sevenSegmentPin[5],0);
          break;
          case 2: 
          digitalWrite(sevenSegmentPin[0],0);
          digitalWrite(sevenSegmentPin[1],0);
          digitalWrite(sevenSegmentPin[2],0);
          digitalWrite(sevenSegmentPin[3],0);
          digitalWrite(sevenSegmentPin[4],1);
          digitalWrite(sevenSegmentPin[5],1);
          break;
          case 3: 
          digitalWrite(sevenSegmentPin[0],0);
          digitalWrite(sevenSegmentPin[1],0);
          digitalWrite(sevenSegmentPin[2],0);
          digitalWrite(sevenSegmentPin[3],1);
          digitalWrite(sevenSegmentPin[4],0);
          digitalWrite(sevenSegmentPin[5],1);
          break;
        }
      brightness[a] = (100-distanceResult[a])*2;
      Serial.print("brightness level port ");
      Serial.print(a);
      Serial.print(" = ");
      Serial.println(brightness[a]);
    }
    Serial.println();
    Serial.println();
  //delay(1000);
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
int compare(){
  int maxValue = 9999; //minValue
  int maxValueIndex = 0; //minValueIndex
  for(int a = 0; a< (sizeof(distanceResult) / sizeof(distanceResult[0])); a++){
    if(distanceResult[a] < maxValue){ //kalau ada yang lebih dekat (ada object dibawahnya)
      maxValue = distanceResult[a]; //max
      maxValueIndex = a; 
    }
  }
  return maxValueIndex; //kembaliin index ke berapa
}
void playCountDown(){
   
  //{A0,A1,A2,A3,A4,A5}; ef,b,c,d,a,g
  if(isFirst){
    for(int a = 0; a< (sizeof(sevenSegmentPin)/sizeof(sevenSegmentPin[0])); a++){
      pinMode(sevenSegmentPin[a],OUTPUT);
    }
/*MAPPINT 
       0
       _
    5 |_| 1
    4 |_| 2
       
       3
 {6 DI TENGAH}
 1 = NYALA
 0 = MATI
 */
    //tulis 5
    /*
    * A0 = EF
    * A1 = B
    * A2 = C
    * A3 = D
    * A4 = A
    * A5 = G
    */
    Serial.println("L");
    digitalWrite(sevenSegmentPin[0],1); 
    digitalWrite(sevenSegmentPin[1],0); 
    digitalWrite(sevenSegmentPin[2],0); 
    digitalWrite(sevenSegmentPin[3],1); 
    digitalWrite(sevenSegmentPin[4],0); 
    digitalWrite(sevenSegmentPin[5],0); 
    delay(1000);
    //tulis 4
    Serial.println("U");
    /*
    * A0 = EF
    * A1 = B
    * A2 = C
    * A3 = D
    * A4 = A
    * A5 = G
    */
    digitalWrite(sevenSegmentPin[0],0);
    digitalWrite(sevenSegmentPin[1],0);
    digitalWrite(sevenSegmentPin[2],0);
    digitalWrite(sevenSegmentPin[3],0);
    digitalWrite(sevenSegmentPin[4],1);
    digitalWrite(sevenSegmentPin[5],1);
    delay(1000);
    //tulis 3
    Serial.println("N");
    digitalWrite(sevenSegmentPin[0],0);
    digitalWrite(sevenSegmentPin[1],0);
    digitalWrite(sevenSegmentPin[2],0);
    digitalWrite(sevenSegmentPin[3],1);
    digitalWrite(sevenSegmentPin[4],0);
    digitalWrite(sevenSegmentPin[5],1);
    delay(1000);
    //tulis 2
    Serial.println("A");
     /*
    * A0 = EF
    * A1 = B
    * A2 = C
    * A3 = D
    * A4 = A
    * A5 = G
    */
    digitalWrite(sevenSegmentPin[0],0);
    digitalWrite(sevenSegmentPin[1],0);
    digitalWrite(sevenSegmentPin[2],0);
    digitalWrite(sevenSegmentPin[3],1);
    digitalWrite(sevenSegmentPin[4],0);
    digitalWrite(sevenSegmentPin[5],0
    );
    delay(1000);
    //tulis 1
    Serial.println("R");
    digitalWrite(sevenSegmentPin[0],1);
    digitalWrite(sevenSegmentPin[1],0);
    digitalWrite(sevenSegmentPin[2],0);
    digitalWrite(sevenSegmentPin[3],0);
    digitalWrite(sevenSegmentPin[4],1);
    digitalWrite(sevenSegmentPin[5],0);
    delay(1000);
    //tulis 0
    
    Serial.println("O");
    digitalWrite(sevenSegmentPin[0],1);
    digitalWrite(sevenSegmentPin[1],1);
    digitalWrite(sevenSegmentPin[2],1);
    digitalWrite(sevenSegmentPin[3],1);
    digitalWrite(sevenSegmentPin[4],1);
    digitalWrite(sevenSegmentPin[5],0);
    delay(1000);
    isFirst = false;
  }
  //code 5 - 1
  
}
/*int minValueIndex = compare(); //lempar ke method compare
    switch(minValueIndex){ //dievaluasi index mana (lampu ke berapa start:0 yang nyala)
      case 0: 
      Serial.println("nyala lampu 1");
      if(distanceResult[0]<10){
      digitalWrite(ledPin[0],HIGH);
      }
      else digitalWrite(ledPin[0],LOW);
      digitalWrite(ledPin[1],LOW);
      digitalWrite(ledPin[2],LOW);
      digitalWrite(ledPin[3],LOW);
      break;
      case 1: 
      
      Serial.println("nyala lampu 2");
      digitalWrite(ledPin[0],LOW);
      
      if(distanceResult[1]<10){
      digitalWrite(ledPin[1],HIGH);
      }
      else digitalWrite(ledPin[1],LOW);
      digitalWrite(ledPin[2],LOW);
      digitalWrite(ledPin[3],LOW);
      break;
      case 2: 
      
      Serial.println("nyala lampu 3");
      digitalWrite(ledPin[0],LOW);
      digitalWrite(ledPin[1],LOW);
      if(distanceResult[2]<10){
      digitalWrite(ledPin[2],HIGH);
      }
      else digitalWrite(ledPin[2],LOW);
      digitalWrite(ledPin[3],LOW);
      break;
      case 3: 
      
      Serial.println("nyala lampu 4");
      digitalWrite(ledPin[0],LOW);
      digitalWrite(ledPin[1],LOW);
      digitalWrite(ledPin[2],LOW);
      if(distanceResult[3]<10){
        digitalWrite(ledPin[3],HIGH);
      }
      else digitalWrite(ledPin[3],LOW);
      break;
    }
    */
