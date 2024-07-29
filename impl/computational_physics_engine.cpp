#pragma once

#include "computational_physics_engine.h"
#include "hyperedge.h"
#include "hypergraph.h"
#include "hypervertex.h"

#include <iostream>
#include <cassert>

/*
* Hypergraph Symbology
*
* In hypergraph theory, the following symbols and conventions are commonly used:
*
* V: The set of all vertices in the hypergraph.
*    - Example: V = {v1, v2, v3, ..., vn}
*
* W: A subset of the vertex set V.
*    - Example: V = {v1, v2, v3, ..., vn}
*               W = {v2, v3}
*
* E: The set of all hyperedges in the hypergraph.
*    - Each hyperedge is itself a subset of the vertex set V.
*    - Example: E = {e1, e2, e3, ..., em} where each ei is a subset of V
*
* F: A subset of the edge set E.
*    - Example:  E = {e1, e2, e3, ..., em}
*                F = {e2, e3}
*
* v: A single vertex in the hypergraph
* 
* e: A single edge in the hypergraph
* 
* General Notation:
* - Hypergraphs are often denoted as H = (V, E), where V is the set of vertices
*   and E is the set of hyperedges.
* - A hyperedge e in E is a set of vertices, e.g., e = {v1, v2, v3}.
* - The incidence relation between vertices and hyperedges is fundamental in hypergraph theory.
*
* Usage in Code:
* - std::vector<Hypervertex> V;   // The set of all vertices
* - std::vector<Hyperedge> E;     // The set of all hyperedges
* - std::vector<Vertex> W;        // A subset of vertices
* - std::vector<Hyperedge> F;     // A subset of hyperedges
* - std::weak_ptr<Hypervertex> v; // A single vertex
* - std::weak_ptr<Hyperedge> e;   // A single edge
*
* This symbology helps in clearly defining the structure and operations of hypergraphs
* in both theoretical discussions and practical implementations.
*/

