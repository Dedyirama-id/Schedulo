#include <iostream>
#include <cstdlib>
#include <fstream>
#include "graph.h"
#include "utils.h"
#include "students.h"

using namespace std;

// void connectingEdge(int *classList, int totalClass);
void showDefaultMenu();
void showCourseMenu();
void showStudentsMenu();
void showSchedule();
void loadFileInput();

gr::Graph g;
st::StudentList s;

ifstream fileInput;

int main() {
  system("cls");

  showDefaultMenu();
  cout << "Check!!" << endl;
  showCourseMenu();
  showStudentsMenu();

  system("cls");
  g.printGraph();
  u::wait("Tekan Enter Untuk Melanjutkan...");

  system("cls");
  cout << "# Menyusun Jadwal..." << endl;
  g.graphColoring();

  showSchedule();

  return 0;
}

// void connectingEdge(int *classList, int totalClass) {
//   for (int i = 0; i < totalClass; i++) {
//     if (classList[i] != 1) continue;
//     for (int j = 0; j < totalClass; j++) {
//       if (i == j) continue;
//       else if (classList[j] == 1) g.addEdgeByID(i + 1, j + 1);
//     }
//   }
// }

void showDefaultMenu() {
  system("cls");
  cout << "# PROGRAM MATA KULIAH" << endl;
  cout << "1. Gunakan File External" << endl;
  cout << "2. Input Data Secara Manual" << endl;
  cout << "0. Batalkan dan Keluar Dari Program" << endl;

  int choice = u::getChoice(0, 2);
  switch (choice) {
  case 1:
    loadFileInput();
    return;
  default: 
    return;
  }
}

void showCourseMenu() {
  while (true) {
    system("cls");
    cout << "# DAFTAR MATA KULIAH" << endl;
    cout << "+---------------------------------------------------------+" << endl;
    cout << "ID \tKode \tMata Kuliah" << endl;
    g.printVertexList("\t");
    cout << "+---------------------------------------------------------+" << endl;
    cout << "1. Tambah Mata Kuliah" << endl;
    cout << "2. Simpan dan Lanjutkan" << endl;
    cout << "0. Batalkan dan Keluar Dari Program" << endl;

    int choice = u::getChoice(0, 2);
    string id, name;

    switch (choice) {
    case 1:
      id = u::getStringInput("Masukkan Nama Kode Mata Kuliah (max 5 char): ", 5);
      name = u::getStringInput("\nMasukkan Nama Mata Kuliah (max 20 char): ", 20);
      g.addVertex(gr::Vertex(id, name));
      break;
    case 2:
      if (g.isVerticesEmpty() == false) return;
      cout << "Harus ada minimal 1 mata kuliah yang ditambahkan!" << endl;
      u::wait();
      break;
    case 0:
      exit(0);
    default:
      break;
    }
  }
}

void showStudentsMenu() {
  while (true) {
    system("cls");
    cout << "# DAFTAR MAHASISWA" << endl;
    cout << "+---------------------------------------------------------+" << endl;
    cout << "ID \tNama Mahasiswa \t\tMata Kuliah Pilihan" << endl;
    s.print();
    cout << "+---------------------------------------------------------+" << endl;
    cout << "1. Tambah Mahasiswa" << endl;
    cout << "2. Simpan dan Lanjutkan" << endl;
    cout << "0. Batalkan dan Keluar Dari Program" << endl;


    int choice = u::getChoice(0, 1);
    string name;
    int id = -1;

    st::Student newStudent;
    switch (choice) {
    case 1:
      id = u::getIntInput("\nMasukkan ID Mahasiswa: ");
      name = u::getStringInput("Masukkan Nama Mahasiswa (max 20 char): ", 20);
      newStudent.id = id;
      newStudent.name = name;

      cout << "Mata Kuliah Yang Diambil: " << endl;
      for (const auto &v : g.vertices) {
        cout << " - [" << v.id << "] " << v.name;
        bool isTaken = u::getBoolInput();
        if (isTaken) newStudent.courseList.push_back(st::Course(v.id, v.name));
      }

      for (auto it = newStudent.courseList.begin(); it != newStudent.courseList.end(); it++) {
        for (auto it2 = newStudent.courseList.begin(); it2 != newStudent.courseList.end(); it2++) {
          if (it->id != it2->id) {
            g.addEdgeByID(it->id, it2->id);
          }
        }
      }

      s.add(newStudent);
      break;
    case 2:
      if (s.isEmpty() == false) return;
      cout << "Harus ada minimal 1 mahasiswa yang ditambahkan!" << endl;
      u::wait();
      break;
    case 0:
      exit(0);
    default:
      break;
    }
  }
}

