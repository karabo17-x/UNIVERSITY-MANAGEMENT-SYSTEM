#ifndef PERSON_H
#define PERSON_H

#include <string>

// Base class for all persons in the university
class Person {
protected:
    std::string id;
    std::string name;
    std::string email;
    std::string phone;

public:
    Person(const std::string& id, const std::string& name, const std::string& email, const std::string& phone);
    virtual ~Person();

    // Getters
    std::string getId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getPhone() const;

    // Setters
    void setName(const std::string& name);
    void setEmail(const std::string& email);
    void setPhone(const std::string& phone);

    // Virtual method to display information
    virtual void displayInfo() const;
};

#endif // PERSON_H
