#ifndef PROCEDURALGENERATOR_H
#define PROCEDURALGENERATOR_H

#include <vector>
#include "Room.h"

class ProceduralGenerator {
public:
    std::vector<Room> rooms;

    ProceduralGenerator();

    // Genera múltiples habitaciones de manera procedural
    void generateRooms(int numRooms, float maxWidth, float maxHeight, float maxDepth);

    // Dibuja todas las habitaciones generadas
    void drawRooms();
};

#endif
