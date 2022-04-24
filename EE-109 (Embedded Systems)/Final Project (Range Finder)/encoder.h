// Rotary encoder header file

void rotary_init();

extern volatile unsigned char new_state, old_state; // Rotary States (Used from Lab 7)
extern volatile unsigned char rotaryChange; // Rotary Flag
extern volatile int count; // Rotary ISR will be summed
extern volatile unsigned char a, b; // Used for Rotary Encoder