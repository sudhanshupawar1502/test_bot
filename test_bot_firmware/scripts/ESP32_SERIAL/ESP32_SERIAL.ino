
#include<ros.h>
#include<std_msgs/Bool.h>
#include<std_msgs/Int16.h>


const int ldirPin = 17;
const int rdirPin = 18;
bool ldir;
bool rdir;
int lpwm;
int rpwm;

const int left_side_pwm = 4;
const int right_side_pwm = 23;

ros::NodeHandle nh;


void ldir_cb(const std_msgs::Bool& data){
  ldir = data.data;
  digitalWrite(ldirPin,ldir);
}

void rdir_cb(const std_msgs::Bool& data){
  rdir = data.data;
  digitalWrite(rdirPin,rdir);
}

void lpwmCB( const std_msgs::Int16& data){
  lpwm = data.data;
  analogWrite(left_side_pwm,lpwm);
}

void rpwmCB( const std_msgs::Int16& data){
  rpwm = data.data;
  analogWrite(right_side_pwm,rpwm);
  }
std_msgs::Bool bool_msg;
std_msgs::Int16 int16_msg;

ros::Subscriber<std_msgs::Bool> lsub ("/ldir", ldir_cb);
ros::Subscriber<std_msgs::Bool> rsub ("/rdir", rdir_cb);
ros::Subscriber<std_msgs::Int16> lpwm1 ("/lpwm", lpwmCB);
ros::Subscriber<std_msgs::Int16> rpwm1 ("/rpwm", rpwmCB);

void setup() {
  // put your setup code here, to run once:
Serial.begin(57600);
pinMode(ldirPin,OUTPUT);
pinMode(rdirPin,OUTPUT);
pinMode(right_side_pwm ,OUTPUT);
pinMode(left_side_pwm ,OUTPUT);
nh.initNode();
nh.subscribe(lsub);
nh.subscribe(rsub);
nh.subscribe(lpwm1);
nh.subscribe(rpwm1);

}

void loop() {
  // put your main code here, to run repeatedly:
nh.spinOnce();
}