#include <vector>
#include "point.hpp"

struct individual
{
    float score;

    // Gene
    float X1; // First locus
};

#define SAMPLE_SIZE 2000
#define HI  1.0
#define LO -1.0
#define RADIATION 0.08

#define BALL_RADIUS 0.01

class Individuals
{
public:
Individuals(float (*a_func)(float))
{
    eval_func = a_func;

    /*SHADERS*/

    //Vertex shader
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec2 aPos;\n"
        "layout (location = 1) in vec2 center;\n"
        "out vec2 the_pos;\n"
        "out vec2 out_center;\n"
        "void main()\n"
        "{\n"
            "gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
            "out_center = center;\n"
            "the_pos = aPos;\n"
        "}\0";

    //Fragment Shader
    const char *fragmentShaderSource = "#version 330 core\n"
    "in vec2 the_pos;\n"
    "in vec2 center;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
        "//if ((pow(the_pos.x - center.x, 2) + pow(the_pos.y - center.y, 2)) < 0.05)\n"
            "FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
        "//else FragColor = vec4(0.0f);\n"
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
    
    //VBO
    glGenBuffers(1, &VBO);

    generation = 0;
    init_population();
}

~Individuals()
{}

unsigned int shaderProgram;
unsigned int VBO;
unsigned int VAO;
unsigned int generation;

float (*eval_func) (float);

individual individuals[10];

void elitism()
{
    int best_index = 0;
    float hi_score = individuals[0].score;

    for (int i = 1; i < 10; ++i)
    {
        if (individuals[i].score > hi_score)
        {
            hi_score = individuals[i].score;
            best_index = i;
        }
    }

    printf("Best individual: %d -> %f\n", best_index, hi_score);

    for (int i = 0; i < 10; ++i)
    {
        if (i == best_index) continue;
        //Crossover
        individuals[i].X1 += individuals[best_index].X1;
        individuals[i].X1 /= 2.0;

        //Mutation
        const float mutation = LO +
            static_cast <float> (rand()) /
            (static_cast <float> (RAND_MAX/(HI-LO)));
        
        printf("Mutation is: %f\n", mutation);
        individuals[i].X1 += mutation * RADIATION;

        //Clipping
        if (individuals[i].X1 < LO) individuals[i].X1 = LO;
        else if (individuals[i].X1 > HI) individuals[i].X1 = HI;
    }
}

void evaluate()
{
    for (int i = 0; i < 10; ++i)
    {
        individuals[i].score = eval_func(individuals[i].X1);
        printf("Ind[%d]: %f -> %f\n", i, individuals[i].X1, individuals[i].score);
    }
}

void init_population()
{
    // Randomly init the population
    for (int i = 0; i < 10; ++i)
    {
        individuals[i].X1 = //LO + ((float) i * (HI-LO));
        (LO +
            static_cast <float> (rand()) /
            (static_cast <float> (RAND_MAX/(HI-LO))));
    }
    evaluate(); //First evaluation
    gen_buffers();
}

void run_ga() //One iteration for genetic algorithm.
{
    printf("Generation %d\n", generation);
    elitism(); //Based on last evaluation, spread genes across the population.
    evaluate();

    generation++;
}

std::vector<float> vtx_attribs;

void gen_buffers()
{
    //Grab scores and pass to gpu.
    vtx_attribs.clear();

    //X Y X_c Y_c
    for (int i = 0; i < 10; ++i)
    {
        float c_x = individuals[i].X1;
        float c_y = individuals[i].score;

        //First triangle
        vtx_attribs.push_back(c_x - BALL_RADIUS); //Upper left
        vtx_attribs.push_back(c_y + BALL_RADIUS);
        vtx_attribs.push_back(c_x); //This is the center
        vtx_attribs.push_back(c_y);

        vtx_attribs.push_back(c_x - BALL_RADIUS); //Lower left
        vtx_attribs.push_back(c_y - BALL_RADIUS);
        vtx_attribs.push_back(c_x); //This is the center
        vtx_attribs.push_back(c_y);

        vtx_attribs.push_back(c_x + BALL_RADIUS); //Lower Right
        vtx_attribs.push_back(c_y - BALL_RADIUS);
        vtx_attribs.push_back(c_x); //This is the center
        vtx_attribs.push_back(c_y);

        //Second triangle
        vtx_attribs.push_back(c_x - BALL_RADIUS); //Upper left
        vtx_attribs.push_back(c_y + BALL_RADIUS);
        vtx_attribs.push_back(c_x); //This is the center
        vtx_attribs.push_back(c_y);

        vtx_attribs.push_back(c_x + BALL_RADIUS); //Upper right
        vtx_attribs.push_back(c_y + BALL_RADIUS);
        vtx_attribs.push_back(c_x); //This is the center
        vtx_attribs.push_back(c_y);

        vtx_attribs.push_back(c_x + BALL_RADIUS); //Lower right
        vtx_attribs.push_back(c_y - BALL_RADIUS);
        vtx_attribs.push_back(c_x); //This is the center
        vtx_attribs.push_back(c_y);
    }

    //After generating all points, pass it to the GPU.
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
            vtx_attribs.size() * sizeof(float),
            &vtx_attribs[0],
            GL_STATIC_DRAW);

    //LINKING VERTEX ATTRIBUTES
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2* sizeof(float)));
    glEnableVertexAttribArray(1);
}

void draw()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 10 * 2 * 3);
}
};