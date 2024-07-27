#pragma once

#include <climits>
#include <cstddef>

namespace cpe
{
namespace core
{
namespace utility
{
template <typename T, size_t BlockSize = 4096>
class MemoryPool
{
public:
   /* Member types */
   using value_type = T;
   using pointer = T*;
   using reference = T&;
   using const_pointer = const T*;
   using const_reference = const T&;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using propagate_on_container_copy_assignment = std::false_type;
   using propagate_on_container_move_assignment = std::true_type;
   using propagate_on_container_swap = std::true_type;

   template <typename U> struct rebind {
      typedef MemoryPool<U> other;
   };

   MemoryPool() noexcept
   {
      currentBlock_ = nullptr;
      currentSlot_ = nullptr;
      lastSlot_ = nullptr;
      freeSlots_ = nullptr;
   }

   MemoryPool(const MemoryPool& memoryPool) noexcept 
      : MemoryPool()
   {
   }

   MemoryPool(MemoryPool&& memoryPool) noexcept
   {
      currentBlock_ = memoryPool.currentBlock_;
      memoryPool.currentBlock_ = nullptr;
      currentSlot_ = memoryPool.currentSlot_;
      lastSlot_ = memoryPool.lastSlot_;
      freeSlots_ = memoryPool.freeSlots;
   }

   template<class U>
   MemoryPool(const MemoryPool<U>& memoryPool) noexcept 
      : MemoryPool()
   {
   }

   ~MemoryPool() noexcept
   {
      slot_pointer_ curr = currentBlock_;

      while (curr != nullptr) 
      {
         slot_pointer_ prev = curr->next;
         operator delete(reinterpret_cast<void*>(curr));
         curr = prev;
      }
   }

   MemoryPool& operator=(const MemoryPool& memoryPool) = delete;

   MemoryPool<T, BlockSize>& operator=(MemoryPool&& memoryPool) noexcept
   {
      if (this != &memoryPool)
      {
         std::swap(currentBlock_, memoryPool.currentBlock_);
         currentSlot_ = memoryPool.currentSlot_;
         lastSlot_ = memoryPool.lastSlot_;
         freeSlots_ = memoryPool.freeSlots;
      }

      return *this;
   }

   inline pointer address(reference x) const noexcept
   {
      return &x;
   }

   inline const_pointer address(const_reference x) const noexcept
   {
      return &x;
   }

   // Can only allocate one object at a time. n and hint are ignored
   inline pointer allocate(size_type n = 1, const_pointer hint = 0)
   {
      if (freeSlots_ != nullptr) 
      {
         pointer result = reinterpret_cast<pointer>(freeSlots_);
         freeSlots_ = freeSlots_->next;
         return result;
      }
      else 
      {
         if (currentSlot_ >= lastSlot_)
         {
            allocateBlock();
         }

         return reinterpret_cast<pointer>(currentSlot_++);
      }
   }

   inline void deallocate(pointer p, size_type n = 1)
   {
      if (p != nullptr) 
      {
         reinterpret_cast<slot_pointer_>(p)->next = freeSlots_;
         freeSlots_ = reinterpret_cast<slot_pointer_>(p);
      }
   }

   inline size_type max_size() const noexcept
   {
      size_type maxBlocks = -1 / BlockSize;
      return (BlockSize - sizeof(data_pointer_)) / sizeof(slot_type_) * maxBlocks;
   }


   template <class U, class... Args>
   inline void construct(U* p, Args&&... args)
   {
      new (p) U(std::forward<Args>(args)...);
   }

   template <class U>
   inline void destroy(U* p)
   {
      p->~U();
   }

   template <class... Args>
   inline pointer newElement(Args&&... args)
   {
      pointer result = allocate();
      construct<value_type>(result, std::forward<Args>(args)...);
      return result;
   }

   inline void deleteElement(pointer p)
   {
      if (p != nullptr) {
         p->~value_type();
         deallocate(p);
      }
   }

private:
   union Slot_ {
      value_type element;
      Slot_* next;

      Slot_() {}
      ~Slot_() {}
   };

   typedef char* data_pointer_;
   typedef Slot_ slot_type_;
   typedef Slot_* slot_pointer_;

   slot_pointer_ currentBlock_;
   slot_pointer_ currentSlot_;
   slot_pointer_ lastSlot_;
   slot_pointer_ freeSlots_;

   inline size_type padPointer(data_pointer_ p, size_type align) const noexcept
   {
      uintptr_t result = reinterpret_cast<uintptr_t>(p);
      return ((align - result) % align);
   }

   void allocateBlock()
   {
      // Allocate space for the new block and store a pointer to the previous one
      data_pointer_ newBlock = reinterpret_cast<data_pointer_>
         (operator new(BlockSize));
      reinterpret_cast<slot_pointer_>(newBlock)->next = currentBlock_;
      currentBlock_ = reinterpret_cast<slot_pointer_>(newBlock);
      // Pad block body to staisfy the alignment requirements for elements
      data_pointer_ body = newBlock + sizeof(slot_pointer_);
      size_type bodyPadding = padPointer(body, alignof(slot_type_));
      currentSlot_ = reinterpret_cast<slot_pointer_>(body + bodyPadding);
      lastSlot_ = reinterpret_cast<slot_pointer_>
         (newBlock + BlockSize - sizeof(slot_type_) + 1);
   }

   static_assert(BlockSize >= 2 * sizeof(slot_type_), "BlockSize too small.");
};
}
}
}
