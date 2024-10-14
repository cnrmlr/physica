#include <physica/library/utility/common_utility.h>
#include <physica/library/structures/hyperedge.h>
#include <physica/library/structures/node.h>
#include <physica/library/functions/pattern_match.h>

#include <functional>
#include <map>
#include <set>

namespace physica::functions
{
   struct CompareOrder;
   using AbstractElementToNodeMap = std::map<size_t, std::shared_ptr<structures::Node>>;
   using AbstractElementSet = std::set<size_t>;
   using NodeSet = std::set<std::shared_ptr<structures::Node>, CompareOrder>;
   using NodeVector = std::vector<std::shared_ptr<structures::Node>>;
   using EdgeVector = std::vector<std::shared_ptr<structures::Hyperedge>>;

   // Custom comparator for ordering nodes based on their position in an input vector.
   //
   // The `CompareOrder` struct provides a way to compare and order nodes (`std::shared_ptr<structures::Node>`)
   // based on their positions in a provided vector (`NodeVector`). This is particularly useful when you need
   // to maintain the original order of nodes from a specific sequence in a set or other ordered container.
   //
   // The struct initializes an `orderMap` that maps each node in the input vector to its index (position)
   // within that vector. The `operator()` function then compares two nodes based on their indices in this map,
   // allowing for custom ordering of nodes according to their original order in the vector.
   struct CompareOrder
   {
      CompareOrder(const NodeVector &edgeNodes)
      {
         for (size_t i = 0; i < edgeNodes.size(); ++i)
         {
            if (orderMap.find(edgeNodes[i]) == orderMap.end())
            {
               orderMap[edgeNodes[i]] = i;
            }
         }
      }

      std::unordered_map<std::shared_ptr<structures::Node>, size_t> orderMap;

      bool operator()(const std::shared_ptr<structures::Node> &lhs, const std::shared_ptr<structures::Node> &rhs) const
      {
         return orderMap.at(lhs) < orderMap.at(rhs);
      }
   };

   // This function creates a set of unique nodes from the provided vector of nodes (`edgeNodes`).
   // The uniqueness of nodes is determined using a custom comparator (`CompareOrder`) that
   // maintains the original order of nodes in the vector.
   static NodeSet GetUniqueNodesInEdge(const NodeVector &edgeNodes)
   {
      CompareOrder comp(edgeNodes);

      NodeSet uniqueNodesInEdge(comp);

      for (const auto &node : edgeNodes)
      {
         uniqueNodesInEdge.insert(node);
      }

      return uniqueNodesInEdge;
   }

   // This function creates a mapping between unique abstract elements in the pattern
   // and unique nodes in the edge. It requires that the number of unique elements
   // in the pattern is equal to the number of unique nodes in the edge.
   static AbstractElementToNodeMap MapUniqueElementsToUniqueNodes(AbstractElementSet uniquePatternElements, NodeSet uniqueEdgeNodes)
   {
      AbstractElementToNodeMap map;

      if (uniquePatternElements.size() != uniqueEdgeNodes.size())
      {
         return map; // at this point in the algorithm the sizes of these containers must match
      }

      // Now that we have verified that the unique sets are of the same size we declare iters at the first elements of each
      auto uniquePatternElementsIter = uniquePatternElements.begin();
      auto uniqueEdgeNodesIter = uniqueEdgeNodes.begin();

      // Local lambda function for determining if we should continue iterating through the two sets
      std::function<bool()> shouldContinueLoop = [&uniquePatternElementsIter, &uniqueEdgeNodesIter, &uniquePatternElements, &uniqueEdgeNodes]()
      {
         return uniquePatternElementsIter != uniquePatternElements.end() && uniqueEdgeNodesIter != uniqueEdgeNodes.end();
      };

      // Local lambda function for incremeanting the iterators for each unique set
      std::function<void()> incremeantIterators = [&uniquePatternElementsIter, &uniqueEdgeNodesIter]()
      {
         ++uniquePatternElementsIter;
         ++uniqueEdgeNodesIter;
      };

      // The actual loop that maps each unique pattern element to a unique node
      for (; shouldContinueLoop(); incremeantIterators())
      {
         map[*uniquePatternElementsIter] = *uniqueEdgeNodesIter;
      }

      return map;
   }

