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
class Hypervertex;

class Hyperedge : public utility::IdentifiableBase, public std::enable_shared_from_this<Hyperedge>
{
   friend class Hypergraph;

public:
   Hyperedge();
   Hyperedge(const std::vector<std::shared_ptr<Hypervertex>>& vertices);
   ~Hyperedge();
   Hyperedge(const Hyperedge& rhs) = delete;
   Hyperedge operator=(const Hyperedge& rhs) = delete;

   const std::vector<std::weak_ptr<Hypervertex>> getVertices() const;
   
   bool isAdjacentTo(const std::weak_ptr<Hyperedge>& edge);
   bool isIncidentTo(const std::weak_ptr<Hypervertex>& vertex);

   bool operator==(const Hyperedge& rhs) const;
   bool operator!=(const Hyperedge& rhs) const;

protected:
   const std::vector<std::shared_ptr<Hypervertex>>::iterator findVertex(std::weak_ptr<Hypervertex> vertex);
   void removeVertex(std::weak_ptr<Hypervertex> vertex);
   void removeFromVertexIncidenceLists();

private:
   std::vector<std::shared_ptr<Hypervertex>> vertices_;
};
}
}
}
