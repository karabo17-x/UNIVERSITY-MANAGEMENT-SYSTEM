#include "Sports.h"
#include <iostream>
#include <algorithm>

Sports::Sports(const std::string& id, const std::string& name, const std::string& coord, double fee)
    : sportId(id), sportName(name), coordinator(coord), affiliationFee(fee) {}

Sports::~Sports() {}

std::string Sports::getSportId() const {
    return sportId;
}

std::string Sports::getSportName() const {
    return sportName;
}

std::string Sports::getCoordinator() const {
    return coordinator;
}

double Sports::getAffiliationFee() const {
    return affiliationFee;
}

std::vector<std::string> Sports::getAffiliatedStudents() const {
    return affiliatedStudents;
}

int Sports::getTotalAffiliations() const {
    return affiliatedStudents.size();
}

void Sports::setCoordinator(const std::string& coord) {
    coordinator = coord;
}

void Sports::setAffiliationFee(double fee) {
    affiliationFee = fee;
}

void Sports::addStudent(const std::string& studentId) {
    auto it = std::find(affiliatedStudents.begin(), affiliatedStudents.end(), studentId);
    if (it == affiliatedStudents.end()) {
        affiliatedStudents.push_back(studentId);
        std::cout << "Student " << studentId << " affiliated with " << sportName << "\n";
    }
}

void Sports::removeStudent(const std::string& studentId) {
    auto it = std::find(affiliatedStudents.begin(), affiliatedStudents.end(), studentId);
    if (it != affiliatedStudents.end()) {
        affiliatedStudents.erase(it);
        std::cout << "Student " << studentId << " removed from " << sportName << "\n";
    }
}

bool Sports::isStudentAffiliated(const std::string& studentId) const {
    auto it = std::find(affiliatedStudents.begin(), affiliatedStudents.end(), studentId);
    return it != affiliatedStudents.end();
}

void Sports::displaySportInfo() const {
    std::cout << "\n===== SPORT INFO =====\n";
    std::cout << "Sport ID: " << sportId << "\n";
    std::cout << "Sport Name: " << sportName << "\n";
    std::cout << "Coordinator: " << coordinator << "\n";
    std::cout << "Affiliation Fee: R" << affiliationFee << "\n";
    std::cout << "Total Affiliations: " << getTotalAffiliations() << "\n";
    std::cout << "========================\n";
}

Soccer::Soccer(const std::string& id, const std::string& coord)
    : Sports(id, "Soccer", coord, 150.0) {}

void Soccer::displaySportInfo() const {
    std::cout << "\n===== SOCCER =====\n";
    Sports::displaySportInfo();
}

Tennis::Tennis(const std::string& id, const std::string& coord)
    : Sports(id, "Tennis", coord, 120.0) {}

void Tennis::displaySportInfo() const {
    std::cout << "\n===== TENNIS =====\n";
    Sports::displaySportInfo();
}

Rugby::Rugby(const std::string& id, const std::string& coord)
    : Sports(id, "Rugby", coord, 140.0) {}

void Rugby::displaySportInfo() const {
    std::cout << "\n===== RUGBY =====\n";
    Sports::displaySportInfo();
}

Volleyball::Volleyball(const std::string& id, const std::string& coord)
    : Sports(id, "Volleyball", coord, 100.0) {}

void Volleyball::displaySportInfo() const {
    std::cout << "\n===== VOLLEYBALL =====\n";
    Sports::displaySportInfo();
}

Karate::Karate(const std::string& id, const std::string& coord)
    : Sports(id, "Karate", coord, 175.0) {}

void Karate::displaySportInfo() const {
    std::cout << "\n===== KARATE =====\n";
    Sports::displaySportInfo();
}

Swimming::Swimming(const std::string& id, const std::string& coord)
    : Sports(id, "Swimming", coord, 130.0) {}

void Swimming::displaySportInfo() const {
    std::cout << "\n===== SWIMMING =====\n";
    Sports::displaySportInfo();
}

Gymnastics::Gymnastics(const std::string& id, const std::string& coord)
    : Sports(id, "Gymnastics", coord, 160.0) {}

void Gymnastics::displaySportInfo() const {
    std::cout << "\n===== GYMNASTICS =====\n";
    Sports::displaySportInfo();
}

Jujitsu::Jujitsu(const std::string& id, const std::string& coord)
    : Sports(id, "Jujitsu", coord, 180.0) {}

void Jujitsu::displaySportInfo() const {
    std::cout << "\n===== JUJITSU =====\n";
    Sports::displaySportInfo();
}

Boxing::Boxing(const std::string& id, const std::string& coord)
    : Sports(id, "Boxing", coord, 165.0) {}

void Boxing::displaySportInfo() const {
    std::cout << "\n===== BOXING =====\n";
    Sports::displaySportInfo();
}

Basketball::Basketball(const std::string& id, const std::string& coord)
    : Sports(id, "Basketball", coord, 135.0) {}

void Basketball::displaySportInfo() const {
    std::cout << "\n===== BASKETBALL =====\n";
    Sports::displaySportInfo();
}

Cricket::Cricket(const std::string& id, const std::string& coord)
    : Sports(id, "Cricket", coord, 145.0) {}

void Cricket::displaySportInfo() const {
    std::cout << "\n===== CRICKET =====\n";
    Sports::displaySportInfo();
}

Chess::Chess(const std::string& id, const std::string& coord)
    : Sports(id, "Chess", coord, 110.0) {}

void Chess::displaySportInfo() const {
    std::cout << "\n===== CHESS  =====\n";
    Sports::displaySportInfo();
}
