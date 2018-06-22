#define sensor A0  
#define LED0 D0
#define LED1 D1
#define LED2 D2

int val, preVal=0; 
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);  
   pinMode(LED_BUILTIN,OUTPUT);
   pinMode(LED0,OUTPUT);
   pinMode(LED1,OUTPUT);
   pinMode(LED2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  preVal = val;
  val=analogRead(sensor);  
  Serial.print("Light sensor value is :");  
  Serial.print(val);   
  Serial.print("\n"); 
  Serial.print("Pre-Light sensor value is :"); 
  Serial.print(preVal);
  Serial.print("\n"); 
  delay(400); 
  
  
  if(val<preVal-10){
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
  }
  else if(val>preVal+10){
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
  else{
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
 }
 }

