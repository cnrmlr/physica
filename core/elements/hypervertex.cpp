#include "hypervertex.h"

namespace cpe
{
namespace core
{
namespace elements
{
Hypervertex::Hypervertex()
   : IdentifiableBase()
{
}

Hypervertex::~Hypervertex()
{
}

Hypervertex::Hypervertex(const Hypervertex& rhs)
   : IdentifiableBase(rhs)
{
}

Hypervertex Hypervertex::operator=(const Hypervertex& rhs)
{
   if (this != &rhs)
   {
      IdentifiableBase::operator=(rhs);
   }
   return *this;
}

bool Hypervertex::operator==(const Hypervertex& rhs) const
{
   return IdentifiableBase::operator==(rhs);
}
}
}
}
