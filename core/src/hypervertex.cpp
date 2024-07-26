#include "hypervertex.h"

namespace cpe
{
namespace core
{
Hypervertex::Hypervertex()
   : IdentifiableBase()
{
}

Hypervertex::~Hypervertex()
{
}

Hypervertex::Hypervertex(const Hypervertex& rhs)
   : core::IdentifiableBase(rhs)
{
}

Hypervertex Hypervertex::operator=(const Hypervertex& rhs)
{
   if (this != &rhs)
   {
      core::IdentifiableBase::operator=(rhs);
   }
   return *this;
}

bool Hypervertex::operator==(const Hypervertex& rhs) const
{
   return IdentifiableBase::operator==(rhs);
}
}
}
