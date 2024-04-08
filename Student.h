// Copyright 2024 Lee V.

#ifndef INCLUDE_STUDENT_H
#define INCLUDE_STUDENT_H

#include <string>
#include <vector>

class Group;

class Student {
 private:
    std::string m_id;
    std::string m_SNP;  // Surname Name Patronymic --> SNP
    Group* m_group;
    std::vector<std::uint16_t> m_marks;

 public:
    explicit Student(const std::string id, const std::string SNP,
        Group* group = nullptr,
        std::vector<std::uint16_t> marks = std::vector<std::uint16_t>(0));

    void enrollment(Group* group);
    void addMark(std::uint16_t mark);
    float getAverageScore() const;

    std::string getId() const;
    std::string getSNP() const;
    Group* getGroup() const;
    const std::vector<std::uint16_t>& getMarks() const;

    void setId(std::string id);
    void setSNP(std::string SNP);

    friend std::ostream& operator<<(std::ostream& out, const Student& student);
};

#endif  // INCLUDE_STUDENT_H
