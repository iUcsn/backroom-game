#include "Room.h"
#include <GL/gl.h>
#include <cstdlib>

// Constructor para inicializar la habitación con posición y dimensiones
Room::Room(float _x, float _y, float _z, float _width, float _height, float _depth) 
    : x(_x), y(_y), z(_z), width(_width), height(_height), depth(_depth) {}

// Función para dibujar el suelo, las paredes y el techo de la habitación
void Room::draw() {
    // Dibujar el suelo
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);  // Color gris para el suelo
    glVertex3f(x, y, z);
    glVertex3f(x + width, y, z);
    glVertex3f(x + width, y, z + depth);
    glVertex3f(x, y, z + depth);
    glEnd();

    // Dibujar las paredes
    // Pared frontal
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.1f, 0.1f);  // Color rojo
    glVertex3f(x, y, z);  // Esquina inferior izquierda
    glVertex3f(x + width, y, z);  // Esquina inferior derecha
    glVertex3f(x + width, y + height, z);  // Esquina superior derecha
    glVertex3f(x, y + height, z);  // Esquina superior izquierda
    glEnd();

    // Pared trasera
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.1f, 0.8f);  // Color azul
    glVertex3f(x, y, z + depth);  // Esquina inferior izquierda
    glVertex3f(x + width, y, z + depth);  // Esquina inferior derecha
    glVertex3f(x + width, y + height, z + depth);  // Esquina superior derecha
    glVertex3f(x, y + height, z + depth);  // Esquina superior izquierda
    glEnd();

    // Pared izquierda
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.8f, 0.1f);  // Color amarillo
    glVertex3f(x, y, z);  // Esquina inferior delantera izquierda
    glVertex3f(x, y, z + depth);  // Esquina inferior trasera izquierda
    glVertex3f(x, y + height, z + depth);  // Esquina superior trasera izquierda
    glVertex3f(x, y + height, z);  // Esquina superior delantera izquierda
    glEnd();

    // Pared derecha
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.8f, 0.1f);  // Color verde
    glVertex3f(x + width, y, z);  // Esquina inferior delantera derecha
    glVertex3f(x + width, y, z + depth);  // Esquina inferior trasera derecha
    glVertex3f(x + width, y + height, z + depth);  // Esquina superior trasera derecha
    glVertex3f(x + width, y + height, z);  // Esquina superior delantera derecha
    glEnd();

    // Dibujar el techo
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 1.0f);  // Color azul claro para el techo
    glVertex3f(x, y + height, z);  // Esquina inferior izquierda del techo
    glVertex3f(x + width, y + height, z);  // Esquina inferior derecha del techo
    glVertex3f(x + width, y + height, z + depth);  // Esquina superior derecha del techo
    glVertex3f(x, y + height, z + depth);  // Esquina superior izquierda del techo
    glEnd();
}

Room Room::generateRandom(float maxWidth, float maxHeight, float maxDepth) {
    float width = 10.0f + rand() % (int)(maxWidth - 10.0f);   // Entre 10 y maxWidth
    float height = 5.0f + rand() % (int)(maxHeight - 5.0f);   // Entre 5 y maxHeight
    float depth = 10.0f + rand() % (int)(maxDepth - 10.0f);   // Entre 10 y maxDepth

    // Posiciones aleatorias en un rango
    float x = rand() % 100;
    float z = rand() % 100;
    
    return Room(x, 0.0f, z, width, height, depth);
}

// Verifica si esta habitación colisiona con otra
bool Room::collidesWith(const Room& other) {
    return (x < other.x + other.width && x + width > other.x &&
            z < other.z + other.depth && z + depth > other.z);
}