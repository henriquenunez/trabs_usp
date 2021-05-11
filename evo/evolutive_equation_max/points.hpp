#include "point.hpp"

#define SAMPLE_SIZE 2000

class points
{
public:
    points(float (*a_func)(float))
    {
        eval_func = a_func;

        /*SHADERS*/

        //Vertex shader
        const char *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec2 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
            "}\0";

        //Fragment Shader
        const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);"
        "}\0";

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
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "FRAGMENT SHADER COMPILATION FAILED\n" << infoLog << std::endl;
        }

        //Shader Program
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

        //Now, time to use our VAO, so the process is not *cumbersome*
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        Point graph[SAMPLE_SIZE];
        
        for (int i = 0; i < SAMPLE_SIZE ; i++)
        {
          float x = (i - 1000.0) / 100.0;
          graph[i].x = x;
          graph[i].y = eval_func(x);
        }

        //VBO
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
                SAMPLE_SIZE * sizeof(Point),
                graph,
                GL_STATIC_DRAW);

        //LINKING VERTEX ATTRIBUTES
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
        glEnableVertexAttribArray(0);
    }
    
    ~points()
    {}

    unsigned int shaderProgram;
    unsigned int VBO;
    unsigned int VAO;
    float (*eval_func) (float);

    void draw()
    {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 0, SAMPLE_SIZE);
    }
    
};