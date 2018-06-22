#define sensor A0  
#define LED0 D0
#define LED1 D1
#define LED2 D2
#define MAX_QUEUE_SIZE 10

int val, front=0; 
int sp_queue_array[MAX_QUEUE_SIZE];
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
  int sum=0;
  int average;
  val=analogRead(sensor);  
  Serial.print("Light sensor value is :");  
  Serial.print(val);   
  Serial.print("\n"); 
  delay(500); 
  
  sp_queue_array[front]=val;
  front = (front+1)%MAX_QUEUE_SIZE;
  for(int i=0;i<MAX_QUEUE_SIZE;i++){
    sum = sum+sp_queue_array[i];
  }
  average = sum/MAX_QUEUE_SIZE;
  
  if(average>150){
    digitalWrite(LED_BUILTIN, LOW);  
  }
  else{
   digitalWrite(LED_BUILTIN, HIGH);
  }
  if(average<100){
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
  }
  else if(average<200){
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
  }
  else{
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
  Serial.print("Aveage Light sensor value is :");  
  Serial.print(average);   
  Serial.print("\n"); 
 }






