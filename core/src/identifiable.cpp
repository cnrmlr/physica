#include "identifiable.h"

namespace computational_physics_engine
{
namespace core
{
Identifiable::Identifiable()
   : uuid_(UUID::Generate())
{
}

Identifiable::~Identifiable()
{
}

Identifiable::Identifiable(const Identifiable& rhs)
   : uuid_(rhs.uuid_)
{
}

Identifiable& Identifiable::operator=(const Identifiable& rhs)
{
   if (this != &rhs)
   {
      uuid_ = rhs.uuid_;
   }
   return *this;
}

UUID Identifiable::getUUID() const
{
   return uuid_;
}
}
}