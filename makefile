# by default select gcc
CXX=g++
CXXFLAGS= -lGL -lGLU -lglut -I/mnt/c/Users/xiaohe.niu/Libraries/glm-master/
# for error checking, use: -fsanitize=address

.SUFFIXES: .cpp

all: cubeAnimation.o

cubeAnimation.o:
	${CXX} main.cpp src/*.cpp -o cubeAnimation.o ${CXXFLAGS}

clean:
	rm -f cubeAnimation.o
