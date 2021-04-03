// using button and led

#include<avr/io.h>
#include<util/delay.h>

#define MS_DELAY 1000

int main()
{
    int x;
    DDRB |= _BV(DDB5);  // setting pin 13 as output
    DDRB &= ~_BV(DDB0); // setting pin 8 as input

    PORTB &= ~_BV(PORTB5);  // setting pin 13 as low
    PORTB |= _BV(PORTB0);   // activating the pull-up resister
    PINB |= ~_BV(PINB0);
    while(1)
    {
        x = _BV(PINB0);  // reading from the pin 8
        _delay_ms(MS_DELAY);
        if (x == 0)
        {
            PORTB |= _BV(PORTB5);   // setting pin 13 as high
            
        }
        else if(x==1)
        {
            PORTB &= ~_BV(PORTB5);
            
        }
        else{}
    }
}