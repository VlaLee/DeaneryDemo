// Copyright 2024 Lee V.

#ifndef INCLUDE_DEANERY_H
#define INCLUDE_DEANERY_H

#include <string>
#include <vector>

#include "Group.h"

class Deanery {
 private:
    std::vector<Group*> m_groups;
    std::string m_groupsFileName;  // file name for groups
    std::string m_studentsFileName;  // file name for students

    // creating groups and students objects
    void createGroups();
    void hireStudents();

    // searching group by title
    Group* searchGroup(const std::string groupTitle);

    // updating data in files
    void saveStaff();

 public:
    explicit Deanery(const std::string groupsFileName,
        const std::string studentsFileName);
    ~Deanery();

    void initHeads();

    // there are default parameters
    // number - the number of marks we want to add
    // mark - the mark we want to add
    // if mark == -1 (default value) marks will be random
    void addMarksToAll(unsigned int number = 3, int mark = -1);
    void fireStudents();

    // studentInfo - ID or SNP of a student we want to move
    // destination - the title of a group student will be moved
    void moveStudent(const std::string studentInfo,
        const std::string destination);

    void printStatistics();
};

#endif  // INCLUDE_DEANERY_H
