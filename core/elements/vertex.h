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

class Vertex : public utility::IdentifiableBase
{
  friend class Hyperedge;
  friend class Hypergraph;

public:
   Vertex();
   ~Vertex();
   Vertex(const Vertex& rhs) = delete;
   Vertex operator=(const Vertex& rhs) = delete;

   const std::vector<std::weak_ptr<Hyperedge>> getIncidentEdges();

   bool isAdjacentTo(const std::weak_ptr<Vertex>& vertex);
   bool isIncidentTo(const std::weak_ptr<Hyperedge>& edge);

   bool operator==(const Vertex& rhs) const;
   bool operator!=(const Vertex& rhs) const;

protected:
   void addIncidentEdge(const std::weak_ptr<Hyperedge>& incidentEdge);
   void removeIncidentEdge(const std::weak_ptr<Hyperedge>& incidentEdge);

private:
   std::vector<std::shared_ptr<Hyperedge>> incidentEdges_;
};
}
}
}