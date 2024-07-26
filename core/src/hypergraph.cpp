#include "hypergraph.h"

namespace cpe
{
namespace core
{
Hypergraph::Hypergraph()
   : IdentifiableBase()
   , vertices_(nullptr)
   , edges_(nullptr)
{
   vertices_ = std::make_unique<std::vector<Hypervertex>>();
   vertices_->reserve(10000);

   edges_ = std::make_unique<std::vector<Hyperedge>>();
   edges_->reserve(10000);
}

Hypergraph::~Hypergraph()
{
}

const RawVertexPtr Hypergraph::addVertex()
{
   if (vertices_->size() < vertices_->capacity())
   {
      return &vertices_->emplace_back();
   }
   else
   {
      return nullptr;
   }
}

void Hypergraph::removeVertex(const RawVertexPtr vertex)
{
   auto it = std::find(vertices_->begin(), vertices_->end(), *vertex);

   if (it != vertices_->end())
   {
      vertices_->erase(it);
   }

   // @TODO: Need to automate the removal of the vertex from the edges its contain on
   // before its removed from the graph.
}

const std::vector<RawVertexPtr> Hypergraph::addVertices(size_t count)
{
   std::vector<RawVertexPtr> newVertices;
   newVertices.reserve(count);

   for (size_t i = 0; i < count; ++i)
   {
      newVertices.push_back(addVertex());
   }

   return newVertices;
}

const RawEdgePtr Hypergraph::addEdge(const std::vector<RawVertexPtr>& incidentVertices)
{
   if (edges_->size() < edges_->capacity())
   {
      return &edges_->emplace_back(incidentVertices);
   }
   else
   {
      return nullptr;
   }
}

void Hypergraph::removeEdge(const RawEdgePtr edge)
{
   auto it = std::find(edges_->begin(), edges_->end(), *edge);

   if (it != edges_->end())
   {
      edges_->erase(it);
   }
}

const std::vector<Hypervertex>& Hypergraph::getVertices()
{
   return *vertices_.get();
}

const std::vector<Hyperedge>& Hypergraph::getEdges()
{
   return *edges_.get();
}
}
}
