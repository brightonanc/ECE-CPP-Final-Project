/* Main.cpp
 * ECE2036 Final Project Part 2
 * 05-12-2017 Brighton ANCELIN
 *
 * Primary driving program
 */

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include "Course.h"
#include "CourseConflictMap.h"
#include "CoursePair.h"
#include "Student.h"
#include "StudentList.h"

using namespace std;

vector<string> tokenizeFile(istream& stream);

int main() {
    cout << "Please input Classes file name: \n";
    string classesFile;
    getline(cin, classesFile);
    cout << "Please input Students file name: \n";
    string studentsFile;
    getline(cin, studentsFile);

    string dummyStr;

    ifstream courseInStream{classesFile, ios::in};
    if(!courseInStream) {
        cerr << "File \"" << classesFile << "\" could not be opened." << endl;
        exit(EXIT_FAILURE);
    }

    getline(courseInStream, dummyStr);
    string str;
    // Build all Courses (full vector retained as a static member of the Course class)
    while(getline(courseInStream, str)) {
        stringstream strStream{str};
        vector<string> tokens = tokenizeFile(strStream);
        if(tokens.size() < 3) {
            cout << "File \"" << classesFile << "\" has an incomplete line. This line will be ignored." << endl;
            continue;
        }
        string code = tokens.at(0);
        string title = tokens.at(1);
        string prof = tokens.at(2);
        Course{code, title, prof};
    }

    ifstream studentInStream{studentsFile, ios::in};
    if(!studentInStream) {
        cerr << "File \"" << studentsFile << "\" could not be opened." << endl;
        exit(EXIT_FAILURE);
    }

    vector<Student> students;
    getline(studentInStream, dummyStr);
    // Build all students and add them to local vector
    // Also build rosters (vector of StudentList) for each course
    vector<StudentList> rosters = vector<StudentList>(Course::getAllCourses().size(), StudentList());
    while(getline(studentInStream, str)) {
        stringstream strStream{str};
        vector<string> tokens = tokenizeFile(strStream);
        if(tokens.size() < 3) {
            cout << "File \"" << studentsFile << "\" has an incomplete line. This line will be ignored." << endl;
            continue;
        }
        string gtid = tokens.at(0);
        string name = tokens.at(1);
        vector<Course> curStudCourses;
        for(size_t i{2}; i < tokens.size(); i++) {
            Course c{Course::getCourseByCode(tokens.at(i))};
            if(c.isValid()) {
                curStudCourses.push_back(Course::getCourseByCode(tokens.at(i)));
            } else {
                cout << "Student \"" << name << "\" requested course \"" << tokens.at(i) << "\", which is not offered. Ignoring request." << endl;
            }
        }
        Student curStudent{gtid, name, curStudCourses};
        students.push_back(curStudent);
        for(const Course& c : curStudCourses) {
            // Safeguard against extra-courses being added by students and indexing beyond the vector size
            while (c.getEnumID() >= rosters.size()) {
                rosters.push_back(StudentList());
            }
            rosters.at(c.getEnumID()).addStudent(curStudent);
        }
    }

    // ONLY CREATE THIS WHEN COURSES ARE FULLY INITIALIZED
    CourseConflictMap conflicts;
    // For all students, add all their conflicts to the conflicts object
    for(const Student& student : students) {
        for(const CoursePair& cpair : student.getCourseConflicts()) {
            conflicts.addConflict(cpair.getCourse1(), cpair.getCourse2(), student);
        }
    }

    // Add edges to the conflict matrix for professor conflicts
    CourseConflictMap conflictsProfs{conflicts};
    for(size_t i{0}; i < Course::getAllCourses().size(); i++) {
        for(size_t j{i+1}; j < Course::getAllCourses().size(); j++) {
            Course c1{Course::getCourseByEnumID(i)};
            Course c2{Course::getCourseByEnumID(j)};
            if(c1.getProf() == c2.getProf()) {
                conflictsProfs.addConflict(c1, c2, Student{"N/A", c1.getProf(), vector<Course>()});
            }
        }
    }

    // Build all timeslots of courses
    // In effect, each course goes through all currently existing timeslots and checks to see if the course can go in each one.
    // Once the course finds a timeslot the course can join, the course joins the timeslot.
    // If the course never finds such a timeslot, the course will be placed in a new timeslot
    vector<vector<Course>> timeslots;
    for(Course c : Course::getAllCourses()) {
        bool hasBeenInserted = false;
        for(vector<Course>& curBlock : timeslots) {
            // If the timeslot is full, skip it
            if(curBlock.size() >= 6) {
                continue;
            }
            // If the course has already found a timeslot, stop searching for a timeslot
            if(hasBeenInserted) {
                break;
            }
            // If any course currently in the timeslot conflicts with this new course, break and try the next timeslot
            bool canInsertCurCourse = true;
            for(Course c2 : curBlock) {
                if(conflictsProfs.at(c, c2).getSize() != 0) {
                    canInsertCurCourse = false;
                    break;
                }
            }
            // If no course currently in the timeslot conflicts with this new course, add the new course to the timeslot
            if(canInsertCurCourse) {
                curBlock.push_back(c);
                hasBeenInserted = true;
            }
        }
        // If no currently existing time slot could hold this new course, give it its own timeslot
        if(!hasBeenInserted) {
            vector<Course> newBlock(1, c);
            timeslots.push_back(newBlock);
        }
    }

    ofstream conflMatFile{"theConflictMatrix.csv", ios::out};
    if(!conflMatFile) {
        cerr << "File theConflictMatrix.csv couldn't be made." << endl;
        exit(EXIT_FAILURE);
    }

    // Write the header to the file
    for(const Course& c1 : Course::getAllCourses()) {
        conflMatFile << "," << c1.getCode();
    }
    conflMatFile << endl;
    for(const Course& c1 : Course::getAllCourses()) {
        // Write the side column entries
        conflMatFile << c1.getCode();
        for(const Course& c2 : Course::getAllCourses()) {
            if(c1.getEnumID() == c2.getEnumID()) {
                // Leave the cell 0 for impossible conflicts
                conflMatFile << ",0";
                continue;
            }
            // Output the conflict count
            conflMatFile << "," << conflicts.at(c1, c2).getSize();
        }
        conflMatFile << endl;
    }

    ofstream whoHasConflFile{"whoHasConflicts.txt", ios::out};
    if(!whoHasConflFile) {
        cerr << "File whoHasConflicts.txt couldn't be made." << endl;
        exit(EXIT_FAILURE);
    }

    // Print header to file
    whoHasConflFile << "List of class pairs and students with conflicts for that class pair:\n";
    for(const CoursePair& cpair : CoursePair::getAllUniqueCoursePairs()) {
        // Print current course pair title
        whoHasConflFile << "For the course pair: " << cpair.getCourse1().getCode()
                << " : " << cpair.getCourse2().getCode() << endl;
        // Print each student's name below the title
        for(const Student& student : conflicts.at(cpair.getCourse1(), cpair.getCourse2()).getInnerVec()) {
            whoHasConflFile << student.getName() << endl;
        }
        // Separate regions with an extra newline character
        whoHasConflFile << endl;
    }

    ofstream scheduleFile{"Schedule.txt", ios::out};
    if(!scheduleFile) {
        cerr << "File Schedule.txt couldn't be made." << endl;
        exit(EXIT_FAILURE);
    }

    // Print timeslot concerns to the console
    if(timeslots.size() > 24) {
        cout << "There's not enough time in a day for this many classes" << endl;
        cout << "It is necessary to remove to some classes, conflicts, or find more classrooms" << endl;
    } else if(timeslots.size() > 16) {
        cout << "Classes will run past midnight. That might upset some students" << endl;
    } else if(timeslots.size() > 14) {
        cout << "Classes will run past 10PM. That might upset some students." << endl;
    }

    size_t blockHour{8};
    for(const vector<Course>& curBlock : timeslots) {
        // Print the block hour
        scheduleFile << (blockHour++ % 24) << ":00";
        // Print all courses at this block hour
        for(const Course& c : curBlock) {
            scheduleFile << " " << c.getCode();
        }
        scheduleFile << endl;
    }

    ofstream classRollsFile{"ClassRolls.csv", ios::out};
    if(!classRollsFile) {
        cerr << "File ClassRolls.csv couldn't be made." << endl;
        exit(EXIT_FAILURE);
    }

    for(size_t i{0}; i < rosters.size(); i++) {
        // Print course name
        classRollsFile << Course::getCourseByEnumID(i).getCode() << ":" << endl;
        // Print all students in the course, enclosed in quotes to keep a single column
        for(const Student& curStud : rosters.at(i).getInnerVec()) {
            classRollsFile << "\"" << curStud.getName() << "\"" << endl;
        }
        classRollsFile << endl;
    }
}

/* Tokenizes a CSV file line, where columns are separated by commas, rows by newlines, and quotes encapsulate text directly*/
vector<string> tokenizeFile(istream& stream) {
    vector<string> tokens;
    string str;
    // Read up to next instance of opening quote
    while(getline(stream, str, '"')) {
        stringstream strStream{str};
        // Read from strStream up to first comma
        while(getline(strStream, str, ',')) {
            // Push token
            tokens.push_back(str);
        }
        // If a closing quote is found (i.e. not EOF)
        if(getline(stream, str, '"')) {
            // Push token
            tokens.push_back(str);
            // Remove left-over following delimiter
            if(',' == stream.peek()) {
                getline(stream, str, ',');
            }
        }
    }
    return tokens;
}


