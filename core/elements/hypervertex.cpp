#include "common_utility.h"
#include "hyperedge.h"
#include "hypervertex.h"

#include <algorithm>

namespace cpe
{
namespace core
{
namespace elements
{
Hypervertex::Hypervertex()
   : IdentifiableBase()
{
}

Hypervertex::~Hypervertex()
{
}

const std::vector<std::weak_ptr<Hyperedge>> Hypervertex::getIncidentEdges()
{
   return utility::MakeWeakPtrVector(incidentEdges_);
}

bool Hypervertex::isAdjacentTo(const std::weak_ptr<Hypervertex>& vertex)
{
   for (auto& edge : incidentEdges_)
   {
      if (edge->isIncidentTo(vertex))
      {
         return true;
      }
   }

   return false;
}

bool Hypervertex::isIncidentTo(const std::weak_ptr<Hyperedge>& edge)
{
   return utility::FindWithWeakPtr(incidentEdges_, edge) != incidentEdges_.end();
}

void Hypervertex::addIncidentEdge(const std::weak_ptr<Hyperedge>& incidentEdge)
{
   incidentEdges_.emplace_back(incidentEdge);
}

void Hypervertex::removeIncidentEdge(const std::weak_ptr<Hyperedge>& incidentEdge)
{
   auto edgeIter = utility::FindWithWeakPtr(incidentEdges_, incidentEdge);

   if (edgeIter != incidentEdges_.end())
   {
      incidentEdges_.erase(edgeIter);
   }
}

bool Hypervertex::operator==(const Hypervertex& rhs) const
{
   return IdentifiableBase::operator==(rhs);
}

bool Hypervertex::operator!=(const Hypervertex& rhs) const
{
   return IdentifiableBase::operator!=(rhs);
}
}
}
}
