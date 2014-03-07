/* Methods relating to the system timer */

/* Waits for the specified number of microseconds */
void Wait(unsigned int delayInMicroSeconds);

/* Gets the address of the system timer */
void* GetSystemTimerBase();

/* Gets the current timestamp of the system timer */
unsigned long long GetTimeStamp();