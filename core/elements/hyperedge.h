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
class Vertex;

class Hyperedge : public utility::IdentifiableBase, public std::enable_shared_from_this<Hyperedge>
{
   friend class Hypergraph;

public:
   Hyperedge();
   Hyperedge(const std::vector<std::shared_ptr<Vertex>>& vertices);
   ~Hyperedge();
   Hyperedge(const Hyperedge& rhs) = delete;
   Hyperedge operator=(const Hyperedge& rhs) = delete;

   const std::vector<std::weak_ptr<Vertex>> getVertices() const;
   
   bool isAdjacentTo(const std::weak_ptr<Hyperedge>& edge);
   bool isIncidentTo(const std::weak_ptr<Vertex>& vertex);

   bool operator==(const Hyperedge& rhs) const;
   bool operator!=(const Hyperedge& rhs) const;

protected:
   const std::vector<std::shared_ptr<Vertex>>::iterator findVertex(std::weak_ptr<Vertex> vertex);
   void removeVertex(std::weak_ptr<Vertex> vertex);
   void removeFromVertexIncidenceLists();

private:
   std::vector<std::shared_ptr<Vertex>> vertices_;
};
}
}
}
