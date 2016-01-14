#ifndef DIGITAL_CLOCK_H
#define DIGITAL_CLOCK_H

#include <vector>

#include "button.h"
#include "clock.h"
#include "coordinate.h"

class DigitalClock : public Clock {
   public:
    float* getButtonPositions() override;

    void display(bool t_showDate) override;

    void checkKeyPress(unsigned char key) override;

    void reset() override;

   private:
    static const std::vector<Button> buttonList;

    static const Coordinate<float> frameVertices[28];

    static const float frameNormals[28][3];

    static const GLubyte frame[];

    static const Coordinate<float> buttonVertices[20];

    static const float buttonNormals[20][3];

    static const GLubyte button[];

    static const GLubyte surround[];

    static float buttonPositions[10];

    void drawButtons();

    void drawButton(const Button& t_button);

    void drawDigitalClock();

    void toggleHourMode();

    void buttonText();

    void drawDigitalClockFrame();
};

#endif
