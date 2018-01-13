/* StudentList.h
 * ECE2036 Final Project Part 2
 * 09-11-2017 Brighton ANCELIN
 *
 * Interface of StudentList class
 */

#include<vector>
#include "Student.h"

#ifndef STUDENTLIST_H_
#define STUDENTLIST_H_

using namespace std;

class StudentList {
public:
    StudentList();
    virtual ~StudentList();
    Student operator[](const int& index) const;
    Student& operator[](const int& index);
    void addStudent(Student student);
    vector<Student> getInnerVec() const;
    int getSize() const;
private:
    vector<Student> innerVec;
};

#endif /* STUDENTLIST_H_ */
