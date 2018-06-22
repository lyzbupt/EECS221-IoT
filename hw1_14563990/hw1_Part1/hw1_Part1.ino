#define sensor A0  
#define LED0 D0
#define LED1 D1
#define LED2 D2

int val; 
   
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
   
  val=analogRead(sensor);  
  Serial.print("Light sensor value is :");  
  Serial.print(val);   
  Serial.print("\n");  
  delay(500); 
  if(val>150){
    digitalWrite(LED_BUILTIN, LOW);  
  }
  else{
   digitalWrite(LED_BUILTIN, HIGH);
  }
  if(val<100){
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
  }
  else if(val<200){
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
  }
  else{
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
 }




