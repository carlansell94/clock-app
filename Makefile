LIBDIRS = -L/usr/X11R6/lib
LDLIBS = -lglut -lGL -lGLU -lX11 -lm -lpng

CPPFLAGS = -O3 -std=c++14 -Wall
LDFLAGS = $(LIBDIRS)

CXX = g++
SRCS =  characters.cpp materials.cpp time.cpp analogue_clock.cpp digital_clock.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

clock: $(OBJS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

