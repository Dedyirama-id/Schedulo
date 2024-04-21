#pragma once
#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;

namespace st {
  struct Course {
    string id;
    string name;

    Course(string id, string name) : id(id), name(name) {}
  };

  class Student {
  public:
    int id;
    string name;
    vector<Course> courseList;

    Student() {}
    Student(int id, string name) : id(id), name(name) {}
    Student(int id, string name, vector<Course> courseList) : id(id), name(name), courseList(courseList) {}

    void print(string courseListSeparator = ", ") {
      cout << id << "\t" << name;
      if (name.length() > 15) cout << "\t";
      else if (name.length() < 9) cout << "\t\t\t";
      else if (name.length() <= 15) cout << "\t\t";

      for (auto it = courseList.begin(); it != courseList.end(); it++) {
        cout << it->id;
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

    void add(int id, string name, vector<Course> courseList) {
      Student newStudent(id, name, courseList);
      studentList.push_back(newStudent);
    }

    void print(string courseListSeparator = ", ") {
      for (int i = 0; i < studentList.size(); i++) {
        studentList.at(i).print(courseListSeparator);
        cout << endl;
      }
    }
  };
}