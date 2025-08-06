#include <stdio.h>
#include "pico/stdlib.h"


const uint STEP_PINS[4] = {13, 12, 11, 10};                 //Zeitsparen


#define ES_OBEN 14
#define ES_UNTEN 15

const uint8_t STEP_SEQ[8][4] = {                            //uint weil es positiv sein muss
    {1,0,0,0},
    {1,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,1,0},
    {0,0,1,1},
    {0,0,0,1},
    {1,0,0,1}
};

volatile int position = 0;                                  //volatile weil es sich immer ändern kann
volatile bool moving_forward = true;


void gpio_callback(uint gpio, uint32_t events) {            //Interrupt Funktion
    if (gpio == ES_OBEN && events & GPIO_IRQ_EDGE_FALL)
    {
        moving_forward = false;
        printf("\nMax erreicht -> Fahre Rückwärts\n");
    }
    else if (gpio  == ES_UNTEN && events & GPIO_IRQ_EDGE_FALL)
    {
        moving_forward = true;
        printf("\nMin erreicht -> Fahre Vorwärts\n");
    }   
}

void stepper_step(int step_index){                          //Stepper Pins setzen
    for (int i = 0; i < 4; i++)
    {
        gpio_put(STEP_PINS[i], STEP_SEQ[step_index][i]);
    }
    
}

int main()
{
    stdio_init_all();
    sleep_ms(2000);

    for (int i = 0; i < 4; i++)                             //Stepper Pins initialisieren
    {
        gpio_init(STEP_PINS[i]);
        gpio_set_dir(STEP_PINS[i], GPIO_OUT);
    }
    

    gpio_init(ES_OBEN);                                     //Endschalter initialisieren
    gpio_set_dir(ES_OBEN, GPIO_IN);
    gpio_pull_up(ES_OBEN);

    gpio_init(ES_UNTEN);
    gpio_set_dir(ES_UNTEN, GPIO_IN);
    gpio_pull_up(ES_UNTEN);

    gpio_set_irq_enabled_with_callback(ES_UNTEN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);     //Interrupt erstellen und auf Funktion zeigen
    gpio_set_irq_enabled(ES_OBEN, GPIO_IRQ_EDGE_FALL, true);                                    //beim 2ten Mal muss man nicht mehr auf die Funktionzeigen (Darf man nciht)

    int step_index = 0;


    while (true) {
        
        stepper_step(step_index);
        if (moving_forward)
        {
            step_index = (step_index + 1) % 8;              //Einen Schritt weiter
            position++;
        }
        else{
            step_index = (step_index + 7) % 8;              //Mit dem Modulo ist +7 das gleiche wie -1
            position--;
        }
        printf("Position;  %2d\n", position);               //Positionsausgabe per Serial Port
        sleep_ms(1);                                        //Motorgeschwindigkeit
    }
}
