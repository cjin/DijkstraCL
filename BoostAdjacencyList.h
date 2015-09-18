//
// Created by Can on 9/18/15.
//

#ifndef DIJKSTRACL_BOOSTADJACENCYLIST_H
#define DIJKSTRACL_BOOSTADJACENCYLIST_H

#include "UndirectedWeightedGraph.h"
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

namespace GraphUtils {

class BoostAdjacencyList : public UndirectedWeightedGraph {
 public:
  typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, Scalar>> Graph;
  typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
  typedef std::pair<int, int> Edge;
  typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
  struct BoostGraph {
    Graph graph;
    size_t numVertices;
    IndexMap index;
  };
  BoostAdjacencyList(Index numVertices);
  std::shared_ptr<BoostGraph> GetBoostGraph();
  void Connect(Index a, Index b, Scalar weight);
  Index NumVertices() const;
  Index NumEdges() const;
 private:
  Index numVertices_;
  std::vector<Edge> edges_;
  std::vector<Scalar> weights_;

};

} // namespace GraphUtils

#endif //DIJKSTRACL_BOOSTADJACENCYLIST_H
