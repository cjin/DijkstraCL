//
// Created by Can on 9/18/15.
//

#include <numeric>
#include <gsl/gsl_matrix_double.h>
#include "BoostDijkstra.h"


namespace Dijkstra {

typedef GraphUtils::BoostAdjacencyList::BoostGraph BoostGraph;
typedef GraphUtils::BoostAdjacencyList::Graph Graph;
typedef GraphUtils::BoostAdjacencyList::Vertex Vertex;

BoostDijkstra::BoostDijkstra(std::shared_ptr<BoostGraph> graph)
    : graph_(graph),
      numVertices_(graph->numVertices),
      sourceVertices_(graph->numVertices, 0),
      distanceMatrix_(new gsl::Matrix(graph->numVertices, graph->numVertices)) {
  std::iota(sourceVertices_.begin(), sourceVertices_.end(), 0);
}

int BoostDijkstra::Run() {
  boost::graph_traits<Graph>::vertex_iterator vi;
  for (Index i = 0; i < sourceVertices_.size(); ++i) {
    Vertex source = boost::vertex(sourceVertices_[i], graph_->graph);
    boost::dijkstra_shortest_paths(graph_->graph, source, boost::distance_map(&distanceMatrix_->m_->data[i * numVertices_]));
  }
  return 0;
}

std::shared_ptr<gsl::Matrix> BoostDijkstra::GetDistanceMatrix() {
  return distanceMatrix_;
}

}
