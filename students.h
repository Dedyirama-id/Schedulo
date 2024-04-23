#pragma once
#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;

namespace st {
  struct Course {
    string id;
    string name;

    Course() {}
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

    void pushCourselistToGraph(gr::Graph &graph) {
      for (int i = 0; i < courseList.size(); i++) {
        st::Course newCourse = courseList.at(i);
        graph.addVertex(newCourse.id, newCourse.name);
      }
    }

    void connectAllEdgesFromCourseList(gr::Graph &graph) {
      Course course1, course2;
      for (int i = 0; i < courseList.size(); i++) {
        course1 = courseList.at(i);
        for (int j = 0; j < courseList.size(); j++) {
          course2 = courseList.at(j);
          if (course1.id != course2.id) {
            graph.addEdgeByID(course1.id, course2.id);
          }
        }
      }
    }
  };

  class StudentList {
  public:
    gr::Graph &graphRef;
    vector<Student> studentList;

    StudentList(gr::Graph &g) : graphRef(g) {}

    bool isEmpty() {
      return studentList.size() == 0;
    }

    void add(Student newStudent) {
      studentList.push_back(newStudent);
      newStudent.pushCourselistToGraph(graphRef);
      newStudent.connectAllEdgesFromCourseList(graphRef);
    }

    void add(int id, string name, vector<Course> courseList) {
      Student newStudent(id, name, courseList);
      add(newStudent);
    }

    void print(string courseListSeparator = ", ") {
      for (int i = 0; i < studentList.size(); i++) {
        studentList.at(i).print(courseListSeparator);
        cout << endl;
      }
    }
  };
}