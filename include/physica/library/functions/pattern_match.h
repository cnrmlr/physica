#pragma once

#include <physica/library/structures/hypergraph.h>
#include <physica/library/structures/rule.h>

#include <memory>
#include <vector>

namespace physica::functions
{
std::weak_ptr<structures::Hyperedge> PatternMatch(const structures::AbstractRelation& pattern, 
                                                const std::vector<std::weak_ptr<structures::Hyperedge>>& edges);
}