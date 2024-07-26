#include "identifiable_base.h"

namespace cpe
{
namespace core
{
IdentifiableBase::IdentifiableBase()
   : uuid_(UUID::Generate())
{
}

IdentifiableBase::~IdentifiableBase()
{
}

IdentifiableBase::IdentifiableBase(const IdentifiableBase& rhs)
   : uuid_(rhs.uuid_)
{
}

IdentifiableBase& IdentifiableBase::operator=(const IdentifiableBase& rhs)
{
   if (this != &rhs)
   {
      uuid_ = rhs.uuid_;
   }
   return *this;
}

bool IdentifiableBase::operator==(const IdentifiableBase& rhs) const
{
   return uuid_ == rhs.getUUID();
}

UUID IdentifiableBase::getUUID() const
{
   return uuid_;
}
}
}