#ifndef ROOM_H
#define ROOM_H

class Room {
public:
    float x, y, z;        // Posición de la habitación
    float width, height, depth; // Dimensiones de la habitación

    Room(float _x, float _y, float _z, float _width, float _height, float _depth);
    
    // Función para dibujar la habitación
    void draw();

    // Generar una habitación de tamaño aleatorio
    static Room generateRandom(float maxWidth, float maxHeight, float maxDepth);

    // Dibuja una pared con una entrada (solo hueco, sin puerta)
    void drawWallWithEntrance(float x, float y, float z, float width, float height, bool isFrontWall);

    // Verificar si una habitación colisiona con otra
    bool collidesWith(const Room& other);
};

#endif
