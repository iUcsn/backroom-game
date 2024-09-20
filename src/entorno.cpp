#include <GL/gl.h>
#include "entorno.h"

// Función para dibujar el suelo
void drawFloor() {
    glBegin(GL_QUADS);
        glColor3f(0.3f, 0.3f, 0.3f);  // Color gris para el suelo
        glVertex3f(-50.0f, 0.0f, -50.0f);  // Esquina inferior izquierda
        glVertex3f(50.0f, 0.0f, -50.0f);   // Esquina inferior derecha
        glVertex3f(50.0f, 0.0f, 50.0f);    // Esquina superior derecha
        glVertex3f(-50.0f, 0.0f, 50.0f);   // Esquina superior izquierda
    glEnd();
}

// Función para dibujar las paredes
void drawWalls() {
    // Pared trasera (frontal desde la perspectiva del personaje)
    glBegin(GL_QUADS);
        glColor3f(0.8f, 0.1f, 0.1f);  // Pared roja
        glVertex3f(-50.0f, 0.0f, -50.0f);
        glVertex3f(50.0f, 0.0f, -50.0f);
        glVertex3f(50.0f, 50.0f, -50.0f);  // Altura de 50 unidades
        glVertex3f(-50.0f, 50.0f, -50.0f);
    glEnd();

    // Pared derecha
    glBegin(GL_QUADS);
        glColor3f(0.1f, 0.8f, 0.1f);  // Pared verde
        glVertex3f(50.0f, 0.0f, -50.0f);
        glVertex3f(50.0f, 0.0f, 50.0f);
        glVertex3f(50.0f, 50.0f, 50.0f);
        glVertex3f(50.0f, 50.0f, -50.0f);
    glEnd();

    // Pared frontal
    glBegin(GL_QUADS);
        glColor3f(0.1f, 0.1f, 0.8f);  // Pared azul
        glVertex3f(-50.0f, 0.0f, 50.0f);
        glVertex3f(50.0f, 0.0f, 50.0f);
        glVertex3f(50.0f, 50.0f, 50.0f);
        glVertex3f(-50.0f, 50.0f, 50.0f);
    glEnd();

    // Pared izquierda
    glBegin(GL_QUADS);
        glColor3f(0.8f, 0.8f, 0.1f);  // Pared amarilla
        glVertex3f(-50.0f, 0.0f, -50.0f);
        glVertex3f(-50.0f, 0.0f, 50.0f);
        glVertex3f(-50.0f, 50.0f, 50.0f);
        glVertex3f(-50.0f, 50.0f, -50.0f);
    glEnd();
}

// Función para dibujar el techo
void drawCeiling() {
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.5f, 1.0f);  // Techo de color azul claro
        glVertex3f(-50.0f, 50.0f, -50.0f);  // Esquina inferior izquierda
        glVertex3f(50.0f, 50.0f, -50.0f);   // Esquina inferior derecha
        glVertex3f(50.0f, 50.0f, 50.0f);    // Esquina superior derecha
        glVertex3f(-50.0f, 50.0f, 50.0f);   // Esquina superior izquierda
    glEnd();
}
