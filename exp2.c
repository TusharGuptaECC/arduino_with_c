#include<avr/io.h>
#include<util/delay.h>

#define MS_DELAY 1000

void shift(int);
void cleardata(void);

int main()
{
    int i,q,n,r;
    // set pin 12,11,10,8 as output
    DDRB |= _BV(DDB4);
    DDRB |= _BV(DDB3);
    DDRB |= _BV(DDB2);
    DDRB |= _BV(DDB0);

    PORTB &= ~_BV(PORTB2);  // MR' Low reset the shift register of 74HC595N
    PORTB |= _BV(PORTB2);   // MR' high

    // represent 0
    PORTB &= ~_BV(PORTB3);  //datapin=0
    for(i=1;i<=8;i++)
    {
        PORTB |= _BV(PORTB4);   //clockpin = 1
        PORTB &= ~_BV(PORTB4);  // clockpin =0
    }

    PORTB |= _BV(PORTB0);   //latchpin=1
    _delay_ms(MS_DELAY);
    PORTB &= ~_BV(PORTB0);  //latchpin=0
    
    // input
    for(n=1;n<=255;n++)
    {
        q=n;
        while (q!=0)
        {
            q = q/2;
            r = q%2;
            if(r==1)
            {
                PORTB |= _BV(PORTB3);  //datapin=1
                PORTB |= _BV(PORTB4);   //clockpin = 1
                PORTB &= ~_BV(PORTB4);  // clockpin =0
                PORTB &= ~_BV(PORTB3);  //datapin=0
            }
            else
            {
                PORTB &= ~_BV(PORTB3);  //datapin=0 
                PORTB |= _BV(PORTB4);   //clockpin = 1
                PORTB &= ~_BV(PORTB4);  // clockpin =0
            }
        }
        shift(n); // shifts the bits as per the requirements
        PORTB |= _BV(PORTB0);   //latchpin=1
        _delay_ms(MS_DELAY);
        PORTB &= ~_BV(PORTB0);  //latchpin=0
        cleardata();// clears the shift register
        // reseting the loop
        if(n==255)
            n=1;
    }
}

void shift(int n)
{
    int k;
    // 1 is ONE bit so shift of SEVEN
    if(n==1)
    {
        for(k=1;k<=7;k++)
        {
            PORTB |= _BV(PORTB4);   //clockpin = 1
            PORTB &= ~_BV(PORTB4);  //clockpin =0
        }
    }

    // 2-3 are TWO bits so shift of SIX 
    else if(n==2 || n==3)
    {
        for(k=1;k<=6;k++)
        {
            PORTB |= _BV(PORTB4);   //clockpin = 1
            PORTB &= ~_BV(PORTB4);  //clockpin =0
        }
    }

    // 4-7 are THREE bits so shift of FIVE
    else if(n>=4 && n<=7)
    {
        for(k=1;k<=5;k++)
        {
            PORTB |= _BV(PORTB4);   //clockpin = 1
            PORTB &= ~_BV(PORTB4);  //clockpin =0
        }
    }

    // 8-15 are FOUR bits so shift of FOUR
    else if(n>=8 && n<=15)
    {
        for(k=1;k<=4;k++)
        {
            PORTB |= _BV(PORTB4);   //clockpin = 1
            PORTB &= ~_BV(PORTB4);  //clockpin =0
        }
    }

    // 16-31 are FIVE bits so shift of THREE
    else if(n>=16 && n<=31)
    {
        for(k=1;k<=3;k++)
        {
            PORTB |= _BV(PORTB4);   //clockpin = 1
            PORTB &= ~_BV(PORTB4);  //clockpin =0
        }
    }

    // 32-63 are SIX bits so shift of TWO
    else if(n>=32 && n<=63)
    {
        for(k=1;k<=2;k++)
        {
            PORTB |= _BV(PORTB4);   //clockpin = 1
            PORTB &= ~_BV(PORTB4);  //clockpin =0
        }
    }

    // 64-127 are SEVEN bits so shift of ONE
    else if(n>=64 && n<=127)
    {
        PORTB |= _BV(PORTB4);   //clockpin = 1
        PORTB &= ~_BV(PORTB4);  //clockpin =0
        
    }

    // 128-255 are EIGHT bits so shift of ZERO
    else if(n>=128 && n<=255)
    {
        PORTB &= ~_BV(PORTB4);  //clockpin =0
    }

    else{}
}

void cleardata()
{
    int m;
    PORTB &= ~_BV(PORTB3);  //datapin=0
    for(m=1;m<=8;m++)
    {
        PORTB |= _BV(PORTB4);   //clockpin = 1
        PORTB &= ~_BV(PORTB4);  //clockpin =0
    }
}