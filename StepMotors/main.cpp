#include "steps.pio.h" //programa hecho en asm.

#include "hardware/clocks.h"
#include "hardware/pio.h"

#include "pico/stdlib.h"
#include <cstdio>
#include <stdlib.h>

int main() {
    stdio_init_all();

    // Elegir Instancia de PIO, 0 en este caso
    PIO pio = pio0;

    // Pedir 1 de las 4 maquinas de estado, que este libre
    uint sm = pio_claim_unused_sm(pio, true);

    // Copiar el programa PIO , a la memoria del PIO. El SDK lo obtiene SOLO.
    uint offset = pio_add_program(pio, &steps_program);

    // Calcular el Scaler por 4 instruciones
    static const float pio_freq = 1000 * 4;
    float div = (float)clock_get_hz(clk_sys) / pio_freq;

    // Inicializar el programa usando el "helper function" del .pio
    steps_program_init(pio, sm, offset, 1, div);

    // Arrancamos la instancia del programa.
    pio_sm_set_enabled(pio, sm, true);

    for(int i = 0; i < 10; i++) pio_sm_put_blocking(pio, sm, i);

    // NAAAAAAAAAAAAAAAAADAAAAAAAAAAAAAAAA
    while(true) { sleep_ms(1000); }
}