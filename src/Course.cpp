/* Course.cpp
 * ECE2036 Final Project Part 2
 * 05-12-2017 Brighton ANCELIN
 *
 * Implementation of Course class
 */

#include<iostream>
#include<string>
#include "Course.h"

using namespace std;

/* Used for unique identifier */
int Course::enum_ctr{0};
/* Static vector of all unique course objects */
vector<Course> Course::all_courses{};

/* Instantiates a new course and gives it a unique integer identifier*/
Course::Course(string code, string title, string prof) :
        code{code}, title{title}, prof{prof}, enumID{enum_ctr} {
    // If this Course shares code with another (duplicate), do not add it to the static all_courses vector
    for(const Course& c : getAllCourses()) {
        if(c.getCode() == code) {
            cout << "Duplicate course listing \"" << code << "\". Ignoring the latter duplicate." << endl;
            return;
        }
    }
    enum_ctr++; // Increment unique identifier variable
    all_courses.push_back(*this); // Add this to all_courses vector
}

/* Constructor for an invalid course. Used as a flag, not an object, in practice */
Course::Course(int invalidPlaceholder) :
        code{"N/A"}, title{"N/A"}, prof{"N/A"}, enumID{-1} {}

Course::~Course() {}

vector<Course> Course::getAllCourses() {
    return all_courses;
}

Course Course::getCourseByCode(const string& code) {
    // Search for this course in vector of known courses
    for(const Course& c : all_courses) {
        if(code == c.code)
            return c;
    }
    // If course can't be found, say so and create an invalid one
    return Course{-1};
}

Course Course::getCourseByEnumID(const int& enumID) {
    return all_courses.at(enumID);
}

string Course::getCode() const {
    return this->code;
}
string Course::getTitle() const {
    return this->title;
}
string Course::getProf() const {
    return this->prof;
}
int Course::getEnumID() const {
    return this->enumID;
}

bool Course::isValid() const {
    return this->enumID != -1;
}

