#include "Residence.h"
#include <iostream>

Residence::Residence(const std::string& resId, const std::string& resName, const std::string& block, 
                     int totalRooms, const std::string& warden)
    : residenceId(resId), residenceName(resName), blockName(block), totalRooms(totalRooms), 
      occupiedRooms(0), warden(warden) {}

Residence::~Residence() {}

std::string Residence::getResidenceId() const {
    return residenceId;
}

std::string Residence::getResidenceName() const {
    return residenceName;
}

std::string Residence::getBlockName() const {
    return blockName;
}

std::string Residence::getWarden() const {
    return warden;
}

int Residence::getTotalRooms() const {
    return totalRooms;
}

int Residence::getOccupiedRooms() const {
    return occupiedRooms;
}

int Residence::getAvailableRooms() const {
    return totalRooms - occupiedRooms;
}

void Residence::setWarden(const std::string& warden) {
    this->warden = warden;
}

void Residence::assignRoom(int roomNumber, Student* student) {
    if (roomNumber < 1 || roomNumber > totalRooms) {
        std::cout << "Invalid room number!\n";
        return;
    }
    
    if (roomAssignments.find(roomNumber) != roomAssignments.end()) {
        std::cout << "Room " << roomNumber << " is already occupied!\n";
        return;
    }
    
    roomAssignments[roomNumber] = student;
    occupiedRooms++;
    student->setResidenceBlock(blockName + " - Room " + std::to_string(roomNumber));
    std::cout << "Room " << roomNumber << " assigned to student " << student->getName() << "\n";
}

void Residence::vacateRoom(int roomNumber) {
    auto it = roomAssignments.find(roomNumber);
    if (it != roomAssignments.end()) {
        std::cout << "Room " << roomNumber << " vacated by student " << it->second->getName() << "\n";
        it->second->setResidenceBlock("");
        roomAssignments.erase(it);
        occupiedRooms--;
    } else {
        std::cout << "Room " << roomNumber << " is not occupied!\n";
    }
}

Student* Residence::getRoomOccupant(int roomNumber) const {
    auto it = roomAssignments.find(roomNumber);
    if (it != roomAssignments.end()) {
        return it->second;
    }
    return nullptr;
}

void Residence::displayRoomOccupancy() const {
    std::cout << "\n========== Room Occupancy Status ==========\n";
    std::cout << "Building: " << residenceName << " | Block: " << blockName << "\n";
    std::cout << "Occupancy: " << occupiedRooms << "/" << totalRooms << " rooms occupied\n\n";
    
    for (int i = 1; i <= totalRooms; i++) {
        auto it = roomAssignments.find(i);
        std::cout << "Room " << i << ": ";
        if (it != roomAssignments.end()) {
            std::cout << "Occupied by " << it->second->getName();
        } else {
            std::cout << "Available";
        }
        std::cout << "\n";
    }
    std::cout << "==========================================\n";
}

void Residence::displayResidenceInfo() const {
    std::cout << "\n========== Residence Information ==========\n"
              << "Residence ID: " << residenceId << "\n"
              << "Residence Name: " << residenceName << "\n"
              << "Block Name: " << blockName << "\n"
              << "Total Rooms: " << totalRooms << "\n"
              << "Occupied Rooms: " << occupiedRooms << "\n"
              << "Available Rooms: " << getAvailableRooms() << "\n"
              << "Warden: " << warden << "\n"
              << "=========================================\n";
}

void Residence::displayAllOccupants() const {
    std::cout << "\n========== All Room Occupants ==========\n";
    if (roomAssignments.empty()) {
        std::cout << "No rooms are currently occupied.\n";
    } else {
        for (const auto& room : roomAssignments) {
            std::cout << "Room " << room.first << " - Student: " << room.second->getName() 
                      << " (Roll: " << room.second->getRollNumber() << ")\n";
        }
    }
    std::cout << "======================================\n";
}
