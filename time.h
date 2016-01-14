#ifndef TIME_H
#define TIME_H

#include <string>

extern bool isAfternoon;

extern bool stopwatchIsRunning;

extern bool isStopwatch;

std::string getStopwatchTimeString();

struct tm* getCurrentTime();

std::string getCurrentTimeString(bool t_24hour);

std::string getDateString();

void resetStopwatch();

void toggleStopwatch();

void disableStopwatch();

#endif
