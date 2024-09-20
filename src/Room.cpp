#include "Room.h"
#include <GL/gl.h>
#include <cstdlib>

// Constructor para inicializar la habitación con posición y dimensiones
Room::Room(float _x, float _y, float _z, float _width, float _height, float _depth) 
    : x(_x), y(_y), z(_z), width(_width), height(_height), depth(_depth) {}

// Función para dibujar el suelo, las paredes y el techo de la habitación
void Room::draw() {
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

// Dibuja una pared con una entrada del tamaño del pasillo
void Room::drawWallWithEntrance(float corridorX, float corridorZ, float corridorWidth) {
    glBegin(GL_QUADS);

    // Pared izquierda (antes de la entrada)
    glColor3f(0.7f, 0.7f, 0.7f);  // Color de la pared
    glVertex3f(x, y, z);
    glVertex3f(x, y + height, z);
    glVertex3f(corridorX, y + height, z);
    glVertex3f(corridorX, y, z);

    // Pared derecha (después de la entrada)
    glVertex3f(corridorX + corridorWidth, y, z);
    glVertex3f(corridorX + corridorWidth, y + height, z);
    glVertex3f(x + width, y + height, z);
    glVertex3f(x + width, y, z);

    // Techo (opcional, si quieres dejar una abertura arriba)
    glVertex3f(corridorX, y + height, z);
    glVertex3f(corridorX + corridorWidth, y + height, z);
    glVertex3f(corridorX + corridorWidth, y + height, z + depth);
    glVertex3f(corridorX, y + height, z + depth);

    glEnd();
}

bool Room::collidesWith(const Room& other) {
    // Verificamos si las áreas (en el plano XZ) de las dos habitaciones se superponen
    bool collisionX = (x < other.x + other.width) && (x + width > other.x);
    bool collisionZ = (z < other.z + other.depth) && (z + depth > other.z);
    
    return collisionX && collisionZ;
}
