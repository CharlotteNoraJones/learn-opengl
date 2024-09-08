#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const int WIDTH = 640;
const int HEIGHT = 480;

bool init();
void clean_up();

static void error_callback(int error, const char *description);
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

GLFWwindow *gWindow = nullptr;

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f};

int main(void)
{
    bool initSuccessful{init()};
    if (!initSuccessful)
        return -1;

    while (!glfwWindowShouldClose(gWindow))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(gWindow);
        glfwPollEvents();
    }

    clean_up();
    return 0;
}

bool init()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        fprintf(stderr, "Could not initialize GLFW\n");
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    gWindow = glfwCreateWindow(WIDTH, HEIGHT, "Trongle!", nullptr, nullptr);
    if (!gWindow)
    {
        glfwTerminate();
        gWindow = nullptr;
        fprintf(stderr, "Could not initialize GLFW gWindow\n");
        return false;
    }

    glfwMakeContextCurrent(gWindow);
    glfwSetFramebufferSizeCallback(gWindow, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to initialize GLAD\n");
        glfwDestroyWindow(gWindow);
        gWindow = nullptr;
        glfwTerminate();
        return false;
    }

    glViewport(0, 0, 640, 480);

    glfwSetKeyCallback(gWindow, key_callback);

    glfwSwapInterval(1);

    glfwSetWindowShouldClose(gWindow, GLFW_FALSE);

    return true;
}

void clean_up()
{
    glfwDestroyWindow(gWindow);
    gWindow = nullptr;
    glfwTerminate();
}

static void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
