#pragma once

#include "uuid.h"

namespace cpe
{
namespace core
{
class IdentifiableBase
{
public:
   IdentifiableBase();
   virtual ~IdentifiableBase();
   IdentifiableBase(const IdentifiableBase& rhs);
   IdentifiableBase& operator=(const IdentifiableBase& rhs);

   bool operator==(const IdentifiableBase& rhs) const;
   UUID getUUID() const;

protected:
   UUID uuid_;
};
}
}
