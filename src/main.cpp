#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <cmath>
#include "entorno.h"  // Incluir el header del entorno

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
    float cameraX = 0.0f, cameraY = 1.8f, cameraZ = 0.0f; // Cámara en el centro del cubo, altura de 1.8
    float pitch = 0.0f, yaw = 0.0f;
    float speed = 0.1f;  // Aumentar un poco la velocidad para pruebas
    float sensitivity = 0.005f;  // Aumentar sensibilidad para pruebas

    // Habilitar el modo relativo del ratón
    SDL_SetRelativeMouseMode(SDL_TRUE);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            // Si se cambia el tamaño de la ventana, ajustamos el viewport y la perspectiva
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
                SDL_GetWindowSize(window, &windowWidth, &windowHeight);
                glViewport(0, 0, windowWidth, windowHeight);
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluPerspective(45.0, (double)windowWidth / (double)windowHeight, 0.1, 1000.0);
                glMatrixMode(GL_MODELVIEW);
            }

            // Procesar eventos de teclado para el movimiento de la cámara
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_w:  // Mover hacia adelante
                    cameraX += sin(yaw) * speed;
                    cameraZ -= cos(yaw) * speed;
                    break;
                case SDLK_s:  // Mover hacia atrás
                    cameraX -= sin(yaw) * speed;
                    cameraZ += cos(yaw) * speed;
                    break;
                case SDLK_a:  // Mover hacia la izquierda
                    cameraX -= cos(yaw) * speed;
                    cameraZ -= sin(yaw) * speed;
                    break;
                case SDLK_d:  // Mover hacia la derecha
                    cameraX += cos(yaw) * speed;
                    cameraZ += sin(yaw) * speed;
                    break;
                }
            }

            // Procesar movimiento del ratón para ajustar la rotación de la cámara
            if (event.type == SDL_MOUSEMOTION) {
                int xrel = event.motion.xrel;  // Movimiento relativo en X
                int yrel = event.motion.yrel;  // Movimiento relativo en Y

                yaw += xrel * sensitivity;
                pitch += yrel * sensitivity;  // Invertimos el signo para corregir la rotación vertical

                // Limitar la rotación vertical para evitar voltear completamente
                if (pitch > 1.5f) pitch = 1.5f;
                if (pitch < -1.5f) pitch = -1.5f;
            }
        }

        // Limpiar pantalla y buffer de profundidad
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Aplicar transformaciones de la cámara
        glLoadIdentity();
        glRotatef(pitch * 180.0f / M_PI, 1.0f, 0.0f, 0.0f);  // Inclinación (Pitch)
        glRotatef(yaw * 180.0f / M_PI, 0.0f, 1.0f, 0.0f);    // Rotación horizontal (Yaw)
        glTranslatef(-cameraX, -cameraY, -cameraZ);  // Trasladar la cámara

        // Dibujar el entorno
        drawFloor();
        drawWalls();
        drawCeiling();  // Dibujar el techo

        SDL_GL_SwapWindow(window);
    }

    // Limpiar recursos
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
