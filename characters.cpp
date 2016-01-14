#include <GL/glut.h>

#include <string>
#include <vector>

float textSpacing = 0.03f;

float letterPoints[20][2] = {
    // Define all points used to draw characters
    {-0.01f, 0.01f},  {-0.01f, 0.005f}, {-0.01f, 0.0f},   {-0.01f, -0.005f},
    {-0.01f, -0.01f}, {-0.005f, 0.01f}, {-0.005f, 0.0f},  {-0.005f, -0.01f},
    {0.0f, 0.01f},    {0.0f, 0.0f},     {0.0f, -0.005f},  {0.0f, -0.01f},
    {0.005f, 0.01f},  {0.005f, 0.0f},   {0.005f, -0.01f}, {0.01f, 0.01f},
    {0.01f, 0.005f},  {0.01f, 0.0f},    {0.01f, -0.005f}, {0.01f, -0.01f},
};

std::vector<GLubyte> letters[26] = {
    {4, 8, 19, 13, 6},                     // a
    {0, 4, 14, 18, 13, 16, 12, 0, 13, 2},  // b
    {16, 12, 5, 1, 3, 7, 14, 18, 17, 9},   // c
    {0, 4, 14, 18, 16, 12, 0},             // d
    {15, 0, 2, 17, 2, 4, 19},              // e
    {15, 0, 4, 19, 2, 17},                 // f
    {16, 12, 5, 1, 3, 7, 14, 18, 17, 9},   // g
    {0, 4, 2, 17, 15, 19},                 // h
    {0, 8, 15, 8, 11, 19, 4},              // i
    {12, 15, 18, 14, 7, 3},                // j
    {0, 3, 11, 3, 19, 3, 4},               // k
    {0, 4, 19},                            // l
    {4, 0, 9, 15, 19},                     // m
    {4, 0, 19, 15},                        // n
    {1, 5, 12, 16, 18, 14, 7, 3, 1},       // o
    {4, 0, 12, 16, 13, 2, 0, 4},           // p
    {0},                                   // q
    {4, 0, 12, 16, 13, 2, 19},             // r
    {15, 5, 1, 6, 13, 18, 14, 4},          // s
    {0, 8, 15, 8, 11},                     // t
    {0, 3, 7, 14, 18, 15},                 // u
    {0, 11, 15},                           // v
    {0, 4, 9, 19, 15},                     // w
    {0},                                   // x
    {0, 9, 15, 9, 11},                     // y
    {0}                                    // z
};

std::vector<GLubyte> numbers[10] = {
    {5, 1, 3, 7, 14, 18, 16, 12, 5},             // 0
    {2, 8, 11, 4, 19},                           // 1
    {1, 8, 12, 16, 4, 19},                       // 2
    {1, 8, 16, 13, 9, 13, 18, 11, 3},            // 3
    {11, 8, 2, 17},                              // 4
    {15, 0, 2, 13, 18, 14, 4},                   // 5
    {12, 5, 1, 3, 7, 14, 18, 13, 6, 3},          // 6
    {0, 15, 4},                                  // 7
    {18, 11, 3, 16, 8, 1, 18},                   // 8
    {12, 5, 1, 6, 13, 16, 12, 16, 18, 14, 7, 3}  // 9
};

void drawLetter(char t_char) {
    int number = (int)t_char - 97;
    if (number < 0) {
        number += 32;
    }
    glDrawElements(GL_LINE_STRIP, letters[number].size(), GL_UNSIGNED_BYTE,
                   letters[number].data());
};

void drawNumber(char t_char) {
    int number = (int)t_char - 48;
    glDrawElements(GL_LINE_STRIP, numbers[number].size(), GL_UNSIGNED_BYTE,
                   numbers[number].data());
}

void drawString(const std::string& t_string) {
    for (const char& character : t_string) {
        if (isdigit(character)) {
            drawNumber(character);
        } else if (character != ' ') {
            drawLetter(character);
        }
        glTranslatef(textSpacing, 0.0f, 0.0f);
    }
};
