/* CourseConflictMap.cpp
 * ECE2036 Final Project Part 2
 * 09-11-2017 Brighton ANCELIN
 *
 * Implementation of CourseConflictMap class
 */

#include "Course.h"
#include "CourseConflictMap.h"

/* REQUIRES ALL COURSES TO HAVE ALREADY BEEN INITIALIZED
 * Initializes vector mapping to an upper triangular matrix, minus the diagonal
 */
CourseConflictMap::CourseConflictMap() {
    const size_t dim = Course::getAllCourses().size();
    for(size_t i{0}; i < dim-1; i++) {
        this->innerMapping.push_back(vector<StudentList>(dim-i-1, StudentList()));
    }
}

CourseConflictMap::~CourseConflictMap() {}

/* Adds a conflict to the inner mapping
 * Uses an upper triangular matrix, so the first course enum must be less than the second
 */
void CourseConflictMap::addConflict(const Course& c1, const Course& c2, Student student) {
    if(c1.getEnumID() < c2.getEnumID()) {
        this->innerMapping.at(c1.getEnumID()).at(c2.getEnumID()-c1.getEnumID()-1).addStudent(student);
    } else {
        this->innerMapping.at(c2.getEnumID()).at(c1.getEnumID()-c2.getEnumID()-1).addStudent(student);
    }
}

/* Gets a conflict from the inner mapping
 * Uses an upper triangular matrix, so the first course enum must be less than the second
 */
StudentList CourseConflictMap::at(const Course& c1, const Course& c2) {
    if(c1.getEnumID() < c2.getEnumID()) {
        return this->innerMapping.at(c1.getEnumID()).at(c2.getEnumID()-c1.getEnumID()-1);
    } else {
        return this->innerMapping.at(c2.getEnumID()).at(c1.getEnumID()-c2.getEnumID()-1);
    }
}
