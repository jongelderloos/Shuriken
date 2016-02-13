#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "engine.h"
#include "Table.h"

using namespace std;


//int main(int argc, char **argv)
int main()
{

  // OPENGL code
  /*
    GLenum error;

    printf("a");
    if(!glfwInit())
    {
        printf("Failed to init GLFW");
        return -1;
    }

    printf("b");
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, 0); //We don't want the old OpenGL 

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    printf("c");
    GLFWwindow* window;
    window = glfwCreateWindow(1024, 768, "Test Window", NULL, NULL);
    printf("d");
    if(window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }

    printf("1");
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        printf("Failed to init glew");
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    printf("2");
    
  if (glGenVertexArrays == NULL)
  {
    // chances are you don't have this feature...
    printf("DONT HAVE");
  }

    GLuint VertexArrayID;
  printf("2a");
    glGenVertexArrays(1, &VertexArrayID);
  printf("2b");
    glBindVertexArray(VertexArrayID);
  printf("2c");

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
   
    printf("3");
    
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint programID = LoadShaders("vertexShader.txt", "fragmentShader.txt");
    printf("before loop");
    do {
        glfwSwapBuffers(window);
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);
        printf("drawing stuff..");
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(0);
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    printf("after loop");

  */
  
  srand(time(0));

  Table gameTable;
  
  Engine myEngine(&gameTable);
  myEngine.init();

  myEngine.run(ENG_NORMAL);
  
  //glfwTerminate();

  return 0;
}

