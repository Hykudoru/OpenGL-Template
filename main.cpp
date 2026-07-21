#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Vector.h"
#include "Matrix.h"
#include "Transform.h"

using namespace std;

GLFWwindow* window;

static GLuint SetupShaders(string vertexPath, string fragPath) {

    ifstream vertFile(vertexPath);
    ifstream fragFile(fragPath);
    stringstream vertStream;
    stringstream fragStream;
    vertStream << vertFile.rdbuf();
    fragStream << fragFile.rdbuf();
    const char* vertexShaderSource = vertStream.str().c_str();
    const char* fragmentShaderSource = fragStream.str().c_str();

    // Create a vertex shader object and specify it as a vertex shader type
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach the vertex shader source code to the vertex shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile the vertex shader to convert the source code into machine-readable instructions
    glCompileShader(vertexShader);

    // Create a fragment shader object and specify it as a fragment shader type
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach the fragment shader source code to the fragment shader object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compile the fragment shader to convert the source code into machine-readable instructions
    glCompileShader(fragmentShader);


    if (vertexShader == 0 || fragmentShader == 0) {
        cerr << "Shader compilation produced invalid handles!" << endl;
    }

    // Create a shader program to link the compiled shaders together
    GLuint shaderProgram = glCreateProgram();

    // Attach the compiled vertex shader to the shader program
    glAttachShader(shaderProgram, vertexShader);

    // Attach the compiled fragment shader to the shader program
    glAttachShader(shaderProgram, fragmentShader);

    // Link the shaders in the program, combining them into an executable for the GPU
    glLinkProgram(shaderProgram);

    // Delete the vertex shader object, as it is no longer needed after linking
    glDeleteShader(vertexShader);

    // Delete the fragment shader object, as it is no longer needed after linking
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

Matrix4x4 projection = {{
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, -0.1, -0.1},
    {0, 0, -1, 0}
}};

float points[] = {
    // Front Face               rgb
    -0.5f, -0.5f, 0.5f,     1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,      1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f,       1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,     1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f,       1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f,      1.0f, 0.0f, 0.0f,

    // Right Face
    0.5f, -0.5f, 0.5f,      0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f,       0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f,      0.0f, 1.0f, 0.0f,    
    0.5f, -0.5f, 0.5f,      0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f,      0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,     0.0f, 1.0f, 0.0f,

    // Back Face 
    0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f,      0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f,     0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f,     0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,

    // Left Face
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f,     0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,      0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,      0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 1.0f,

    // Top face
    -0.5f, 0.5f, 0.5f,      0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f,     0.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f,      0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,      0.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f,      0.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f,       0.0f, 1.0f, 1.0f,

    // Bottom face
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f,      0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f,      0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,     0.0f, 1.0f, 1.0f,
};


GLuint VAO, VBO;

void setupCube() {
    // Generate buffer on gpu
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // bind buffer before using
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // assign data in that buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);    

    // attributes (describe the layout of our data)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(3*sizeof(float)));

    // unbind everything
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

int main() 
{
    if (!glfwInit()) return -1;

    // Request OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 800, "Modern OpenGL with Custom Matrix", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cerr << "Failed to initialize GLAD" << endl;
        return -1;
    }

    cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    
    // Check window visibility
    int visible = glfwGetWindowAttrib(window, GLFW_VISIBLE);
    cout << "Window visible: " << visible << endl;

    glViewport(0, 0, 800, 800);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GLuint shader = SetupShaders("vertexShader.glsl", "fragmentShader.glsl");
    setupCube(); // ALLOCATE DATA ON GPU

    vector<Transform> transforms {
        Transform(Vec3(0, 0, -10), 1.0f),
        Transform(Vec3(2, 0, -10), 1.0f),
        Transform(Vec3(4, 0, -10), 0.5f),
    };

    // Game Loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        for (int i = 0; i < transforms.size(); i++)
        {
            Transform& t = transforms[i];
            if (i == 0) {
                t.rotation =  Matrix3x3::RotY((360*3.1415f/180)*0.002) * t.rotation;
                t.position += Vec3(0.01, 0, 0);
            }
            Matrix4x4 model = t.TRS();
        
            // Render()
            glUseProgram(shader);
            GLuint modelLocation = glGetUniformLocation(shader, "model");
            GLuint projLocation = glGetUniformLocation(shader, "projection");
            glUniformMatrix4fv(modelLocation, 1, true, &model.m[0][0]);
            glUniformMatrix4fv(projLocation, 1, true, &projection.m[0][0]);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}








