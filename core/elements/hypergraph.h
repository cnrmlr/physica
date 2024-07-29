#pragma once

#include "identifiable_base.h"

#include <memory>
#include <vector>

namespace cpe
{
namespace core
{
namespace elements
{
class Hyperedge;
class Hypervertex;

class Hypergraph : public utility::IdentifiableBase
{
public:
   Hypergraph();
   ~Hypergraph();
   Hypergraph(const Hypergraph&) = delete;
   Hypergraph operator=(const Hypergraph) = delete;

   const std::weak_ptr<Hypervertex> addVertex();
   void removeVertex(const std::weak_ptr<Hypervertex>& vertex);

   const std::vector<std::weak_ptr<Hypervertex>> addVertices(const size_t count);
   void removeVertices(const std::vector<std::weak_ptr<Hypervertex>>& vertices);

   const std::weak_ptr<Hyperedge> addEdge(std::vector<std::weak_ptr<Hypervertex>> vertices);
   void removeEdge(const std::weak_ptr<Hyperedge>& edge);

   const std::vector<std::weak_ptr<Hyperedge>> addEdges(std::vector<std::vector<std::weak_ptr<Hypervertex>>> vertexSets);
   void removeEdges(const std::vector<std::weak_ptr<Hyperedge>>& edges);

   const std::vector<std::weak_ptr<Hypervertex>> getVertices() const;
   const std::vector<std::weak_ptr<Hyperedge>> getEdges() const;

private:
   std::vector<std::shared_ptr<Hypervertex>> vertices_;
   std::vector<std::shared_ptr<Hyperedge>> edges_;
};
}
}
}
