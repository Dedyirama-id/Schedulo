// Program to scheduling class exam

#include <iostream>
#include "graph.h"

using namespace std;

void connectingEdge(int *classList, int totalClass);

gr::Graph g;

int main(int argc, char const *argv[]) {
  system("cls");

  cout << "Masukkan Jumlah Mata Kuliah: ";
  int totalClass;
  cin >> totalClass;

  for (size_t i = 0; i < totalClass; i++) {
    string name = "Matkul " + to_string(i + 1);
    g.addVertex(gr::Vertex(i + 1, name));
  }

  cout << "\nMasukkan Jumlah Mahasiswa: ";
  int totalStudent;
  cin >> totalStudent;

  for (size_t i = 0; i < totalStudent; i++) {
    string name = "Mahasiswa " + to_string(i + 1);
    cout << "\n" << name << ": " << endl;;

    int classList[totalClass];
    for (size_t j = 0; j < totalClass; j++) {
      cout << "Apakah mengambil matakuliah " << j + 1 << " (Y/N)? ";
      char answer;
      cin >> answer;
      
      if (answer == 'Y' || answer == 'y') classList[j] = 1;
      else classList[j] = 0;
    }

    connectingEdge(classList, totalClass);
  }

  g.printGraph();
  g.graphColoring();
  g.printColoringResult();
  g.printColorTable();

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
