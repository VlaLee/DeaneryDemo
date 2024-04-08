// Copyright 2024 Lee V.

#include <iostream>

#include "Group.h"

Group::Group(const std::string title, const std::string spec) : m_title(title),
    m_spec(spec), m_head(nullptr) { }

void Group::addStudent(Student* student) {
    // if we add student in an empty group
    // we appoint him as a head
    if (m_students.size() == 0)
        m_head = student;

    m_students.push_back(student);
    student->enrollment(this);
}

void Group::chooseHead() {
    float maxAverage = 0.0;
    std::string new_head;  // name of a student with max average score

    for (const Student* student : m_students) {
        if (maxAverage < student->getAverageScore()) {
            maxAverage = student->getAverageScore();
            new_head = student->getSNP();
        }
    }

    m_head = searchStudentBySNP(new_head);
}

Student* Group::searchStudentById(const std::string id) {
    for (Student* student : m_students) {
        if (student->getId() == id)
            return student;
    }

    return nullptr;  // if we couldn't search student
}

Student* Group::searchStudentBySNP(const std::string SNP) {
    for (Student* student : m_students) {
        if (student->getSNP() == SNP)
            return student;
    }
    return nullptr;  // if we couldn't search student
}

float Group::getAverageGroupScore() const {
    if (m_students.size() == 0)
        return 0.0;

    float sumOfAverages = 0.0;
    for (const Student* student : m_students) {
        sumOfAverages += student->getAverageScore();
    }

    return sumOfAverages / m_students.size();
}

void Group::exclusionStudent(Student* student) {
    size_t position = -1;  // position of excluded student

    for (size_t index = 0; index < m_students.size(); ++index) {
        if (m_students[index]->getId() == student->getId()) {
            position = index;
            break;
        }
    }

    if (position == -1)  // if we couldn't find the student
        return;

    m_students[position]->enrollment(nullptr);
    m_students.erase(m_students.begin() + position);

    if (m_head == student)  // if we exclude head, choose new head
        chooseHead();
}

std::string Group::getTitle() const {
    return m_title;
}

std::string Group::getSpec() const {
    return m_spec;
}

Student* Group::getHead() const {
    return m_head;
}

const std::vector<Student*>& Group::getStudentVector() const {
    return m_students;
}

void Group::utilizeMemory() const {
    for (const auto* student : m_students)
        delete student;
}

std::ostream& operator<<(std::ostream& out, const Group& group) {
    out << "Group " << group.getTitle() << '\n';
    out << "Specialization: " << group.getSpec() << '\n';

    if (group.m_head == nullptr)
        out << "Head undefined.\n";
    else
        out << "Head: [" << group.m_head->getId() << "] "
            << group.m_head->getSNP() << '\n';

    out << "Average score of group: " << group.getAverageGroupScore() << "\n\n";
    out << "Student list:\n";

    // if there are not any students in a group
    if (group.m_students.size() == 0)
        out << "None\n";

    for (const auto* student : group.m_students)
        out << *student << "\n\n";

    return out;
}
