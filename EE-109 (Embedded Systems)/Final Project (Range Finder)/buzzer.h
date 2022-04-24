// Buzzer header file

void buzzer_init();
void play_note();

extern volatile unsigned char speakerState; // State for Buzzer
extern volatile int buzzerCount; // Used for Buzzer