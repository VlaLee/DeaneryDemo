// Copyright 2024 Lee V.

#include <algorithm>
#include <iostream>

#include "Student.h"
#include "Group.h"

Student::Student(const std::string id, const std::string SNP, Group* group,
    std::vector<std::uint16_t> marks)
    : m_id(id), m_SNP(SNP), m_group(nullptr), m_marks(marks) { }

void Student::enrollment(Group* group) {
    m_group = group;
}

void Student::addMark(std::uint16_t mark) {
    if (mark > 10) {
        std::cerr << "INCORRECT MARK\n";
        return;
    }

    m_marks.push_back(mark);
}

float Student::getAverageScore() const {
    if (m_marks.size() == 0)
        return 0.0;

    float sum = 0.0;
    for (const int& mark : m_marks)
        sum += mark;

    return sum / m_marks.size();
}

std::string Student::getId() const {
    return m_id;
}

std::string Student::getSNP() const {
    return m_SNP;
}

Group* Student::getGroup() const {
    return m_group;
}

const std::vector<std::uint16_t>& Student::getMarks() const {
    return m_marks;
}

void Student::setId(std::string id) {
    m_id = id;
}

void Student::setSNP(std::string SNP) {
    m_SNP = SNP;
}

std::ostream& operator<<(std::ostream& out, const Student& student) {
    out << "Student [" << student.m_id << "]:\n";
    out << "Name Surname Patronymic: " << student.m_SNP << '\n';
    out << "Group: " << student.m_group->getTitle() << '\n';
    out << "Marks: ";

    for (const std::uint16_t& mark : student.m_marks)
        out << mark << ' ';

    out << "\nAverage score: " << student.getAverageScore();

    return out;
}
