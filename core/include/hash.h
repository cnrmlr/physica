#pragma once

#include <functional>
#include <memory>

namespace computational_physics_engine
{
namespace core
{
struct WeakPtrHash {
   template <class T>
   std::size_t operator()(const std::weak_ptr<T>& wp) const {
      if (auto sp = wp.lock()) {
         return std::hash<std::uintptr_t>()(reinterpret_cast<std::uintptr_t>(sp.get()));
      }
      return 0;
   }
};

struct WeakPtrEqual {
   template <class T>
   bool operator()(const std::weak_ptr<T>& wp1, const std::weak_ptr<T>& wp2) const {
      return wp1.lock() == wp2.lock();
   }
};
}
}
