#include "keyboard_runtime_thread.hpp"
#include "kb_macros_define.h"
#include "led_matrix_runtime.hpp"

extern void start_keyboard_runtime_thread(void);
extern void reprogram_key(uint16_t map[], size_t map_size);

// Allows us to reset the current keymap. 
void reset_keymap(void);

// Setting up the current keymap information. 
volatile uint16_t current_keymap[NUM_ROWS * NUM_COLS];

// Checking if there is a new click.
bool new_click = false; 

/**************************************************************************/
/*!
    @brief Thread function and stack space for dealing the keyboard runtime stuff. 
*/
/**************************************************************************/
static THD_WORKING_AREA(keyboard_runtime_thread_wa, 4096);
static THD_FUNCTION(keyboard_runtime_thread, arg){
    (void)arg; 

    start_keyboard_gpio();
    Keyboard.begin();
    reset_keymap();
   
   // Latest keystate information. 
    KeyState key_state; 

    // previous key state information information
    KeyState prev_key_state;

    for(uint8_t i = 0; i < NUM_ROWS * NUM_COLS; i++)
        prev_key_state[i] = 1; 

    systime_t kb_thread_begin_tick;
    systime_t kb_thread_end_tick; 
 
    while(1){
        // Get current tick  aneiobfk
        kb_thread_begin_tick = chVTGetSystemTimeX();

        // Reads in the keyboard data from the matrix. 
        read_keyboard_gpio();
        get_keyboard_values(key_state);   

        // Run through 2D array, check which keys are pressed and which arent. 
        for(uint8_t x = 0; x < NUM_ROWS * NUM_COLS; x++){
            
            if((key_state[x] == 0) && !(key_state[x] == prev_key_state[x])){
                new_click = true; 
                Keyboard.press(current_keymap[x]);
                // Setting the previous key state to the next key_state
                prev_key_state[x] = key_state[x];
            }
            if((key_state[x] == 1) && !(key_state[x] == prev_key_state[x])){
                new_click = true; 
                Keyboard.release(current_keymap[x]);
                // Setting the previous key state to the next key_state
                prev_key_state[x] = key_state[x];
                key_state[x] = 0; 
            }
        }
        // END OF KEYSTROKE KEYBOARD OUTPUT // 

        if(new_click){
            // Send keystroke information to the LED strip thread, casts to volatile unsigned 8 bit integer. 
            trigger_keymap((volatile uint8_t*)key_state);
            new_click = false; 
        }
        // we sleep the remainder of the time for the keyboard. 
        kb_thread_end_tick = kb_thread_begin_tick + TIME_I2MS(33);
        if(kb_thread_end_tick > chVTGetSystemTimeX())
            chThdSleepUntil(kb_thread_end_tick);
    }   
}

/**************************************************************************/
/*!
    @brief Allows us to start up our keyboard runtime thread
*/
/**************************************************************************/
extern void start_keyboard_runtime_thread(void){
    chThdCreateStatic(keyboard_runtime_thread_wa, 
                      sizeof(keyboard_runtime_thread_wa), 
                      NORMALPRIO + 3, 
                      keyboard_runtime_thread, 
                      NULL);
}

void reset_keymap(void){
    current_keymap[0] = DEFAULT_KB_MACRO_0;
    current_keymap[1] = DEFAULT_KB_MACRO_1; 
    current_keymap[2] = DEFAULT_KB_MACRO_2; 
    current_keymap[3] = DEFAULT_KB_MACRO_3;
    current_keymap[4] = DEFAULT_KB_MACRO_4; 
    current_keymap[5] = DEFAULT_KB_MACRO_5; 
    current_keymap[6] = DEFAULT_KB_MACRO_6; 
    current_keymap[7] = DEFAULT_KB_MACRO_7; 
    current_keymap[8] = DEFAULT_KB_MACRO_8; 
    current_keymap[9] = DEFAULT_KB_MACRO_9; 
    current_keymap[10] = DEFAULT_KB_MACRO_10; 
    current_keymap[11] = DEFAULT_KB_MACRO_11; 
    current_keymap[12] = DEFAULT_KB_MACRO_12; 
    current_keymap[13] = DEFAULT_KB_MACRO_13; 
    current_keymap[14] = DEFAULT_KB_MACRO_14; 
    current_keymap[15] = DEFAULT_KB_MACRO_15; 
}

extern void reprogram_key(uint16_t map[], size_t map_size){
    for(size_t i = 0; i < map_size; i++)
        current_keymap[i] = map[i];
}