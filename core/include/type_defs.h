#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

namespace cpe
{
namespace core
{
class Hypervertex;

using RawVertexPtr = Hypervertex*;
using WeakVertexPtr = std::weak_ptr<Hypervertex>;
using SharedVertexPtr = std::shared_ptr<Hypervertex>;
using UniqueVertexPtr = std::unique_ptr<Hypervertex>;

class Hyperedge;

using RawEdgePtr = Hyperedge*;
using WeakEdgePtr = std::weak_ptr<Hyperedge>;
using SharedEdgePtr = std::shared_ptr<Hyperedge>;
using UniqueEdgePtr = std::unique_ptr<Hyperedge>;
}
}
