#pragma once

#include "uuid.h"

namespace computational_physics_engine
{
namespace core
{
class Identifiable
{
public:
   Identifiable();
   virtual ~Identifiable();
   Identifiable(const Identifiable&);
   Identifiable& operator=(const Identifiable&);
   UUID getUUID() const;

protected:
   UUID uuid_;
};
}
}
