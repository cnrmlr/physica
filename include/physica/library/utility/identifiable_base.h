#pragma once

#include <physica/library/utility/uuid.h>

namespace physica::utility
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
