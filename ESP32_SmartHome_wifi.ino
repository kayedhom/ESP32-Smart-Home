
#include <Robojax_L298N_DC_motor.h>
// motor 1 settings
#define CHA 0
#define ENA 19  // this pin must be PWM 
#define IN1 18
#define IN2 5

// motor 2 settings
#define IN3 17
#define IN4 16
#define ENB 4  // this pin must be PWM 
#define CHB 1

const int CCW = 2;  // do not change
const int CW = 1;   // do not change

#define motor1 1  // do not change


#define Switch_one_pin 2  
#define Switch_two_pin 2  

// for single motor
//Robojax_L298N_DC_motor motor(IN1, IN2, ENA, CHA, true);

// for two motors without debug information // Watch video instruciton for this line: https://youtu.be/2JTMqURJTwg
Robojax_L298N_DC_motor motor(IN1, IN2, ENA, CHA, IN3, IN4, ENB, CHB);

// fore two motors with debut information
//Robojax_L298N_DC_motor motor(IN1, IN2, ENA, CHA, IN3, IN4, ENB, CHB, true);


int motor1Direction = CW;         //default direction of rotation
const int motor1changeStep = 10;  // 10 is 10% every time button is pushed
int motor1Speed = 40;             // variable holding the light output vlaue (initial value) 40 means 40%
const int motor1MinimumSpeed = 20;
const int motor1MaximumSpeed = 100;
int motor1StopState = HIGH;  //Stope state of motor (HIGH means STOP) and LOW means Start
bool First_Iteration=true;

int Switch_one = HIGH;  //Stope state of Switch (HIGH means STOP) and LOW means Start
int Switch_two = HIGH;  //Stope state of Switch (HIGH means STOP) and LOW means Start



#include "ESP32_L298N_DC_motor_wifi_page.h"



#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char *ssid = "POCO X3 NFC";
const char *password = "abcd1234";
bool passwordSubmitted = false;
String submittedPassword; // Variable to store the submitted password
int count = 0; // Initialize the count variable
char countinternal[] = "0";


WebServer server(80);

const int led = 13;



void handleFirstPage() {
String firstPage = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><title>First Page</title>";
firstPage += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
firstPage += "<title>First Page</title>";
  firstPage += "<style>";
  firstPage += "body {";
  firstPage += "background-image: linear-gradient(to right, #ffcccc, #e6ccff); /* Gradient background */";
  firstPage += "background-attachment: fixed; /* Keep background fixed while scrolling */";
  firstPage += "font-family: 'Arial', sans-serif; /* Change font family for better readability */";
  firstPage += "color: #333; /* Set default text color */";
  firstPage += "margin: 0; /* Remove default margin for full-width background */";
  firstPage += "padding: 0; /* Remove default padding */";
  firstPage += "}";
  firstPage += "form {";
  firstPage += "background-color: #f4cccc;";
  firstPage += "padding: 20px;";
  firstPage += "border-radius: 8px;";
  firstPage += "box-shadow: 0 2px 4px rgba(0,0,0,0.1);";
  firstPage += "max-width: 300px;";
  firstPage += "width: 100%;";
  firstPage += "}";
  firstPage += "input[type='password'],";
  firstPage += "input[type='submit'] {";
  firstPage += "width: 100%;";
  firstPage += "padding: 10px;";
  firstPage += "margin: 5px 0;";
  firstPage += "box-sizing: border-box;";
  firstPage += "border: 1px solid #ccc;";
  firstPage += "border-radius: 5px;";
  firstPage += "font-size: 16px;";
  firstPage += "}";
  firstPage += "input[type='submit'] {";
  firstPage += "background-color: #e06666;";
  firstPage += "cursor: pointer;";
  firstPage += "}";
  firstPage += "input[type='submit']:hover {";
  firstPage += "background-color: #cc0000;";
  firstPage += "}";
  firstPage += "</style>";
  firstPage += "</head><body>";
  firstPage += "<h2>WELCOME HOME!</h2>";
  firstPage += "<form action='/submit' method='POST'>";
  firstPage += "<label for='password'>Password:</label><br>";
  firstPage += "<input type='password' id='password' name='password'><br><br>";
  firstPage += "<input type='submit' value='Submit'></form>";
  firstPage += "</body></html>";



  server.send(200, "text/html", firstPage);
}



