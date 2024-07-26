#include "hyperedge.h"
#include "hypervertex.h"

namespace cpe
{
namespace core
{
Hyperedge::Hyperedge()
   : IdentifiableBase()
   , vertices_(0)
{
   vertices_.reserve(100);
}

Hyperedge::~Hyperedge()
{
}

Hyperedge::Hyperedge(const Hyperedge& rhs)
   : core::IdentifiableBase(rhs)
   , vertices_(rhs.vertices_)
{
}

Hyperedge Hyperedge::operator=(const Hyperedge& rhs)
{
   if (this != &rhs)
   {
      core::IdentifiableBase::operator=(rhs);
   }
   return *this;
}

Hyperedge::Hyperedge(const std::vector<RawVertexPtr>& vertices)
   : IdentifiableBase()
   , vertices_(vertices)
{
}

bool Hyperedge::operator==(const Hyperedge& rhs)
{
   return IdentifiableBase::operator==(rhs);
}

const std::vector<RawVertexPtr>& Hyperedge::getVertices()
{
   return vertices_;
}
}
}