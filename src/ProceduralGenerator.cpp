#include "ProceduralGenerator.h"
#include <cstdlib>  // Para números aleatorios
#include <cmath>    // Para funciones matemáticas
#include <iostream>



ProceduralGenerator::ProceduralGenerator() {}

void ProceduralGenerator::generateRooms(int numRooms, float maxWidth, float maxHeight, float maxDepth) {
    int attempts = 0;
    for (int i = 0; i < numRooms; ++i) {
        bool validRoom = false;
        while (!validRoom && attempts < 100) {
            Room room = Room::generateRandom(maxWidth, maxHeight, maxDepth);
            validRoom = true;
            
            // Verificamos si esta habitación colisiona con otras habitaciones existentes
            for (const Room& existingRoom : rooms) {
                if (room.collidesWith(existingRoom)) {
                    validRoom = false;  // Si colisiona, no es válida
                    attempts++;
                    break;
                }
            }
            
            // Si no colisiona, agregamos la habitación
            if (validRoom) {
                rooms.push_back(room);
            }
        }
        if (attempts >= 100) {
            std::cerr << "No se pudieron generar suficientes habitaciones sin colisiones." << std::endl;
            break;
        }
    }
}

void ProceduralGenerator::connectRooms() {
    if (rooms.size() < 2) return;  // No tiene sentido si hay menos de dos habitaciones

    for (int i = 1; i < rooms.size(); ++i) {
        // Conectar la habitación i-1 con la habitación i
        float startX = rooms[i-1].x + rooms[i-1].width / 2;
        float startZ = rooms[i-1].z + rooms[i-1].depth / 2;
        float endX = rooms[i].x + rooms[i].width / 2;
        float endZ = rooms[i].z + rooms[i].depth / 2;

        Corridor corridor = Corridor::generateBetween(startX, startZ, endX, endZ);
        corridors.push_back(corridor);
    }
}

void ProceduralGenerator::drawRooms() {
    for (Room& room : rooms) {
        room.draw();
    }
}

void ProceduralGenerator::drawCorridors() {
    for (Corridor& corridor : corridors) {
        corridor.draw();
    }
}
