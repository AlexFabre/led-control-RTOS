# led-control-RTOS

The device has three main states.

- ACTIVE: The led is blinking every 300ms during 20s. After those 20s the device goes into STANBY state.
- STANDBY: The led is blinking every 600ms during 40s. After those 40s the device goes again in ACTIVE state.
- SHUTDOWN: The led is permanently off, and the device remain like this while the user has not clicked on the button.

The device periodic toggle from ACTIVE state to STANDBY state goes by itself forever, while the user has not clicked on the button.

To sart or stop the device, the user has to click on the button.

When the user performs a double click the device sends a 4kB frame over UART at 4800 Bauds. This transmission should not affect the blinking timings nor the button responsiveness.

# Problems

1. When the user performs a double click, the button are not responding during the UART transfer (During the few seconds of the transfer it's impossible to click and toggle the device in ACTIVE/SHUTDOWN). Explain and fix this bug using a dedicated task for the UART messages.
2. Some blinking timings need to be upgraded in functions `enter_sequence_running()`, `enter_sequence_stanby()`, and `stop_sequence()`. Implement those missing features.
