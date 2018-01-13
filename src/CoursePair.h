/* CoursePair.h
 * ECE2036 Final Project Part 2
 * 09-11-2017 Brighton ANCELIN
 *
 * Interface of CoursePair class
 */

#ifndef COURSEPAIR_H_
#define COURSEPAIR_H_

#include "Course.h"

using namespace std;

class CoursePair {
public:
    CoursePair(Course c1, Course c2);
    virtual ~CoursePair();
    static vector<CoursePair> getAllUniqueCoursePairs();
    Course getCourse1() const;
    Course getCourse2() const;
private:
    Course c1;
    Course c2;
};

#endif /* COURSEPAIR_H_ */
