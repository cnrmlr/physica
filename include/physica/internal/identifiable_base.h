#pragma once

#include <physica/internal/uuid.h>

namespace phys::internal
{
   class identifiable_base
   {
   public:
      identifiable_base() : uuid_(internal::uuid::generate()) {}
      virtual ~identifiable_base() = default;
      identifiable_base(const identifiable_base &) = delete;
      identifiable_base(identifiable_base &&) = default;
      identifiable_base &operator=(const identifiable_base &) = delete;
      identifiable_base &operator=(identifiable_base &&) = delete;

      bool operator==(const identifiable_base &rhs) const
      {
         return uuid_ == rhs.uuid();
      };

      bool operator!=(const identifiable_base &rhs) const
      {
         return uuid_ != rhs.uuid();
      }

      const internal::uuid uuid() const
      {
         return uuid_;
      }

   protected:
      internal::uuid uuid_;
   };
}
