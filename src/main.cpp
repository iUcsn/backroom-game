#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "ProceduralGenerator.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Crear ventana en modo OpenGL
    SDL_Window* window = SDL_CreateWindow("Backrooms Game",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (!window) {
        std::cerr << "Error al crear la ventana: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cerr << "Error al crear el contexto OpenGL: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Obtener el tamaño actual de la ventana
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    // Configurar la perspectiva con las dimensiones correctas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)windowWidth / (double)windowHeight, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Color de fondo
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Posición y orientación de la cámara
    float cameraX = 0.0f, cameraY = 1.8f, cameraZ = 0.0f;
    float pitch = 0.0f, yaw = 0.0f;
    float currentSpeed = 0.0f;
    float maxSpeed = 0.1f;
    float acceleration = 0.01f;
    float deceleration = 0.005f;
    float sensitivity = 0.005f;

    bool movingForward = false, movingBackward = false, movingLeft = false, movingRight = false;

    // Habilitar el modo relativo del ratón
    SDL_SetRelativeMouseMode(SDL_TRUE);

    // Inicializar el generador procedural
    ProceduralGenerator generator;
    generator.generateRooms(10, 20.0f, 10.0f, 20.0f);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_w:
                    movingForward = true;
                    break;
                case SDLK_s:
                    movingBackward = true;
                    break;
                case SDLK_a:
                    movingLeft = true;
                    break;
                case SDLK_d:
                    movingRight = true;
                    break;
                }
            }

            if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                case SDLK_w:
                    movingForward = false;
                    break;
                case SDLK_s:
                    movingBackward = false;
                    break;
                case SDLK_a:
                    movingLeft = false;
                    break;
                case SDLK_d:
                    movingRight = false;
                    break;
                }
            }

            if (event.type == SDL_MOUSEMOTION) {
                int xrel = event.motion.xrel;
                int yrel = event.motion.yrel;
                yaw += xrel * sensitivity;
                pitch += yrel * sensitivity;
                if (pitch > 1.5f) pitch = 1.5f;
                if (pitch < -1.5f) pitch = -1.5f;
            }
        }

        // Movimiento de la cámara
        if (movingForward || movingBackward || movingLeft || movingRight) {
            if (currentSpeed < maxSpeed) {
                currentSpeed += acceleration;
            }
        } else {
            if (currentSpeed > 0) {
                currentSpeed -= deceleration;
            }
        }

        if (movingForward) {
            cameraX += sin(yaw) * currentSpeed;
            cameraZ -= cos(yaw) * currentSpeed;
        }
        if (movingBackward) {
            cameraX -= sin(yaw) * currentSpeed;
            cameraZ += cos(yaw) * currentSpeed;
        }
        if (movingLeft) {
            cameraX -= cos(yaw) * currentSpeed;
            cameraZ -= sin(yaw) * currentSpeed;
        }
        if (movingRight) {
            cameraX += cos(yaw) * currentSpeed;
            cameraZ += sin(yaw) * currentSpeed;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glRotatef(pitch * 180.0f / M_PI, 1.0f, 0.0f, 0.0f);
        glRotatef(yaw * 180.0f / M_PI, 0.0f, 1.0f, 0.0f);
        glTranslatef(-cameraX, -cameraY, -cameraZ);

        generator.drawRooms();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
