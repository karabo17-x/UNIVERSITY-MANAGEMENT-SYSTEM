#ifndef EXAM_H
#define EXAM_H

#include <string>
#include <vector>

// Base class for all exams
class Exam {
protected:
    std::string examId;
    std::string examName;
    std::string examType;      // Midterm, Final, Quiz, Assignment
    std::string department;
    std::string date;
    std::string time;
    int duration;              
    int maxMarks;
    std::string venue;

public:
    Exam(const std::string& id, const std::string& name, const std::string& type, 
         const std::string& dept, const std::string& date, const std::string& time,
         int duration, int maxMarks, const std::string& venue);
    
    virtual ~Exam();

    // Getters
    std::string getExamId() const;
    std::string getExamName() const;
    std::string getExamType() const;
    std::string getDepartment() const;
    std::string getDate() const;
    std::string getTime() const;
    int getDuration() const;
    int getMaxMarks() const;
    std::string getVenue() const;

   
    void setDate(const std::string& date);
    void setTime(const std::string& time);
    void setVenue(const std::string& venue);
    void setMaxMarks(int marks);

 
    virtual void displayExamInfo() const;
};


class Midterm : public Exam {
public:
    Midterm(const std::string& id, const std::string& name, const std::string& dept,
            const std::string& date, const std::string& time, int duration, 
            int maxMarks, const std::string& venue);
    void displayExamInfo() const override;
};

class Final : public Exam {
public:
    Final(const std::string& id, const std::string& name, const std::string& dept,
          const std::string& date, const std::string& time, int duration,
          int maxMarks, const std::string& venue);
    void displayExamInfo() const override;
};

class Quiz : public Exam {
public:
    Quiz(const std::string& id, const std::string& name, const std::string& dept,
         const std::string& date, const std::string& time, int duration,
         int maxMarks, const std::string& venue);
    void displayExamInfo() const override;
};

class Assignment : public Exam {
public:
    Assignment(const std::string& id, const std::string& name, const std::string& dept,
               const std::string& date, const std::string& time, int duration,
               int maxMarks, const std::string& venue);
    void displayExamInfo() const override;
};

#endif // EXAM_H
