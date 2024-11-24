#pragma once

#include <algorithm>
#include <memory>
#include <physica/identifiable_base.h>
#include <physica/internal/common_utility.h>
#include <unordered_set>
#include <utility>
#include <vector>

namespace phys
{
template <class T>
class node;

template <class T>
class hyperedge;

template <class T>
class hypergraph;

template <class T>
using node_set = std::unordered_set<node<T>, internal::uuid_hash, internal::uuid_equal>;

template <class T>
using edge_set = std::unordered_set<hyperedge<T>, internal::uuid_hash, internal::uuid_equal>;

template <class T>
class node : public identifiable_base
{
   friend class hyperedge<T>;
   friend class hypergraph<T>;

 public:
   node() : object_(), identifiable_base() {}

   template <class... Args, typename = std::enable_if_t<std::is_constructible_v<T, Args&&...>>>
   node(Args&&... args) : object_(std::forward<Args>(args)...), identifiable_base()
   {
   }
   node(const T& obj) : object_(obj), identifiable_base() {}
   node(T&& obj) : object_(std::move(obj)), identifiable_base() {}

   T& data() { return object_; }
   const T& data() const { return object_; }

   bool operator==(const node& rhs) const { return identifiable_base::operator==(rhs); }
   bool operator!=(const node& rhs) const { return !(*this == rhs); }

 private:
   T object_;
};

template <class T, class... Args,
          typename = std::enable_if_t<std::is_constructible_v<T, Args&&...>>>
node<T> make_node(Args&&... args)
{
   return node<T>(std::forward<Args>(args)...);
}

template <class T>
node<T> make_node(const T& obj)
{
   return node<T>(obj);
}

template <class T>
node<T> make_node(T&& obj)
{
   return node<T>(std::move(obj));
}

template <class T>
node_set<T> make_node_set(std::initializer_list<node<T>> init_list)
{
   return node_set<T>(init_list);
}

template <class T>
class hyperedge : public identifiable_base
{
   friend class hypergraph<T>;

 public:
   explicit hyperedge(const std::vector<node<T>>& nodes) : nodes_(nodes), identifiable_base() {}
   explicit hyperedge(std::vector<node<T>>&& nodes) : nodes_(std::move(nodes)), identifiable_base()
   {
   }

   hyperedge()                 = default;
   virtual ~hyperedge()        = default;
   hyperedge(const hyperedge&) = default;
   hyperedge& operator=(const hyperedge&) = default;
   hyperedge(hyperedge&&)                 = default;
   hyperedge& operator=(hyperedge&&) = default;

   std::vector<node<T>>& nodes() { return nodes_; }
   const std::vector<node<T>>& nodes() const { return nodes_; }

   typename std::vector<node<T>>::iterator add_node(const node<T>& node)
   {
      return nodes_.push_back(node);
   }

   typename std::vector<node<T>>::reference add_node(node<T>&& node)
   {
      return nodes_.emplace_back(std::move(node));
   }

   template <class... Args, typename = std::enable_if_t<std::is_constructible_v<T, Args&&...>>>
   typename std::vector<node<T>>::reference add_node(Args&&... args)
   {
      return nodes_.emplace_back(std::forward<Args>(args)...);
   }

   typename std::vector<node<T>>::iterator
   insert_node(const typename std::vector<node<T>>::iterator& position, const node<T>& node)
   {
      return nodes_.insert(position, node);
   }

   typename std::vector<node<T>>::iterator
   insert_node(const typename std::vector<node<T>>::iterator& position, node<T>&& node)
   {
      return nodes_.emplace(position, node);
   }

   template <class... Args, typename = std::enable_if_t<std::is_constructible_v<T, Args&&...>>>
   typename std::vector<node<T>>::iterator
   insert_node(const typename std::vector<node<T>>::iterator& position, Args&&... args)
   {
      return nodes_.emplace(position, std::forward<Args>(args)...);
   }

   bool operator==(const hyperedge& rhs) const { return identifiable_base::operator==(rhs); }
   bool operator!=(const hyperedge& rhs) const { return !(*this == rhs); }

 private:
   std::vector<node<T>> nodes_;
};

template <class T>
hyperedge<T> make_hyperedge()
{
   return hyperedge<T>();
}

template <class T>
hyperedge<T> make_hyperedge(const std::vector<node<T>>& nodes)
{
   return hyperedge<T>(nodes);
}

template <class T>
hyperedge<T> make_hyperedge(std::vector<node<T>>&& nodes)
{
   return hyperedge<T>(std::move(nodes));
}

template <class T>
edge_set<T> make_edge_set(std::initializer_list<hyperedge<T>> init_list)
{
   return edge_set<T>(init_list);
}

template <class T>
class hypergraph : identifiable_base
{
 public:
   hypergraph(const node_set<T>& nodes, const edge_set<T>& edges)
      : nodes_(nodes), edges_(edges), identifiable_base()
   {
   }

   hypergraph(node_set<T>&& nodes, edge_set<T>&& edges)
      : nodes_(nodes), edges_(std::move(edges)), identifiable_base()
   {
   }

   node_set<T>& nodes() { return nodes_; }
   const node_set<T>& nodes() const { return nodes_; }

   edge_set<T>& edges() { return edges_; }
   const edge_set<T>& edges() const { return edges_; }

 private:
   node_set<T> nodes_;
   edge_set<T> edges_;
};

template <class T>
hypergraph<T> make_hypergraph()
{
   return hypergraph<T>();
}

template <class T>
hypergraph<T> make_hypergraph(const node_set<T>& nodes, const edge_set<T>& edges)
{
   return hypergraph<T>(nodes, edges);
}

template <class T>
hypergraph<T> make_hypergraph(node_set<T>&& nodes, edge_set<T>&& edges)
{
   return hypergraph<T>(std::move(nodes), std::move(edges));
}

} // namespace phys