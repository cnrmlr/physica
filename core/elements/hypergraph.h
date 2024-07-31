#pragma once

#include "identifiable_base.h"

#include <memory>
#include <vector>

namespace graphica
{
namespace core
{
namespace elements
{
class Hyperedge;
class Vertex;

class Hypergraph : public utility::IdentifiableBase
{
public:
   Hypergraph();
   ~Hypergraph();
   Hypergraph(const Hypergraph&) = delete;
   Hypergraph operator=(const Hypergraph) = delete;

   const std::weak_ptr<Vertex> addVertex();
   void removeVertex(const std::weak_ptr<Vertex>& vertex);

   const std::vector<std::weak_ptr<Vertex>> addVertices(const size_t count);
   void removeVertices(const std::vector<std::weak_ptr<Vertex>>& vertices);

   const std::weak_ptr<Hyperedge> addEdge(std::vector<std::weak_ptr<Vertex>> vertices);
   void removeEdge(const std::weak_ptr<Hyperedge>& edge);

   const std::vector<std::weak_ptr<Hyperedge>> addEdges(std::vector<std::vector<std::weak_ptr<Vertex>>> vertexSets);
   void removeEdges(const std::vector<std::weak_ptr<Hyperedge>>& edges);

   const std::vector<std::weak_ptr<Vertex>> getVertices() const;
   const std::vector<std::weak_ptr<Hyperedge>> getEdges() const;

private:
   std::vector<std::shared_ptr<Vertex>> vertices_;
   std::vector<std::shared_ptr<Hyperedge>> edges_;
};
}
}
}
