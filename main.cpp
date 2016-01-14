#include <GL/glut.h>
#include <stdbool.h>

#include <memory>

#include "analogue_clock.h"
#include "controls.h"
#include "digital_clock.h"

bool showMenu = false;
bool showDate = false;

// Default to analogue clock
std::unique_ptr<Clock> runningClock = std::make_unique<AnalogueClock>();

void clock(int x) {
    cameraInit();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!showMenu) {
        runningClock->display(showDate);
        drawMenuPrompt();
    } else {
        drawMenu();
    }

    glutSwapBuffers();
    glutTimerFunc(1, clock, 0);
}

void toggleClockType() {
    if (typeid(*runningClock) == typeid(AnalogueClock)) {
        runningClock = std::make_unique<DigitalClock>();
    } else {
        runningClock = std::make_unique<AnalogueClock>();
    }
}

void setDisplay() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    clock(0);
}

void setDefaultValues() {
    runningClock->reset();
    cameraReset();
}

ButtonType getButtonUnderMouse(int x, int y) {
    const float* buttonBounds = runningClock->getButtonPositions();
    Coordinate<double> mouseCoordinate = getMouseCoordinate(x, y);

    if (mouseCoordinate.y >= buttonBounds[6] &&
        mouseCoordinate.y <= buttonBounds[7] &&
        mouseCoordinate.z <= buttonBounds[8] &&
        mouseCoordinate.z >= buttonBounds[9]) {
        if (mouseCoordinate.x >= buttonBounds[0] &&
            mouseCoordinate.x <= buttonBounds[1]) {
            return RESET_BUTTON;
        } else if (mouseCoordinate.x >= buttonBounds[2] &&
                   mouseCoordinate.x <= buttonBounds[3]) {
            return MODE_BUTTON;
        } else if (mouseCoordinate.x >= buttonBounds[4] &&
                   mouseCoordinate.x <= buttonBounds[5]) {
            return START_STOP_BUTTON;
        }
    }

    return NO_BUTTON;
}

void readMouseMove(int x, int y) {
    if (getButtonUnderMouse(x, y) == NO_BUTTON) {
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    } else {
        glutSetCursor(GLUT_CURSOR_INFO);
    }
}

void readMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        switch (getButtonUnderMouse(x, y)) {
            case RESET_BUTTON:
                if (isStopwatch) runningClock->resetButtonPressed();
                break;
            case MODE_BUTTON:
                isStopwatch = !isStopwatch;
                runningClock->modeButtonPressed();
                break;
            case START_STOP_BUTTON:
                if (isStopwatch) runningClock->startButtonPressed();
                break;
            default:
                break;
        }
    }
}

void readKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'd':
            showDate = !showDate;
            break;
        case 'm':
            showMenu = !showMenu;
            break;
        case 'q':
            exit(1);
        case 'r':
            setDefaultValues();
            break;
        case 't':
            toggleClockType();
            break;
        case '+':
            cameraZoomIn();
            break;
        case '-':
            cameraZoomOut();
            break;
        default:
            runningClock->checkKeyPress(key);
            break;
    }
}

void readSpecialKeys(int key, int x, int y) {
    switch (key) {
        // Camera controls
        case GLUT_KEY_RIGHT:
            cameraMoveRight();
            break;
        case GLUT_KEY_LEFT:
            cameraMoveLeft();
            break;
        case GLUT_KEY_UP:
            cameraMoveUp();
            break;
        case GLUT_KEY_DOWN:
            cameraMoveDown();
            break;
        case GLUT_KEY_PAGE_UP:
            cameraZoomIn();
            break;
        case GLUT_KEY_PAGE_DOWN:
            cameraZoomOut();
            break;
        case GLUT_KEY_HOME:
            cameraReset();
            break;
    }
}

int main(int argc, char* argv[]) {
    const int windowWidth = 800;
    const int windowHeight = 600;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH |
                        GLUT_MULTISAMPLE);

    // Set window size and position
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - windowWidth) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - windowHeight) / 2);

    // Set window name
    glutCreateWindow("Clock");

    // Define app functions
    glutDisplayFunc(setDisplay);
    glutKeyboardFunc(readKeypress);
    glutSpecialFunc(readSpecialKeys);
    glutPassiveMotionFunc(readMouseMove);
    glutMouseFunc(readMouseClick);

    glutMainLoop();

    return 0;
}