void handleRoot() {
    if (passwordSubmitted) {
    // If password is submitted, serve the second page

  String HTML_page = motorControlHeader_1;

  HTML_page.concat(".bar1 {width: " + String(motor1Speed) + "%;}\n");
  //HTML_page.concat(motor1Speed);
  //HTML_page.concat("%;}");
  //HTML_page.concat(".bar2 {width: " + "String(LedSpeed)" + "%;}\n");

  HTML_page.concat(motorControlHeader_2);

  HTML_page.concat(motor1Control_p1);

  if (motor1Direction == CW) {
    if (motor1StopState == HIGH) {
      HTML_page.concat("<strong>Stopped - CW at ");
    } else {
      HTML_page.concat("<strong>Running - CW at ");
    }
  } else {
    if (motor1StopState == HIGH) {
      HTML_page.concat("<strong>Stopped - CCW at ");
    } else {
      HTML_page.concat("<strong>Running - CCW at ");
    }
  }
  HTML_page.concat(motor1Speed);
  HTML_page.concat(motor1Control_p2);
  if (motor1StopState == HIGH) {
    HTML_page.concat("m0START\">START");
  } else {
    HTML_page.concat("m0STOP\">STOP");
  }
  HTML_page.concat(motor1Control_p3);

  ///Switch_one begins
  HTML_page.concat(Switch_one_control_p1);

    if (Switch_one == HIGH) {
      HTML_page.concat("<strong>Refrigerator off");
    } else {
      HTML_page.concat("<strong>Refrigerator on");
    }

  
  HTML_page.concat(Switch_one_control_p2);
  if (Switch_one == HIGH) {
    HTML_page.concat("m1START\">ON");
  } else {
    HTML_page.concat("m1STOP\">OFF");
  }
  HTML_page.concat(Switch_one_control);
  ///Switch_one ends




 ///Switch_two begins
  HTML_page.concat(Switch_two_control_p1);

    if (Switch_two == HIGH) {
      HTML_page.concat("<strong>Lampshades off ");
    } else {
      HTML_page.concat("<strong>Lampshades on ");
    }

  
  HTML_page.concat(Switch_two_control_p2);
  if (Switch_two == HIGH) {
    HTML_page.concat("m2START\">ON");
  } else {
    HTML_page.concat("m2STOP\">OFF");
  }
  HTML_page.concat(Switch_two_control);

  ///Switch_two Ends

//Counter Container start
  HTML_page.concat(CounterStartContainer);

  //CounterStart
  HTML_page.concat(Counter);
  HTML_page.concat("COUNTNOW\">Timer:  ");
  HTML_page.concat(countinternal);
  HTML_page.concat(" sec </a>");
  //CounterEnd
//ResetCounter Start
  HTML_page.concat(ResetCounter);
  HTML_page.concat("RESETCOUNTER\">Reset </a> ");
//ResetCounter End
  HTML_page.concat(CounterEndContainer);

 //Counter Container End

  //HTML_page.concat();


  HTML_page.concat("</body>\n</html>");

  server.send(200, "text/html", HTML_page);

    } else {
    // Otherwise, serve the first page
    handleFirstPage();
  }
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}



hw_timer_t *TIMER0 = NULL;
void IRAM_ATTR onTimer0(){
digitalWrite(Switch_one_pin, !digitalRead(Switch_two_pin));
  Serial.println("Timer Finished");
  Serial.println(countinternal);


  timerDetachInterrupt(TIMER0);
  timerEnd(TIMER0);


}


hw_timer_t *TIMER1 = NULL;
void IRAM_ATTR onTimer1(){
digitalWrite(Switch_one_pin, !digitalRead(Switch_two_pin));
  Serial.println("Timer Finished");
  Serial.println(countinternal);


  timerDetachInterrupt(TIMER1);
  timerEnd(TIMER1);


}


