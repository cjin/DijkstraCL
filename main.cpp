#include <iostream>
#include "AdjacencyList.h"
#include "DijkstraCL.h"
#include "BoostAdjacencyList.h"
#include "BoostDijkstra.h"

using namespace std;
using namespace GraphUtils;
using namespace Dijkstra;

void GenerateExampleGraph(std::vector<std::shared_ptr<UndirectedWeightedGraph>> graphs);

int main() {

  auto adjList = make_shared<AdjacencyList>(10);
  auto boostAdjList = make_shared<BoostAdjacencyList>(10);
  vector<shared_ptr<UndirectedWeightedGraph>> graphList = {adjList, boostAdjList};
  GenerateExampleGraph(graphList);

  auto g = adjList->GetGraphArray<DijkstraCL::cl_Index, DijkstraCL::cl_Scalar>();
  for (auto c : g->vertices) cout << " " << c;
  cout << endl;
  for (auto c : g->edges) cout << " " << c;
  cout << endl;
  for (auto c : g->weights) cout << " " << c;
  cout << endl;

  DijkstraCL dijkstraCL(g);
  dijkstraCL.Run();
  auto dijkstraCLResultMat = dijkstraCL.GetDistanceMatrix();
  cout << *dijkstraCLResultMat;
  cout << endl;


  BoostDijkstra boostDijkstra(boostAdjList->GetBoostGraph());
  boostDijkstra.Run();
  auto boostResultMat = boostDijkstra.GetDistanceMatrix();
  cout << *boostResultMat;

  cout << "Equality: " << (*dijkstraCLResultMat == *boostResultMat) << endl;
  return 0;
}

void GenerateExampleGraph(std::vector<std::shared_ptr<UndirectedWeightedGraph>> graphs) {
  std::vector<Index> verticesA = {0, 2, 2, 4, 5};
  std::vector<Index> verticesB = {2, 3, 5, 8, 9};
  std::vector<Scalar> weights = {1, 2, 3, 4, 1};
  for (Index i = 0; i < verticesA.size(); ++i) {
    for (auto g : graphs) {
      g->Connect(verticesA[i], verticesB[i], weights[i]);
    }
  }
}