#pragma once

#include <physica/library/structures/hypergraph.h>
#include <physica/library/structures/rule.h>

#include <memory>

namespace physica
{
class Model
{
public:
   Model();
   ~Model();
   Model(const Model& rhs);
   Model& operator=(const Model& rhs);

private:
   std::unique_ptr<structures::Hypergraph> hypergraph_;

   structures::Rule rule_;

   size_t steps_;

};
}
