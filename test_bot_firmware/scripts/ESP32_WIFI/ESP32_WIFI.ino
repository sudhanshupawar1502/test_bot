#include<ros.h>
#include<std_msgs/Bool.h>
#include<std_msgs/Int16.h>
#include<WiFi.h>

const int ldirPin = 17;
const int rdirPin = 18;
bool ldir;
bool rdir;
int lpwm;
int rpwm;

const int left_side_pwm = 4;
const int right_side_pwm = 23;

const char* ssid = "Sudhanshu";
const char* password = "ryie5722";

WiFiClient client;
//add host device IP address
// to find host IP in cmd : hostname -I
IPAddress server(192,168,12,109);

class WiFiHardware {
  public:
    WiFiHardware() {};
    void init() {
      client.connect(server, 11411);
    }
    int read() {
      return client.read();
    }
    void write(uint8_t* data, int length) {
      for (int i = 0; i < length ; i++)
        client.write(data[i]);
    }
    unsigned long time() {
      return millis();
    }
};

void setupWiFi() {
    
    WiFi.begin(ssid, password);
    Serial.print("\nConnecting to "); Serial.println(ssid);
    uint8_t i = 0;
    while (WiFi.status() != WL_CONNECTED && i++ < 20) delay(500);
    if (i == 21) {
      Serial.print("Could not connect to"); Serial.println(ssid);
      while (1) delay(500);
    }
    Serial.print("Ready! Use ");
    Serial.print(WiFi.localIP());
    Serial.println(" to access client");
  }


ros::NodeHandle_<WiFiHardware> nh;


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
Serial.begin(115200);
setupWiFi();
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
