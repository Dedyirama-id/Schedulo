#include <iostream>
#include "graph.h"
#include "utils.h"

using namespace std;

void connectingEdge(int *classList, int totalClass);
void showSubjects();


gr::Graph g;

int main() {
  system("cls");

  showSubjects();

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

void showSubjects() {
  int id = 1;
  while (true) {
    system("cls");
    cout << "# DAFTAR MATA KULIAH" << endl;
    cout << "+-------------------------------------+" << endl;
    cout << "ID \tAlias \tMata Kuliah" << endl;
    g.printVertexList("\t");
    cout << "+-------------------------------------+" << endl;
    cout << "1. Tambah Mata Kuliah" << endl;
    cout << "0. Simpan dan Lanjutkan" << endl;

    int choice = u::getChoice(0, 1);
    string name, alias;

    switch (choice) {
    case 1:
      name = u::getStringInput("Masukkan Nama Mata Kuliah: ");
      alias = u::getStringInput("Masukkan Nama Alias Mata Kuliah: ");
      g.addVertex(gr::Vertex(id, name, alias));
      id++;
      break;
    case 0:
      return;

    default:
      break;
    }
  }
}