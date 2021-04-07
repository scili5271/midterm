#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2);

AnalogOut Aout(D7);
AnalogIn Ain(A3);

InterruptIn up(A2);
InterruptIn down(A1);
InterruptIn sel(A0);
DigitalOut led(LED1);
EventQueue queue(32 * EVENTS_EVENT_SIZE);


Thread t;

float now = 1, tmp = 1;
float ADCdata[128];
int sample = 128;

void add()
{
    if(tmp == 1)
    {
        tmp = 1;
    }
    else
    {
        tmp = tmp * 2;
    }
    uLCD.cls();
    uLCD.text_width(4); 
    uLCD.text_height(4);
    uLCD.printf("\n%.3f\n",tmp);
}

void sub()
{
    if(tmp == 0.125)
    {
        tmp = 0.125;
    }
    else
    {
        tmp = tmp / 2;
    }
    uLCD.cls();
    uLCD.text_width(4); 
    uLCD.text_height(4);
    uLCD.printf("\n%.3f\n",tmp);
}

void sele()
{
    now = tmp;
    uLCD.cls();
    uLCD.text_width(4); 
    uLCD.text_height(4);
    uLCD.color(RED);
    uLCD.printf("\n%.3f\n",now);
    while (1)
    {
    if (now == 1)
    {
        Aout = 0;
        for (int i = 0; i < 240; i++) {
            if ( i < 80)
            {
                Aout = Aout + 0.01136;
                ThisThread::sleep_for(1ms);
            }
            else if (i > 160)
            {
                Aout = Aout - 0.0136;
                ThisThread::sleep_for(1ms);
            }
            else
            {
                Aout = Aout;
                ThisThread::sleep_for(1ms);
            }
        }
    }
    else if (now == 0.5)
    {
        Aout = 0;
        for (int i = 0; i < 240; i++) {
            if ( i < 40)
            {
                Aout = Aout + 0.02272;
                ThisThread::sleep_for(1ms);
            }
            else if (i > 200)
            {
                Aout = Aout - 0.02272;
                ThisThread::sleep_for(1ms);
            }
            else
            {
                Aout = Aout;
                ThisThread::sleep_for(1ms);
            }
        }
    }
    else if (now == 0.25)
    {
        Aout = 0;
        for (int i = 0; i < 240; i++) {
            if ( i < 20)
            {
                Aout = Aout + 0.04545;
                ThisThread::sleep_for(1ms);
            }
            else if (i > 220)
            {
                Aout = Aout - 0.04545;
                ThisThread::sleep_for(1ms);
            }
            else
            {
                Aout = Aout;
                ThisThread::sleep_for(1ms);
            }
        }
    }
    else if (now == 0.125)
    {
        Aout = 0;
        for (int i = 0; i < 240; i++) {
            if ( i < 10)
            {
                Aout = Aout + 0.0909;
                ThisThread::sleep_for(1ms);
            }
            else if (i > 230)
            {
                Aout = Aout-0.0909;
                ThisThread::sleep_for(1ms);
            }
            else
            {
                Aout = Aout;
                ThisThread::sleep_for(1ms);
            }
        }
    }
    }
}


int main()
{
    Aout = 0;
    t.start(callback(&queue, &EventQueue::dispatch_forever));

    up.rise(queue.event(add));
    down.rise(queue.event(sub));
    sel.rise(queue.event(sele));
}