   // This function verifies whether the sequence of nodes in an edge corresponds
   // to the sequence of abstract elements in a pattern. The comparison is based
   // on a mapping between the elements in the pattern and the nodes in the edge.
   static bool EdgeMatchesPattern(const structures::AbstractRelation pattern, const NodeVector &edgeNodes, const AbstractElementToNodeMap &map)
   {
      if (pattern.size() != edgeNodes.size())
      {
         return false; // at this point in the algorithm, the sizes of these containers must match
      }

      for (size_t i = 0; i < pattern.size() && i < edgeNodes.size(); ++i)
      {
         if (map.at(pattern.at(i)) == edgeNodes.at(i))
         {
            continue;
         }
         else
         {
            return false;
         }
      }

      return true;
   }

   // This function attempts to find an edge within a set of edges that matches
   // a specified pattern of nodes.
   static bool PatternMatch(const structures::AbstractRelation &pattern,
                            const std::shared_ptr<structures::Hyperedge> &edge)
   {
      const AbstractElementSet uniqueElementsInPattern(pattern.begin(), pattern.end());

      const NodeVector edgeNodes = utility::MakeSharedPtrVector(edge->getNodes());

      if (edgeNodes.size() != pattern.size())
      {
         return false; // number of nodes in edge must equal number of elements in pattern to be a match, skipping...
      }

      const NodeSet uniqueNodesInEdge = GetUniqueNodesInEdge(edgeNodes);

      if (uniqueElementsInPattern.size() != uniqueNodesInEdge.size())
      {
         return false; // number of unique nodes in edge must equal number of unique elements in pattern to be a match, skipping...
      }

      const AbstractElementToNodeMap map = MapUniqueElementsToUniqueNodes(uniqueElementsInPattern, uniqueNodesInEdge);

      if (EdgeMatchesPattern(pattern, edgeNodes, map))
      {
         return true; // all matching criteria have been met, return this edge
      }

      return false; // none of the edges in the set match the pattern, return nullptr
   }

   static AbstractElementSet GetUniqueElements(const std::vector<structures::AbstractRelation> &elementLists)
   {
      AbstractElementSet uniqueElements;

      for (auto& elementList : elementLists)
      {
         for (auto& element : elementList)
         {
            uniqueElements.insert(element);
         }
      }

      return uniqueElements;
   }

   void SetReplace_v1(structures::Hypergraph &graph, const structures::Rule &rule)
   {
      EdgeVector edges = utility::MakeSharedPtrVector(graph.getEdges());
      size_t numberOfRelationsInPattern = rule.getPattern().size();
      size_t offset = 0;
      size_t numberOfEdgesAtStart = edges.size();
      bool continueLoop = false;

      do
      {
         bool patternMatch = true;
         EdgeVector edgesToRemove;

         for (size_t i = 0; i < numberOfRelationsInPattern; ++i)
         {
            if (i + offset > numberOfEdgesAtStart - 1)
            {
               continueLoop = false;
               break;
            }

            auto& edge = edges.at(i + offset);

            if (!PatternMatch(rule.getPattern().at(i), edge))
            {
               patternMatch = false;
               continueLoop = false;
               break;
            }
            
            edgesToRemove.push_back(edge);
            ++offset;
         }

         if (patternMatch)
         {
            for (auto& edge : edgesToRemove)
            {
               graph.removeEdge(edge);
            }

            AbstractElementSet uniqueElements = GetUniqueElements(rule.getReplace());

            auto nodes = graph.addNodes(uniqueElements.size());

            AbstractElementToNodeMap map = MapUniqueElementsToUniqueNodes(uniqueElements, NodeSet(nodes.begin(), nodes.end()));

            for (auto& relation : rule.getPattern())
            {
               NodeVector edgeNodes;

               for (auto& element : relation)
               {
                  edgeNodes.push_back(map[element]);
               }

               graph.addEdge(utility::MakeWeakPtrVector(edgeNodes));
            }
         }

      } while (continueLoop);
   }
}
