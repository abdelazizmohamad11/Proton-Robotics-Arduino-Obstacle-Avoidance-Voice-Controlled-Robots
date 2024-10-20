unsigned long startTime = 0;  // Variable to store the start time of the timer
unsigned long elapsedTime = 0;  // Variable to store the elapsed time
unsigned long duration = 0;  // Variable to store the desired duration of the timer
bool timerRunning = false;  // Flag to indicate whether the timer is running

void startTimer(unsigned long _duration, char unit) {
  if (unit == 's') {
    duration = _duration * 1000;  // Convert seconds to milliseconds
  } else if (unit == 'm') {
    duration = _duration * 60000;  // Convert minutes to milliseconds
  } else if (unit == 'h') {
    duration = _duration * 3600000;  // Convert hours to milliseconds
  } else {
    Serial.println("Invalid time unit. Please use 's' for seconds, 'm' for minutes, or 'h' for hours.");
    return;
  }
  startTime = millis();
  timerRunning = true;

}

void resetTimer() {
  timerRunning = false;
  Serial.println("Timer reset!");
}
