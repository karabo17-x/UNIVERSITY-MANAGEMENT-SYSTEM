#ifndef RESIDENCE_H
#define RESIDENCE_H

#include <string>
#include <vector>
#include <map>
#include "../Student/Student.h"

class Residence {
private:
    std::string residenceId;
    std::string residenceName;
    std::string blockName;
    int totalRooms;
    int occupiedRooms;
    // Map to store room number -> student occupying it
    std::map<int, Student*> roomAssignments;
    std::string warden;

public:
    Residence(const std::string& resId, const std::string& resName, const std::string& block, 
              int totalRooms, const std::string& warden);
    ~Residence();

    // Getters
    std::string getResidenceId() const;
    std::string getResidenceName() const;
    std::string getBlockName() const;
    std::string getWarden() const;
    int getTotalRooms() const;
    int getOccupiedRooms() const;
    int getAvailableRooms() const;

    // Setters
    void setWarden(const std::string& warden);

    // Room management
    void assignRoom(int roomNumber, Student* student);
    void vacateRoom(int roomNumber);
    Student* getRoomOccupant(int roomNumber) const;
    void displayRoomOccupancy() const;

    // Display information
    void displayResidenceInfo() const;
    void displayAllOccupants() const;
};

#endif // RESIDENCE_H
