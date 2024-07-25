#pragma once

#include "identifiable.h"
#include "hash.h"

#include <unordered_set>
#include <memory>

namespace computational_physics_engine
{
namespace core
{
class Hyperedge;

using SharedEdgeSet = std::unordered_set<std::shared_ptr<Hyperedge>>;

class Hypervertex : public core::Identifiable
{
public:
   Hypervertex();
   ~Hypervertex();
   Hypervertex(const Hypervertex&);
   Hypervertex& operator=(const Hypervertex&);

   Hypervertex(SharedEdgeSet incidentEdges);

   void setIncidentEdges(SharedEdgeSet incidentEdges);
   const SharedEdgeSet getIncidentEdges() const;

   void addIncidentEdge(std::shared_ptr<Hyperedge> incidentEdge);
   void removeIncidentEdge(std::shared_ptr<Hyperedge> incidentEdge);

   void clearIncidentEdges();

private:
   SharedEdgeSet incidentEdges_;
};
}
}