// Range finder header file

void range_init();

extern volatile unsigned char changed; // Flag for Range Finder
extern volatile unsigned char complete; // Flag for Range Finder (Indicating Measurement was captured)
extern volatile unsigned long long int pulse_count; // Used to capture Range Finder Count
extern volatile unsigned char threshhold; // 0 is when Threshhold is set to near, 1 when far