#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <vector>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

#define CIRCLE_VTX_NUM 16

/*SHADERS*/

//Vertex shader
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 color;\n"
    "out vec3 a_color;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "a_color = color;\n"
    "}\0";

//Fragment Shader
const char *fragmentShaderSource = "#version 330 core\n"
"in vec3 a_color;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(a_color.x,a_color.y,a_color.z, 1.0f);"
"}\0";

struct vertex2d
{
    float x, y;

    vertex2d operator + (const vertex2d& _vertex)
    {
        vertex2d ret;

        ret.x = this->x + _vertex.x;
        ret.y = this->y + _vertex.y;

        return ret;
    }

    vertex2d operator / (float val)
    {
        vertex2d ret;

        ret.x = this->x / val;
        ret.y = this->y / val;

        return ret;
    }
};

void generateSierpinsky(vertex2d a, vertex2d b, vertex2d c, std::vector<float>& triangles_vec, int level, int *triangle_amount, int max)
{
    if (level == 0) return;

    vertex2d a_b_mean;
    vertex2d b_c_mean;
    vertex2d a_c_mean;

    a_b_mean = (a + b)/2;
    b_c_mean = (b + c)/2;
    a_c_mean = (a + c)/2;

    float color_x; //= ((float)level/(float)max);  // 1.0; 
    float color_y; //= (1.0);                     // 1.0; 
    float color_z; //= ((float)level/(float)max) * 0.8;  // 1.0;

    if (level % 2)
    {
        color_x = 1.0;
        color_y = 1.0;
        color_z = 1.0;
    }
    else
    {
        color_x = 0.0;
        color_y = 0.0;
        color_z = 0.0;
    }

    printf("Pushing: (%f, %f) (%f, %f) (%f, %f)\n", a_b_mean.x, a_b_mean.y, b_c_mean.x, b_c_mean.y, a_c_mean.x, a_c_mean.y);
    // Pushing back vertex info.
    (*triangle_amount)++;
    triangles_vec.push_back(a.x); triangles_vec.push_back(a.y); triangles_vec.push_back(-1.0 + (float)level/(float)10); //Cause we want positive z.
    triangles_vec.push_back(color_x); triangles_vec.push_back(color_y); triangles_vec.push_back(color_z);
    
    triangles_vec.push_back(b.x); triangles_vec.push_back(b.y); triangles_vec.push_back(-1.0 + (float)level/(float)10);
    triangles_vec.push_back(color_x); triangles_vec.push_back(color_y); triangles_vec.push_back(color_z);
    
    triangles_vec.push_back(c.x); triangles_vec.push_back(c.y); triangles_vec.push_back(-1.0 + (float)level/(float)10);
    triangles_vec.push_back(color_x); triangles_vec.push_back(color_y); triangles_vec.push_back(color_z);

    /*
    if (!(level % 2))
    {
        color_x = 1.0;
        color_y = 1.0;
        color_z = 1.0;
    }
    else
    {
        color_x = 0.0;
        color_y = 0.0;
        color_z = 0.0;
    }

    (*triangle_amount)++;
    triangles_vec.push_back(a_b_mean.x); triangles_vec.push_back(a_b_mean.y); triangles_vec.push_back(-1.0 + (float)level/(float)10 +0.1); //Cause we want positive z.
    triangles_vec.push_back(color_x); triangles_vec.push_back(color_y); triangles_vec.push_back(color_z);
    
    triangles_vec.push_back(b_c_mean.x); triangles_vec.push_back(b_c_mean.y); triangles_vec.push_back(-1.0 + (float)level/(float)10 + 0.1);
    triangles_vec.push_back(color_x); triangles_vec.push_back(color_y); triangles_vec.push_back(color_z);
    
    triangles_vec.push_back(a_c_mean.x); triangles_vec.push_back(a_c_mean.y); triangles_vec.push_back(-1.0 + (float)level/(float)10 + 0.1);
    triangles_vec.push_back(color_x); triangles_vec.push_back(color_y); triangles_vec.push_back(color_z);
    */

    
    // Generating recursively
    generateSierpinsky(a, a_b_mean, a_c_mean, triangles_vec, level-1, triangle_amount, max);
    generateSierpinsky(b, a_b_mean, b_c_mean, triangles_vec, level-1, triangle_amount, max);
    generateSierpinsky(c, b_c_mean, a_c_mean, triangles_vec, level-1, triangle_amount, max);
}

