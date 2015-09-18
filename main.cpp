#include <iostream>
#include "AdjacencyList.h"
#include "DijkstraCL.h"
#include "BoostAdjacencyList.h"
#include "BoostDijkstra.h"

using namespace std;
using namespace GraphUtils;
using namespace Dijkstra;

void GenerateExampleGraph(std::shared_ptr<UndirectedWeightedGraph> graph);

int main() {

  auto adjList = make_shared<AdjacencyList>(10);
//  std::shared_ptr<GraphUtils::GraphUtils> graph(adjList);
  GenerateExampleGraph(adjList);

  auto g = adjList->GetGraphArray<DijkstraCL::cl_Index, DijkstraCL::cl_Scalar>();
  for (auto c : g->vertices) cout << " " << c;
  cout << endl;
  for (auto c : g->edges) cout << " " << c;
  cout << endl;
  for (auto c : g->weights) cout << " " << c;
  cout << endl;

  DijkstraCL dijkstraCL(g);
  cout << dijkstraCL.Run() << endl;
  int count = 0;
  for (auto v : *dijkstraCL.GetResultsArray()) {
    if (v == numeric_limits<DijkstraCL::cl_Scalar>::max()) {
      cout << "- ";
    } else {
      cout << v << " ";
    }
    count++;
    if (count == 10) {
      count = 0;
      cout << endl;
    }
  }
  cout << endl;
  auto boostAdjList = make_shared<BoostAdjacencyList>(10);
  GenerateExampleGraph(boostAdjList);
  BoostDijkstra boostDijkstra(boostAdjList->GetBoostGraph());
  boostDijkstra.Run();
  auto boostResultMat = boostDijkstra.GetDistanceMatrix();
  cout << *boostResultMat;
  return 0;
}

void GenerateExampleGraph(std::shared_ptr<UndirectedWeightedGraph> graph) {
  graph->Connect(0, 2, 1);
  graph->Connect(2, 3, 2);
  graph->Connect(2, 5, 3);
  graph->Connect(4, 8, 4);
  graph->Connect(5, 9, 1);
}