namespace cpe
{
int Run()
{
   using namespace core::elements;



   // Each hypergraph instance should be managed by std::unique_ptr as these graphs
   // are fundamentally unique in nature and non-copyable. When a new graph is created,
   // it will have zero vertices and zero edges.
   std::unique_ptr<Hypergraph> G = std::make_unique<Hypergraph>();

   assert(G->getVertices().empty());                               // Ensure no vertices exist initially
   assert(G->getEdges().empty());                                  // Ensure no edges exist initially



   // Adding a single vertex to the hypergraph will return a non-reference counted
   // pointer to the new vertex using std::weak_ptr. The vertex can be removed from
   // the graph using Hypergraph::removeVertex(<weak vertex ptr>). The removal 
   // operation will validate the weak pointer and remove it from the graph if it is
   // not expired. The local weak ptr to the vertex will then be expired.
   {
      std::weak_ptr<Hypervertex> v = G->addVertex();

      assert(G->getVertices().size() == 1);              // Ensure one vertex is added
      assert(v.lock());                                  // Ensure the weak_ptr is valid (not expired)

      auto V = G->getVertices();

      assert(V.size() == 1);                             // Ensure one vertex is in the graph
      assert(V.front().lock() == v.lock());              // Ensure the vertex in the graph matches the added vertex

      G->removeVertex(v);

      assert(G->getVertices().empty());                  // Ensure no vertices exist after removal
      assert(v.expired());                               // Ensure the weak_ptr is expired after removal
   }



   // Vertices can also be added in bulk by specifying the number of vertices to add.
   // This operation will return a vector of weak ptrs to the newly created vertices.
   // We can also remove vertices in bulk by specifying a std::vector or 
   // std::initializer_list of the weak vertex ptrs. Note there is no need to check if the
   // weak vertex ptrs are expired before passing them to the remove operation.
   {
      std::vector<std::weak_ptr<Hypervertex>> W = G->addVertices(3);

      assert(G->getVertices().size() == 3);                          // Ensure three vertices are added
      assert(W.size() == 3);                                         // Ensure the returned vector has three elements
      for (auto& v : W)
         assert(v.lock());                                           // Ensure each weak_ptr is valid (not expired)

      auto V = G->getVertices();

      assert(W.size() == 3);                                         // Ensure the graph has three vertices
      for (size_t i = 0; i < W.size(); ++i)
         assert(W[i].lock() == V[i].lock());                         // Ensure the vertices match
      assert(W[0].lock() != W[1].lock());                            // Ensure all vertices are unique.
      assert(W[0].lock() != W[2].lock());
      assert(W[1].lock() != W[2].lock());

      G->removeVertices(W);

      assert(G->getVertices().empty());                              // Ensure no vertices exist after removal
      for (auto& v : W)
         assert(v.expired());                                        // Ensure each weak_ptr is expired after removal
   }



   // Edges are added to the hypergraph by specifying a set of incident vertices using 
   // a vector or initializer list of weak ptrs to the vertices. If an attempt is made
   // to add a non-existent vertex to an edge, that vertex will not be added to the edge.
   // Once an edge is created, it can be removed from the graph by passing a weak ptr to
   // Hypergraph::removeEdge(<weak edge ptr>). The removeEdge operation also handles the
   // removal of the edge from the incidence lists of the vertices on the edge to ensure
   // there are no dangling strong refs and the edge can be properly removed. If a vertex is 
   // removed from the graph while it exists on one or more edges, it is first removed 
   // from all of its incident edges and then removed from the graph.
   {
      std::vector<std::weak_ptr<Hypervertex>> W = G->addVertices(3);

      std::weak_ptr<Hyperedge> e = G->addEdge({ W[0], W[1], W[2] });

      assert(G->getEdges().size() == 1);                             // Ensure one edge is added
      assert(e.lock());                                              // Ensure the weak_ptr to edge is valid
      assert(e.lock()->getVertices().size() == 3);                   // Ensure the edge has three vertices
      for (auto& v : e.lock()->getVertices())
         assert(v.lock());                                           // Ensure each vertex on the edge is valid
      for (size_t i = 0; i < W.size(); ++i)
         assert(e.lock()->isIncidentTo(W[i]));                       // Ensure each vertex is incident to the edge
      assert(W[0].lock()->isAdjacentTo(W[1]));                       // Ensure W[0] is adjacent to W[1]
      assert(W[0].lock()->isAdjacentTo(W[2]));                       // Ensure W[0] is adjacent to W[2]
      assert(W[1].lock()->isAdjacentTo(W[2]));                       // Ensure W[1] is adjacent to W[2]

      G->removeVertex(W[1]);

      assert(e.lock()->isIncidentTo(W[1]) == false);                 // Ensure W[1] is no longer incident to the edge
      assert(W[0].lock()->isAdjacentTo(W[1]) == false);              // Ensure W[0] is no longer adjacent to W[1]
      assert(e.lock()->getVertices().size() == 2);                   // Ensure the edge now has two vertices
      assert(e.lock()->isIncidentTo(W[0]));                          // Ensure remaining vertices are still incident to the edge.
      assert(e.lock()->isIncidentTo(W[2]));

      G->removeEdge(e);

      assert(G->getEdges().empty());                                 // Ensure no edges exist after removal
      assert(e.expired());                                           // Ensure the weak_ptr to edge is expired after removal
   }



   // Just as vertices can be added in bulk, edges can as well. Hypergraph::addEdges
   // takes a vector of vectors where each sub-vector specifies the vertices on a specific
   // hyperedge. The operation returns a vector of weak edge ptrs so to not increase the 
   // reference count on the edges that are now owned by the hypergraph. Edges can be removed
   // in bulk as well with the Hypergraph::removeEdges operation which take a vector of weak
   // edge pointers.
   {
      std::vector<std::weak_ptr<Hypervertex>> W = G->addVertices(6);

      std::vector<std::weak_ptr<Hyperedge>> F = G->addEdges({
          { W[0], W[1] },
          { W[1], W[2] },
          { W[0], W[3] },
          { W[1], W[2], W[3], W[4] },
          { W[3], W[4], W[5] }
      });

      assert(G->getEdges().size() == 5);                             // Ensure five edges are added
      assert(F.size() == 5);                                         // Ensure the returned vector has five elements
      assert(F[0].lock()->getVertices().size() == 2);                // Ensure edges have proper number of vertices
      assert(F[1].lock()->getVertices().size() == 2);
      assert(F[2].lock()->getVertices().size() == 2);
      assert(F[3].lock()->getVertices().size() == 4);
      assert(F[4].lock()->getVertices().size() == 3);
      for (size_t i = 0; i < F.size(); ++i)
         assert(F[i].lock());                                        // Ensure each weak_ptr to edge is valid
      for (auto& e : F)
         for (auto& v : e.lock()->getVertices())
            assert(v.lock());                                        // Ensure each vertex on each edge is valid

      G->removeEdges(F);
      G->removeVertices(W);

      assert(G->getEdges().size() == 0);                             // Ensure no edges exist after removal
      for (auto& e : F)
         assert(e.expired());                                        // Ensure each weak_ptr to edge is expired after removal
   }

   return 1;
}
}

