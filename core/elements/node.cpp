#include "common_utility.h"
#include "hyperedge.h"
#include "node.h"

#include <algorithm>

namespace graphica
{
namespace core
{
namespace elements
{
Node::Node()
   : IdentifiableBase()
{
}

Node::~Node()
{
}

const std::vector<std::weak_ptr<Hyperedge>> Node::getIncidentEdges()
{
   return utility::MakeWeakPtrVector(incidentEdges_);
}

bool Node::isAdjacentTo(const std::weak_ptr<Node>& node)
{
   for (auto& edge : incidentEdges_)
   {
      if (edge->isIncidentTo(node))
      {
         return true;
      }
   }

   return false;
}

bool Node::isIncidentTo(const std::weak_ptr<Hyperedge>& edge)
{
   return utility::FindWithWeakPtr(incidentEdges_, edge) != incidentEdges_.end();
}

void Node::addIncidentEdge(const std::weak_ptr<Hyperedge>& incidentEdge)
{
   incidentEdges_.emplace_back(incidentEdge);
}

void Node::removeIncidentEdge(const std::weak_ptr<Hyperedge>& incidentEdge)
{
   auto edgeIter = utility::FindWithWeakPtr(incidentEdges_, incidentEdge);

   if (edgeIter != incidentEdges_.end())
   {
      incidentEdges_.erase(edgeIter);
   }
}

bool Node::operator==(const Node& rhs) const
{
   return IdentifiableBase::operator==(rhs);
}

bool Node::operator!=(const Node& rhs) const
{
   return IdentifiableBase::operator!=(rhs);
}
}
}
}