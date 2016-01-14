#include "time.h"

#include <sys/time.h>

#include <iomanip>
#include <iostream>
#include <string>

bool isAfternoon = false;
bool stopwatchIsRunning = false;
bool isStopwatch;
struct timeval startTime, currentTime, result, pauseTime;
unsigned int min, sec, ms;

tm* getCurrentTime() {
    time_t t = time(NULL);
    struct tm* ltime = localtime(&t);

    if (ltime->tm_hour >= 12) {
        isAfternoon = true;
    } else {
        isAfternoon = false;
    }

    return ltime;
}

std::string getCurrentTimeString(bool t_24hour = false) {
    char timeString[7];
    struct tm* ltime = getCurrentTime();

    if (t_24hour) {
        strftime(timeString, 7, "%H%M%S", ltime);
    } else {
        strftime(timeString, 7, "%I%M%S", ltime);
    }

    return timeString;
}

void addInterval(const struct timeval& t1, const struct timeval& t2,
                 struct timeval* totalTime) {
    totalTime->tv_usec = t2.tv_usec + t1.tv_usec;
    totalTime->tv_sec = t2.tv_sec + t1.tv_sec;
    if (totalTime->tv_usec >= 1000000) {
        totalTime->tv_usec -= 1000000;
        totalTime->tv_sec++;
    }
};

void disableStopwatch() { stopwatchIsRunning = false; }

void toggleStopwatch() {
    stopwatchIsRunning = !stopwatchIsRunning;

    if (stopwatchIsRunning) {
        gettimeofday(&startTime, 0);
    } else {
        addInterval(result, pauseTime, &pauseTime);
    }
}

void updateStopwatchTime() {
    struct timeval totalTime;

    gettimeofday(&currentTime, 0);
    timersub(&currentTime, &startTime, &result);
    addInterval(result, pauseTime, &totalTime);
    min = totalTime.tv_sec / 60;
    sec = (totalTime.tv_sec + (totalTime.tv_usec / 1000000)) % 60;
    ms = totalTime.tv_usec / 10000;
}

std::string getDateString() {
    struct tm* t_time = getCurrentTime();
    char dateString[28];

    strftime(dateString, 28, "%A %d %B %G", t_time);

    return dateString;
}

std::string getStopwatchTimeString() {
    std::string timeString;

    if (stopwatchIsRunning) {
        updateStopwatchTime();
    }

    // Maximum stopwatch display of 59:59:99
    if (min > 59) {
        timeString = std::to_string(595999);
    }

    else {
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << min << std::setfill('0')
            << std::setw(2) << sec << std::setfill('0') << std::setw(2) << ms;
        timeString = oss.str();
    }

    return timeString;
}

void resetStopwatch() {
    min = 0;
    sec = 0;
    ms = 0;
    pauseTime = {0, 0};
}
