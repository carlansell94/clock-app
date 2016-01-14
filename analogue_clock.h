#ifndef ANALOGUE_CLOCK_H
#define ANALOGUE_CLOCK_H

#include <array>
#include <vector>

#include "button.h"
#include "clock.h"
#include "clock_face_texture.h"
#include "coordinate.h"
#include "time.h"

class AnalogueClock : public Clock {
   public:
    float* getButtonPositions() override;

    void display(bool t_showDate) override;

    void checkKeyPress(unsigned char key) override;

    void reset() override;

   private:
    static const std::vector<Button> buttonList;

    static const Coordinate<float> buttonVertices[];

    static const std::array<ClockFaceTexture, 4> textures;

    void loadTexture();

    void cycleTexture();

    void changeHandWidth();

    void drawClockFaceMarkers();

    void drawClockFace();

    void drawTexturedClockFace();

    void drawButtons();

    void drawButton(const Button& t_button);
};

#endif
