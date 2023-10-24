#include <stdlib.h>
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

bool pin = 0;

int main() {
  stdio_init_all();
  if (cyw43_arch_init()) {
    printf("Wi-Fi init failed");
    return -1;
  }
  while (true) {
    pin = !pin;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, pin);
    sleep_ms(1000);
  }
}