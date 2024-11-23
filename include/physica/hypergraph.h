#pragma once

#include <physica/internal/identifiable_base.h>
#include <physica/internal/common_utility.h>

#include <memory>
#include <vector>
#include <utility>

namespace phys
{
   template <class T>
   class hyperedge;

   template <class T>
   class hypergraph;

   template <class T>
   class node : public internal::identifiable_base
   {
      friend class hyperedge<T>;
      friend class hypergraph<T>;

   public:
      template <class... Args>
      node(Args &&...args)
          : object_(std::forward<Args>(args)...), identifiable_base()
      {
      }

      ~node() = default;
      node(const node &rhs) = delete;
      node& operator=(const node &rhs) = delete;

      T &data()
      {
         return object_;
      }

      const T &data() const
      {
         return object_;
      }

      const std::vector<std::weak_ptr<hyperedge<T>>> get_incident_edges()
      {
         return internal::make_weak_ptr_vector(incidentEdges_);
      }

      bool is_adjacent_to(const std::weak_ptr<node> &node)
      {
         for (const auto &edge : incidentEdges_)
         {
            if (edge->isIncidentTo(node))
            {
               return true;
            }
         }

         return false;
      }

      bool is_incident_to(const std::weak_ptr<hyperedge<T>> &edge)
      {
         return internal::find_with_weak_ptr(incidentEdges_, edge) != incidentEdges_.end();
      }

      bool operator==(const node &rhs) const
      {
         return internal::identifiable_base::operator==(rhs);

      }

      bool operator!=(const node &rhs) const
      {
         return internal::identifiable_base::operator==(rhs);

      }

   protected:
      void add_incident_edge(const std::weak_ptr<hyperedge<T>> &incidentEdge)
      {
         if (!isIncidentTo(incidentEdge))
         {
            incidentEdges_.emplace_back(incidentEdge);
         }
      }

      void remove_incident_edge(const std::weak_ptr<hyperedge<T>> &incidentEdge)
      {
         auto edgeIter = internal::find_with_weak_ptr(incidentEdges_, incidentEdge);

         if (edgeIter != incidentEdges_.end())
         {
            incidentEdges_.erase(edgeIter);
         }
      }

   private:
      T object_;
      std::vector<std::shared_ptr<hyperedge<T>>> incidentEdges_;
   };

   template <class T>
   class hyperedge : internal::identifiable_base, std::enable_shared_from_this<hyperedge<T>>
   {
      friend class hypergraph<T>;

   public:
      hyperedge() = delete;
      ~hyperedge() = default;
      hyperedge(const hyperedge &rhs) = delete;
      hyperedge operator=(const hyperedge &rhs) = delete;

      hyperedge(const std::vector<std::shared_ptr<node<T>>> &nodes)
         : internal::identifiable_base()
      {
         nodes_.reserve(nodes.size());

         for (auto &node : nodes)
         {
            nodes_.push_back(node);
         }
      }

      const std::vector<std::weak_ptr<node<T>>> get_nodes() const
      {
         return internal::make_weak_ptr_vector(nodes_);
      }

      bool is_adjacent_to(const std::weak_ptr<hyperedge<T>> &edge)
      {
         for (auto &node : nodes_)
         {
            if (edge.lock() && edge.lock()->is_incident_to(node))
            {
               return true;
            }
         }

         return false;
      }

      bool is_incident_to(const std::weak_ptr<node<T>> &node)
      {
         return findnode(node) != nodes_.end();
      }

      bool operator==(const hyperedge &rhs) const
      {
         return internal::identifiable_base::operator==(rhs);
      }

      bool operator!=(const hyperedge &rhs) const
      {
         return internal::identifiable_base::operator!=(rhs);
      }

   protected:
      const std::vector<std::shared_ptr<node<T>>>::iterator find_node(std::weak_ptr<node<T>> node)
      {
         return internal::find_with_weak_ptr(nodes_, node);
      }

      void remove_node(std::weak_ptr<node<T>> node)
      {
         auto nodeIter = find_node(node);

         if (nodeIter != nodes_.end())
         {
            nodes_.erase(find_node(node));
         }
      }

      void remove_from_node_incidence_lists()
      {
         for (auto &node : nodes_)
         {
            node->remove_incident_edge(std::enable_shared_from_this<hyperedge<T>>::shared_from_this());
         }
      }

