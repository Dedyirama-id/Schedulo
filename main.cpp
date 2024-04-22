#include <iostream>
#include <cstdlib>
#include <fstream>
#include "graph.h"
#include "utils.h"
#include "students.h"

using namespace std;

void showDefaultMenu();
void showCourseMenu();
void showStudentsMenu();
void showSchedule();
void loadInputFile();
void connectAllEdgesFromCourseList(vector<st::Course> newCourseList);
void pushCourselistToGraph(vector<st::Course> newCourseList);
void showResultMenu();

gr::Graph mainGraph;
st::StudentList studentList;

ifstream inputFile;
ofstream outputFile;

int main() {
  system("cls");

  showDefaultMenu();
  showCourseMenu();
  showStudentsMenu();

  system("cls");
  mainGraph.printGraph();
  u::wait("Tekan Enter Untuk Melanjutkan...");

  system("cls");
  cout << "# Menyusun Jadwal..." << endl;
  mainGraph.graphColoring();

  showResultMenu();

  inputFile.close();
  return 0;
}

void connectAllEdgesFromCourseList(vector<st::Course> newCourseList) {
  st::Course course1, course2;
  for (int i = 0; i < newCourseList.size(); i++) {
    course1 = newCourseList.at(i);
    for (int j = 0; j < newCourseList.size(); j++) {
      course2 = newCourseList.at(j);
      if (course1.id != course2.id) {
        mainGraph.addEdgeByID(course1.id, course2.id);
      }
    }
  }
}

void pushCourselistToGraph(vector<st::Course> newCourseList) {
  for (int i = 0; i < newCourseList.size(); i++) {
    st::Course newCourse = newCourseList.at(i);
    mainGraph.addVertex(newCourse.id, newCourse.name);
  }
}

void showDefaultMenu() {
  system("cls");
  cout << "# PROGRAM MATA KULIAH" << endl;
  cout << "1. Gunakan File External" << endl;
  cout << "2. Input Data Secara Manual" << endl;
  cout << "0. Batalkan dan Keluar Dari Program" << endl;

  int choice = u::getChoice(0, 2);
  switch (choice) {
  case 1:
    loadInputFile();
    return;

  default:
    return;
  }

  loadInputFile();
}

void loadInputFile() {
  string fileName = "input/";
  inputFile.open(fileName);
  while (inputFile.is_open() == false) {
    string input = u::getStringInput("\nMasukkan Nama File: (input.txt) ");
    if (input == "") input = "input.txt";
    if (input.find(".txt") == string::npos) input += ".txt";

    fileName += input;
    inputFile.open(fileName);
    if (inputFile.is_open() == false) cout << "File tidak ditemukan!" << endl;
  }

  while (inputFile.eof() == false) {
    string line;
    getline(inputFile, line);
    line = u::cleanString(line);

    st::Student newStudent;
    if (line == "") continue;

    newStudent.id = stoi(line.substr(0, line.find("-")));
    string name = line.substr(
      line.find("-") + 1,
      line.find("<") - (line.find("-") + 1)
    );
    name = u::cleanString(name);
    newStudent.name = u::capitalize(name);

    string courseListBlock = line.substr(
      line.find("<") + 1,
      line.find(">") - (line.find("<") + 1)
    );
    courseListBlock = u::removeSpaces(courseListBlock);
    courseListBlock = u::toUppercase(courseListBlock);

    while (courseListBlock.find(",") != string::npos) {
      const string id = courseListBlock.substr(0, courseListBlock.find(","));
      courseListBlock = courseListBlock.substr(courseListBlock.find(",") + 1);
      newStudent.courseList.push_back(st::Course(id, id));
    }
    newStudent.courseList.push_back(st::Course(courseListBlock, courseListBlock));

    studentList.add(newStudent);
    pushCourselistToGraph(newStudent.courseList);
    connectAllEdgesFromCourseList(newStudent.courseList);
  }
}

void showCourseMenu() {
  while (true) {
    system("cls");
    cout << "# DAFTAR MATA KULIAH" << endl;
    cout << "+---------------------------------------------------------+" << endl;
    cout << "ID \tMata Kuliah" << endl;
    mainGraph.printVertexList("\t");
    cout << "+---------------------------------------------------------+" << endl;
    cout << "1. Tambah Mata Kuliah" << endl;
    cout << "2. Simpan dan Lanjutkan" << endl;
    cout << "0. Batalkan dan Keluar Dari Program" << endl;

    int choice = u::getChoice(0, 2);
    string id, name;

    switch (choice) {
    case 1:
      id = u::getStringInput("\nMasukkan Kode Mata Kuliah (max 5 char): ", 5);
      name = u::getStringInput("Masukkan Nama Mata Kuliah (max 20 char): ", 20);
      mainGraph.addVertex(gr::Vertex(id, name));
      break;

    case 2:
      if (mainGraph.isVerticesEmpty() == false) return;
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
    studentList.print();
    cout << "+---------------------------------------------------------+" << endl;
    cout << "1. Tambah Mahasiswa" << endl;
    cout << "2. Simpan dan Lanjutkan" << endl;
    cout << "0. Batalkan dan Keluar Dari Program" << endl;

    int choice = u::getChoice(0, 2);
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
      for (const auto &v : mainGraph.vertices) {
        cout << " - [" << v.id << "] " << v.name;
        bool isTaken = u::getBoolInput();
        if (isTaken) newStudent.courseList.push_back(st::Course(v.id, v.name));
      }

      connectAllEdgesFromCourseList(newStudent.courseList);
      studentList.add(newStudent);
      break;

    case 2:
      if (studentList.isEmpty() == false) return;
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
  for (auto session = mainGraph.colorList.begin(); session != mainGraph.colorList.end(); session++) {
    cout << sessionNumber << "\t";
    for (auto course = session->begin(); course != session->end(); course++) {
      cout << mainGraph.getVertexByID(*course).id;
      if (course != session->end() - 1) cout << ", ";
    }
    cout << endl;
    sessionNumber++;
  }

  cout << "+---------------------------------------------------------+" << endl;
}

void showResultMenu() {
  while (true) {
    system("cls");
    showSchedule();
    cout << "1. Simpan ke File" << endl;
    cout << "0. Keluar Tanpa Menyimpan" << endl;

    int choice = u::getChoice(0, 1);
    string fileName = "output/";
    string input;
    int sessionNumber;
    switch (choice) {
    case 1:
      while (true) {
        input = u::getStringInput("\nMasukkan Nama File: (output.txt) ");
        if (input == "") input = "output.txt";
        if (input.find(".txt") == string::npos) input += ".txt";

        fileName += input;
        inputFile.open(fileName);
        if (inputFile.is_open() == true) break;
        cout << "Gagal Membuat File! Coba Lagi..." << endl;
      }

      outputFile.open(fileName, ios::out | ios::trunc);
      outputFile << "Sesi \tMata Kuliah" << endl;

      sessionNumber = 1;
      for (auto session = mainGraph.colorList.begin(); session != mainGraph.colorList.end(); session++) {
        outputFile << sessionNumber << "\t";
        for (auto course = session->begin(); course != session->end(); course++) {
          outputFile << mainGraph.getVertexByID(*course).id;
          if (course != session->end() - 1) outputFile << ",";
        }
        outputFile << endl;
        sessionNumber++;
      }
      outputFile.close();

      cout << "Jadwal Telah Disimpan!" << endl;
      u::wait();

    default:
      return;
    }
  }
}