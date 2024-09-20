#include "Corridor.h"
#include <GL/gl.h>
#include <cmath>  // Para cálculos matemáticos

Corridor::Corridor(float _x, float _y, float _z, float _length, float _width, float _height) 
    : x(_x), y(_y), z(_z), length(_length), width(_width), height(_height) {}

void Corridor::draw() {
    glBegin(GL_QUADS);
    
    // Suelo del pasillo
    glColor3f(0.6f, 0.6f, 0.6f);  // Color gris para el suelo
    glVertex3f(x, y, z);
    glVertex3f(x + width, y, z);
    glVertex3f(x + width, y, z + length);
    glVertex3f(x, y, z + length);
    
    // Pared izquierda
    glColor3f(0.7f, 0.7f, 0.7f);  // Pared de color más claro
    glVertex3f(x, y, z);
    glVertex3f(x, y + height, z);
    glVertex3f(x, y + height, z + length);
    glVertex3f(x, y, z + length);
    
    // Pared derecha
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex3f(x + width, y, z);
    glVertex3f(x + width, y + height, z);
    glVertex3f(x + width, y + height, z + length);
    glVertex3f(x + width, y, z + length);

    // Techo del pasillo
    glColor3f(0.5f, 0.5f, 0.5f);  // Color más oscuro para el techo
    glVertex3f(x, y + height, z);
    glVertex3f(x + width, y + height, z);
    glVertex3f(x + width, y + height, z + length);
    glVertex3f(x, y + height, z + length);

    glEnd();
}

Corridor Corridor::generateBetween(float startX, float startZ, float endX, float endZ) {
    // Calculamos la longitud del pasillo en función de la distancia entre las dos habitaciones
    float deltaX = endX - startX;
    float deltaZ = endZ - startZ;

    float width = 5.0f;  // Ancho fijo del pasillo
    float height = 3.0f; // Altura fija del pasillo

    // Si la distancia es más grande en el eje Z, el pasillo será recto en Z
    if (std::abs(deltaZ) > std::abs(deltaX)) {
        float length = std::abs(deltaZ);  // La longitud del pasillo es la diferencia en Z
        return Corridor(startX - width / 2, 0.0f, startZ, length, width, height);
    } 
    // Si la distancia es mayor en el eje X, el pasillo será recto en X
    else {
        float length = std::abs(deltaX);  // La longitud del pasillo es la diferencia en X
        return Corridor(startX, 0.0f, startZ - width / 2, length, width, height);
    }
}
