#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C LCD at address 0x27, 16 columns and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define IR sensor pins (change as per your wiring)
const int seatSensors[4] = {34, 35, 32, 33};  // GPIO pins for IR sensors

int totalSeats = 4;
int occupiedSeats = 0;

void setup() {
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Bus Seat Monitor");

  // Set sensor pins as input
  for (int i = 0; i < totalSeats; i++) {
    pinMode(seatSensors[i], INPUT);
  }

  delay(2000);
  lcd.clear();
}

void loop() {
  occupiedSeats = 0;

  // Read all seat sensors
  for (int i = 0; i < totalSeats; i++) {
    int seatState = digitalRead(seatSensors[i]);

    // If IR sensor is blocked (seat occupied), count it
    if (seatState == LOW) {  // IR sensors usually go LOW when blocked
      occupiedSeats++;
    }
  }

  int availableSeats = totalSeats - occupiedSeats;

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Occupied: ");
  lcd.print(occupiedSeats);
  lcd.print("   "); // Clear leftovers

  lcd.setCursor(0, 1);
  lcd.print("Available: ");
  lcd.print(availableSeats);
  lcd.print("   ");

  delay(1000); // Update every second
}

