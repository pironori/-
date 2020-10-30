#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <playtune.h>
#include <songs/WTJP328p.h>

void setup(void)
{
      // set everything low that we aren't using
    DDRB |= (1<<PB2) | (1<<PB4) | (1<<PB3) | (1<<PB5);
    PORTB &= ~(1<<PB2) | ~(1<<PB4) | ~(1<<PB3) | ~(1<<PB5);


    PlayTune p0(0,WTJP328P0);
    PlayTune p1(1,WTJP328P1);
    PlayTune p2(2,WTJP328P2);
    while ( p0.isPlaying() || p1.isPlaying() || p2.isPlaying()) {

        p0.playNote();
        p1.playNote();
        p2.playNote();
        _delay_ms(87);
    }


    /*
    PlayTune pk0(0,ASUHENO0);
    PlayTune pk1(1,ASUHENO1);
    PlayTune pk2(1,ASUHENO2);
    while ( pk0.isPlaying() || pk1.isPlaying() || pk2.isPlaying()) {

        pk0.playNote();
        pk1.playNote();
        pk2.playNote();
        _delay_ms(30);
    }
    */


    digitalWrite(6, LOW);
    digitalWrite(9, LOW); 
    digitalWrite(11, LOW); 
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
  }

void loop(void)
{
}
