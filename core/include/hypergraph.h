#pragma once

#include "hyperedge.h"
#include "hypervertex.h"
#include "identifiable_base.h"
#include "type_defs.h"

#include <utility>
#include <memory>
#include <unordered_set>

namespace cpe
{
namespace core
{
class Hypergraph : public IdentifiableBase
{
public:
   Hypergraph();
   ~Hypergraph();
   Hypergraph(const Hypergraph&) = delete;
   Hypergraph operator=(const Hypergraph) = delete;

   const RawVertexPtr addVertex();
   void removeVertex(const RawVertexPtr vertex);

   const std::vector<RawVertexPtr> addVertices(size_t count);

   const RawEdgePtr addEdge(const std::vector<RawVertexPtr>& incidentVertices);
   void removeEdge(const RawEdgePtr edge);

   const std::vector<Hypervertex>& getVertices();
   const std::vector<Hyperedge>& getEdges();

private:
   std::unique_ptr<std::vector<Hypervertex>> vertices_;
   std::unique_ptr<std::vector<Hyperedge>> edges_;
};
}
}
