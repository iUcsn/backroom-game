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

void ProceduralGenerator::drawRooms() {
    for (Room& room : rooms) {
        room.draw();
    }
}
