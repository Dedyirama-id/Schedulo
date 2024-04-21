#pragma once

#include <iostream>
#include <string>
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
    string id;

    Edge() {}
    Edge(string vertexId) : id(vertexId) {}
  };

  class Vertex {
  public:
    string id;
    string name;
    int degree = 0;
    int colorIndex = -1;
    list < Edge > edgeList;

    Vertex() {}
    Vertex(string id, string name) : id(id), name(name) {}

    bool isColored() {
      return colorIndex >= 0;
    }

    bool isNeighborhood(string vertexId) {
      for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
        if (it->id == vertexId) return true;
      }
      return false;
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
  };

  class Graph {
  public:
    vector < Vertex > vertices;
    vector<vector<string>> colorList;

    bool isVerticesEmpty() {
      return vertices.size() == 0;
    }

    Vertex getVertexByID(string vertexId) {
      for (int i = 0; i < vertices.size(); i++) {
        if (vertices.at(i).id == vertexId) return vertices.at(i);
      }
    }

    bool checkIfEdgeExistByID(string sourceVID, string destVID) {
      Vertex tempVertex = getVertexByID(sourceVID);
      list < Edge > tempEdgeList;
      tempEdgeList = tempVertex.edgeList;
      for (auto it = tempEdgeList.begin(); it != tempEdgeList.end(); it++) {
        if (it->id == destVID) return true;
      }
      return false;
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

    int findVertexByID(string vertexId) {
      for (int i = 0; i < vertices.size(); i++) {
        if (vertices.at(i).id == vertexId) return i;
      }
      return -1;
    }

    void addVertex(Vertex newVertex) {
      if (findVertexByID(newVertex.id) < 0) vertices.push_back(newVertex);
    }

    void addVertex(string id, string name) {
      Vertex newVertex(id, name);
      if (findVertexByID(newVertex.id) < 0) vertices.push_back(newVertex);
    }

    void addEdgeByID(string sourceVID, string destVID) {
      int sourceLocation = findVertexByID(sourceVID);
      int destLocation = findVertexByID(destVID);
      if (sourceLocation < 0 || destLocation < 0) {
        cout << "Invalid Vertex ID entered." << endl;
        return;
      }

      bool isEdgeExist = checkIfEdgeExistByID(sourceVID, destVID);
      if (isEdgeExist == false) {
        Edge newEdge(destVID);
        vertices.at(sourceLocation).addEdge(newEdge);
      }
    }

    void printGraph() {
      cout << "\nVertex count: " << vertices.size() << endl;
      cout << "+---------------------------------------------------------+" << endl;

      for (int i = 0; i < vertices.size(); i++) {
        Vertex temp;
        temp = vertices.at(i);
        cout << "[" << temp.id << "] " << temp.name << " (" << temp.degree << ") --> ";
        temp.printEdgeList();
      }
      cout << "+---------------------------------------------------------+" << endl;
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
      sortById();
    }

    void printVertexList(string separator = " - ") {
      if (vertices.size() == 0) return;
      for (const auto &vertex : vertices) {
        cout << vertex.id << separator << vertex.name << endl;
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
      for (const vector<string> &row : colorList) {
        cout << "[";
        for (const string &col : row) {
          cout << col << " ";
        }
        cout << "]" << endl;
      }
    }
  };
}