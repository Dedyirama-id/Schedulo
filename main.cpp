#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include "graph.h"
#include "utils.h"
#include "students.h"

using namespace std;

#define DIVIDER "+---------------------------------------------------------+"

void showDefaultMenu();
void showCourseMenu();
void showStudentsMenu();
void showSchedule();
void loadInputFile(string fileName = "");
void showResultMenu();
void saveColorListToFile(string fileName);

gr::Graph mainGraph;
st::StudentList studentList(mainGraph);

ifstream inputFile;
ofstream outputFile;

string inputFileName = "";
string outputFileName = "";
bool skipAll = false;

int main(int argc, char *argv[]) {
  system("cls");

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
      inputFileName = argv[i + 1];
    } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
      outputFileName = argv[i + 1];
    } else if (strcmp(argv[i], "--skip") == 0) {
      skipAll = true;
    }
  }

  if (inputFileName == "") {
    showDefaultMenu();
    showCourseMenu();
    showStudentsMenu();
  } else {
    loadInputFile(inputFileName);
  }

  if (skipAll == false) {
    system("cls");
    mainGraph.printGraph();
    u::wait("Tekan Enter Untuk Melanjutkan...");

    system("cls");
    cout << "# Menyusun Jadwal..." << endl;
  }

  mainGraph.graphColoring();
  if (outputFileName == "") {
    showResultMenu();
  } else {
    showSchedule();
    saveColorListToFile(outputFileName);
  }

  inputFile.close();
  return 0;
}

st::Student getNewStudentData() {
  st::Student newStudent;
  int id = u::getIntInput("\nMasukkan ID Mahasiswa: ");
  string name = u::getStringInput("Masukkan Nama Mahasiswa (max 20 char): ", 20);
  newStudent.id = id;
  newStudent.name = name;

  cout << "Mata Kuliah Yang Diambil: " << endl;
  for (const auto &v : mainGraph.vertices) {
    cout << " - [" << v.id << "] " << v.name;
    bool isTaken = u::getBoolInput();
    if (isTaken) newStudent.courseList.push_back(st::Course(v.id, v.name));
  }

  return newStudent;
}

gr::Vertex getNewCourseVertexData() {
  string id = u::getStringInput("\nMasukkan Kode Mata Kuliah (max 5 char): ", 5);
  string name = u::getStringInput("Masukkan Nama Mata Kuliah (max 20 char): ", 20);
  return gr::Vertex(id, name);
}

void showDefaultMenu() {
  system("cls");
  cout << "# PROGRAM MATA KULIAH" << endl;
  cout << "1. Gunakan File External" << endl;
  cout << "2. Input Data Secara Manual" << endl;
  cout << "0. Batalkan dan Keluar Dari Program" << endl;

  int choice = u::getChoice(0, 2);
  switch (choice) {
  case 0:
    exit(0);

  case 1:
    loadInputFile();
    return;

  default:
    return;
  }

  loadInputFile();
}

void loadInputFile(string fileName) {
  string filePath = "input/";
  if (fileName != "") {
    if (fileName.find(".txt") == string::npos) fileName += ".txt";
    filePath += fileName;
    inputFile.open(filePath);

    if (inputFile.is_open() == false) {
      cout << "File Input Tidak Ditemukan!" << endl;
      u::wait();
      exit(0);
    }
  } else {
    while (inputFile.is_open() == false) {
      filePath = "input/";
      string input = u::getStringInput("\nMasukkan Nama File: (input.txt) ");
      if (input == "") input = "input.txt";
      if (input.find(".txt") == string::npos) input += ".txt";

      filePath += input;
      inputFile.open(filePath);
      if (inputFile.is_open() == true) break;
      cout << "File tidak ditemukan!" << endl;
    }
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
  }
}

void showCourseMenu() {
  while (true) {
    system("cls");
    cout << "# DAFTAR MATA KULIAH" << endl;
    cout << DIVIDER << endl;
    cout << "ID \tMata Kuliah" << endl;
    mainGraph.printVertexList("\t");
    cout << DIVIDER << endl;
    cout << "1. Tambah Mata Kuliah" << endl;
    cout << "2. Simpan dan Lanjutkan" << endl;
    cout << "0. Batalkan dan Keluar Dari Program" << endl;

    int choice = u::getChoice(0, 2);

    switch (choice) {
    case 1:
      mainGraph.addVertex(getNewCourseVertexData());
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
    cout << DIVIDER << endl;
    cout << "ID \tNama Mahasiswa \t\tMata Kuliah Pilihan" << endl;
    studentList.print();
    cout << DIVIDER << endl;
    cout << "1. Tambah Mahasiswa" << endl;
    cout << "2. Simpan dan Lanjutkan" << endl;
    cout << "0. Batalkan dan Keluar Dari Program" << endl;

    int choice = u::getChoice(0, 2);
    switch (choice) {
    case 1:
      studentList.add(getNewStudentData());
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
  cout << DIVIDER << endl;
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

  cout << DIVIDER << endl;
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
    switch (choice) {
    case 1:
      while (true) {
        input = u::getStringInput("\nMasukkan Nama File: (output.txt) ");
        if (input == "") input = "output.txt";
        if (input.find(".txt") == string::npos) input += ".txt";

        fileName += input;
        outputFile.open(fileName);
        if (outputFile.is_open() == true) {
          outputFile.close();
          break;
        }
        cout << "Gagal Membuat File! Coba Lagi..." << endl;
      }

      saveColorListToFile(input);

    default:
      return;
    }
  }
}

void saveColorListToFile(string fileName) {
  string filePath = "output/";
  if (fileName != "") {
    if (fileName.find(".txt") == string::npos) fileName += ".txt";
    filePath += fileName;
    outputFile.open(filePath, ios::out | ios::trunc);
  } else {
    cout << "Nama File Tidak Valid!" << endl;
    exit(0);
  }

  if (outputFile.is_open() == false) cout << "Gagal Menulis File!" << endl;

  outputFile << "Sesi \tMata Kuliah" << endl;

  int sessionNumber = 1;
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
}