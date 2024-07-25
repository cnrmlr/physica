#include "hypergraph.h"

namespace computational_physics_engine
{
namespace core
{
Hypergraph::Hypergraph()
   : Identifiable()
{
}

Hypergraph::~Hypergraph()
{
}

void Hypergraph::setVertices(SharedVertexSet vertices)
{
   vertices_ = vertices;
}

SharedVertexSet Hypergraph::getVertices() const
{
   return vertices_;
}

void Hypergraph::clearVertices()
{
   vertices_.clear();
}

void Hypergraph::addVertex(std::shared_ptr<Hypervertex> vertex)
{
   vertices_.insert(vertex);
}

void Hypergraph::removeVertex(std::shared_ptr<Hypervertex> vertex)
{
   vertices_.erase(vertex);
}

void Hypergraph::setEdges(SharedEdgeSet edges)
{
   edges_ = edges;
}

SharedEdgeSet Hypergraph::getEdges() const
{
   return edges_;
}

void Hypergraph::clearEdges()
{
   edges_.clear();
}

void Hypergraph::addEdge(std::shared_ptr<Hyperedge> edge)
{
   edges_.insert(edge);
}

void Hypergraph::removeEdge(std::shared_ptr<Hyperedge> edge)
{
   edges_.erase(edge);
}
}
}

