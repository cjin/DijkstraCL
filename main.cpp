#include <iostream>
#include "AdjacencyList.h"
#include "DijkstraCL.h"

using namespace std;
int main() {

  UndirectedWeightedGraph::AdjacencyList<Dijkstra::DijkstraCL::cl_Index, Dijkstra::DijkstraCL::cl_Scalar> adjList(10);
  adjList.Connect(0, 2, 1);
  adjList.Connect(2, 3, 1);
  adjList.Connect(2, 5, 1);
  adjList.Connect(4, 8, 1);
  auto g = adjList.GetGraphArray();
  for (auto c : g->vertices) cout << " " << c;
  cout << endl;
  for (auto c : g->edges) cout << " " << c;
  cout << endl;
  for (auto c : g->weights) cout << " " << c;
  cout << endl;

  Dijkstra::DijkstraCL dijkstraCL(g);
  cout << dijkstraCL.Run() << endl;
  int count = 0;
  for (auto v : *dijkstraCL.GetResultsArray()) {
    if (v == numeric_limits<Dijkstra::DijkstraCL::cl_Scalar>::max()) {
      cout << "X ";
    } else {
      cout << v << " ";
    }
    count++;
    if (count == 10) {
      count = 0;
      cout << endl;
    }
  }

  return 0;
}