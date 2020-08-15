#include <Servo.h>
#include <PID_v1.h>
#include "Filter.h"
#define SERVOPIN  3                                               
#define sensor A0


const float r = 3.25;

float Kp_agg = 58;                                                    
float Ki_agg = 58;                                                    
float Kd_agg = 10;

/*
float Kp_cons = 0;                                                    
float Ki_cons = 0;                                                    
float Kd_cons = 0;
*/

float lower_limit = -2000, upper_limit = 2000;

float servo_zero = 1000;
int cw = 160;
int counter_cw = 160;
int cw_correction = 65;
                                                    
double set_point, Input, Output;

ExponentialFilter<double> FilteredDistance(20, 0);
double SmoothInput;

int last_output = servo_zero;
PID myPID(&SmoothInput, &Output, &set_point, Kp_agg, Ki_agg, Kd_agg, DIRECT);           
Servo myServo;  

bool is_near_setpoint = false;
int current_time = 0;
int entering_time = 0;

bool is_in_range();
bool enough_time_elapsed();

void setup() {
  Serial.begin(9600);                                                
  
   myServo.attach(SERVOPIN,servo_zero - cw, servo_zero + counter_cw);                                         

  Input = readPosition();                                            
  set_point = 17.5;                                                                   
  myPID.SetMode(AUTOMATIC);                                           
  myPID.SetOutputLimits(lower_limit,upper_limit);                                     
  myPID.SetSampleTime(5);
  
  //myServo.write(50);
  //delay(3000);
}

void loop()
{         
                                          
  Input = readPosition();
  // ===================================
  FilteredDistance.Filter(Input);
  SmoothInput = FilteredDistance.Current();
  // ===================================
  current_time = millis();
  if (is_in_range() && is_near_setpoint == false)
  {
    entering_time = current_time;
    is_near_setpoint = true;
  }
  else
    is_near_setpoint = false;

  if (is_near_setpoint == true && enough_time_elapsed())
  {
    myServo.writeMicroseconds(last_output);
    Serial.println(SmoothInput);
  }
  else
  {
    myPID.Compute();
    Output = map(Output, lower_limit, upper_limit, servo_zero + counter_cw, servo_zero - cw);
    if (Output < servo_zero)
    {
      Output = Output-cw_correction;
    }
    else
    {
      Output = Output;
    }
    myServo.writeMicroseconds(Output);
    Serial.println(SmoothInput);
    last_output = Output;
  }
  
}
      
float readPosition() {
  float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
  float distance = 13*pow(volts, -1); // worked out from datasheet graph
  if (distance > 30)
   return 30;

  else
    return distance;
}

bool is_in_range()
{
  if (abs(set_point - SmoothInput) <= 1.5)
    return true;
  else
    return false;
}

bool enough_time_elapsed()
{
  if (current_time - entering_time >= 3000)
    return true;
  else
    return false;
}
