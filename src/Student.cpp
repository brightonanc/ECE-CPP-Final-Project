/* Student.cpp
 * ECE2036 Final Project Part 2
 * 09-11-2017 Brighton ANCELIN
 *
 * Implementation of Student class
 */

#include "Course.h"
#include "CoursePair.h"
#include "Student.h"

Student::Student(string gtid, string name, vector<Course> courseRequests) :
        gtid{gtid}, name{name}, courseRequests{courseRequests} {}

Student::~Student() {}

string Student::getGTID() const {
    return this->gtid;
}

string Student::getName() const {
    return this->name;
}

vector<Course> Student::getCourseRequests() const {
    return this->courseRequests;
}

/* Returns all conflicts this student might have */
vector<CoursePair> Student::getCourseConflicts() const {
    vector<CoursePair> conflicts;
    // Iterate over all courses, except the last one
    for(size_t i{0}; i < this->courseRequests.size()-1; i++) {
        // Start iterating one above i
        for(size_t j{i+1}; j < this->courseRequests.size(); j++) {
            conflicts.push_back(CoursePair(static_cast<Course>(this->courseRequests[i]), static_cast<Course>(this->courseRequests[j])));
        }
    }
    return conflicts;
}
