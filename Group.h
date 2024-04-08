// Copyright 2024 Lee V.

#ifndef INCLUDE_GROUP_H
#define INCLUDE_GROUP_H

#include <string>
#include <vector>

#include "Student.h"

class Group {
 private:
    std::string m_title;
    std::string m_spec;
    std::vector<Student*> m_students;
    Student* m_head;

 public:
    explicit Group(const std::string title, const std::string spec);

    // utilization memory when we use dynamic memory allocation
    void utilizeMemory() const;

    void addStudent(Student* student);
    void chooseHead();
    Student* searchStudentById(const std::string id);
    Student* searchStudentBySNP(const std::string SNP);
    float getAverageGroupScore() const;
    void exclusionStudent(Student* student);

    std::string getTitle() const;
    std::string getSpec() const;
    Student* getHead() const;
    const std::vector<Student*>& getStudentVector() const;

    friend std::ostream& operator<<(std::ostream& out, const Group& group);
};

#endif  // INCLUDE_GROUP_H
