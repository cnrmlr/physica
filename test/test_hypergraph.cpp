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

TEST_F(HypergraphTest, MakeNodeWith_lvalue)
{
   Obj obj(OBJ_VALUE);
   auto node = phys::make_node<Obj>(obj);
   EXPECT_EQ(node.data().get_value(), obj.get_value());
}

TEST_F(HypergraphTest, MakeNodeWith_rvalue)
{
   auto node = phys::make_node<Obj>(Obj(OBJ_VALUE));
   EXPECT_EQ(node.data().get_value(), OBJ_VALUE);
}

TEST_F(HypergraphTest, MakeHyperedgeWith_lvalue)
{
   auto nodes = std::vector<phys::node<Obj>>(EDGE_SIZE);
   auto edge  = phys::make_hyperedge<Obj>(nodes);
   EXPECT_EQ(edge.nodes().size(), nodes.size());

   for (size_t i = 0; i < EDGE_SIZE; ++i)
   {
      EXPECT_EQ(edge.nodes().at(i), nodes.at(i));
   }
}

TEST_F(HypergraphTest, MakeHyperedgeWith_rvalue)
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

TEST_F(HypergraphTest, MakeHypergraphWith_rvalue)
{
   auto edge_0 = phys::make_hyperedge<Obj>({phys::node<Obj>(), phys::node<Obj>()});
   auto edge_1 = phys::make_hyperedge<Obj>({phys::node<Obj>(), phys::node<Obj>()});
   auto graph  = phys::make_hypergraph<Obj>({edge_0, edge_1});
   EXPECT_EQ(graph.edges().at(0), edge_0);
   EXPECT_EQ(graph.edges().at(1), edge_1);
}

TEST_F(HypergraphTest, MakeHypergraphWith_lvalue)
{
   auto edge_0 = phys::make_hyperedge<Obj>({phys::node<Obj>(), phys::node<Obj>()});
   auto edge_1 = phys::make_hyperedge<Obj>({phys::node<Obj>(), phys::node<Obj>()});
   std::vector<phys::hyperedge<Obj>> edges = {edge_0, edge_1};
   auto graph                              = phys::make_hypergraph<Obj>(edges);
   EXPECT_EQ(graph.edges().at(0), edge_0);
   EXPECT_EQ(graph.edges().at(1), edge_1);
}
} // namespace physica::test