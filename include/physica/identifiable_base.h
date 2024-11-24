#pragma once

#include <physica/uuid.h>

namespace phys
{
class identifiable_base
{
public:
   identifiable_base() : uuid_(phys::uuid::generate()) {}
   virtual ~identifiable_base()                 = default;
   identifiable_base(const identifiable_base &) = default;
   identifiable_base &operator=(const identifiable_base &) = default;
   identifiable_base(identifiable_base &&)      = default;
   identifiable_base &operator=(identifiable_base &&) = default;

   bool operator==(const identifiable_base &rhs) const { return uuid_ == rhs.uuid(); }
   bool operator!=(const identifiable_base &rhs) const { return uuid_ != rhs.uuid(); }

   const phys::uuid& uuid() const { return uuid_; }

protected:
   phys::uuid uuid_;
};
} // namespace phys::internal
