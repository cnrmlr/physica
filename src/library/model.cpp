#include <physica/library/model.h>

namespace physica
{
Model::Model(structures::Rule rule, size_t steps, TransformationAlgorithm transformer)
   : hypergraph_(nullptr)
   , rule_(rule)
   , steps_(steps)
   , transformer_(transformer)
{
   hypergraph_ = std::make_unique<structures::Hypergraph>();
}

std::chrono::duration<std::chrono::milliseconds> Model::run()
{
   std::chrono::duration<std::chrono::milliseconds> dt{};

   for (std::size_t i = 0; i <= steps_; ++i)
   {
      dt += transformer_(*hypergraph_.get(), rule_);
   }

   return dt;
}
}
