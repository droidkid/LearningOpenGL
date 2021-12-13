#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

using namespace std;

static const char* vertexShaderSource = R"(
#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 color;
uniform mat4 mvp;

out vec3 fragmentColor;
void main() {
    gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
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

    GLFWwindow* window = glfwCreateWindow(1024, 768, "Hello, Rectangle", NULL, NULL);
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

    //glViewport(0, 0, 600, 600);
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
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,

            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,

            0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f,

            1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f,

            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,

            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
    };

    // Bind Layout 0 attribute.
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // Bind Layout 1 attribute.
    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(1);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f/3.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 rotationAxis = glm::vec3(1.0, 0, 0);
    glm::mat4 rotationMat = glm::mat4(1.0f);
    rotationMat = glm::rotate( model, 45.0f, rotationAxis);

    GLuint matrixId = glGetUniformLocation(shaderProgram, "mvp");
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glUseProgram(shaderProgram);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rotationMat = glm::rotate( model, 360.0f * glm::sin((float)glfwGetTime() / 100.0f), rotationAxis);
    glm::mat4 mvp = projection * view * rotationMat * model;
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6*2*3);
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe.
        rotationMat = glm::rotate( model, 360.0f * glm::sin((float)glfwGetTime() / 100.0f), rotationAxis);
        glm::mat4 mvp = projection * view * rotationMat * model;
        glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, 6*2*3);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