   private:
      std::vector<std::shared_ptr<node<T>>> nodes_;
   };

   template <class T>
   class hypergraph
   {
   public:
      hypergraph() = default;
      ~hypergraph() = default;
      hypergraph(const hypergraph &) = delete;
      hypergraph operator=(const hypergraph) = delete;

      template <class... Args>
      const std::weak_ptr<node<T>> add_node(Args &&...args)
      {
         std::shared_ptr<node<T>> sp_Node = std::make_shared<node<T>>(std::forward<Args>(args)...);
         return nodes_.emplace_back(sp_Node);
      }

      void remove_node(const std::weak_ptr<node<T>> &node)
      {
         // remove the node from the edges it exists on
         for (auto &edge : edges_)
         {
            edge->remove_node(node);
         }

         // remove the node from the graph
         auto nodeIter = internal::find_with_weak_ptr(nodes_, node);

         if (nodeIter != nodes_.end())
         {
            nodes_.erase(nodeIter);
         }
      }

      template <class... Args>
      const std::vector<std::weak_ptr<node<T>>> add_nodes(size_t count, Args &&...args)
      {
         std::vector<std::weak_ptr<node<T>>> newNodes;
         newNodes.reserve(count);

         for (size_t i = 0; i < count; ++i)
         {
            newNodes.emplace_back(add_node(std::forward<Args>(args)...));
         }

         return newNodes;
      }

      void remove_nodes(const std::vector<std::weak_ptr<node<T>>> &nodes)
      {
         for (auto &node : nodes)
         {
            remove_node(node);
         }
      }

      const std::weak_ptr<hyperedge<T>> add_edge(std::vector<std::weak_ptr<node<T>>> nodes)
      {
         std::vector<std::shared_ptr<node<T>>> sharedNodes = internal::make_shared_ptr_vector(nodes);

         // return nullptr if there was an issue doing the conversion
         if (sharedNodes.empty())
         {
            return std::shared_ptr<hyperedge<T>>(nullptr);
         }

         // add the edge to the graph and give the incident vertices a ref to the new edge
         std::shared_ptr<hyperedge<T>> edge = std::make_shared<hyperedge<T>>(sharedNodes);

         edges_.push_back(edge);

         for (auto &node : sharedNodes)
         {
            node->add_incident_edge(edge);
         }

         return edge;
      }

      void remove_edge(const std::weak_ptr<hyperedge<T>> &edge)
      {
         auto edgeIter = internal::find_with_weak_ptr(edges_, edge);

         if (edgeIter != edges_.end())
         {
            edgeIter->get()->remove_from_node_incidence_lists();
            edges_.erase(edgeIter);
         }
      }

      const std::vector<std::weak_ptr<hyperedge<T>>> add_edges(std::vector<std::vector<std::weak_ptr<node<T>>>> nodeSets)
      {
         std::vector<std::weak_ptr<hyperedge<T>>> newEdges;
         newEdges.reserve(nodeSets.size());

         for (auto &set : nodeSets)
         {
            newEdges.emplace_back(add_edge(set));
         }

         return newEdges;
      }

      void remove_edges(const std::vector<std::weak_ptr<hyperedge<T>>> &edges)
      {
         for (auto &edge : edges)
         {
            remove_edge(edge);
         }
      }

      const std::vector<std::weak_ptr<node<T>>> get_nodes() const
      {
         return internal::make_weak_ptr_vector(nodes_);
      }

      const std::vector<std::weak_ptr<hyperedge<T>>> get_edges() const
      {
         return internal::make_weak_ptr_vector(edges_);
      }

      std::vector<std::vector<unsigned short>> get_adajency_matrix() const
      {
         std::vector<std::vector<unsigned short>> adjacencyMatrix;
         adjacencyMatrix.reserve(nodes_.size());

         for (auto &node_i : nodes_)
         {
            std::vector<unsigned short> adjacencyList;
            adjacencyList.reserve(nodes_.size());

            for (auto &node_j : nodes_)
            {
               adjacencyList.push_back(static_cast<unsigned short>(node_i->is_adjacent_to(node_j)));
            }

            adjacencyMatrix.push_back(adjacencyList);
         }

         return adjacencyMatrix;
      }

   private:
      std::vector<std::shared_ptr<node<T>>> nodes_;
      std::vector<std::shared_ptr<hyperedge<T>>> edges_;
   };
}