void generateCircle(std::vector<float> &attrib_vertex, float x_offset, float y_offset, float radius, int n_vertices)
{
    float angle = 0.0;
    for (int i = 0; i < n_vertices; ++i)
    {
        //Add
        attrib_vertex.push_back(x_offset + cos(angle) * radius); attrib_vertex.push_back(y_offset + sin(angle) * radius); attrib_vertex.push_back(0.0);
        attrib_vertex.push_back(1.0); attrib_vertex.push_back(0.2); attrib_vertex.push_back(1.0);

        angle += 2*M_PI/n_vertices;
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //WINDOW CREATION
    GLFWwindow* window = glfwCreateWindow(800, 600, "Abstract Drawing", NULL, NULL);

    if (window == NULL)
    {
	std::cout << "Failed to initialize GLFW" << std::endl;
	glfwTerminate();
	return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glViewport(0, 0, 800, 600);

    const GLubyte* vendor = glGetString(GL_VENDOR); // Returns the vendor
    const GLubyte* renderer = glGetString(GL_RENDERER); // Returns a hint to the model

    printf("%s\n", vendor);    
    printf("%s\n", renderer);

    //COMPILING SHADERS
    int shader_success;
    char infoLog[512];

    //Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS,  &shader_success);

    if(!shader_success)
    {
	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	std::cout << "VERTEX SHADER COMPILATION FAILED\n" << infoLog << std::endl;
    }

    //Fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &shader_success);

    if(!shader_success)
    {
	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	std::cout << "FRAGMENT SHADER COMPILATION FAILED\n" << infoLog << std::endl;
    }

    //Shader Program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shader_success);
    if(!shader_success)
    {
	    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	    std::cout << "LINKING SHADER PROGRAM FAILED\n" << infoLog << std::endl;
    }

    //Deleting shader objects since we dont need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //*************************************************************Sierpinsky triangle.
    std::vector<float> sierpinsky_triangle_attribs;
    int triangles_to_draw = 0;
    vertex2d a, b, c;
    a.x = -0.8; a.y = -0.8;
    b.x =  0.0; b.y =  0.8;
    c.x =  0.8; c.y = -0.8;
    generateSierpinsky(a, b, c, sierpinsky_triangle_attribs, 6, &triangles_to_draw, 6);

    //Now, time to use our VAO, so the process is not *cumbersome*
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
            sierpinsky_triangle_attribs.size() * sizeof(float),
            &sierpinsky_triangle_attribs[0],
            GL_STATIC_DRAW);

    //LINKING VERTEX ATTRIBUTES
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //******************************************************CIRCLES
    std::vector<float> circles;
    generateCircle(circles, 0.7, 0.7, 0.1, CIRCLE_VTX_NUM);

    //Now, time to use our VAO, so the process is not *cumbersome*
    unsigned int VAO_CIRCLE;
    glGenVertexArrays(1, &VAO_CIRCLE);
    glBindVertexArray(VAO_CIRCLE);

    //VBO
    unsigned int VBO_CIRCLE;
    glGenBuffers(1, &VBO_CIRCLE);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_CIRCLE);
    glBufferData(GL_ARRAY_BUFFER,
            circles.size() * sizeof(float),
            &circles[0],
            GL_STATIC_DRAW);

    //LINKING VERTEX ATTRIBUTES
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //****************************************************** LINES
    float lines_buf[] = {
       //X     Y    Z    R    G    B
        -0.9, -0.9, 0.0, 1.0, 0.0, 0.0,
         0.9, -0.9, 0.0, 1.0, 0.0, 0.0,
        
        -0.9, -0.8, 0.0, 1.0, 0.0, 0.0,
         0.9, -0.8, 0.0, 1.0, 0.0, 0.0,
        
        -0.9, -0.7, 0.0, 1.0, 0.0, 0.0,
         0.9, -0.7, 0.0, 1.0, 0.0, 0.0,
    };

    //Now, time to use our VAO, so the process is not *cumbersome*
    unsigned int VAO_LINES;
    glGenVertexArrays(1, &VAO_LINES);
    glBindVertexArray(VAO_LINES);

    //VBO
    unsigned int VBO_LINES;
    glGenBuffers(1, &VBO_LINES);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_LINES);
    glBufferData(GL_ARRAY_BUFFER,
            sizeof(lines_buf),
            lines_buf,
            GL_STATIC_DRAW);

    //LINKING VERTEX ATTRIBUTES
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //****************************************************** POINTS
    std::vector<float> points_buf;

    for (float i = -1.0; i < 1.0 ; i+= 0.1)
    {
        for (float j = -1.0; j < 1.0 ; j+= 0.1)
        {
            points_buf.push_back(i); points_buf.push_back(j); points_buf.push_back(0.5);
            points_buf.push_back(1.0); points_buf.push_back(0.2); points_buf.push_back(1.0);
        }
    }

    //Now, time to use our VAO, so the process is not *cumbersome*
    unsigned int VAO_POINTS;
    glGenVertexArrays(1, &VAO_POINTS);
    glBindVertexArray(VAO_POINTS);

    //VBO
    unsigned int VBO_POINTS;
    glGenBuffers(1, &VBO_POINTS);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_POINTS);
    glBufferData(GL_ARRAY_BUFFER,
            points_buf.size() * sizeof(float),
            &points_buf[0],
            GL_STATIC_DRAW);

    //LINKING VERTEX ATTRIBUTES
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //EVENT LOOP
    while(!glfwWindowShouldClose(window))
    { 
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Sierpinsky triangle
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, triangles_to_draw * 3);

        if (true) //Later i'll just leave the fractal.
        {
            glBindVertexArray(VAO_CIRCLE);
            glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_VTX_NUM);

            glBindVertexArray(VAO_LINES);
            glDrawArrays(GL_LINES, 0, 6);

            glBindVertexArray(VAO_POINTS);
            glDrawArrays(GL_POINTS, 0, points_buf.size()/6);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
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
}

