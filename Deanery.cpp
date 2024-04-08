// Copyright 2024 Lee V.

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <locale>

#include "Deanery.h"

Deanery::Deanery(const std::string groupsFileName,
    const std::string studentsFileName)
    : m_groupsFileName(groupsFileName), m_studentsFileName(studentsFileName) {
    // create groups and students objects
    createGroups();
    hireStudents();
}

Deanery::~Deanery() {
    // we need to free memory, because we use
    // dynamic memory allocation in this class
    for (const auto* group : m_groups) {
        group->utilizeMemory();
        delete group;
    }
}

void Deanery::createGroups() {
    std::ifstream file(m_groupsFileName);

    if (!file.is_open()) {
        std::cerr << "FILE OPEN ERROR";
        std::exit(-3);
    }

    while (!file.eof()) {
        std::string word;
        std::getline(file, word);
        std::istringstream ist(word);

        std::string temp_groupTitle, temp_groupSpec;
        ist >> temp_groupTitle >> temp_groupSpec;

        Group* temp_group = new Group(temp_groupTitle, temp_groupSpec);
        m_groups.push_back(temp_group);
    }

    file.close();
}

void Deanery::hireStudents() {
    std::ifstream file(m_studentsFileName);

    if (!file.is_open()) {
        std::cerr << "FILE OPEN ERROR";
        std::exit(-3);
    }

    while (!file.eof()) {
        std::string word;
        std::getline(file, word);
        std::istringstream ist(word);

        std::string temp_id, temp_surname, temp_name,
            temp_patronymic, temp_group_name;

        ist >> temp_id >> temp_surname >> temp_name;
        ist >> temp_patronymic >> temp_group_name;

        std::string temp_SNP = temp_surname + ' ' + temp_name +
            ' ' + temp_patronymic;

        Student* temp_student = new Student(temp_id, temp_SNP);

        // if there are any words - it is a marks of student
        while (ist >> word) {
            temp_student->addMark(std::stoi(word));
        }

        temp_student->setSNP(temp_SNP);
        searchGroup(temp_group_name)->addStudent(temp_student);
    }

    file.close();
}

Group* Deanery::searchGroup(const std::string groupTitle) {
    for (auto* group : m_groups)
        if (group->getTitle() == groupTitle)
            return group;

    return nullptr;  // if we couldn't search a group
}

void Deanery::saveStaff() {
    std::ofstream out(m_groupsFileName);

    if (!out.is_open()) {
        std::cerr << "FILE OPEN ERROR";
        std::exit(-3);
    }

    for (const auto* group : m_groups) {
        out << group->getTitle() << ' ' << group->getSpec() << '\n';
    }

    out.close();
    out.open(m_studentsFileName);

    if (!out.is_open()) {
        std::cerr << "FILE OPEN ERROR";
        std::exit(-3);
    }

    for (const auto* group : m_groups) {
        for (const auto* student : group->getStudentVector()) {
            if (student->getGroup() == nullptr)
                continue;

            out << student->getId() << ' ' << student->getSNP() << ' '
                << group->getTitle();
            for (const auto mark : student->getMarks()) {
                out << ' ' << mark;
            }
            out << '\n';
        }
    }

    out.close();
}

void Deanery::initHeads() {
    for (auto* group : m_groups)
        group->chooseHead();
}

void Deanery::addMarksToAll(unsigned int number, int mark) {
    srand(time(nullptr));  // set random settings

    for (const auto* group : m_groups) {
        for (auto* student : group->getStudentVector()) {
            for (size_t counter = 0; counter < number; ++counter) {
                if (mark == -1)
                    student->addMark(rand() % 11);
                else
                    student->addMark(mark);
            }
        }
    }

    saveStaff();  // update data
}

void Deanery::fireStudents() {
    for (auto* group : m_groups) {
        float averageGroupScore = group->getAverageGroupScore();

        for (auto* student : group->getStudentVector()) {
            // exclusion criterion
            if (student->getAverageScore() * 2 <= averageGroupScore)
                group->exclusionStudent(student);
        }
    }

    saveStaff();  // update data
}

void Deanery::moveStudent(const std::string studentInfo,
    const std::string destination) {
    Group* destinationGroup = searchGroup(destination);

    // if we couldn't find a group with that title
    if (destinationGroup == nullptr)
        return;

    Student* movingStudent = nullptr;
    Group* source = nullptr;
    for (auto* group : m_groups) {
        for (auto* student : group->getStudentVector()) {
            // check student's ID and SNP
            if (student->getSNP() == studentInfo ||
                student->getId() == studentInfo) {
                movingStudent = student;
                source = group;
                break;
            }
        }
    }

    // if we couldn't find a group of student we want to move
    if (source == nullptr)
        return;

    // if a group of a student and destination are equal
    if (source == destinationGroup)
        return;

    source->exclusionStudent(movingStudent);
    destinationGroup->addStudent(movingStudent);

    // maybe moved student has a better marks than current head of a group
    // so we should choose the new head
    destinationGroup->chooseHead();

    saveStaff();  // update data
}

void Deanery::printStatistics() {
    setlocale(LC_ALL, "RUS");  // for printing russian letters

    std::cout << "Deanery:\n";
    for (const auto* group : m_groups) {
        std::cout << "============================================\n";
        std::cout << *group;
        std::cout << "============================================\n";
    }
}

