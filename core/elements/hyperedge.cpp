#include "hyperedge.h"
#include "hypervertex.h"

namespace cpe
{
namespace core
{
namespace elements
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
   : IdentifiableBase(rhs)
   , vertices_(rhs.vertices_)
{
}

Hyperedge Hyperedge::operator=(const Hyperedge& rhs)
{
   if (this != &rhs)
   {
      IdentifiableBase::operator=(rhs);
   }
   return *this;
}

Hyperedge::Hyperedge(const std::vector<VertexPtr>& vertices)
   : IdentifiableBase()
   , vertices_(vertices)
{
}

bool Hyperedge::operator==(const Hyperedge& rhs)
{
   return IdentifiableBase::operator==(rhs);
}

const std::vector<VertexPtr>& Hyperedge::getVertices()
{
   return vertices_;
}
}

}
}