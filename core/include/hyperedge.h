#pragma once

#include "identifiable_base.h"
#include "type_defs.h"

#include <memory>
#include <unordered_set>

namespace cpe
{
namespace core
{
class Hypervertex;

class Hyperedge : public IdentifiableBase
{
public:
   Hyperedge();
   ~Hyperedge();
   Hyperedge(const Hyperedge& rhs);
   Hyperedge operator=(const Hyperedge& rhs);

   Hyperedge(const std::vector<RawVertexPtr>& vertices);

   bool operator==(const Hyperedge& rhs);

   const std::vector<RawVertexPtr>& getVertices();

private:
   std::vector<RawVertexPtr> vertices_;
};
}
}
