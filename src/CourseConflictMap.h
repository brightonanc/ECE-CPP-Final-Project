/* CourseConflictMap.h
 * ECE2036 Final Project Part 2
 * 09-11-2017 Brighton ANCELIN
 *
 * Interface of CourseConflictMap class
 */

#include<vector>
#include "StudentList.h"
#include "CoursePair.h"

#ifndef COURSECONFLICTMAP_H_
#define COURSECONFLICTMAP_H_

using namespace std;

class CourseConflictMap {
public:
    CourseConflictMap();
    virtual ~CourseConflictMap();
    void addConflict(const Course& c1, const Course& c2, Student student);
    StudentList at(const Course& c1, const Course& c2);
private:
    vector<vector<StudentList>> innerMapping;
};

#endif /* COURSECONFLICTMAP_H_ */
