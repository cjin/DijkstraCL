//***************************************************************************************
//
//! \file AdjacencyList.h
//!  A simple implementation of adjacency list for undirected weighted graph with
//! OpenCL C graph array representation supported.
//!
//! \author    Can
//! \version   1.0
//! \date      2015-03-23
//! \copyright GNU Public License V3.0
//
//***************************************************************************************

#ifndef DIJKSTRACL_UWGADJACENCYLIST_H
#define DIJKSTRACL_UWGADJACENCYLIST_H

#include <vector>
#include "UndirectedWeightedGraph.h"

namespace UndirectedWeightedGraph {

template <typename T_Index, typename T_Scalar>
struct GraphArray {
  std::vector<T_Index> vertices;
  std::vector<T_Index> edges;
  std::vector<T_Scalar> weights;
  GraphArray() { }
  GraphArray(const GraphArray& g) : vertices(g.vertices), edges(g.edges), weights(g.weights) { }
};

template <typename T_Index, typename T_Scalar>
class AdjacencyList {
 public:
  AdjacencyList(T_Index numVertices);
  AdjacencyList(const AdjacencyList& other);
  ~AdjacencyList();
  void Connect(T_Index a, T_Index b, T_Scalar weight);
  T_Scalar GetWeight(T_Index a, T_Index b) const;
  T_Index NumVertices() const;
  T_Index NumEdges() const;
  std::shared_ptr<GraphArray<T_Index, T_Scalar>> GetGraphArray() const;
  const AdjacencyList<T_Index, T_Scalar>& operator=(const AdjacencyList<T_Index, T_Scalar>& other);
 private:
  struct ListNode
  {
    T_Index idx;
    T_Scalar weight;
    ListNode * next;
    ListNode(T_Index idx, T_Scalar weight, ListNode * next = NULL) : idx(idx), weight(weight), next(next) { }
  };
  ListNode ** list_;
  T_Index numVertices_;
  T_Index numEdges_;
  mutable std::shared_ptr<GraphArray<T_Index, T_Scalar>> graph_;
  ListNode * ConnectNode(ListNode *node, T_Index d, T_Scalar weight);
  T_Index Traverse(ListNode * node, T_Index base, T_Index depth) const;
  void RemoveNode(ListNode * node);
  void CopyFrom(const AdjacencyList&);
  ListNode * CopyNode(ListNode *dest, ListNode *src);
};

} // namespace UndirectedWeightedGraph

#endif //DIJKSTRACL_UWGADJACENCYLIST_H
