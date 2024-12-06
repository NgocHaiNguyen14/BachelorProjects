  
const int ENA1 = 9;
const int ENB1 = 10;
const int ENC1 = 11;
const int buzzer=12;
const int itr1 = 18;
float pi=3.14;

volatile float c = pi*136; // -- unit: mm
//volatile float rounds = s*1000/427.42 ;
//volatile unsigned long int test = 1200*rounds;

volatile unsigned long int count1 = 0; 
volatile unsigned long int count2 = 0;
volatile unsigned long int count3 = 0;

void count_pulse1() // motor 1 pulse counter function21
{
    count1++;
}
void count_pulse2() // motor 2 pulse counter function
{
   count2++;
}
void count_pulse3() // motor 3 pulse counter function
{
   count3++;
}
 

void motor1(int pulse) // control motor 1
{
  digitalWrite(22,HIGH);
  digitalWrite(23,LOW);
  analogWrite(9,pulse); 
}
void motor2(int pulse) // control motor 2
{
  digitalWrite(25,LOW);
  digitalWrite(24,HIGH);
  analogWrite(ENB1,pulse); 
}

void motor3(int pulse) // control motor 2
{
  digitalWrite(26,LOW);
  digitalWrite(27,HIGH);
  analogWrite(ENC1,pulse); 
}

void setup() {
  Serial.begin(9600);
  pinMode(0,INPUT);
  pinMode(1,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(18,INPUT_PULLUP);
  pinMode(19,INPUT_PULLUP);
  pinMode(20,INPUT_PULLUP);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(51, OUTPUT);
  pinMode(52, OUTPUT);
  pinMode(53, OUTPUT);
  //attachInterrupt(1,clear_motor,RISING);
  attachInterrupt(2,count_pulse3,RISING);
  attachInterrupt(3,count_pulse2,RISING);
  attachInterrupt(4,count_pulse1,RISING);
  digitalWrite(buzzer,LOW);

}
/*
void clear_motor()
{
  stop_all_motor();
  delay(2000);
}*/
/////////// moving controller ///////////////////
void go_straight(/*long int s /*unit--mm*/ int pulse_str1, int pulse_str2)
{
  count1=0;
  count2=0;
  //float np = 3379.7*s;
  //float np = 3450;// go a straight 120cm
  //float np = 1725;// go a straight 60cm
  /*while(count1<np&&count2<np)
  {
    if(Serial.available()>0)
    {
      digitalWrite(buzzer,HIGH); 
      stop_all_motor(); delay(200000);  
    }*/
    motor1(pulse_str1);
    motor2(pulse_str2);
    motor3(0);
  }



void stop_all_motor()
{
  digitalWrite(22,LOW);
  digitalWrite(23,LOW);
  digitalWrite(24,LOW);
  digitalWrite(25,LOW);
  digitalWrite(26,LOW);
  digitalWrite(27,LOW);
}

void rotate_clockwise(int angle)
{
  int pulse=70;
  count1=0;
  //float pulses= 11.95*angle /*9.9325*angle*/ ;
  float pulses= 16*angle;
  //Serial.println(pulses);
  while(count1<pulses){
    //Serial.println(count1);
    digitalWrite(22,HIGH);
    digitalWrite(23,LOW);
    digitalWrite(24,LOW);
    digitalWrite(25,HIGH);
    digitalWrite(26,HIGH);
    digitalWrite(27,LOW);
    analogWrite(ENA1,pulse);
    analogWrite(ENB1,pulse);
    analogWrite(ENC1,pulse);
    //Serial.println(count1);
  }
 
}

void rotate_anticlockwise(int angle)
{
  int pulse=70;
  count1=0;
  //float pulses= 11.95*angle /*9.9325*angle*/ ;
  float pulses= 17*angle;
  //Serial.println(pulses);
  while(count1<pulses){
    //Serial.println(count1);
    digitalWrite(22,LOW);
    digitalWrite(23,HIGH);
    digitalWrite(24,HIGH);
    digitalWrite(25,LOW);
    digitalWrite(26,LOW);
    digitalWrite(27,HIGH);
    analogWrite(ENA1,pulse);
    analogWrite(ENB1,pulse);
    analogWrite(ENC1,pulse);
    //Serial.println(count1);
  }
 
}

////////////////////////////////////////////////


void loop() {
    if (Serial.available() > 0) {
    int receivedValue = Serial.parseInt();  // Read the incoming integer value
    Serial.print("Received value: ");
    Serial.println(receivedValue);  // Print the received value back to the serial monitor
  }
    delay(50);
    //go_straight(value1, value2);
}
