#pragma once

#include "instance.h"

namespace computational_physics_engine
{
Instance::Instance()
{
}

Instance::~Instance()
{
}

void Instance::run()
{
   // create new vertices
   auto v1 = std::make_shared<core::Hypervertex>();
   auto v2 = std::make_shared<core::Hypervertex>();
   auto v3 = std::make_shared<core::Hypervertex>();
   auto v4 = std::make_shared<core::Hypervertex>();
   auto v5 = std::make_shared<core::Hypervertex>();
   auto v6 = std::make_shared<core::Hypervertex>();

   core::SharedVertexSet X = { v1, v2, v3, v4, v5, v6 };

   // create directed hyperedges by specifying the tail and head vertex sets
   auto e1 = std::make_shared<core::Hyperedge>(core::SharedVertexSet({ v1 }), core::SharedVertexSet({ v2 }));
   auto e2 = std::make_shared<core::Hyperedge>(core::SharedVertexSet({ v2 }), core::SharedVertexSet({ v3 }));
   auto e3 = std::make_shared<core::Hyperedge>(core::SharedVertexSet({ v3 }), core::SharedVertexSet({ v1 }));
   auto e4 = std::make_shared<core::Hyperedge>(core::SharedVertexSet({ v2, v3 }), core::SharedVertexSet({ v4, v5 }));
   auto e5 = std::make_shared<core::Hyperedge>(core::SharedVertexSet({ v3, v5 }), core::SharedVertexSet({ v6 }));

   core::SharedEdgeSet E = { e1, e2, e3, e4, e5 };

   // add vertices and edges to the hypergraph
   hypergraph_.setVertices(X);
   hypergraph_.setEdges(E);
}
}