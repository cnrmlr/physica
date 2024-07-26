#pragma once

#include "instance.h"

namespace cpe
{
Instance::Instance()
{
}

Instance::~Instance()
{
}

void Instance::run()
{
   // add a single vertex to the hypergraph
   core::RawVertexPtr vertex = hypergraph_.addVertex();

   // add multiple vertices to the hypergraph
   std::vector<core::RawVertexPtr> v = hypergraph_.addVertices(6);

   // add directed hyperedges by specifying an ordered set vertices for each edge
   core::RawEdgePtr e1 = hypergraph_.addEdge({ v[0], v[1] });
   core::RawEdgePtr e2 = hypergraph_.addEdge({ v[1], v[2] });
   core::RawEdgePtr e3 = hypergraph_.addEdge({ v[2], v[0] });
   core::RawEdgePtr e4 = hypergraph_.addEdge({ v[1], v[2], v[3], v[4] });
   core::RawEdgePtr e5 = hypergraph_.addEdge({ v[2], v[4], v[5] });

   // remove a single vertex from the hypergraph
   hypergraph_.removeVertex(v[2]);

   // remove a single edge from the hypergraph
   hypergraph_.removeEdge(e3);

   // get the current graph data
   const std::vector<core::Hypervertex>& currentVertices = hypergraph_.getVertices();
   const std::vector<core::Hyperedge>& currentEdges = hypergraph_.getEdges();
}
}