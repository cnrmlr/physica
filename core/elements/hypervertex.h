#pragma once

#include "identifiable_base.h"

#include <unordered_set>
#include <memory>

namespace cpe
{
namespace core
{
namespace elements
{
class Hypervertex : public utility::IdentifiableBase
{
public:
   Hypervertex();
   ~Hypervertex();
   Hypervertex(const Hypervertex& rhs);
   Hypervertex operator=(const Hypervertex& rhs);

   bool operator==(const Hypervertex& rhs) const;

private:
   // empty

protected:
   // empty
};
}
}
}