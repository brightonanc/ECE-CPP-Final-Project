/* CoursePair.cpp
 * ECE2036 Final Project Part 2
 * 09-11-2017 Brighton ANCELIN
 *
 * Implementation of CoursePair class
 */

#include "Course.h"
#include "CoursePair.h"

using namespace std;

CoursePair::CoursePair(Course c1, Course c2) :
        c1{c1}, c2{c2} {}

CoursePair::~CoursePair() {}

/* Creates upper triangular matrix entries, minus the diagonal, for a conflicts matrix
 */
vector<CoursePair> CoursePair::getAllUniqueCoursePairs() {
    vector<CoursePair> uniqPairs;
    vector<Course> allCourses = Course::getAllCourses();
    // Iterate over all courses, except the last one
    for(size_t i{0}; i < allCourses.size()-1; i++) {
        // Start iterating one above i
        for(size_t j{i+1}; j < allCourses.size(); j++) {
            uniqPairs.push_back(CoursePair(allCourses[i], allCourses[j]));
        }
    }
    return uniqPairs;
}

Course CoursePair::getCourse1() const {
    return this->c1;
}
Course CoursePair::getCourse2() const {
    return this->c2;
}


