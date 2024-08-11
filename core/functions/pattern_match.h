#pragma once

#include "hypergraph.h"
#include "rule.h"

#include <memory>
#include <vector>

namespace graphica
{
namespace core
{
namespace elements
{
class Hyperedge;
}
namespace functions
{
std::weak_ptr<elements::Hyperedge> PatternMatch(const elements::AbstractRelation pattern, 
                                                const std::vector<std::weak_ptr<elements::Hyperedge>>& edges);
}
}
}