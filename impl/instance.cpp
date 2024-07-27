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
   auto vertex = hypergraph_.addVertex();

   // add multiple vertices to the hypergraph
   auto v = hypergraph_.addVertices(6);

   // add directed hyperedges by specifying an ordered set vertices for each edge
   auto e1 = hypergraph_.addEdge({ v[0], v[1] });
   auto e2 = hypergraph_.addEdge({ v[1], v[2] });
   auto e3 = hypergraph_.addEdge({ v[2], v[0] });
   auto e4 = hypergraph_.addEdge({ v[1], v[2], v[3], v[4] });
   auto e5 = hypergraph_.addEdge({ v[2], v[4], v[5] });

   // remove a single vertex from the hypergraph
   hypergraph_.removeVertex(v[2]);

   // remove a single edge from the hypergraph
   hypergraph_.removeEdge(e3);

   // get the current graph data
   auto& currentVertices = hypergraph_.getVertices();
   auto& currentEdges = hypergraph_.getEdges();
}
}