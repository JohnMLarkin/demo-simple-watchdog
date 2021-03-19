#include <mbed.h>

Watchdog &watchdog = Watchdog::get_instance();
BusOut ledCounter(LED1,LED2,LED3);
DigitalOut heartbeat(LED4);
DigitalIn badThing(p5);
Ticker t;

void countdown() {
  ledCounter = ledCounter - 1;
}

void all_is_well() {
  watchdog.kick();
  ledCounter = 7;
}

int main() {
  printf("It is a good day to be alive\n");
  watchdog.start(7000);
  ledCounter = 7;
  t.attach(&countdown, 1s);

  while (1) {
    heartbeat = !heartbeat;
    if (badThing) {
      printf("Ouch!\n");
      heartbeat = 0; // heart is stopped
      while (1) { } // and no longer beating
    }
    ThisThread::sleep_for(250ms);
    all_is_well();
  }
}