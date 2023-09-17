#ifndef __BUTTON_H
#define __BUTTON_H

typedef enum {
    BTN_STILL_PROCESSING,
    BTN_RELEASED,
    BTN_CLICK,
    BTN_LONG_CLICK,
    BTN_VERY_LONG_CLICK,
    BTN_DOUBLE_CLICK,
    BTN_TRIPLE_CLICK,

    BTN_UNKNOWN_CLICK,
} button_event_t;

/* The maximum number of consecutive/successive click */
#define BTN_MAX_CONSECUTIVE_CLICK        (3)
/* Minimum pressure duration to validate a click */
#define BTN_SINGLE_CLICK_MIN_DURATION    (80)
/* Duration after which a click becomes a long press */
#define BTN_LONG_CLICK_MIN_DURATION      (1000)
/* Duration after which a long press becomes a very long press */
#define BTN_VERY_LONG_CLICK_MIN_DURATION (2000)
/* Minimum duration to tell the button was released */
#define BTN_MIN_PAUSE_BETWEEN_CLICK      (80)
/* Duration after which a released button cannot accept a consecutive click anymore */
#define BTN_MAXIMUM_PAUSE_BETWEEN_CLICK  (300)
/* If user presses button more than this delay it performs a software reset */
#define BTN_SOFT_RESET_DURATION          (6000)

/* MCU reset macro */
#define SYSTEM_RESET() NVIC_SystemReset()

/* MCU tick read macro */
#define SYSTEM_TICK() HAL_GetTick()

/* Reset the button logic */
void reset_button_variables(void);

/* Button pressed function to be called from the button IRQ */
void button_pressed_IRQ(void);

/* Button release function to be called from the button IRQ */
void button_released_IRQ(void);

/* Get the button state */
button_event_t get_button_state(void);

#endif /* __BUTTON_H */