#include "Room.h"
#include <GL/gl.h>
#include <cstdlib>  // Para funciones aleatorias

Room::Room(float _x, float _y, float _z, float _width, float _height, float _depth) 
    : x(_x), y(_y), z(_z), width(_width), height(_height), depth(_depth) {}

void Room::draw() {
    glBegin(GL_QUADS);
    
    // Suelo y techo

    glColor3f(0.7f, 0.7f, 0.7f);  // Color más claro para el techo
    glVertex3f(x, y + height, z);
    glVertex3f(x + width, y + height, z);
    glVertex3f(x + width, y + height, z + depth);
    glVertex3f(x, y + height, z + depth);

    // Dibujar las paredes con un hueco para la entrada
    glColor3f(0.8f, 0.8f, 0.8f);  // Paredes más claras

    // Pared frontal con hueco (entrada)
    drawWallWithEntrance(x, y, z, width, height, true);  // Hueco en la parte frontal

    // Pared trasera
    glVertex3f(x, y, z + depth);
    glVertex3f(x, y + height, z + depth);
    glVertex3f(x + width, y + height, z + depth);
    glVertex3f(x + width, y, z + depth);

    // Pared izquierda
    glVertex3f(x, y, z);
    glVertex3f(x, y + height, z);
    glVertex3f(x, y + height, z + depth);
    glVertex3f(x, y, z + depth);

    // Pared derecha
    glVertex3f(x + width, y, z);
    glVertex3f(x + width, y + height, z);
    glVertex3f(x + width, y + height, z + depth);
    glVertex3f(x + width, y, z + depth);

    glEnd();
}

// Función para dibujar una pared con un hueco (entrada)
void Room::drawWallWithEntrance(float x, float y, float z, float width, float height, bool isFrontWall) {
    // Definir el tamaño de la entrada
    float entranceWidth = width * 0.2f;  // 20% del ancho de la habitación
    float entranceHeight = height * 0.6f;  // 60% de la altura de la habitación

    glBegin(GL_QUADS);

    if (isFrontWall) {
        // Pared frontal dividida en tres partes: antes del hueco, el hueco, después del hueco

        // Parte izquierda de la pared (antes del hueco)
        glVertex3f(x, y, z);
        glVertex3f(x, y + height, z);
        glVertex3f(x + width / 2 - entranceWidth / 2, y + height, z);
        glVertex3f(x + width / 2 - entranceWidth / 2, y, z);

        // Parte derecha de la pared (después del hueco)
        glVertex3f(x + width / 2 + entranceWidth / 2, y, z);
        glVertex3f(x + width / 2 + entranceWidth / 2, y + height, z);
        glVertex3f(x + width, y + height, z);
        glVertex3f(x + width, y, z);

        // Nota: no dibujamos nada en el área del hueco.
    }
    
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

bool Room::collidesWith(const Room& other) {
    bool collisionX = (x < other.x + other.width) && (x + width > other.x);
    bool collisionZ = (z < other.z + other.depth) && (z + depth > other.z);
    return collisionX && collisionZ;
}