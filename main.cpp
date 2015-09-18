#include <iostream>
#include "AdjacencyList.h"
#include "DijkstraCL.h"

using namespace std;

void GenerateRandomGraph(std::shared_ptr<UndirectedWeightedGraph::UndirectedWeightedGraph> graph);

int main() {

  auto adjList = make_shared<UndirectedWeightedGraph::AdjacencyList>(10);
  std::shared_ptr<UndirectedWeightedGraph::UndirectedWeightedGraph> graph(adjList);
  GenerateRandomGraph(graph);

  auto g = adjList->GetGraphArray<Dijkstra::DijkstraCL::cl_Index, Dijkstra::DijkstraCL::cl_Scalar>();
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

void GenerateRandomGraph(std::shared_ptr<UndirectedWeightedGraph::UndirectedWeightedGraph> graph) {
  graph->Connect(0, 2, 1);
  graph->Connect(2, 3, 1);
  graph->Connect(2, 5, 1);
  graph->Connect(4, 8, 1);
}