#pragma once

#include "uuid.h"

namespace cpe
{
namespace core
{
namespace utility
{
class IdentifiableBase
{
public:
   IdentifiableBase();
   virtual ~IdentifiableBase();
   IdentifiableBase(const IdentifiableBase& rhs) = delete;
   IdentifiableBase& operator=(const IdentifiableBase& rhs) = delete;

   bool operator==(const IdentifiableBase& rhs) const;
   bool operator!=(const IdentifiableBase& rhs) const;

   const UUID getUUID() const;

protected:
   UUID uuid_;
};
}
}
}
