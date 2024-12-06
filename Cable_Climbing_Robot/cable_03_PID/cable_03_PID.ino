// port 14 - 15 - 16 encoder of 3 springs 

#define kp 1
#define kd 0.01
#include<math.h>

//int pulse_motor_applied = 200;
int pulse_motor_come_back = 150;


const int button = 12;
const int ENA1 = 9;
const int ENB1 = 10;
const int ENC1 = 11;

const int ENA2 = 4;
const int ENB2 = 5;
const int ENC2 = 6;

const int itr1 = 18; //interrupt 3 - ngat 3 - count pulse of motor 1
const int itr2 = 19; //interrupt 4 - ngat 4 - count pulse of motor 2
const int itr3 = 20; //interrupt 5 - ngat 5 - count pulse of motor 3

const float pi = 3.14159;
//unsigned long int running_time = 10*1000; // controlling running time variable depend on reality calculating - unit (s) -- a(s) x 1000 = millis

const float distance = 300*10; //- UNIT - mm - change distance which be determined - input() = cm
unsigned long int stop_con_pulse = distance * 220/(65*3.1459);

const int ve = 10;// v - expected - RPM

int T = 50; // determine period of PID 
float E1a = 0, E1b = 0; // PID variables of motor 1
float E2a = 0, E2b = 0; // PID variables of motor 1
float E3a = 0, E3b = 0; // PID variables of motor 1

volatile unsigned long int count1 = 0; //count pulse variables of 3 motors
volatile unsigned long int count2 = 0;
volatile unsigned long int count3 = 0;

volatile unsigned long int spring01 = 0; //count pulse variables of 3 springs
volatile unsigned long int spring02 = 0;
volatile unsigned long int spring03 = 0;

unsigned int spring_pulse = 250; // changing input pulse of spring motor 0-255
int pulse_of_motor1 = 0, pulse_of_motor2 = 0, pulse_of_motor3 = 0;

///////////// count pulse ////////////
void count_pulse1() // motor 1 pulse counter function // encoder create 220 pulse per round
{
    count1++;
}

void count_pulse2() // // motor 2 pulse counter function
{
   count2++;
}

void count_pulse3() // motor 3 pulse counter function
{
   count3++;
}

void count_spring1() // motor 1 pulse counter function // encoder create 220 pulse per round
{
    spring01++;
}

void count_spring2() // motor 1 pulse counter function // encoder create 220 pulse per round
{
    spring02++;
}

void count_spring3() // motor 1 pulse counter function // encoder create 220 pulse per round
{
    spring03++;
}


///////////// motor and string controller ///////////////////

