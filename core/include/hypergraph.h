#pragma once

#include "hyperedge.h"
#include "hypervertex.h"
#include "identifiable.h"

#include <utility>
#include <memory>
#include <unordered_set>

namespace computational_physics_engine
{
namespace core
{
class Hypergraph : public core::Identifiable
{
public:
   Hypergraph();
   ~Hypergraph();
   Hypergraph(const Hypergraph&) = delete;
   Hypergraph operator=(const Hypergraph) = delete;

   void setVertices(SharedVertexSet vertices);
   SharedVertexSet getVertices() const;
   void clearVertices();

   void addVertex(std::shared_ptr<Hypervertex> vertex);
   void removeVertex(std::shared_ptr<Hypervertex> vertex);

   void setEdges(SharedEdgeSet edges);
   SharedEdgeSet getEdges() const;
   void clearEdges();

   void addEdge(std::shared_ptr<Hyperedge> edge);
   void removeEdge(std::shared_ptr<Hyperedge> edge);

private:
   SharedVertexSet vertices_;
   SharedEdgeSet edges_;
};
}
}
