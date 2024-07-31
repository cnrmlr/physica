#include "common_utility.h"
#include "hyperedge.h"
#include "vertex.h"
#include "identifiable_base.h"

namespace graphica
{
namespace core
{
namespace elements
{
Hyperedge::Hyperedge()
   : IdentifiableBase()
   , vertices_(0)
{
}

Hyperedge::Hyperedge(const std::vector<std::shared_ptr<Vertex>>& vertices)
   : IdentifiableBase()
{
   vertices_.reserve(vertices.size());

   for (auto& vertex : vertices)
   {
      vertices_.push_back(vertex);
   }
}

Hyperedge::~Hyperedge()
{
}

const std::vector<std::weak_ptr<Vertex>> Hyperedge::getVertices() const
{
   return utility::MakeWeakPtrVector(vertices_);
}

bool Hyperedge::isAdjacentTo(const std::weak_ptr<Hyperedge>& edge)
{
   for (auto& vertex : vertices_)
   {
      if (edge.lock() && edge.lock()->isIncidentTo(vertex))
      {
         return true;
      }
   }

   return false;
}

bool Hyperedge::isIncidentTo(const std::weak_ptr<Vertex>& vertex)
{
   return findVertex(vertex) != vertices_.end();
}

const std::vector<std::shared_ptr<Vertex>>::iterator Hyperedge::findVertex(std::weak_ptr<Vertex> vertex)
{
   return utility::FindWithWeakPtr(vertices_, vertex);
}

void Hyperedge::removeVertex(std::weak_ptr<Vertex> vertex)
{
   auto vertexIter = findVertex(vertex);
   
   if (vertexIter != vertices_.end())
   {
      vertices_.erase(findVertex(vertex));
   }
}

void Hyperedge::removeFromVertexIncidenceLists()
{
   for (auto& vertex : vertices_)
   {
      vertex->removeIncidentEdge(shared_from_this());
   }
}

bool Hyperedge::operator==(const Hyperedge& rhs) const
{
   return IdentifiableBase::operator==(rhs);
}

bool Hyperedge::operator!=(const Hyperedge& rhs) const
{
   return IdentifiableBase::operator!=(rhs);
}
}
}
}