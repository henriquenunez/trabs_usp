#include <iostream>
#include <chrono>
#include <thread>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>

#include "points.hpp"
#include "individuals.hpp"

#include <cstdlib>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

//Fragment Shader
const char *fragmentShaderSource_pizza = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 myColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0);//myColor;"
"}\0";

/*Defining a simple triangle*/

float triangle_vertexes[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

/* Now, defining a pizza*/

float pizza[] =
{
        0.0f,     0.0f, 0.0f,
        0.8f,     0.0f, 0.0f,
     0.5657f,  0.5657f, 0.0f,
        0.0f,     0.8f, 0.0f,
    -0.5657f,  0.5657f, 0.0f,
       -0.8f,     0.0f, 0.0f,
    -0.5657f, -0.5657f, 0.0f,
        0.0f,    -0.8f, 0.0f,
     0.5657f, -0.5657f, 0.0f
};

unsigned int pizza_idx[] = 
{
    0, 1, 2,
    0, 2, 3,
    0, 3, 4,
    0, 4, 5,
    0, 5, 6,
    0, 6, 7,
    0, 7, 8,
    0, 8, 1
};

enum
{
    TRIANGLE,
    PIZZA
} fig_type = TRIANGLE;

inline float func(float x)
{
    if (x > 0)
        return -x;
    else
        return x;
}

inline float crazy_func(float x)
{
    x *= 1000;
    return ((2*cos(0.039*x) + 5*sin(0.05*x) + 0.5*cos(0.01*x) + 10*sin(0.07*x) + 5*sin(0.1*x) + 5*sin(0.035*x)) * 10 + 500) / (275 + 500);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //WINDOW CREATION
    GLFWwindow* window = glfwCreateWindow(800, 600, "Trianglin", NULL, NULL);

    if (window == NULL)
    {
	std::cout << "Failed to initialize GLFW" << std::endl;
	glfwTerminate();
	return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glViewport(0, 0, 800, 600);

    // Points object
    //points z_points(func);
    points z_points(crazy_func);

    // Samples object
    //Individuals guesses(func);
    Individuals guesses(crazy_func);

    std::chrono::milliseconds timespan(2000); // or whatever
    //std::chrono::milliseconds timespan(50); // or whatever

    //EVENT LOOP
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        z_points.draw();

        guesses.draw();
        guesses.run_ga();
        guesses.gen_buffers();

    	glfwSwapBuffers(window);
        glfwPollEvents();

        //sleep(2);
        std::this_thread::sleep_for(timespan);
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	    glfwSetWindowShouldClose(window, true);
    else if(glfwGetKey(window, GLFW_KEY_F1))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else if(glfwGetKey(window, GLFW_KEY_F2))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else if(glfwGetKey(window, GLFW_KEY_F3))
        fig_type = TRIANGLE;
    else if(glfwGetKey(window, GLFW_KEY_F4))
        fig_type = PIZZA;
}