void showSchedule() {
  system("cls");
  cout << "# JADWAL" << endl;
  cout << "+---------------------------------------------------------+" << endl;
  cout << "Sesi \tMata Kuliah" << endl;

  int sessionNumber = 1;
  for (auto session = g.colorList.begin(); session != g.colorList.end(); session++) {
    cout << sessionNumber << "\t";
    for (auto course = session->begin(); course != session->end(); course++) {
      cout << g.getVertexByID(*course).id;
      if (course != session->end() - 1) cout << ", ";
    }
    cout << endl;
    sessionNumber++;
  }

  cout << "+---------------------------------------------------------+" << endl;
}

string fixDoubleSpaces(string str) {
  while (str.find("  ") != string::npos) {
    str = str.replace(str.find("  "), 2, " ");
  }
  return str;
}

string removeSpaces(string str) {
  while (str.find(" ") != string::npos) {
    str = str.replace(str.find(" "), 1, "");
  }
  return str;
}

void connectAllEdges(st::Student newStudent) {
  for (auto it = newStudent.courseList.begin(); it != newStudent.courseList.end(); it++) {
    for (auto it2 = newStudent.courseList.begin(); it2 != newStudent.courseList.end(); it2++) {
      if (it->id != it2->id) {
        g.addEdgeByID(it->id, it2->id);
      }
    }
  }
}

void pushCourselistToGraph(st::Student newStudent) {
  for (auto it = newStudent.courseList.begin(); it != newStudent.courseList.end(); it++) {
    g.addVertex(it->id, it->name);
  }
}

void loadFileInput() {
  string fileName = "input/";
  while (fileInput.is_open() == false) {
    fileName += u::getStringInput("Masukkan Nama File: ");
    fileInput.open(fileName);
    if (fileInput.is_open() == false) cout << "File tidak ditemukan!" << endl;
  }
  
  while (fileInput.eof() == false) {
    string line;
    getline(fileInput, line);
    line = fixDoubleSpaces(line);

    st::Student newStudent;

    if (line != "") {
      newStudent.id = stoi(line.substr(0, line.find("-")));
      newStudent.name = line.substr(
        line.find("-") + 1,
        line.find("<") - (line.find("-") + 1)
      );

      string courseListBlock = line.substr(
        line.find("<") + 1,
        line.find(">") - (line.find("<") + 1)
      );
      courseListBlock = removeSpaces(courseListBlock);

      while (courseListBlock.find(",") != string::npos) {
        const string id = courseListBlock.substr(0, courseListBlock.find(","));
        courseListBlock = courseListBlock.substr(courseListBlock.find(",") + 1);
        newStudent.courseList.push_back(st::Course(id, id));
      }

      newStudent.courseList.push_back(st::Course("aa", "aa"));

      cout << "Check!!" << endl;
      newStudent.print();
      pushCourselistToGraph(newStudent);
      cout << "Check!!" << endl;
      connectAllEdges(newStudent);
      cout << "Check!!" << endl;
      s.add(newStudent);
      cout << "Check!!" << endl;
      u::wait();
    }
  }
}