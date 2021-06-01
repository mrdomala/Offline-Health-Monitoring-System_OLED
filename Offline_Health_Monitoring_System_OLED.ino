#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);

//oled 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in 
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const unsigned char bitmap [] PROGMEM=
{
0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x00, 0x0f, 0xe0, 0x7f, 0x00, 0x3f, 0xf9, 0xff, 0xc0,
0x7f, 0xf9, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xf0,
0xff, 0xf7, 0xff, 0xf0, 0xff, 0xe7, 0xff, 0xf0, 0xff, 0xe7, 0xff, 0xf0, 0x7f, 0xdb, 0xff, 0xe0,
0x7f, 0x9b, 0xff, 0xe0, 0x00, 0x3b, 0xc0, 0x00, 0x3f, 0xf9, 0x9f, 0xc0, 0x3f, 0xfd, 0xbf, 0xc0,
0x1f, 0xfd, 0xbf, 0x80, 0x0f, 0xfd, 0x7f, 0x00, 0x07, 0xfe, 0x7e, 0x00, 0x03, 0xfe, 0xfc, 0x00,
0x01, 0xff, 0xf8, 0x00, 0x00, 0xff, 0xf0, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x3f, 0xc0, 0x00,
0x00, 0x0f, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void setup()
{
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000); // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();
    // Draw a single pixel in white
  display.drawPixel(10, 10, WHITE);
  display.display();
  delay(1000);
}
void loop()
{
  int heartrate=analogRead(A0);
  heartrate = map(heartrate, 0, 1023, 40, 100);
  if(heartrate>65)
      {
        digitalWrite(LED_BUILTIN,1);
        Serial.print("Heart Pluse: ");
        Serial.println(heartrate);
        display.clearDisplay();
        display.drawBitmap( 50, 10, bitmap, 28, 28, 1);
        display.display();
        display.setCursor(10,0);
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.println("Health Monitoring");
        display.setCursor(0,45);
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.print("Heart Pulse : "); 
        display.setCursor(90,45);
        display.setTextSize(1);
        display.println(heartrate);
        //display.println("Pluse is High");
        display.display();
        mySerial.println("AT+CMGF=1");//Sets the GSM Module in Text Mode
        delay(1000);//Delay of 1 second
        mySerial.println("AT+CMGS=\"+918328528973\"\r"); //Replace x with mobile number
        delay(1000);
        mySerial.println("Hello User! Your heat pluse above 65!");//The SMS text you want to send
        delay(100);
        mySerial.println((char)26);//ASCII code of CTRL+Z for saying the end of sms to  the module 
        delay(1000); 
      }
  
  
  /*display.setCursor(0,20);
  display.println("HIR Value ");
  display.println(irValue);*/
  display.display();
  
  delay(5000);
}
