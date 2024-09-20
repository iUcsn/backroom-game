#ifndef PROCEDURALGENERATOR_H
#define PROCEDURALGENERATOR_H

#include <vector>
#include "Room.h"
#include "Corridor.h"

class ProceduralGenerator {
public:
    std::vector<Room> rooms;
    std::vector<Corridor> corridors;

    ProceduralGenerator();

    // Genera múltiples habitaciones de manera procedural
    void generateRooms(int numRooms, float maxWidth, float maxHeight, float maxDepth);

    // Conectar habitaciones con pasillos
    void connectRooms();

    // Dibuja todas las habitaciones generadas
    void drawRooms();

    // Dibuja todos los pasillos generados
    void drawCorridors();
};

#endif
