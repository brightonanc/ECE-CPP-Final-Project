/* StudentList.cpp
 * ECE2036 Final Project Part 2
 * 09-11-2017 Brighton ANCELIN
 *
 * Implementation of StudentList class
 */

#include "StudentList.h"

StudentList::StudentList() {}

StudentList::~StudentList() {}

Student StudentList::operator[](const int& index) const {
    return this->innerVec[index];
}

Student& StudentList::operator[](const int& index) {
    return this->innerVec[index];
}

void StudentList::addStudent(Student student) {
    this->innerVec.push_back(student);
}

vector<Student> StudentList::getInnerVec() const {
    return this->innerVec;
}

int StudentList::getSize() const {
    return this->innerVec.size();
}

