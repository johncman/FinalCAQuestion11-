#include "mbed.h"
/* The button is set up as a DigitalIn object and is attached to pin PC_13.
Two LEDs are set up as DigitalOut objects and are attached to pins.
Led1 is initially configured as ON (1) and led2 as OFF (0).
The loop never stops detecting whether the button is pressed. Button == 0 shows that the button is pressed since the button is active-low.
The LEDs' statuses are toggled and the flag is set to true to stop further toggling until the button is released if the button 
is pushed and the flag is false (signaling that the button press has not been handled).
The LEDs can be toggled with the next press when the button is released (button == 1). This resets the flag to false.
After the LEDs are toggled, a 200 ms delay (wait_us(200000)) is added to the button 
to debounce it and prevent mechanical bounce from causing repeated toggles with a single press.
Every time you press the button, the LEDs will toggle. The LEDs only toggle when the button is pressed;
releasing it has no effect on them. Even if the button is held down for a long time, the flag makes sure that every button hit results in exactly one toggle.
*/

// Create DigitalIn object for the blue button (connected to PC_13)
DigitalIn button(PC_13);

// Create DigitalOut objects for the two LEDs (connected to PA_5 and PA_6)
DigitalOut led1(PA_5); // LED1
DigitalOut led2(PA_6); // LED2

int main() {
    // Initialize LED1 as ON and LED2 as OFF
    led1 = 1;  // LED1 ON
    led2 = 0;  // LED2 OFF

    // Initialize a flag and set it to 0
    bool flag = false;

    // Infinite loop
    while (1) {
        // Check if the button is pressed (active low)
        if (button == 0) {
            // If the flag is 0 (meaning the last press was not handled)
            if (flag == false) {
                // Set the flag as 1 to indicate the button press is being handled
                flag = true;

                // Toggle the states of LED1 and LED2
                led1 = !led1;
                led2 = !led2;

                // Delay to debounce the button press (if needed)
                wait_us(200000); // 200ms delay for debounce
            }
        } else {
            // When the button is released, reset the flag to 0
            // so that the next press will be handled
            flag = false;
        }
    }
}