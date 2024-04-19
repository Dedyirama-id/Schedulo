#include <iostream>
#include <cstdlib>
#include "graph.h"
#include "utils.h"
#include "students.h"

using namespace std;

void connectingEdge(int *classList, int totalClass);
void showCourseMenu();
void showStudentsMenu();
void showSchedule();

gr::Graph g;
st::StudentList s;

int main() {
  system("cls");

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

void connectingEdge(int *classList, int totalClass) {
  for (int i = 0; i < totalClass; i++) {
    if (classList[i] != 1) continue;
    for (int j = 0; j < totalClass; j++) {
      if (i == j) continue;
      else if (classList[j] == 1) g.addEdgeByID(i + 1, j + 1);
    }
  }
}

void showCourseMenu() {
  int id = 1;
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
    string name, code;

    switch (choice) {
    case 1:
      name = u::getStringInput("\nMasukkan Nama Mata Kuliah (max 20 char): ", 20);
      code = u::getStringInput("Masukkan Nama Kode Mata Kuliah (max 5 char): ", 5);
      g.addVertex(gr::Vertex(id, name, code));
      id++;
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
        cout << " - [" << v.code << "] " << v.name;
        bool isTaken = u::getBoolInput();
        if (isTaken) newStudent.courseList.push_back(st::Course(v.id, v.name, v.code));
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
      cout << g.getVertexByID(*course).code;
      if (course != session->end() - 1) cout << ", ";
    }
    cout << endl;
    sessionNumber++;
  }

  cout << "+---------------------------------------------------------+" << endl;
}
