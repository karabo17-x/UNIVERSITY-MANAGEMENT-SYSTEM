#include "SportsAffiliation.h"
#include <iostream>
#include <algorithm>

SportsAffiliation::SportsAffiliation() {
    initializeSports();
}

SportsAffiliation::~SportsAffiliation() {
    for (auto& pair : allSports) {
        delete pair.second;
    }
    allSports.clear();
}

void SportsAffiliation::initializeSports() {
    allSports["S001"] = new Soccer("S001", "Coach Tshepiso");
    allSports["S002"] = new Tennis("S002", "Coach Neo");
    allSports["S003"] = new Rugby("S003", "Coach Evald");
    allSports["S004"] = new Volleyball("S004", "Coach Patricia");
    allSports["S005"] = new Karate("S005", "Coach Rorisang");
    allSports["S006"] = new Swimming("S006", "Coach Portia");
    allSports["S007"] = new Gymnastics("S007", "Coach Emphraim");
    allSports["S008"] = new Jujitsu("S008", "Coach Mbasto");
    allSports["S009"] = new Boxing("S009", "Coach Nakedi");
    allSports["S010"] = new Basketball("S010", "Happy");
    allSports["S011"] = new Cricket("S011", "Coach Keiden");
    allSports["S012"] = new Chess("S012", "Coach Issac");
}

Sports* SportsAffiliation::getSport(const std::string& sportId) {
    auto it = allSports.find(sportId);
    if (it != allSports.end()) {
        return it->second;
    }
    return nullptr;
}

void SportsAffiliation::affiliateStudentWithSport(const std::string& studentId, const std::string& sportId) {
    Sports* sport = getSport(sportId);
    if (sport) {
        sport->addStudent(studentId);
        auto& affiliations = studentAffiliations[studentId];
        auto it = std::find(affiliations.begin(), affiliations.end(), sportId);
        if (it == affiliations.end()) {
            affiliations.push_back(sportId);
            recordPayment(studentId, sport->getAffiliationFee());
        }
    } else {
        std::cout << "Invalid sport ID!\n";
    }
}

void SportsAffiliation::removeStudentFromSport(const std::string& studentId, const std::string& sportId) {
    Sports* sport = getSport(sportId);
    if (sport) {
        sport->removeStudent(studentId);
        auto& affiliations = studentAffiliations[studentId];
        auto it = std::find(affiliations.begin(), affiliations.end(), sportId);
        if (it != affiliations.end()) {
            affiliations.erase(it);
        }
    }
}

std::vector<std::string> SportsAffiliation::getStudentAffiliations(const std::string& studentId) const {
    auto it = studentAffiliations.find(studentId);
    if (it != studentAffiliations.end()) {
        return it->second;
    }
    return std::vector<std::string>();
}

void SportsAffiliation::recordPayment(const std::string& studentId, double amount) {
    studentPayments[studentId] += amount;
}

double SportsAffiliation::getStudentPaymentTotal(const std::string& studentId) const {
    auto it = studentPayments.find(studentId);
    if (it != studentPayments.end()) {
        return it->second;
    }
    return 0.0;
}

void SportsAffiliation::displayAllSports() const {
    std::cout << "\n========== ALL SPORTS AVAILABLE ==========\n";
    for (const auto& pair : allSports) {
        Sports* sport = pair.second;
        std::cout << "[" << sport->getSportId() << "] " << sport->getSportName() 
                  << " - Coordinator: " << sport->getCoordinator() 
                  << " - Fee: R" << sport->getAffiliationFee() 
                  << " - Members: " << sport->getTotalAffiliations() << "\n";
    }
    std::cout << "==========================================\n";
}

void SportsAffiliation::displayStudentSportInfo(const std::string& studentId) const {
    auto affiliations = getStudentAffiliations(studentId);
    std::cout << "\n===== STUDENT SPORTS PROFILE =====\n";
    std::cout << "Student ID: " << studentId << "\n";
    
    if (affiliations.empty()) {
        std::cout << "No sports affiliations\n";
    } else {
        std::cout << "Affiliated Sports:\n";
        for (const auto& sportId : affiliations) {
            Sports* sport = const_cast<SportsAffiliation*>(this)->getSport(sportId);
            if (sport) {
                std::cout << "  - " << sport->getSportName() << " (ID: " << sportId << ")\n";
            }
        }
    }
    
    double totalPayment = getStudentPaymentTotal(studentId);
    std::cout << "Total Payment: R" << totalPayment << "\n";
    std::cout << "==================================\n";
}

void SportsAffiliation::displaySportParticipants(const std::string& sportId) const {
    auto it = allSports.find(sportId);
    if (it != allSports.end()) {
        Sports* sport = it->second;
        std::cout << "\n===== " << sport->getSportName() << " PARTICIPANTS =====\n";
        std::cout << "Coordinator: " << sport->getCoordinator() << "\n";
        std::cout << "Fee: R" << sport->getAffiliationFee() << "\n";
        
        auto students = sport->getAffiliatedStudents();
        std::cout << "Total Members: " << students.size() << "\n";
        
        if (!students.empty()) {
            std::cout << "Members:\n";
            for (const auto& studentId : students) {
                std::cout << "  - " << studentId << "\n";
            }
        }
        std::cout << "================================\n";
    } else {
        std::cout << "Invalid sport ID!\n";
    }
}
