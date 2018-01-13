/* Student.h
 * ECE2036 Final Project Part 2
 * 09-11-2017 Brighton ANCELIN
 *
 * Interface of Student class
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include<string>
#include<vector>
#include "Course.h"
#include "CoursePair.h"

using namespace std;

class Student {
public:
    Student(string gtid, string name, vector<Course> courseRequests);
    virtual ~Student();
    string getGTID() const;
    string getName() const;
    vector<Course> getCourseRequests() const;
    vector<CoursePair> getCourseConflicts() const;
private:
    string gtid;
    string name;
    vector<Course> courseRequests;
};

#endif /* STUDENT_H_ */
