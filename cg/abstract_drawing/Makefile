CXX=g++
CXXFLAGS=-g

LDFLAGS=-fsanitize=address #-lstdc++

#GLFW STUFF
GL_DIR=$(shell pwd)/../GL

GL_INCLUDE_DIR=${GL_DIR}/include
GL_LIBS_DIR=${GL_DIR}/src

#BUILD
BUILD_DIR=./build

CXXFLAGS += -I${GL_INCLUDE_DIR}
LDFLAGS += -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -L${GL_LIBS_DIR}

all: build_dir
	${CXX} main.cpp glad.c ${CXXFLAGS} -o ${BUILD_DIR}/main ${LDFLAGS}

build_dir:
	mkdir ${BUILD_DIR} || true

run:
	${BUILD_DIR}/main

clean:
	rm -rf ${BUILD_DIR} || true

