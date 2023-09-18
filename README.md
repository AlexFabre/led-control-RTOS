# led-control-RTOS

The device has three main states.

- ACTIVE: The led is blinking every 300ms during 20s. After those 20s the device goes into STANBY state.
- STANDBY: The led is blinking every 600ms during 40s. After those 40s the device goes again in ACTIVE state.
- SHUTDOWN: The led is permanently off, and the device remain like this while the user has not clicked on the button.

The device periodic toggle from ACTIVE state to STANDBY state goes by itself forever, while the user has not clicked on the button.

To sart or stop the device, the user has to click on the button.

When the user performs a double click the device sends a 4kB frame over UART.

## Hardware architecture with RTOS
* One task handles the LED blink timmings
* RTC handles the application periodic state changes timmings
* Button is managed with External interrupt 7
* One task will handle the frame sending and queue
