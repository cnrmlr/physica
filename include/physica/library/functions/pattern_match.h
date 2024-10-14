#pragma once

#include <physica/library/structures/hypergraph.h>
#include <physica/library/structures/rule.h>

#include <memory>
#include <vector>

namespace physica::functions
{
static void SetReplace_v1(structures::Hypergraph& graph, const structures::Rule& rule);
}