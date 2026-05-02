#ifndef SPORTS_AFFILIATION_H
#define SPORTS_AFFILIATION_H

#include "Sports.h"
#include <map>
#include <vector>

class SportsAffiliation {
private:
    std::map<std::string, Sports*> allSports;
    std::map<std::string, std::vector<std::string>> studentAffiliations;
    std::map<std::string, double> studentPayments;

public:
    SportsAffiliation();
    ~SportsAffiliation();

    void initializeSports();
    Sports* getSport(const std::string& sportId);
    void affiliateStudentWithSport(const std::string& studentId, const std::string& sportId);
    void removeStudentFromSport(const std::string& studentId, const std::string& sportId);
    std::vector<std::string> getStudentAffiliations(const std::string& studentId) const;
    void recordPayment(const std::string& studentId, double amount);
    double getStudentPaymentTotal(const std::string& studentId) const;
    void displayAllSports() const;
    void displayStudentSportInfo(const std::string& studentId) const;
    void displaySportParticipants(const std::string& sportId) const;
};

#endif // SPORTS_AFFILIATION_H
