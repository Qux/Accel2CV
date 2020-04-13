#include <Wire.h>
#include <ADXL345.h>

ADXL345 accel(ADXL345_STD);
constexpr byte CV_PIN = 9;  //CV出力ピン

constexpr uint8_t CV_Max = 96;  //CV電圧の最大値。
constexpr uint8_t CV_Min = 32;  //CV電圧の最小値。
constexpr uint8_t CV_Range = CV_Max - CV_Min; //計算用

void setup() {
  /* LPFをつけない場合はこの以下の２行のコメントアウトを解除してください。
    TCCR1B &= B11111000;
    TCCR1B |= B00000001;
  */

  Wire.begin();
  accel.writeRange(ADXL345_RANGE_16G);
  accel.start();

  pinMode(CV_PIN, OUTPUT);
}

void loop() {
  if (accel.update()) {
    val = accel.getZ();
  }

  static float vol;
  vol = (val + 1.0) * 0.5 * CV_Range + CV_Min;

  analogWrite(CV_PIN, static_cast<int>(vol));
}
