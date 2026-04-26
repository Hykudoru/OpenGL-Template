#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// g++ src/glad.c main.cpp -o myapp.exe -Iinclude  -L"C:/Users/Hykudo/Documents/Stuff/OpenGL/lib" -lglfw3 -lopengl32 -lgdi32
// VS Code: Compile: Ctrl-Shift-B. Run using F5
#include <vector>

using namespace std;

GLFWwindow* window;

int main() 
{
    if (!glfwInit()) return -1;

    window = glfwCreateWindow(800, 800, "OpenGL Window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Game Loop 
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0, 0, 0, 1.0f);
        //glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);

        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}