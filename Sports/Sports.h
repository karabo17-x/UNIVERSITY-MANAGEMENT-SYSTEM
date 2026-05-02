#ifndef SPORTS_H
#define SPORTS_H

#include <string>
#include <vector>

class Sports {
protected:
    std::string sportId;
    std::string sportName;
    std::string coordinator;
    std::vector<std::string> affiliatedStudents;
    double affiliationFee;

public:
    Sports(const std::string& id, const std::string& name, const std::string& coord, double fee);
    virtual ~Sports();

    std::string getSportId() const;
    std::string getSportName() const;
    std::string getCoordinator() const;
    double getAffiliationFee() const;
    std::vector<std::string> getAffiliatedStudents() const;
    int getTotalAffiliations() const;

    void setCoordinator(const std::string& coord);
    void setAffiliationFee(double fee);
    void addStudent(const std::string& studentId);
    void removeStudent(const std::string& studentId);
    bool isStudentAffiliated(const std::string& studentId) const;

    virtual void displaySportInfo() const;
};

class Soccer : public Sports {
public:
    Soccer(const std::string& id, const std::string& coord);
    void displaySportInfo() const override;
};

class Tennis : public Sports {
public:
    Tennis(const std::string& id, const std::string& coord);
    void displaySportInfo() const override;
};

class Rugby : public Sports {
public:
    Rugby(const std::string& id, const std::string& coord);
    void displaySportInfo() const override;
};

class Volleyball : public Sports {
public:
    Volleyball(const std::string& id, const std::string& coord);
    void displaySportInfo() const override;
};

class Karate : public Sports {
public:
    Karate(const std::string& id, const std::string& coord);
    void displaySportInfo() const override;
};

class Swimming : public Sports {
public:
    Swimming(const std::string& id, const std::string& coord);
    void displaySportInfo() const override;
};

class Gymnastics : public Sports {
public:
    Gymnastics(const std::string& id, const std::string& coord);
    void displaySportInfo() const override;
};

class Jujitsu : public Sports {
public:
    Jujitsu(const std::string& id, const std::string& coord);
    void displaySportInfo() const override;
};

class Boxing : public Sports {
public:
    Boxing(const std::string& id, const std::string& coord);
    void displaySportInfo() const override;
};

class Basketball : public Sports {
public:
    Basketball(const std::string& id, const std::string& coord);
    void displaySportInfo() const override;
};

class Cricket : public Sports {
public:
    Cricket(const std::string& id, const std::string& coord);
    void displaySportInfo() const override;
};

class Chess : public Sports {
public:
    Chess(const std::string& id, const std::string& coord);
    void displaySportInfo() const override;
};

#endif // SPORTS_H
