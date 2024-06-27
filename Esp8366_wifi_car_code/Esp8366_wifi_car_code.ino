#include <ESP8266WiFi.h>
#include <Servo.h>

// WiFi credentials
const char* ssid = "Jsmakers";
const char* password = "Jsmakers15";

// Motor pins
const int motor1Pin1 = D1;
const int motor1Pin2 = D2;
const int motor2Pin1 = D3;
const int motor2Pin2 = D4;

// Lights, horn
const int lightsPin = D5;
const int hornPin = D6;

WiFiServer server(80);

Servo myServo;

bool motorRunning = false;

void setup() {
  Serial.begin(9600);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(lightsPin, OUTPUT);
  pinMode(hornPin, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println();
  Serial.println("Connected to WiFi");
  server.begin();
  Serial.println(WiFi.localIP());
}

void loop() {
  manualControl();
}

void manualControl() {
  WiFiClient client = server.available();
  
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    if (request.indexOf("/FORWARD") != -1) {
      moveForward();
    } else if (request.indexOf("/BACKWARD") != -1) {
      moveBackward();
    } else if (request.indexOf("/LEFT") != -1) {
      turnLeft();
    } else if (request.indexOf("/RIGHT") != -1) {
      turnRight();
    } else if (request.indexOf("/STOP") != -1) {
      stopCar();
    } else if (request.indexOf("/LIGHTS_ON") != -1) {
      lightsOn();
    } else if (request.indexOf("/LIGHTS_OFF") != -1) {
      lightsOff();
    } else if (request.indexOf("/HORN_ON") != -1) {
      hornOn();
    } else if (request.indexOf("/HORN_OFF") != -1) {
      hornOff();
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<title>JS MAKER'S CAR CONTROLLER</title>");
    client.println("<style>");
    client.println("body { font-family: Arial, sans-serif; text-align: center; }");
    client.println("h1 { color: #333; }");
    client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; border-radius: 12px; }");
    client.println(".button-stop { background-color: #f44336; }");
    client.println(".button-container { display: flex; justify-content: center; align-items: center; flex-wrap: wrap; max-width: 600px; margin: 0 auto; }");
    client.println(".button-container div { flex: 1; min-width: 100px; margin: 5px; }");
    client.println("</style>");
    client.println("</head>");
    client.println("<body>");
    client.println("<h1>JS MAKER'S CAR CONTROLLER</h1>");
    client.println("<div class=\"button-container\">");
    client.println("<div><a href=\"/FORWARD\" class=\"button\">Forward</a></div>");
    client.println("<div><a href=\"/BACKWARD\" class=\"button\">Backward</a></div>");
    client.println("<div><a href=\"/LEFT\" class=\"button\">Left</a></div>");
    client.println("<div><a href=\"/RIGHT\" class=\"button\">Right</a></div>");
    client.println("<div><a href=\"/STOP\" class=\"button button-stop\">Stop</a></div>");
    client.println("<div><a href=\"/LIGHTS_ON\" class=\"button\">Lights On</a></div>");
    client.println("<div><a href=\"/LIGHTS_OFF\" class=\"button\">Lights Off</a></div>");
    client.println("<div><a href=\"/HORN_ON\" class=\"button\">Horn On</a></div>");
    client.println("<div><a href=\"/HORN_OFF\" class=\"button\">Horn Off</a></div>");
    client.println("</div>");
    client.println("</body>");
    client.println("</html>");
    delay(1);
  }
}

void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void moveBackward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void turnRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void stopCar() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void lightsOn() {
  digitalWrite(lightsPin, HIGH);
}

void lightsOff() {
  digitalWrite(lightsPin, LOW);
}

void hornOn() {
  digitalWrite(hornPin, HIGH);
}

void hornOff() {
  digitalWrite(hornPin, LOW);
}
