#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2);

AnalogOut Aout(D7);

InterruptIn up(A2);
InterruptIn down(A1);
InterruptIn sel(A0);
DigitalOut led(LED1);
EventQueue queue(32 * EVENTS_EVENT_SIZE);

Thread t;
float now = 1, tmp = 1;

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
}


int main()
{

    t.start(callback(&queue, &EventQueue::dispatch_forever));

    up.rise(queue.event(add));
    down.rise(queue.event(sub));
    sel.rise(queue.event(sele));

}
