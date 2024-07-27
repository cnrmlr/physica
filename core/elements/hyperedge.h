#pragma once

#include "identifiable_base.h"
#include "type_defs.h"

#include <memory>
#include <unordered_set>

namespace cpe
{
namespace core
{
namespace elements
{
class Hypervertex;

class Hyperedge : public utility::IdentifiableBase
{
public:
   Hyperedge();
   ~Hyperedge();
   Hyperedge(const Hyperedge& rhs);
   Hyperedge operator=(const Hyperedge& rhs);

   Hyperedge(const std::vector<VertexPtr>& vertices);

   bool operator==(const Hyperedge& rhs);

   const std::vector<VertexPtr>& getVertices();

private:
   std::vector<VertexPtr> vertices_;
};
}
}
}
