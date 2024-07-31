#pragma once

#include "graphica.h"
#include "hyperedge.h"
#include "hypergraph.h"
#include "vertex.h"

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

namespace graphica
{
int Run()
{
   using namespace core::elements;



   // Each hypergraph instance should be managed by std::unique_ptr as these graphs
   // are fundamentally unique in nature and non-copyable. When a new graph is created,
   // it will have zero vertices and zero edges.

   std::unique_ptr<Hypergraph> G = std::make_unique<Hypergraph>();



   // The full sets of vertices and edges that currently exist on the hypergraph can be 
   // fetched using the following functions. Note that these are sets of weak ptrs, 
   // intended to not increase the reference count on objects managed by the hypergraph,
   // and may expire if operations to the hypergraph occur within the same scope that 
   // these sets are declared.
   {
      std::vector<std::weak_ptr<Vertex>> V = G->getVertices();

      std::vector<std::weak_ptr<Hyperedge>> E = G->getEdges();
   }



   // Adding a single vertex to the hypergraph will return a single non-reference counted
   // pointer to the new vertex. The removal operation will validate the weak pointer and 
   // remove it from the graph if it is not expired. The local weak ptr to the vertex will 
   // then be expired.
   {
      std::weak_ptr<Vertex> v = G->addVertex();

      G->removeVertex(v);
   }



   // Vertices can also be added in bulk by specifying the number of vertices to add.
   // This operation will return a vector of weak ptrs to the newly created vertices.
   // We can also remove vertices in bulk by specifying a std::vector or 
   // std::initializer_list of the weak vertex ptrs.
   {
      std::vector<std::weak_ptr<Vertex>> W = G->addVertices(3);

      G->removeVertices(W);
   }



   // Edges are added to the hypergraph by specifying a set of incident vertices using 
   // a vector or initializer list of weak ptrs to the vertices. If an attempt is made
   // to add an expired vertex to an edge, that vertex will not be added to the edge.
   // Once an edge is created, it can be removed from the graph by passing a weak ptr to
   // the hypergraph::removeEdge operation. The remove edge operation also handles the
   // removal of the edge from the incidence lists of the vertices on the edge to ensure
   // there are no dangling strong refs and the edge can be properly removed. If a vertex is 
   // removed from the graph while it exists on one or more edges, it is first removed 
   // from all of its incident edges and then removed from the graph.
   {
      std::vector<std::weak_ptr<Vertex>> W = G->addVertices(3);

      std::weak_ptr<Hyperedge> e = G->addEdge(W);

      G->removeEdge(e);

      G->removeVertices(W);
   }



   // Just as vertices can be added in bulk, edges can as well. Hypergraph::addEdges
   // takes a vector of vectors where each sub-vector specifies the vertices on a specific
   // hyperedge. The operation returns a vector of weak edge ptrs so to not increase the 
   // reference count on the edges that are now owned by the hypergraph. Edges can be removed
   // in bulk as well with the Hypergraph::removeEdges operation which take a vector of weak
   // edge pointers.
   {
      std::vector<std::weak_ptr<Vertex>> W = G->addVertices(6);

      std::vector<std::weak_ptr<Hyperedge>> F = G->addEdges({
          { W[0], W[1] },
          { W[1], W[2] },
          { W[0], W[3] },
          { W[1], W[2], W[3], W[4] },
          { W[3], W[4], W[5] }
      });

      G->removeEdges(F);

      G->removeVertices(W);
   }

   return 1;
}
}

