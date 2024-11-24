#pragma once

#include <physica/identifiable_base.h>
#include <algorithm>
#include <memory>
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
class node : public identifiable_base
{
   friend class hyperedge<T>;
   friend class hypergraph<T>;

 public:
   node() : object_(), identifiable_base() {}

   template <class... Args, typename = std::enable_if_t<std::is_constructible_v<T, Args&&...>>>
   node(Args &&... args) : object_(std::forward<Args>(args)...), identifiable_base() {}
   node(const T &obj) : object_(obj), identifiable_base() {}
   node(T &&obj) : object_(std::move(obj)), identifiable_base() {}

   T &data() { return object_; }
   const T &data() const { return object_; }

   bool operator==(const node &rhs) const { return identifiable_base::operator==(rhs); }
   bool operator!=(const node &rhs) const { return !(*this == rhs); }

 private:
   T object_;
};

template <class T, class... Args>
node<T> make_node(Args &&... args)
{
   return node<T>(std::forward<Args>(args)...);
}

template <class T>
node<T> make_node(const T &obj)
{
   return node<T>(obj);
}

template <class T>
node<T> make_node(T &&obj)
{
   return node<T>(std::move(obj));
}

template <class T>
class hyperedge : public identifiable_base
{
   friend class hypergraph<T>;

 public:
   explicit hyperedge(const std::vector<node<T>> &nodes) : nodes_(nodes), identifiable_base() {}
   explicit hyperedge(std::vector<node<T>> &&nodes) : nodes_(std::move(nodes)), identifiable_base() {}

   std::vector<node<T>> &nodes() { return nodes_; }
   const std::vector<node<T>> &nodes() const { return nodes_; }

   bool operator==(const hyperedge &rhs) const { return identifiable_base::operator==(rhs); }
   bool operator!=(const hyperedge &rhs) const { return !(*this == rhs); }

 private:
   std::vector<node<T>> nodes_;
};

template <class T>
hyperedge<T> make_hyperedge(const std::vector<node<T>> &nodes)
{
   return hyperedge<T>(nodes);
}

template <class T>
hyperedge<T> make_hyperedge(std::vector<node<T>> &&nodes)
{
   return hyperedge<T>(std::move(nodes));
}

template <class T>
class hypergraph : identifiable_base
{
 public:
   explicit hypergraph(const std::vector<hyperedge<T>> &edges) : edges_(edges), identifiable_base() {}
   explicit hypergraph(std::vector<hyperedge<T>> &&edges) : edges_(std::move(edges)), identifiable_base() {}

   std::vector<hyperedge<T>> &edges() { return edges_; }
   const std::vector<hyperedge<T>> &edges() const { return edges_; }

 private:
   std::vector<hyperedge<T>> edges_;
};

template <class T>
hypergraph<T> make_hypergraph(const std::vector<hyperedge<T>> &edges)
{
   return hypergraph<T>(edges);
}

template <class T>
hypergraph<T> make_hypergraph(std::vector<hyperedge<T>> &&edges)
{
   return hypergraph<T>(std::move(edges));
}

} // namespace phys