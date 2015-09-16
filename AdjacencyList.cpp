//
// Created by Can on 3/10/15.
//

#include "AdjacencyList.h"

namespace UndirectedWeightedGraph {

template<typename T_Index, typename T_Scalar>
AdjacencyList<T_Index, T_Scalar>::AdjacencyList(T_Index numVertices) : numVertices_(numVertices), numEdges_(0), graph_(nullptr) {
  list_ = new ListNode * [numVertices];
  for (T_Index i = 0; i < numVertices; ++i) {
    list_[i] = NULL;
  }
}

template<typename T_Index, typename T_Scalar>
AdjacencyList<T_Index, T_Scalar>::~AdjacencyList() {
  for (T_Index i = 0; i < numVertices_; ++i) {
    RemoveNode(list_[i]);
  }
  delete [] list_;
}

template<typename T_Index, typename T_Scalar>
void AdjacencyList<T_Index, T_Scalar>::Connect(T_Index a, T_Index b, T_Scalar weight) {
  if (a == b) return;
  if (graph_ != nullptr) graph_.reset();
  if (a > b) std::swap(a, b);
  list_[a] = ConnectNode(list_[a], b, weight);
  list_[b] = ConnectNode(list_[b], a, weight);
}

template<typename T_Index, typename T_Scalar>
typename AdjacencyList<T_Index, T_Scalar>::ListNode *AdjacencyList<T_Index, T_Scalar>::ConnectNode(AdjacencyList<T_Index, T_Scalar>::ListNode *node, T_Index b, T_Scalar weight) {
  if (node == NULL) { // insert as the last node in the list
    ListNode * newNode = new ListNode(b, weight);
    numEdges_++;
    return newNode;
  }
  if (node->idx == b) { // update the existing weight
    node->weight = weight;
    return node;
  }
  if (node->idx > b) { // insert in the list
    ListNode * newNode = new ListNode(b, weight, node);
    return newNode;
  }
  node->next = ConnectNode(node->next, b, weight);
  return node;
}

template <typename T_Index, typename T_Scalar>
T_Scalar AdjacencyList<T_Index, T_Scalar>::GetWeight(T_Index a, T_Index b) const {
  throw std::invalid_argument("Not implemented");
  return 0;
}

template <typename T_Index, typename T_Scalar>
T_Index AdjacencyList<T_Index, T_Scalar>::NumVertices() const {
  return numVertices_;
}

template <typename T_Index, typename T_Scalar>
T_Index AdjacencyList<T_Index, T_Scalar>::NumEdges() const {
  return numEdges_;
}

template <typename T_Index, typename T_Scalar>
std::shared_ptr<GraphArray<T_Index, T_Scalar>> AdjacencyList<T_Index, T_Scalar>::GetGraphArray() const {
  if (graph_ != nullptr) return std::make_shared<GraphArray<T_Index, T_Scalar>>(*graph_);
  graph_ = std::make_shared<GraphArray<T_Index, T_Scalar>>();
  graph_->vertices.resize(numVertices_);
  graph_->edges.resize(numEdges_);
  graph_->weights.resize(numEdges_);
  T_Index base = 0;
  for (T_Index i = 0; i < numVertices_; ++i) {
    graph_->vertices[i] = base;
    base += Traverse(list_[i], base, 0);
  }
  // return a current copy of cache in case of cache flushing without acknowledgement
  return std::make_shared<GraphArray<T_Index, T_Scalar>>(*graph_);
}

template <typename T_Index, typename T_Scalar>
T_Index AdjacencyList<T_Index, T_Scalar>::Traverse(AdjacencyList<T_Index, T_Scalar>::ListNode *node, T_Index base, T_Index depth) const {
  if (!node) return depth;
  graph_->edges[base + depth] = node->idx;
  graph_->weights[base + depth] = node->weight;
  return Traverse(node->next, base, depth + 1);
}

template <typename T_Index, typename T_Scalar>
void AdjacencyList<T_Index, T_Scalar>::RemoveNode(AdjacencyList<T_Index, T_Scalar>::ListNode *node) {
  if (!node) return;
  RemoveNode(node->next);
  delete node;
}

template <typename T_Index, typename T_Scalar>
void AdjacencyList<T_Index, T_Scalar>::CopyFrom(const AdjacencyList &adjacencyList) {
  if (this == &adjacencyList) return;
  for (T_Index i = 0; i < numVertices_; ++i) {
    RemoveNode(list_[i]);
  }
  delete [] list_;
  numVertices_ = adjacencyList.numVertices_;
  numEdges_ = adjacencyList.numEdges_;
  list_ = new ListNode * [numVertices_];
  for (T_Index i = 0; i < numVertices_; ++i) {
    list_[i] = CopyNode(list_[i], adjacencyList.list_[i]);
  }
  graph_ = adjacencyList.graph_;
}

template <typename T_Index, typename T_Scalar>
typename AdjacencyList<T_Index, T_Scalar>::ListNode * AdjacencyList<T_Index, T_Scalar>::CopyNode(AdjacencyList<T_Index, T_Scalar>::ListNode *dest, AdjacencyList<T_Index, T_Scalar>::ListNode *src) {
  if (src == NULL) return NULL;
  dest = new ListNode(src->idx, src->weight);
  dest->next = CopyNode(dest->next, src->next);
  return dest;
}

template <typename T_Index, typename T_Scalar>
AdjacencyList<T_Index, T_Scalar>::AdjacencyList(const AdjacencyList &other) {
  CopyFrom(other);
}

template <typename T_Index, typename T_Scalar>
const AdjacencyList<T_Index, T_Scalar> &AdjacencyList<T_Index, T_Scalar>::operator=(const AdjacencyList<T_Index, T_Scalar> &other) {
  CopyFrom(other);
  return *this;
}


// explicit instantiations
template class AdjacencyList<size_t, float>;
template class AdjacencyList<size_t, double>;
template class AdjacencyList<int, float>;
template class AdjacencyList<int, double>;

} // namespace UndirectedWeightedGraph
