#pragma once

#include "hypergraph.h" 

namespace computational_physics_engine
{
class Instance
{
public:
   Instance();
   ~Instance();
   Instance(const Instance&) = delete;
   Instance& operator=(const Instance&) = delete;

   void run();

private:
   core::Hypergraph hypergraph_;
};
}