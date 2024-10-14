#pragma once

#include <physica/library/structures/hypergraph.h>
#include <physica/library/structures/rule.h>

#include <memory>
#include <functional>
#include <chrono>

namespace physica
{
using TransformationAlgorithm = std::function<void(structures::Hypergraph&, const structures::Rule&)>;

class Model final
{
public:
   Model(structures::Rule rule, size_t steps, TransformationAlgorithm transformer);
   Model() = delete;
   ~Model() = default;
   Model(const Model& rhs) = delete;
   Model& operator=(const Model& rhs) = delete;

   std::chrono::duration<std::chrono::milliseconds> run();

private:
   std::unique_ptr<structures::Hypergraph> hypergraph_;
   structures::Rule rule_;
   size_t steps_;
   TransformationAlgorithm transformer_;
};
}
