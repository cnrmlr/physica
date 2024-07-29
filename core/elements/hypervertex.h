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

class Hypervertex : public utility::IdentifiableBase
{
  friend class Hyperedge;
  friend class Hypergraph;

public:
   Hypervertex();
   ~Hypervertex();
   Hypervertex(const Hypervertex& rhs) = delete;
   Hypervertex operator=(const Hypervertex& rhs) = delete;

   const std::vector<std::weak_ptr<Hyperedge>> getIncidentEdges();

   bool isAdjacentTo(const std::weak_ptr<Hypervertex>& vertex);
   bool isIncidentTo(const std::weak_ptr<Hyperedge>& edge);

   bool operator==(const Hypervertex& rhs) const;
   bool operator!=(const Hypervertex& rhs) const;

protected:
   void addIncidentEdge(const std::weak_ptr<Hyperedge>& incidentEdge);
   void removeIncidentEdge(const std::weak_ptr<Hyperedge>& incidentEdge);

private:
   std::vector<std::shared_ptr<Hyperedge>> incidentEdges_;
};
}
}
}