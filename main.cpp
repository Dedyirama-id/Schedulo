#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include "graph.h"
#include "utils.h"
#include "students.h"
#include "app.h"
#include "ansi_escape_sequences.h"

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
  int id = u::getIntInput("Masukkan ID Mahasiswa: ");
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
  string id = u::getStringInput("Masukkan Kode Mata Kuliah (max 5 char): ", 5);
  string name = u::getStringInput("Masukkan Nama Mata Kuliah (max 20 char): ", 20);
  return gr::Vertex(id, name);
}

void loadInputFile(string fileName) {
  string filePath = "input/";
  if (fileName != "") {
    if (fileName.find(".txt") == string::npos) fileName += ".txt";
    filePath += fileName;
    inputFile.open(filePath);

    if (inputFile.is_open() == false) {
      app::printWarning("File Tidak Ditemukan!");
      u::wait();
      exit(0);
    }
  } else {
    while (inputFile.is_open() == false) {
      filePath = "input/";
      string input = u::getStringInput("Masukkan Nama File: (input.txt) ");
      if (input == "") input = "input.txt";
      if (input.find(".txt") == string::npos) input += ".txt";

      filePath += input;
      inputFile.open(filePath);
      if (inputFile.is_open() == true) break;

      app::printWarning("File Tidak Ditemukan!");
      u::wait();
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

void showDefaultMenu() {
  system("cls");
  app::printH1("# MENU UTAMA");

  app::Menu defaultMenu({"Batalkan dan Keluar Dari Program", "Gunakan File External", "Input Data Secara Manual"});
  int choice = defaultMenu.getChoice();

  switch (choice) {
  case 1:
    loadInputFile();
    return;

  case 0:
    exit(0);

  default:
    return;
  }

  loadInputFile();
}

void showCourseMenu() {
  while (true) {
    system("cls");
    app::printH1("# DAFTAR MATA KULIAH");
    cout << DIVIDER << endl;
    app::printH2("ID \tMata Kuliah");
    mainGraph.printVertexList("\t");
    cout << DIVIDER << endl;

    app::Menu courseMenu({ "Batalkan dan Keluar Dari Program", "Tambah Mata Kuliah", "Simpan dan Lanjutkan" });
    int choice = courseMenu.getChoice();

    switch (choice) {
    case 1:
      mainGraph.addVertex(getNewCourseVertexData());
      break;

    case 2:
      if (mainGraph.isVerticesEmpty() == false) return;
      app::printWarning("Harus ada minimal 1 mata kuliah yang ditambahkan!");
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
    app::printH1("# DAFTAR MAHASISWA");
    cout << DIVIDER << endl;
    app::printH2("ID \tNama Mahasiswa \t\tMata Kuliah Pilihan");
    studentList.print();
    cout << DIVIDER << endl;

    app::Menu studentsMenu({ "Batalkan dan Keluar Dari Program", "Tambah Mahasiswa", "Simpan dan Lanjutkan" });
    int choice = studentsMenu.getChoice();

    switch (choice) {
    case 1:
      studentList.add(getNewStudentData());
      break;

    case 2:
      if (studentList.isEmpty() == false) return;
      app::printWarning("Harus ada minimal 1 mahasiswa yang ditambahkan!");
      u::wait();
      break;

    case 0:
      exit(0);

    default:
      break;
    }
  }
}

void showResultMenu() {
  while (true) {
    system("cls");
    showSchedule();

    app::Menu resultMenu({ "Keluar Tanpa Menyimpan", "Simpan ke File" });
    int choice = resultMenu.getChoice();

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
        app::printWarning("File tidak ditemukan, silahkan coba lagi!");
      }

      saveColorListToFile(input);

    default:
      return;
    }
  }
}

void showSchedule() {
  system("cls");

  app::printH1("# JADWAL");
  cout << DIVIDER << endl;

  app::printH2("Sesi \tMata Kuliah");

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

void saveColorListToFile(string fileName) {
  string filePath = "output/";
  if (fileName != "") {
    if (fileName.find(".txt") == string::npos) fileName += ".txt";
    filePath += fileName;
    outputFile.open(filePath, ios::out | ios::trunc);
  } else {
    app::printError("Nama File Tidak Valid!");
    exit(0);
  }

  if (outputFile.is_open() == false) app::printError("Gagal Menulis File!");

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

  app::printSuccess("File Berhasil Disimpan!");
}