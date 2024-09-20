#ifndef CORRIDOR_H
#define CORRIDOR_H

class Corridor {
public:
    float x, y, z;        // Posición inicial del pasillo
    float length;         // Longitud del pasillo
    float width, height;  // Dimensiones del pasillo

    // Constructor
    Corridor(float _x, float _y, float _z, float _length, float _width, float _height);

    // Método para dibujar el pasillo
    void draw();

    // Genera un pasillo que conecta dos habitaciones
    static Corridor generateBetween(float startX, float startZ, float endX, float endZ);
};

#endif
