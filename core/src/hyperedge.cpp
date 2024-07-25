#include "hyperedge.h"
#include "hypervertex.h"

namespace computational_physics_engine
{
namespace core
{
Hyperedge::Hyperedge()
   : Identifiable()
{
}

Hyperedge::~Hyperedge()
{
}

Hyperedge::Hyperedge(const Hyperedge& rhs)
   : core::Identifiable(rhs)
   , endpoints_(rhs.endpoints_)
{
}

Hyperedge& Hyperedge::operator=(const Hyperedge& rhs)
{
   if (this != &rhs)
   {
      core::Identifiable::operator=(rhs);
      endpoints_ = rhs.endpoints_;
   }
   return *this;
}

Hyperedge::Hyperedge(SharedVertexSet tail, SharedVertexSet head)
{
   setEndpoints(tail, head);
}

void Hyperedge::setEndpoints(SharedVertexSet tail, SharedVertexSet head)
{
   setTail(tail);
   setHead(head);
}

const std::pair<SharedVertexSet, SharedVertexSet> Hyperedge::getEndpoints() const
{
   return endpoints_;
}

void Hyperedge::setHead(SharedVertexSet head)
{
   endpoints_.second = head;
}

const SharedVertexSet Hyperedge::getHead() const
{
   return endpoints_.second;
}

void Hyperedge::setTail(SharedVertexSet tail)
{
   endpoints_.first = tail;
}

const SharedVertexSet Hyperedge::getTail() const
{
   return endpoints_.first;
}

void Hyperedge::AddThisEdgeToIncidenceLists(SharedVertexSet incidentVertices)
{
   for (auto& vertex : incidentVertices)
   {
      vertex->addIncidentEdge(shared_from_this());
   }
}
}
}
