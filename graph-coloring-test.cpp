// Program to scheduling class exam

#include <iostream>
#include <initializer_list>
#include "graph.h"

using namespace std;

void connectingEdge(int *classList);
void addStudent(string name, initializer_list<int> classArray);

gr::Graph g;
const int totalClass = 6;

int main(int argc, char const *argv[]) {
  system("cls");


  for (size_t i = 0; i < totalClass; i++) {
    string name = "Matkul " + to_string(i + 1);
    g.addVertex(gr::Vertex(i + 1, name));
  }

  int classOption1[totalClass] = { 1, 1, 0, 0, 0, 1 };
  addStudent("Mahasiswa 1", { 1, 1, 0, 0, 0, 1 });

  int classOption2[totalClass] = { 1, 0, 0, 0, 1, 1 };
  addStudent("Mahasiswa 2", { 1, 0, 0, 0, 1, 1 });

  int classOption3[totalClass] = { 1, 0, 1, 0, 1, 0 };
  addStudent("Mahasiswa 3", { 1, 0, 1, 0, 1, 0 });

  int classOption4[totalClass] = { 0, 0, 0, 1, 1, 0 };
  addStudent("Mahasiswa 4", { 0, 0, 0, 1, 1, 0 });

  int classOption5[totalClass] = { 0, 1, 0, 1, 0, 0 };
  addStudent("Mahasiswa 5", { 0, 1, 0, 1, 0, 0 });

  int classOption6[totalClass] = { 1, 0, 1, 0, 0, 0 };
  addStudent("Mahasiswa 6", { 1, 0, 1, 0, 0, 0 });

  int classOption7[totalClass] = { 0, 0, 0, 0, 1, 1 };
  addStudent("Mahasiswa 7", { 0, 0, 0, 0, 1, 1 });

  int classOption8[totalClass] = { 1, 1, 0, 0, 0, 0 };
  addStudent("Mahasiswa 8", { 1, 1, 0, 0, 0, 0 });

  int classOption9[totalClass] = { 0, 0, 1, 0, 1, 0 };
  addStudent("Mahasiswa 9", { 0, 0, 1, 0, 1, 0 });

  int classOption10[totalClass] = { 1, 0, 0, 0, 0, 1 };
  addStudent("Mahasiswa 10", { 1, 0, 0, 0, 0, 1 });

  g.printGraph();
  g.graphColoring();
  g.printColoringResult();

  g.printColorTable();

  return 0;
}

void connectingEdge(int *classList) {
  for (int i = 0; i < totalClass; i++) {
    if (classList[i] != 1) continue;
    for (int j = 0; j < totalClass; j++) {
      if (i == j) continue;
      else if (classList[j] == 1) g.addEdgeByID(i + 1, j + 1);
    }
  }
}

void addStudent(string name, initializer_list<int> classArray) {
  int classArrayArray[totalClass];
  copy(classArray.begin(), classArray.end(), classArrayArray);
  connectingEdge(classArrayArray);
}