#pragma once

#include <memory>
#include <vector>
#include <algorithm>

namespace phys::internal
{
   // converts a weak ptr to a shared ptr to query the given container using std::find. If the value
   // was not found or if the weak ptr could not be locked conatiner.end() is returned.
   template <class T>
   typename std::vector<std::shared_ptr<T>>::iterator find_with_weak_ptr(std::vector<std::shared_ptr<T>> &sharedVector, const std::weak_ptr<T> &value)
   {
      auto iter = sharedVector.end();

      if (auto sharedPtr = value.lock())
      {
         iter = std::find(sharedVector.begin(), sharedVector.end(), sharedPtr);
      }

      return iter;
   }

   // converts a vector of shared ptrs to a vector of weak ptrs so that a list objects can be returned
   // without increasing the refernce counts of the managed objects.
   template <class T>
   std::vector<std::weak_ptr<T>> make_weak_ptr_vector(const std::vector<std::shared_ptr<T>> &sharedVector)
   {
      std::vector<std::weak_ptr<T>> weakVector;
      weakVector.reserve(sharedVector.size());

      for (const auto &element : sharedVector)
      {
         weakVector.emplace_back(element);
      }

      return weakVector;
   }

   // converts a vector of weak ptrs to a vector of shared ptrs. If one of the structures in the weak ptr
   // vector could not be locked, the conversion will abort and return an empty vector.
   template <class T>
   std::vector<std::shared_ptr<T>> make_shared_ptr_vector(const std::vector<std::weak_ptr<T>> &weakVector)
   {
      std::vector<std::shared_ptr<T>> sharedVector;
      sharedVector.reserve(weakVector.size());

      for (auto &element : weakVector)
      {
         if (auto &sharedElement = element.lock())
         {
            sharedVector.push_back(sharedElement);
         }
         else
         {
            sharedVector.clear();
            break;
         }
      }

      return sharedVector;
   }
}
