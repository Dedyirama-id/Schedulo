#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <map>
#include "utils.h"

using namespace std;

namespace gr {
  class Edge;
  class Vertex;

  class Edge {
  public:
    int id;

    Edge() {}

    Edge(int vertexId) {
      id = vertexId;
    }
  };

  class Vertex {
  public:
    int id;
    string name;
    string alias;
    int degree = 0;
    int colorIndex = -1;
    list < Edge > edgeList;

    Vertex() {
      id = 0;
      name = "";
    }

    Vertex(int id, string name, string alias) {
      this->id = id;
      this->name = name;
      this->alias = alias;
    }

    Edge addEdge(Edge newEdge) {
      edgeList.push_back(newEdge);
      degree++;
    }

    void printEdgeList() {
      cout << "[";
      for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
        if (it == edgeList.begin()) cout << it->id;
        else cout << " --> " << it->id;
      }
      cout << "]" << endl;
    }

    bool isColored() {
      return colorIndex >= 0;
    }

    bool isNeighborhood(int vertexId) {
      for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
        if (it->id == vertexId) return true;
      }
      return false;
    }
  };

  class Graph {
  public:
    vector < Vertex > vertices;
    vector<vector<int>> colorList;

    int findVertexByID(int vertexId) {
      for (int i = 0; i < vertices.size(); i++) {
        if (vertices.at(i).id == vertexId) return i;
      }
      return -1;
    }

    void addVertex(Vertex newVertex) {
      if (findVertexByID(newVertex.id) >= 0) {
        cout << "Vertex with this ID already exist" << endl;
      } else {
        vertices.push_back(newVertex);
        cout << "New Vertex Added Successfully" << endl;
      }
      u::wait();
    }

    void addVertex(int id, string name, string alias) {
      Vertex newVertex(id, name, alias);
      addVertex(newVertex);
    }

    Vertex getVertexByID(int vertexId) {
      for (int i = 0; i < vertices.size(); i++) {
        if (vertices.at(i).id == vertexId) return vertices.at(i);
      }
    }

    bool checkIfEdgeExistByID(int sourceVID, int destVID) {
      Vertex v = getVertexByID(sourceVID);
      list < Edge > e;
      e = v.edgeList;
      for (auto it = e.begin(); it != e.end(); it++) {
        if (it->id == destVID) return true;
      }
      return false;
    }

    void addEdgeByID(int sourceVID, int destVID) {
      int sourceLocation = findVertexByID(sourceVID);
      int destLocation = findVertexByID(destVID);
      if (sourceLocation < 0 || destLocation < 0) {
        cout << "Invalid Vertex ID entered." << endl;
        return;
      }

      bool isEdgeExist = checkIfEdgeExistByID(sourceVID, destVID);
      if (isEdgeExist) {
        cout << "Edge between " << sourceVID << " and " << destVID << " already exist" << endl;
      } else {
        Edge newEdge(destVID);
        vertices.at(sourceLocation).addEdge(newEdge);
        cout << "Edge between " << sourceVID << " and " << destVID << " added Successfully" << endl;
      }
    }

    void printGraph() {
      cout << "\nvertex count: " << vertices.size() << endl;
      for (int i = 0; i < vertices.size(); i++) {
        Vertex temp;
        temp = vertices.at(i);
        cout << temp.name << " (" << temp.degree << ") --> ";
        temp.printEdgeList();
      }
    }

    void printVertexList(string separator = " - ") {
      if (vertices.size() == 0) return;
      for (const auto& vertex : vertices) {
        cout << vertex.id << separator << vertex.alias << separator << vertex.name << endl;
      }
    }

    void resetVertexColor() {
      for (int i = 0; i < vertices.size(); i++) {
        vertices.at(i).colorIndex = -1;
      }
    }

    void sortByDegree() {
      sort(vertices.begin(), vertices.end(), [](const Vertex &a, const Vertex &b) {
        return a.degree > b.degree;
        });
    }

    void sortById() {
      sort(vertices.begin(), vertices.end(), [](const Vertex &a, const Vertex &b) {
        return a.id < b.id;
        });
    }

    void graphColoring() {
      resetVertexColor();
      welchPowell();
    }

    void welchPowell() {
      sortByDegree();
      int numColors = 0;

      for (int i = 0; i < vertices.size(); i++) {
        if (!vertices[i].isColored()) {
          vertices[i].colorIndex = numColors;
          numColors++;

          for (int j = i + 1; j < vertices.size(); j++) {
            if (!vertices[j].isColored() && !vertices[i].isNeighborhood(vertices[j].id)) {
              vertices[j].colorIndex = numColors - 1;
            }
          }
        }
      }
      colorList.resize(numColors);
      for (int i = 0; i < vertices.size(); i++) {
        colorList[vertices[i].colorIndex].push_back(vertices[i].id);
      }
    }

    void printColoringResult() {
      cout << "\nColoring Result:" << endl;
      for (const Vertex &vertex : vertices) {
        cout << "Vertex " << vertex.id << " colored with: " << vertex.colorIndex << endl;
      }
    }

    void printColorTable() {
      cout << "\nColor Table:" << endl;
      for (const vector<int> &row : colorList) {
        cout << "[";
        for (const int &col : row) {
          cout << col << " ";
        }
        cout << "]" << endl;
      }
    }
  };
}