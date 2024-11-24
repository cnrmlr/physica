#include <gtest/gtest.h>
#include <physica/hypergraph.h>

constexpr size_t OBJ_VALUE = 42;
constexpr size_t EDGE_SIZE = 3;

class Obj
{
 public:
   Obj() {}
   Obj(size_t value) : value(value) {}
   size_t get_value() { return value; }

 private:
   size_t value;
};

namespace physica::test
{
class HypergraphTest : public ::testing::Test
{
 public:
   HypergraphTest() {}

   ~HypergraphTest() {}

 protected:
   void SetUp() override {}

   void TearDown() override {}
};

TEST_F(HypergraphTest, MakeNodeWithArgs)
{
   auto node = phys::make_node<Obj>(OBJ_VALUE);
   EXPECT_EQ(node.data().get_value(), OBJ_VALUE);
}

TEST_F(HypergraphTest, MakeNodeWithLValue)
{
   Obj obj(OBJ_VALUE);
   auto node = phys::make_node<Obj>(obj);
   EXPECT_EQ(node.data().get_value(), obj.get_value());
}

TEST_F(HypergraphTest, MakeNodeWithRValue)
{
   auto node = phys::make_node<Obj>(Obj(OBJ_VALUE));
   EXPECT_EQ(node.data().get_value(), OBJ_VALUE);
}

TEST_F(HypergraphTest, MakeHyperedgeWithLValue)
{
   auto nodes = std::vector<phys::node<Obj>>(EDGE_SIZE);
   auto edge  = phys::make_hyperedge<Obj>(nodes);
   EXPECT_EQ(edge.nodes().size(), nodes.size());

   for (size_t i = 0; i < EDGE_SIZE; ++i)
   {
      EXPECT_EQ(edge.nodes().at(i), nodes.at(i));
   }
}

TEST_F(HypergraphTest, MakeHyperedgeWithRValue)
{
   auto node_0 = phys::make_node<Obj>();
   auto node_1 = phys::make_node<Obj>();
   auto node_2 = phys::make_node<Obj>();
   auto edge   = phys::make_hyperedge<Obj>({node_0, node_1, node_2});

   EXPECT_EQ(edge.nodes().size(), EDGE_SIZE);
   EXPECT_EQ(edge.nodes().at(0), node_0);
   EXPECT_EQ(edge.nodes().at(1), node_1);
   EXPECT_EQ(edge.nodes().at(2), node_2);
}

TEST_F(HypergraphTest, MakeHypergraphWithRValue)
{
   auto node_0 = phys::make_node<Obj>();
   auto node_1 = phys::make_node<Obj>();
   auto edge   = phys::make_hyperedge<Obj>({node_0, node_1});
   auto graph  = phys::make_hypergraph<Obj>({node_0, node_1}, {edge});

   EXPECT_TRUE(graph.nodes().find(node_0) != graph.nodes().end());
   EXPECT_TRUE(graph.nodes().find(node_1) != graph.nodes().end());
   EXPECT_TRUE(graph.edges().find(edge) != graph.edges().end());
}

TEST_F(HypergraphTest, MakeHypergraphWithLValue)
{
   auto node_0 = phys::make_node<Obj>();
   auto node_1 = phys::make_node<Obj>();
   auto node_2 = phys::make_node<Obj>();
   auto edge_0 = phys::make_hyperedge<Obj>({node_0, node_1});

   auto nodes = phys::make_node_set<Obj>({node_0, node_1, node_2});
   auto edges = phys::make_edge_set<Obj>({edge_0});

   auto graph = phys::make_hypergraph<Obj>(nodes, edges);

   EXPECT_TRUE(graph.nodes().find(node_0) != graph.nodes().end());
   EXPECT_TRUE(graph.nodes().find(node_1) != graph.nodes().end());
   EXPECT_TRUE(graph.nodes().find(node_2) != graph.nodes().end());
   EXPECT_TRUE(graph.edges().find(edge_0) != graph.edges().end());
}

TEST_F(HypergraphTest, AddNodeToEdgeWithArgs)
{
   auto edge = phys::make_hyperedge<Obj>();
   auto node = edge.add_node(OBJ_VALUE);
   EXPECT_EQ(node.data().get_value(), OBJ_VALUE);
   EXPECT_EQ(edge.nodes().size(), 1);
}

TEST_F(HypergraphTest, AddNodeToEdgeWithLValue)
{
   auto edge = phys::make_hyperedge<Obj>();
   Obj obj(OBJ_VALUE);
   auto node = edge.add_node(obj);
   EXPECT_EQ(node.data().get_value(), OBJ_VALUE);
   EXPECT_EQ(edge.nodes().size(), 1);
}

TEST_F(HypergraphTest, AddNodeToEdgeWithRValue)
{
   auto edge = phys::make_hyperedge<Obj>();
   auto node = edge.add_node(Obj(OBJ_VALUE));
   EXPECT_EQ(node.data().get_value(), OBJ_VALUE);
   EXPECT_EQ(edge.nodes().size(), 1);
}

TEST_F(HypergraphTest, InsertNodeOnEdgeWithArgs)
{
   auto edge = phys::make_hyperedge<Obj>();
   edge.add_node(1);
   auto it = edge.insert_node(edge.nodes().begin(), OBJ_VALUE);
   EXPECT_EQ(it->data().get_value(), OBJ_VALUE);
   EXPECT_EQ(edge.nodes().size(), 2);
   EXPECT_EQ(edge.nodes().front().data().get_value(), OBJ_VALUE);
}

TEST_F(HypergraphTest, InsertNodeOnEdgeWithLValue)
{
   auto edge = phys::make_hyperedge<Obj>();
   edge.add_node(1); // Add a node first
   Obj obj(OBJ_VALUE);
   auto it = edge.insert_node(edge.nodes().begin(), obj);
   EXPECT_EQ(it->data().get_value(), OBJ_VALUE);
   EXPECT_EQ(edge.nodes().size(), 2);
   EXPECT_EQ(edge.nodes().front().data().get_value(), OBJ_VALUE);
}

TEST_F(HypergraphTest, InsertNodeOnEdgeWithRValue)
{
   auto edge = phys::make_hyperedge<Obj>();
   edge.add_node(1); // Add a node first
   auto it = edge.insert_node(edge.nodes().begin(), Obj(OBJ_VALUE));
   EXPECT_EQ(it->data().get_value(), OBJ_VALUE);
   EXPECT_EQ(edge.nodes().size(), 2);
   EXPECT_EQ(edge.nodes().front().data().get_value(), OBJ_VALUE);
}

TEST_F(HypergraphTest, AddMultipleNodesToEdgeWithArgs)
{
   auto edge = phys::make_hyperedge<Obj>();
   edge.add_node(1);
   edge.add_node(2);
   edge.add_node(3);
   EXPECT_EQ(edge.nodes().size(), 3);
   EXPECT_EQ(edge.nodes().at(0).data().get_value(), 1);
   EXPECT_EQ(edge.nodes().at(1).data().get_value(), 2);
   EXPECT_EQ(edge.nodes().at(2).data().get_value(), 3);
}
} // namespace physica::test