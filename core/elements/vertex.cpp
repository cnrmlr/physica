#include "common_utility.h"
#include "hyperedge.h"
#include "vertex.h"

#include <algorithm>

namespace graphica
{
namespace core
{
namespace elements
{
Vertex::Vertex()
   : IdentifiableBase()
{
}

Vertex::~Vertex()
{
}

const std::vector<std::weak_ptr<Hyperedge>> Vertex::getIncidentEdges()
{
   return utility::MakeWeakPtrVector(incidentEdges_);
}

bool Vertex::isAdjacentTo(const std::weak_ptr<Vertex>& vertex)
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

bool Vertex::isIncidentTo(const std::weak_ptr<Hyperedge>& edge)
{
   return utility::FindWithWeakPtr(incidentEdges_, edge) != incidentEdges_.end();
}

void Vertex::addIncidentEdge(const std::weak_ptr<Hyperedge>& incidentEdge)
{
   incidentEdges_.emplace_back(incidentEdge);
}

void Vertex::removeIncidentEdge(const std::weak_ptr<Hyperedge>& incidentEdge)
{
   auto edgeIter = utility::FindWithWeakPtr(incidentEdges_, incidentEdge);

   if (edgeIter != incidentEdges_.end())
   {
      incidentEdges_.erase(edgeIter);
   }
}

bool Vertex::operator==(const Vertex& rhs) const
{
   return IdentifiableBase::operator==(rhs);
}

bool Vertex::operator!=(const Vertex& rhs) const
{
   return IdentifiableBase::operator!=(rhs);
}
}
}
}
