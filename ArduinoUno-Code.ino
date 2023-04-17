#define red_pin 9
#define green_pin 10
#define blue_pin 11


 



void setup() {
  Serial.begin(115200);

 pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  // Initialize the LED to a low state
   digitalWrite(red_pin, LOW);
digitalWrite(green_pin, LOW);
digitalWrite(blue_pin, LOW);
}

void loop() {

  if (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    Serial.println(message);


    int start = message.indexOf("\"") + 1;  // Find the position of the first double quote
int end = message.indexOf("\"", start);  // Find the position of the second double quote
String redStr = message.substring(start, end);  // Extract the substring between the double quotes
int red = redStr.toInt();  // Convert the substring to an integer value

start = message.indexOf("\"", end + 1) + 1;  // Find the position of the third double quote
end = message.indexOf("\"", start);  // Find the position of the fourth double quote
String greenStr = message.substring(start, end);  // Extract the substring between the double quotes
int green = greenStr.toInt();  // Convert the substring to an integer value

start = message.indexOf("\"", end + 1) + 1;  // Find the position of the fifth double quote
end = message.indexOf("\"", start);  // Find the position of the sixth double quote
String blueStr = message.substring(start, end);  // Extract the substring between the double quotes
int blue = blueStr.toInt();  // Convert the substring to an integer value

    Serial.print("Red: ");
    Serial.println(red);

    Serial.print("Green: ");
    Serial.println(green);

    Serial.print("Blue: ");
    Serial.println(blue);

    analogWrite(red_pin, red);
    analogWrite(green_pin, green);
    analogWrite(blue_pin, blue);

  // Delay for 1 second
  }
}