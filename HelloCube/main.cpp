#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

static const char* vertexShaderSource = R"(
#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 color;
out vec3 fragmentColor;
void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    fragmentColor = color;
}
)";

static const char* fragmentShaderSource = R"(
#version 460 core
in vec3 fragmentColor;
out vec4 fragColor;
void main() {
    fragColor = vec4(fragmentColor, 1.0f);
}
)";

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, 0);

    GLFWwindow* window = glfwCreateWindow(600, 600, "Hello, Rectangle", NULL, NULL);
    if (window == NULL) {
        cout<<"Failed to create GLFW window"<<endl;
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window,
                       [](GLFWwindow *window, int key, int scancode, int action, int mods) {
                           if (key == GLFW_KEY_ESCAPE && action==GLFW_PRESS) {
                               glfwSetWindowShouldClose(window, GLFW_TRUE);
                           }
                       });

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);

    glViewport(0, 0, 600, 600);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glad_glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout<<" COMPILE FAILED!  "<< infoLog<<endl;
    } else {
        cout<<" COMPILE SUCCEEDED!"<<endl;
    }

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    int cube_indices[12 * 3] = {
            0, 3, 1,
            0, 3, 2,

            0, 5, 1,
            0, 5, 4,

            0, 6, 2,
            0, 6, 4,

            7, 1, 3,
            7, 1, 5,

            7, 2, 3,
            7, 2, 6,

            7, 4, 5,
            7, 4, 6
    };

    float vertices[12*3*3];
    for (int i=0; i<12*3; i++) {
        int index = cube_indices[i];
        for (int j=0; j<3; j++) {
            if (index & (1<<j)) {
                vertices[i*3 + j] = 0.5;
            } else {
                vertices[i*3 + j] = -0.5;
            }
        }
        cout<<vertices[i*3+0]<<" "<<vertices[i*3+1]<<" "<<vertices[i*3+2]<<endl;
    }

    float colors[12*3*3] = {
            0.0f, 0.5f, 0.5f,
            0.0f, 0.5f, 0.5f,
            0.0f, 0.5f, 0.5f,

            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,

            1.0f, 0.0f, 0.0,
            0.0f, 1.0f, 0.0,
            0.0f, 0.0f, 1.0,

            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,

            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,

            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.0,

            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,

            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
            0.5f, 0.5f, 0.5,
    };


    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Bind Layout 0 attribute.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    // Bind Layout 1 attribute.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(1);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe.
        glDrawArrays(GL_TRIANGLES, 0, 6*2*3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

