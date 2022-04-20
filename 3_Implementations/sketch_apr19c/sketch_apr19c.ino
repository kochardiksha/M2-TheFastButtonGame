#include <avr/io.h> ///library for avr microcontroller 
#include <util/delay.h>  //for delay

void ProcessPressedButton(int ButtonPressed);   ///Fuctions for lighting up led
void ProcessReleasedButton(int ButtonReleased);
int Pressed_Confidence_Level[2]; //Array declaration for lighting up led one by one
int Released_Confidence_Level[2];
int Pressed[2];
int LEDNumber[2];
int main(void)
{
DDRB = 0b01111111;  //Direction data for port B as output
DDRD = 0b01111111;  //Direction data for port D as output
PORTB = 0b10000000;  //Clear all bits except last for button
PORTD = 0b10000000; //Clear all bits except last for button

while (1)
{
if (bit_is_clear(PINB, 7)) // if button1 is pressed
{
ProcessPressedButton(0); //Calling this function for user1 lighting up the Led
}
else
{
ProcessReleasedButton(0); //calling this function for releasing the button
}
if (bit_is_clear(PIND, 7)) //Checking the button on Pin D7
{
ProcessPressedButton(1); // Calling the function for user2 Led
}
else
{
ProcessReleasedButton(1);
}
}
}

void ProcessPressedButton(int ButtonPressed)  //Function forlighting up the led
{
Pressed_Confidence_Level[ButtonPressed] ++; //increment the array
if (Pressed_Confidence_Level[ButtonPressed] > 500)
{
if (Pressed[ButtonPressed] == 0)
{
Pressed[ButtonPressed] = 1;
if (ButtonPressed == 0) PORTB |= 1 << LEDNumber[ButtonPressed]; //light up all led one by one on port B
if (ButtonPressed == 1) PORTD |= 1 << LEDNumber[ButtonPressed]; //light up all led one by one on port D
LEDNumber[ButtonPressed] ++; //Counter increment
if (LEDNumber[ButtonPressed] >6)
{
for(int i=0;i < 10;i++)
{
if (ButtonPressed == 0) PORTB = 0b11111111; //Set all pins at 5volts on port B
if (ButtonPressed == 1) PORTD = 0b11111111; //Set all pins at 5volts on port D
_delay_ms(10);
if (ButtonPressed == 0) PORTB = 0b10000000; //Set all pins at 0volts on port B except pin 8
if (ButtonPressed == 1) PORTD = 0b10000000;  //Set all pins at 0volts on port D accept pin 8
_delay_ms(10);
}
LEDNumber[0] = 0;
LEDNumber[1] = 0;
PORTB = 0b10000000;
PORTD = 0b10000000;
}
}
Pressed_Confidence_Level[ButtonPressed] = 0;
}
}

void ProcessReleasedButton(int ButtonReleased) //Function for performing on releasing the button
{
Released_Confidence_Level[ButtonReleased] ++;
if (Released_Confidence_Level[ButtonReleased] > 500)
{
Pressed[ButtonReleased] = 0;
Released_Confidence_Level[ButtonReleased] = 0;
}
}
