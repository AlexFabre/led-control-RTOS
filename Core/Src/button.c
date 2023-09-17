#include <stdint.h>
#include <string.h>

#include "button.h"
#include "main.h"

/* Constant array of button events */
static const unsigned _single_click_event_array[]    = { BTN_CLICK, BTN_RELEASED };
static const unsigned _long_click_event_array[]      = { BTN_LONG_CLICK, BTN_RELEASED };
static const unsigned _very_long_click_event_array[] = { BTN_VERY_LONG_CLICK, BTN_RELEASED };
static const unsigned _double_click_event_array[]    = { BTN_CLICK, BTN_CLICK, BTN_RELEASED };
static const unsigned _triple_click_event_array[]    = { BTN_CLICK, BTN_CLICK, BTN_CLICK, BTN_RELEASED };

/* Local variables */
static uint32_t _t_pressed; /* Timestamp of previous pressed IRQ */
static uint32_t _t_released; /* Timestamp of previous released IRQ */

/* Array of the consecutive button actions performed by the user */
static unsigned _click_event_array[BTN_MAX_CONSECUTIVE_CLICK + 1];
static unsigned _click_event_nbr; /* Number of consecutive button state */

void reset_button_variables(void)
{
    _t_pressed  = 0;
    _t_released = 0;

    /* Reset the array of consecutive clicks */
    for (unsigned i = 0; i < (sizeof(_click_event_array) / sizeof(_click_event_array[0])); i++) {
        _click_event_array[i] = BTN_RELEASED;
    }

    _click_event_nbr = 0;
}

void button_pressed_IRQ(void)
{
    /* Debounce consecutive press IRQ */
    if ((SYSTEM_TICK() - _t_pressed) < BTN_MIN_PAUSE_BETWEEN_CLICK) {
        return;
    }

    uint32_t btn_released_duration = SYSTEM_TICK() - _t_released;

    /* Check the button was released enough time before being clicked */
    if (btn_released_duration < BTN_MIN_PAUSE_BETWEEN_CLICK) {
        /* Too short for being a real click. Probably noise...
         * Not saving its timestamp it's not a valid press */
        return;
    }

    /* Save new btn pressed timestamp */
    _t_pressed = SYSTEM_TICK();
}

void button_released_IRQ(void)
{
    /* Debounce consecutive press IRQ */
    if ((SYSTEM_TICK() - _t_released) < BTN_MIN_PAUSE_BETWEEN_CLICK) {
        return;
    }

    /* Check that the button has been pressed before being released */
    if (_t_pressed == 0) {
        /* BTN pressed timestamp is zero at boot.
         * This means the mcu started with the button pressed.
         * We do not want to take care of this */
        return;
    }

    uint32_t btn_pressed_duration = SYSTEM_TICK() - _t_pressed;

    /* Check the button was pressed enough time before being released */
    if (btn_pressed_duration < BTN_SINGLE_CLICK_MIN_DURATION) {
        /* Too short for being a real click. Probably noise...
         * Not saving its timestamp it's not a valid release */
        return;
    }

    /* Save new btn release timestamp */
    _t_released = SYSTEM_TICK();

    if (_click_event_nbr >= BTN_MAX_CONSECUTIVE_CLICK) {
        /* User clicked more than max allowed consecutively... */
        return;
    }

    if (btn_pressed_duration < BTN_LONG_CLICK_MIN_DURATION) {
        _click_event_array[_click_event_nbr] = BTN_CLICK;
        _click_event_nbr++;
        return;
    }

    if (btn_pressed_duration < BTN_VERY_LONG_CLICK_MIN_DURATION) {
        _click_event_array[_click_event_nbr] = BTN_LONG_CLICK;
        _click_event_nbr++;
        return;
    }

    if (btn_pressed_duration < BTN_SOFT_RESET_DURATION) {
        _click_event_array[_click_event_nbr] = BTN_VERY_LONG_CLICK;
        _click_event_nbr++;
        return;
    }

    /* The button was pressed for a very long time.
     * The user wants to reset the device. */
    SYSTEM_RESET();
}

button_event_t get_button_state(void)
{
    if (_t_released < _t_pressed) {
        /* Button is still being pressed */
        return BTN_STILL_PROCESSING;
    }

    if (_click_event_nbr == 0) {
        /* No click detected */
        return BTN_RELEASED;
    }

    uint32_t btn_released_duration = SYSTEM_TICK() - _t_released;

    if (btn_released_duration < BTN_MAXIMUM_PAUSE_BETWEEN_CLICK) {
        /* We don't know yet if the user will make a onsecutive click... */
        return BTN_STILL_PROCESSING;
    }

    button_event_t state;

    /* Click patterns */

    if (memcmp(_click_event_array, _single_click_event_array, sizeof(_single_click_event_array)) == 0) {
        /* Single click */
        state = BTN_CLICK;
    } else if (memcmp(_click_event_array, _long_click_event_array, sizeof(_long_click_event_array)) == 0) {
        /* Long click */
        state = BTN_LONG_CLICK;
    } else if (memcmp(_click_event_array, _very_long_click_event_array, sizeof(_very_long_click_event_array)) == 0) {
        /* Very long click */
        state = BTN_VERY_LONG_CLICK;
    } else if (memcmp(_click_event_array, _double_click_event_array, sizeof(_double_click_event_array)) == 0) {
        /* Double click */
        state = BTN_DOUBLE_CLICK;
    } else if (memcmp(_click_event_array, _triple_click_event_array, sizeof(_triple_click_event_array)) == 0) {
        /* Tripple click */
        state = BTN_TRIPLE_CLICK;
    } else {
        /* Unknown pattern */
        state = BTN_UNKNOWN_CLICK;
    }

    /* Reset the array of consecutive clicks */
    for (unsigned i = 0; i < (sizeof(_click_event_array) / sizeof(_click_event_array[0])); i++) {
        _click_event_array[i] = BTN_RELEASED;
    }

    _click_event_nbr = 0;

    return state;
}
