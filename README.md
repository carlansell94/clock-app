A simple clock application built using C++ and OpenGL.

Features:
* Analogue and digital clock modes
* Time and stopwatch modes
* Clickable controls on each clock model
* Date display option
* Configurable clock styles

Pressing the 'm' key on launching the application will provide a list of the controls and configuration options available.

## How to Build
A Makefile is included to build the app. Simply run

```
make
```

in the project directory, and the application should build successfully.

Math, OpenGL and PNG libraries are required for compilation, as is the g++ compiler. This app is targeted at C++14.

## Analogue Clock Textures
Textures used for the analogue clock can be found in /images. A GIMP template is included to allow you to make your own, though you'll also need to add an entry to AnalogueClock::textures (found in analogue_clock.cpp) to reference any added images.

## Screenshots
Analogue clock, running in time mode:

![Analogue clock](analogue.webp?raw=true "Analogue clock")

Digital clock, running in stopwatch mode:

![Digital clock](digital.webp?raw=true "Digital clock")