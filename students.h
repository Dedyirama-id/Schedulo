#pragma once
#include <iostream>
#include <vector>

using namespace std;

namespace st {
  struct Course {
    int id;
    string name;
    string code;

    Course(int id, string name, string code) {
      this->id = id;
      this->name = name;
      this->code = code;
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

    void print(string courseListSeparator = ", ") {
      cout << id << "\t" << name;
      if (name.length() > 15) cout << "\t";
      else if (name.length() < 9) cout << "\t\t\t";
      else if (name.length() <= 15) cout << "\t\t";

      for (auto it = courseList.begin(); it != courseList.end(); it++) {
        cout << it->code;
        if (it != courseList.end() - 1) cout << courseListSeparator;
      }
      if (courseList.begin() == courseList.end()) cout << "-";
    }
  };

  class StudentList {
  public:
    vector<Student> studentList;

    bool isEmpty() {
      return studentList.size() == 0;
    }

    void add(Student newStudent) {
      studentList.push_back(newStudent);
    }

    void add(int id, string name) {
      studentList.push_back(Student(id, name));
    }

    void print(string courseListSeparator = ", ") {
      for (auto it = studentList.begin(); it != studentList.end(); it++) {
        it->print(courseListSeparator);
        cout << endl;
      }
    }
  };
}