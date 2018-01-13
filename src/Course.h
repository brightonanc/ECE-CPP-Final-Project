/* Course.h
 * ECE2036 Final Project Part 2
 * 05-12-2017 Brighton ANCELIN
 *
 * Interface of Course class
 */

#ifndef COURSE_H_
#define COURSE_H_

#include<string>
#include<vector>

using namespace std;

class Course {
public:
    Course(string code, string title, string prof);
    Course(int invalidPlaceholder);
    virtual ~Course();
    static vector<Course> getAllCourses();
    static Course getCourseByCode(const string& code);
    static Course getCourseByEnumID(const int& enumID);
    string getCode() const;
    string getTitle() const;
    string getProf() const;
    int getEnumID() const;
    bool isValid() const;
private:
    static int enum_ctr;
    static vector<Course> all_courses;
    int enumID;
    string code;
    string title;
    string prof;
};

#endif /* COURSE_H_ */
