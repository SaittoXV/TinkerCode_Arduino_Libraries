#include <TuahMini.h>

tuahmini bot((unsigned char[]) { A6, A3, A2, A1, A0} ,5, 4, QTR_NO_EMITTER_PIN);


void setup() {
  bot.Motor(6,5,2,3);
}

void loop() {
  bot.motortank("forward",150,"backward",150);
  for (int count = 0; count < 200; count++) {
    bot.calibrate();
  }
  bot.motorsteer("left",0);
  delay(2000);
  while (1) {
    bot.pid_line(100, 100, 100, 200, 0.10, 0.20, 1, 200);
  }

}
