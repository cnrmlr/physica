#include <gtest/gtest.h>
#include <physica/hypergraph.h>

class Entity
{
 public:
   Entity() = default;
   Entity(size_t val) : val(val) {}
   size_t getVal() { return val; }

 private:
   size_t val;
};

namespace physica::test
{
class HypergraphTest : public ::testing::Test
{
 public:
   HypergraphTest() : hypergraph_(nullptr) {}

   ~HypergraphTest() {}

 protected:
   std::unique_ptr<phys::hypergraph<Entity>> hypergraph_;

   void SetUp() override { hypergraph_ = std::make_unique<phys::hypergraph<Entity>>(); }

   void TearDown() override { hypergraph_.reset(); }
};

TEST_F(HypergraphTest, AddNode)
{
   std::weak_ptr<phys::node<Entity>> node = hypergraph_->add_node();

   ASSERT_TRUE(node.lock());
   ASSERT_EQ(hypergraph_->get_nodes().size(), 1);
   ASSERT_EQ(hypergraph_->get_nodes().at(0).lock(), node.lock());
}

TEST_F(HypergraphTest, RemoveNode)
{
   std::weak_ptr<phys::node<Entity>> node = hypergraph_->add_node();
   hypergraph_->remove_node(node);

   ASSERT_TRUE(node.expired());
   ASSERT_TRUE(hypergraph_->get_nodes().empty());
}

TEST_F(HypergraphTest, AddNodes)
{
   std::vector<std::weak_ptr<phys::node<Entity>>> nodes = hypergraph_->add_nodes(3);

   ASSERT_EQ(nodes.size(), 3);
   ASSERT_EQ(hypergraph_->get_nodes().size(), 3);

   for (size_t i = 0; i < nodes.size() && i < hypergraph_->get_nodes().size(); ++i)
   {
      ASSERT_TRUE(nodes.at(i).lock());
      ASSERT_EQ(nodes.at(i).lock(), hypergraph_->get_nodes().at(i).lock());
   }
}

TEST_F(HypergraphTest, RemoveNodes)
{
   std::vector<std::weak_ptr<phys::node<Entity>>> nodes = hypergraph_->add_nodes(3);
   hypergraph_->remove_nodes(nodes);

   ASSERT_TRUE(hypergraph_->get_nodes().empty());

   for (auto &node : nodes)
   {
      ASSERT_TRUE(node.expired());
   }
}

TEST_F(HypergraphTest, AddEdge)
{
   std::vector<std::weak_ptr<phys::node<Entity>>> nodes = hypergraph_->add_nodes(3);
   std::weak_ptr<phys::hyperedge<Entity>> edge          = hypergraph_->add_edge(nodes);

   ASSERT_TRUE(edge.lock());
   ASSERT_EQ(hypergraph_->get_edges().size(), 1);
   ASSERT_EQ(hypergraph_->get_edges().at(0).lock(), edge.lock());

   for (size_t i = 0; i < nodes.size() && i < edge.lock()->get_nodes().size(); ++i)
   {
      ASSERT_EQ(nodes.at(i).lock(), edge.lock()->get_nodes().at(i).lock());
   }
}

TEST_F(HypergraphTest, RemoveEdge)
{
   std::vector<std::weak_ptr<phys::node<Entity>>> nodes = hypergraph_->add_nodes(3);
   std::weak_ptr<phys::hyperedge<Entity>> edge          = hypergraph_->add_edge(nodes);
   hypergraph_->remove_edge(edge);

   ASSERT_TRUE(edge.expired());
   ASSERT_TRUE(hypergraph_->get_edges().empty());
}

TEST_F(HypergraphTest, RemoveEdges)
{
   std::vector<std::weak_ptr<phys::node<Entity>>> nodeSet_1 = hypergraph_->add_nodes(3);
   std::vector<std::weak_ptr<phys::node<Entity>>> nodeSet_2 = hypergraph_->add_nodes(3);

   std::weak_ptr<phys::hyperedge<Entity>> edge_1 = hypergraph_->add_edge(nodeSet_1);
   std::weak_ptr<phys::hyperedge<Entity>> edge_2 = hypergraph_->add_edge(nodeSet_2);

   hypergraph_->remove_edges({edge_1, edge_2});

   ASSERT_TRUE(edge_1.expired());
   ASSERT_TRUE(edge_2.expired());
   ASSERT_TRUE(hypergraph_->get_edges().empty());
}

TEST_F(HypergraphTest, AddSelfLoop)
{
   std::weak_ptr<phys::node<Entity>> node      = hypergraph_->add_node();
   std::weak_ptr<phys::hyperedge<Entity>> edge = hypergraph_->add_edge({node, node});

   ASSERT_EQ(edge.lock()->get_nodes().size(), 2);
   ASSERT_EQ(node.lock()->get_incident_edges().size(), 1);
   ASSERT_EQ(node.lock()->get_incident_edges().at(0).lock(), edge.lock());
}
} // namespace physica::test