void motor1(int pulse) // control motor 1
{
  digitalWrite(22,HIGH);
  digitalWrite(23,LOW);
  analogWrite(ENA1,pulse); 
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

void spring1(int spr_pulse) // control spring motor 1
{
  digitalWrite(52,HIGH);
  digitalWrite(53,LOW);
  analogWrite(ENA2,spr_pulse); 
}

void spring3(int spr_pulse) // control spring motor 2
{
  digitalWrite(50,LOW);
  digitalWrite(51,HIGH);
  analogWrite(ENC2,spr_pulse); 
}

void spring2(int spr_pulse) // control spring motor 3
{
  digitalWrite(48,HIGH);
  digitalWrite(49,LOW);
  analogWrite(ENB2,spr_pulse); 
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

int PID(float E, float E1, int pulse_of_motor_before)
{
  float delta = kp*E  + kd*E1;
  float pulse_of_motor = round(pulse_of_motor_before + delta);
  if(pulse_of_motor > 255)
  {
    pulse_of_motor = 255;
  }
  E1 = E;
  return pulse_of_motor;
}



void stop_spring_motor12()
{
  digitalWrite(48,LOW);
  digitalWrite(49,LOW);
  digitalWrite(52,LOW);
  digitalWrite(53,LOW);
}


void stop_spring_motor3()
{
  digitalWrite(50,LOW);
  digitalWrite(51,LOW);
}

void stop_spring_motor()
{
  digitalWrite(48,LOW);
  digitalWrite(49,LOW);
  digitalWrite(50,LOW);
  digitalWrite(51,LOW);
  digitalWrite(52,LOW);
  digitalWrite(53,LOW);
}

void run_program()
{
  //t = millis()
  while(true)
  {
    spring1(spring_pulse);
    spring2(spring_pulse);
    spring3(spring_pulse);
    if(spring02 > 1300 || spring01 >1300||spring03>1000)
    {
      stop_spring_motor12();
      stop_spring_motor3();
      break;
    }
  }
  spring1(spring_pulse);
  spring2(spring_pulse);
  spring3(spring_pulse);
  delay(2000);
  
  //volatile unsigned int start_time = millis();
  volatile unsigned int PID_time_b,PID_time_a;
  unsigned int pulse1 = count1;
  unsigned int pulse2 = count2;
  unsigned int pulse3 = count3;
  unsigned int pulse1a, pulse2a, pulse3a;
  PID_time_b = millis();
  while(true)
  {
    //end_time = millis();
    PID_time_a = millis();
    if(count1>stop_con_pulse|| count2>stop_con_pulse)// change stop condition
    {
      stop_all_motor();
      break;
    }
    else
    {
      if(PID_time_a - PID_time_b >= T )
      {
        pulse1a = count1;
        pulse2a = count2;
        pulse3a = count3;
        float vr1 = (pulse1a - pulse1)*408.2*1000/(400*T);
        float vr2 = (pulse2a - pulse2)*408.2*1000/(400*T);
        float vr3 = (pulse3a - pulse3)*408.2*1000/(400*T);
        E1a = ve - vr1;
        E2a = ve - vr2;
        E3a = ve - vr3;
        pulse_of_motor1 = PID(E1a,E1b,pulse_of_motor1);
        pulse_of_motor2 = PID(E2a,E2b,pulse_of_motor2);
        pulse_of_motor3 = PID(E3a,E3b,pulse_of_motor3);
        PID_time_b = PID_time_a;         
      }
      /*motor1(pulse_of_motor1);
      motor2(pulse_of_motor2);
      motor3(pulse_of_motor3);
      motor1(pulse_motor_applied);
      motor2(pulse_motor_applied);
      motor3(pulse_motor_applied);*/
    }
    if(count1>stop_con_pulse|| count2>stop_con_pulse)// change stop condition
    {
      stop_all_motor();
      break;
    }
  }
  
}

void comeback()
{
  volatile unsigned int PID_time_c,PID_time_d;
  digitalWrite(22,LOW);
  digitalWrite(23,HIGH);
  digitalWrite(24,LOW);
  digitalWrite(25,HIGH);
  digitalWrite(27,LOW);
  digitalWrite(26,HIGH);
  PID_time_c = millis();
  while(true)
  {
    //end_time = millis();
    //PID_time_d = millis();
    analogWrite(ENA1,pulse_motor_come_back);
    analogWrite(ENB1,pulse_motor_come_back);
    analogWrite(ENC1,pulse_motor_come_back);
    if(count1>(stop_con_pulse-1100))// change stop condition
    {
      stop_all_motor();
      break;
    }
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(0,INPUT);
  pinMode(1,INPUT);
  pinMode(2,INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
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
  
  pinMode(button, INPUT_PULLUP);

  //attachInterrupt(3,run_program,FALLING); // FALLING or LOW // buttun for starting program using interrupt 0 // 
  attachInterrupt(0,count_spring3,RISING);
  attachInterrupt(1,count_spring2,RISING);
  attachInterrupt(2,count_spring1,RISING);
  attachInterrupt(3,count_pulse3,RISING);
  attachInterrupt(4,count_pulse2,RISING);
  attachInterrupt(5,count_pulse1,RISING);
  pinMode(13,OUTPUT);
  //run_program();
}

void loop(){
  int buttonStatus = digitalRead(button);
  count1 = 0; //count pulse variables of 3 motors
  count2 = 0;
  count3 = 0;
  spring01 = 0; //count pulse variables of 3 springs
  spring02 = 0;
  spring03 = 0; 
  if (buttonStatus == LOW) {
      delay(500);
    //count1 = 0; //count pulse variables of 3 motors
    //count2 = 0;
    //count3 = 0;
    spring01 = 0; //count pulse variables of 3 springs
    spring02 = 0;
    spring03 = 0; 
    digitalWrite(13,HIGH);
    run_program();
    delay(1500);
    count1 = 0; //count pulse variables of 3 motors
    count2 = 0;
    count3 = 0;
    comeback();
  }
  else{
    digitalWrite(13,LOW);
    stop_spring_motor();
    stop_all_motor();
  }
  
}
