#include <iostream>
#include <random>
#include "AdjacencyList.h"
#include "DijkstraCL.h"
#include "BoostAdjacencyList.h"
#include "BoostDijkstra.h"

using namespace std;
using namespace GraphUtils;
using namespace Dijkstra;

void GenerateExampleGraph(std::vector<std::shared_ptr<UndirectedWeightedGraph>> graphs);
void GenerateRandomGraph(std::vector<std::shared_ptr<UndirectedWeightedGraph>> graphs, Index numEdges);

void Example1() {

  auto adjList = make_shared<AdjacencyList>(10);
  auto boostAdjList = make_shared<BoostAdjacencyList>(10);
  vector<shared_ptr<UndirectedWeightedGraph>> graphList = {adjList, boostAdjList};
//  GenerateRandomGraph(graphList, 10000);
//  GenerateRandomGraph()
  GenerateExampleGraph(graphList);

  auto g = adjList->GetGraphArray<DijkstraCL::cl_Index, DijkstraCL::cl_Scalar>();
  for (auto c : g->vertices) cout << " " << c;
  cout << endl;
  for (auto c : g->edges) cout << " " << c;
  cout << endl;
  for (auto c : g->weights) cout << " " << c;
  cout << endl << endl;

  DijkstraCL dijkstraCL(g);
  dijkstraCL.Run();
  auto dijkstraCLResultMat = dijkstraCL.GetDistanceMatrix();
  cout << *dijkstraCLResultMat;
  cout << endl;
  cout << "CL Done." << endl;

  BoostDijkstra boostDijkstra(boostAdjList->GetBoostGraph());
  boostDijkstra.Run();
  auto boostResultMat = boostDijkstra.GetDistanceMatrix();
  cout << *boostResultMat;
  cout << "Boost Done." << endl;
  cout << "Equality: " << (*dijkstraCLResultMat == *boostResultMat) << endl;
}

void Example2() {

  auto adjList = make_shared<AdjacencyList>(2000);
  auto boostAdjList = make_shared<BoostAdjacencyList>(2000);
  vector<shared_ptr<UndirectedWeightedGraph>> graphList = {adjList, boostAdjList};
  GenerateRandomGraph(graphList, 10000);
//  GenerateRandomGraph()
//  GenerateExampleGraph(graphList);

  auto g = adjList->GetGraphArray<DijkstraCL::cl_Index, DijkstraCL::cl_Scalar>();
  for (auto c : g->vertices) cout << " " << c;
  cout << endl;
  for (auto c : g->edges) cout << " " << c;
  cout << endl;
  for (auto c : g->weights) cout << " " << c;
  cout << endl << endl;

  DijkstraCL dijkstraCL(g);
  dijkstraCL.Run();
  auto dijkstraCLResultMat = dijkstraCL.GetDistanceMatrix();
//  cout << *dijkstraCLResultMat;
  cout << endl;
  cout << "CL Done." << endl;

  BoostDijkstra boostDijkstra(boostAdjList->GetBoostGraph());
  boostDijkstra.Run();
  auto boostResultMat = boostDijkstra.GetDistanceMatrix();
//  cout << *boostResultMat;
  cout << "Boost Done." << endl;
  cout << "Equality: " << (*dijkstraCLResultMat == *boostResultMat) << endl;
}

int main() {
  cout << "Example 1" << endl;
  Example1();
  cout << "Example 2" << endl;
  Example2();

  return 0;
}

void GenerateExampleGraph(std::vector<std::shared_ptr<UndirectedWeightedGraph>> graphs) {
  std::vector<Index> verticesA {0, 2, 2, 4, 5};
  std::vector<Index> verticesB {2, 3, 5, 8, 9};
  std::vector<Scalar> weights {1, 2, 3, 4, 1};

//  std::vector<Index> verticesA {8, 3, 5, 4};
//  std::vector<Index> verticesB {9, 7, 2, 8};
//  std::vector<Scalar> weights {1, 2, 3, 4};

  for (Index i = 0; i < verticesA.size(); ++i) {
    for (auto g : graphs) {
      g->Connect(verticesA[i], verticesB[i], weights[i]);
    }
  }
}

void GenerateRandomGraph(std::vector<std::shared_ptr<UndirectedWeightedGraph>> graphs, Index numEdges) {
  Index numVertices = graphs[0]->NumVertices();
  std::vector<Index> verticesA(numEdges, 0);
  std::vector<Index> verticesB(numEdges, 0);
  std::vector<Scalar> weights(numEdges, 0);

  std::random_device randomDevice;
  std::mt19937 gen(randomDevice());
  std::uniform_real_distribution<Scalar> dist(1, 1.0);
  std::uniform_int_distribution<Index> distInt(0, numVertices - 1);
  for (Index i = 0; i < numEdges; ++i) {
    Index a = distInt(gen), b = distInt(gen);
    Scalar w = dist(gen);
    for (auto g : graphs) {
//      cout << a << "->" << b << " w " << w << endl;
      g->Connect(a, b, w);
    }
  }
}