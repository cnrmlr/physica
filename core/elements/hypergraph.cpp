#include "hypergraph.h"

namespace cpe
{
namespace core
{
namespace elements
{
Hypergraph::Hypergraph()
   : IdentifiableBase()
{
}

Hypergraph::~Hypergraph()
{
}

const_VertexPtr Hypergraph::addVertex()
{
   return vertices_.allocate();
}

void Hypergraph::removeVertex(const_VertexPtr vertex)
{
   vertices_.deallocate(vertex);

   // @TODO: Need to automate the removal of the vertex from the edges its contain on
   // before its removed from the graph.
}

const std::vector<VertexPtr> Hypergraph::addVertices(size_t count)
{
   std::vector<VertexPtr> newVertices;
   newVertices.reserve(count);

   for (size_t i = 0; i < count; ++i)
   {
      newVertices.push_back(addVertex());
   }

   return newVertices;
}

const_EdgePtr Hypergraph::addEdge(const std::vector<VertexPtr>& incidentVertices)
{
   return edges_.newElement(incidentVertices);
}

void Hypergraph::removeEdge(const_EdgePtr edge)
{
   edges_.deleteElement(edge);
}

const utility::MemoryPool<Hypervertex>& Hypergraph::getVertices()
{
   return vertices_;
}

const utility::MemoryPool<Hyperedge>& Hypergraph::getEdges()
{
   return edges_;
}
}
}
}
