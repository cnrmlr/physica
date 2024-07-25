#pragma once

#include "identifiable.h"
#include "hash.h"

#include <memory>
#include <unordered_set>

namespace computational_physics_engine
{
namespace core
{
class Hypervertex;

using SharedVertexSet = std::unordered_set<std::shared_ptr<Hypervertex>>;

class Hyperedge : public core::Identifiable, public std::enable_shared_from_this<Hyperedge>
{
public:
   Hyperedge();
   ~Hyperedge();
   Hyperedge(const Hyperedge&);
   Hyperedge& operator=(const Hyperedge&);

   Hyperedge(SharedVertexSet tail, SharedVertexSet head);

   void setEndpoints(SharedVertexSet tail, SharedVertexSet head);
   const std::pair<SharedVertexSet, SharedVertexSet> getEndpoints() const;

   void setHead(SharedVertexSet head);
   const SharedVertexSet getHead() const;

   void setTail(SharedVertexSet tail);
   const SharedVertexSet getTail() const;

private:
   std::pair<SharedVertexSet, SharedVertexSet> endpoints_;

   void AddThisEdgeToIncidenceLists(SharedVertexSet incidentVertices);
};
}
}
