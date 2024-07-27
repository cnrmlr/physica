#pragma once

#include "hyperedge.h"
#include "hypervertex.h"
#include "identifiable_base.h"
#include "type_defs.h"
#include "memory_pool.h"

#include <utility>
#include <memory>
#include <unordered_set>

namespace cpe
{
namespace core
{
namespace elements
{
class Hypergraph : public utility::IdentifiableBase
{
public:
   Hypergraph();
   ~Hypergraph();
   Hypergraph(const Hypergraph&) = delete;
   Hypergraph operator=(const Hypergraph) = delete;

   const_VertexPtr addVertex();
   void removeVertex(const_VertexPtr vertex);

   const std::vector<VertexPtr> addVertices(size_t count);

   const_EdgePtr addEdge(const std::vector<VertexPtr>& incidentVertices);
   void removeEdge(const_EdgePtr edge);

   const utility::MemoryPool<Hypervertex>& getVertices();
   const utility::MemoryPool<Hyperedge>& getEdges();

private:
   utility::MemoryPool<Hypervertex> vertices_;
   utility::MemoryPool<Hyperedge> edges_;
};
}
}
}
