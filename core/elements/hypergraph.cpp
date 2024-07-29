#include "common_utility.h"
#include "hyperedge.h"
#include "hypergraph.h"
#include "hypervertex.h"

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

const std::weak_ptr<Hypervertex> Hypergraph::addVertex()
{
   std::shared_ptr<Hypervertex> vertex = std::make_shared<Hypervertex>();
   return vertices_.emplace_back(vertex);
}

void Hypergraph::removeVertex(const std::weak_ptr<Hypervertex>& vertex)
{
   // remove the vertex from the edges it exists on
   for (auto& edge : edges_)
   {
      edge->removeVertex(vertex);
   }

   // remove the vertex from the graph
   auto vertexIter = utility::FindWithWeakPtr(vertices_, vertex);

   if (vertexIter != vertices_.end())
   {
      vertices_.erase(vertexIter);
   }
}

const std::vector<std::weak_ptr<Hypervertex>> Hypergraph::addVertices(size_t count)
{
   std::vector<std::weak_ptr<Hypervertex>> newVertices;
   newVertices.reserve(count);

   for (size_t i = 0; i < count; ++i)
   {
      newVertices.emplace_back(addVertex());
   }

   return newVertices;
}

void Hypergraph::removeVertices(const std::vector<std::weak_ptr<Hypervertex>>& vertices)
{
   for (auto& vertex : vertices)
   {
      removeVertex(vertex);
   }
}

const std::weak_ptr<Hyperedge> Hypergraph::addEdge(std::vector<std::weak_ptr<Hypervertex>> vertices)
{
   std::vector<std::shared_ptr<Hypervertex>> sharedVertices = utility::MakeSharedPtrVector(vertices);

   // return nullptr if there was an issue doing the conversion
   if (sharedVertices.empty())
   {
      return std::make_shared<Hyperedge>();
   }

   // add the edge to the graph and give the incident vertices a ref to the new edge
   std::shared_ptr<Hyperedge> edge = std::make_shared<Hyperedge>(sharedVertices);

   edges_.push_back(edge);

   for (auto& vertex : sharedVertices)
   {
      vertex->addIncidentEdge(edge);
   }

   return edge;
}

void Hypergraph::removeEdge(const std::weak_ptr<Hyperedge>& edge)
{
   auto edgeIter = utility::FindWithWeakPtr(edges_, edge);

   if (edgeIter != edges_.end())
   {
      edgeIter->get()->removeFromVertexIncidenceLists();
      edges_.erase(edgeIter);
   }
}

const std::vector<std::weak_ptr<Hyperedge>> Hypergraph::addEdges(std::vector<std::vector<std::weak_ptr<Hypervertex>>> vertexSets)
{
   std::vector<std::weak_ptr<Hyperedge>> newEdges;
   newEdges.reserve(vertexSets.size());

   for (auto& set : vertexSets)
   {
      newEdges.emplace_back(addEdge(set));
   }

   return newEdges;
}

void Hypergraph::removeEdges(const std::vector<std::weak_ptr<Hyperedge>>& edges)
{
   for (auto& edge : edges)
   {
      removeEdge(edge);
   }
}

const std::vector<std::weak_ptr<Hypervertex>> Hypergraph::getVertices() const
{
   return utility::MakeWeakPtrVector(vertices_);
}

const std::vector<std::weak_ptr<Hyperedge>> Hypergraph::getEdges() const
{
   return utility::MakeWeakPtrVector(edges_);
}
}
}
}
