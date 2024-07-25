#include "hypervertex.h"

namespace computational_physics_engine
{
namespace core
{
Hypervertex::Hypervertex()
   : Identifiable()
{
}

Hypervertex::~Hypervertex()
{
}

Hypervertex::Hypervertex(const Hypervertex& rhs)
   : core::Identifiable(rhs)
   , incidentEdges_(rhs.incidentEdges_)
{
}

Hypervertex& Hypervertex::operator=(const Hypervertex& rhs)
{
   if (this != &rhs)
   {
      core::Identifiable::operator=(rhs);
      incidentEdges_ = rhs.incidentEdges_;
   }
   return *this;
}

Hypervertex::Hypervertex(SharedEdgeSet incidentEdges)
   : incidentEdges_(incidentEdges_)
{
}

void Hypervertex::setIncidentEdges(SharedEdgeSet incidentEdges)
{
   incidentEdges_ = incidentEdges;
}

const SharedEdgeSet Hypervertex::getIncidentEdges() const
{
   return incidentEdges_;
}

void Hypervertex::addIncidentEdge(std::shared_ptr<Hyperedge> incidentEdge)
{
   incidentEdges_.insert(incidentEdge);
}

void Hypervertex::removeIncidentEdge(std::shared_ptr<Hyperedge> incidentEdge)
{
   incidentEdges_.erase(incidentEdge);
}

void Hypervertex::clearIncidentEdges()
{
   incidentEdges_.clear();
}
}
}

