#pragma once
#include <iostream>
#include <vector>

using namespace std;

namespace st {
  struct Course {
    int id;
    string name;
    string alias;

    Course(int id, string name, string alias) {
      this->id = id;
      this->name = name;
      this->alias = alias;
    }
  };

  class Student {
  public:
    int id;
    string name;
    vector<Course> courseList;

    Student() {}

    Student(int id, string name) {
      this->id = id;
      this->name = name;
    }

    void print(string defaultSeparator = "\t", string courseListSeparator = ", ") {
      cout << id << defaultSeparator << name << defaultSeparator << defaultSeparator;
      for (auto it = courseList.begin(); it != courseList.end(); it++) {
        cout << it->alias;
        if (it != courseList.end() - 1) cout << courseListSeparator;
      }
    }
  };

  class StudentList {
  public:
    vector<Student> StudentList;

    void add(Student newStudent) {
      StudentList.push_back(newStudent);
    }

    void add(int id, string name) {
      StudentList.push_back(Student(id, name));
    }

    void print(string defaultSeparator = "\t", string courseListSeparator = ", ") {
      for (auto it = StudentList.begin(); it != StudentList.end(); it++) {
        it->print(defaultSeparator, courseListSeparator);
        cout << endl;
      }
    }
  };
}