void setup(void) {
  pinMode (2, OUTPUT);
  Serial.begin(115200);
  motor.begin();
  //L298N DC Motor 

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");


  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  if (MDNS.begin("ESP32")) {
    Serial.print("MDNS responder started at http://");
    Serial.println("ESP32 Smart Home");
  }

  server.on("/", handleRoot);

  server.on("/submit", HTTP_POST, [](){
    // Handle form submission
    submittedPassword = server.arg("password"); // Retrieve and store the submitted password

    // Redirect to the root URL (refresh page)
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "");
  });


  server.on("/speed", HTTP_GET, handleMotorSpeed);
  server.on("/direction", HTTP_GET, handleMotorDirection);
  server.on("/stop", HTTP_GET, handleMotorBrake);

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");



}

void loop(void) {
      if(submittedPassword == "good"){passwordSubmitted = true;}
  server.handleClient();


  if (motor1StopState == HIGH) {
    motor.brake(motor1);

  } else {
    motor.rotate(motor1, motor1Speed, motor1Direction);  //run motor1 at motor1Speed% speed in motor1Direction
  }



  delay(100);
}


/*
 * handleMotorSpeed()
 * Slows down or speeds up the motor
 * returns nothing
 */
void handleMotorSpeed() {
  if (server.arg("do") == "m1slower") {
    motor1Speed -= motor1changeStep;

    if (motor1Speed < motor1MinimumSpeed) {
      motor1Speed = motor1MinimumSpeed;
    }
  } else if (server.arg("do") == "m1faster") {
    motor1Speed += motor1changeStep;

    if (motor1Speed > motor1MaximumSpeed) {
      motor1Speed = motor1MaximumSpeed;
    }
  } else {
    motor1Speed = 0;
  }

  handleRoot();
} 

/*
 * handleMotorDirection()
 * changes the direction of motor
 * returns nothing
 */
void handleMotorDirection() {
  if (server.arg("dir") == "m1CW") {
    motor1Direction = CW;

  } else if (server.arg("dir") == "m1CCW") {
    motor1Direction = CCW;

  } else {
  }

  handleRoot();
}  

/*
 * handleMotorBrake()
 * applies brake to the motor
 * returns nothing
 */
void handleMotorBrake() {
  if (server.arg("do") == "m0START") {
    motor1StopState = LOW;
  } else if (server.arg("do") == "m0STOP") {
    motor1StopState = HIGH;
  } else if (server.arg("do") == "m1START") {
    Switch_one = LOW;
    Switch_one_ON_func();

  }
  else if (server.arg("do") == "m1STOP") {
    Switch_one = HIGH;
    Switch_one_OFF_func();

  }
  else if (server.arg("do") == "m2START") {
    Switch_two = LOW;
    Switch_two_ON_func();

  }
  else if (server.arg("do") == "m2STOP") {
    Switch_two = HIGH;
    Switch_two_OFF_func();

  }
  else if (server.arg("do") ==  "COUNTNOW"){
    count++;
    itoa(count, countinternal, 10);
  }

    else if (server.arg("do") ==  "RESETCOUNTER"){
    count=0;
    itoa(count, countinternal, 10);
  }
  
   else {

  }
  handleRoot();
}  

void Switch_one_ON_func(){
      // digitalWrite(Switch_one_pin, HIGH);
        //Timer
      TIMER0 = timerBegin(0, 80, true);
      timerAttachInterrupt(TIMER0, &onTimer0, true);      
      timerAlarmWrite(TIMER0, count*1000000, false);
      timerAlarmEnable(TIMER0); //Just Enable

}

void Switch_one_OFF_func(){
        digitalWrite(Switch_one_pin, LOW);

}


void Switch_two_ON_func(){

      TIMER1 = timerBegin(1, 80, true);
      timerAttachInterrupt(TIMER1, &onTimer1, true);      
      timerAlarmWrite(TIMER1, count*1000000, false);
      timerAlarmEnable(TIMER1); //Just Enable
}

void Switch_two_OFF_func(){
        digitalWrite(Switch_two_pin, LOW);

}
