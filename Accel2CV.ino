#include <Wire.h>
#include <ADXL345.h>

ADXL345 accel(ADXL345_STD);
constexpr byte CV_PIN = 9;

constexpr uint8_t CV_Max = 96;
constexpr uint8_t CV_Min = 32;
constexpr uint8_t CV_Range = CV_Max - CV_Min;

void setup() {
  Wire.begin();
  accel.writeRange(ADXL345_RANGE_16G);
  accel.start();

  pinMode(CV_PIN, OUTPUT);
}

void loop() {
  if(accel.update()) {
    val = accel.getZ();
  }

  static float vol;
  vol = (val + 1.0) * 0.5 * CV_Range + CV_Min;
    
  analogWrite(CV_PIN, static_cast<int>(vol));
}
