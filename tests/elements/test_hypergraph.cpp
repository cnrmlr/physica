#include <gtest/gtest.h>
#include "hyperedge.h"
#include "hypergraph.h"

namespace graphica
{
namespace test
{
class HypergraphTest : public ::testing::Test
{
public:
   HypergraphTest() 
      : hypergraph_(nullptr) 
   {
   }

   ~HypergraphTest() 
   {
   }

protected:
   std::unique_ptr<core::elements::Hypergraph> hypergraph_;

   void SetUp() override
   {
      hypergraph_ = std::make_unique<core::elements::Hypergraph>();
   }

   void TearDown() override
   {
      hypergraph_.reset();
   }
};

TEST_F(HypergraphTest, AddVertex)
{
   std::weak_ptr<core::elements::Vertex> vertex = hypergraph_->addVertex();

   ASSERT_TRUE(vertex.lock());
   ASSERT_EQ(hypergraph_->getVertices().size(), 1);
   ASSERT_EQ(hypergraph_->getVertices().at(0).lock(), vertex.lock());
}

TEST_F(HypergraphTest, RemoveVertex)
{
   std::weak_ptr<core::elements::Vertex> vertex = hypergraph_->addVertex();
   hypergraph_->removeVertex(vertex);

   ASSERT_TRUE(vertex.expired());
   ASSERT_TRUE(hypergraph_->getVertices().empty());
}

TEST_F(HypergraphTest, AddVertices)
{
   std::vector<std::weak_ptr<core::elements::Vertex>> vertices = hypergraph_->addVertices(3);

   ASSERT_EQ(vertices.size(), 3);
   ASSERT_EQ(hypergraph_->getVertices().size(), 3);

   for (size_t i = 0; i < vertices.size() && i < hypergraph_->getVertices().size(); ++i)
   {
      ASSERT_TRUE(vertices.at(i).lock());
      ASSERT_EQ(vertices.at(i).lock(), hypergraph_->getVertices().at(i).lock());
   }
}

TEST_F(HypergraphTest, RemoveVertices)
{
   std::vector<std::weak_ptr<core::elements::Vertex>> vertices = hypergraph_->addVertices(3);
   hypergraph_->removeVertices(vertices);

   ASSERT_TRUE(hypergraph_->getVertices().empty());

   for (auto& vertex : vertices)
   {
      ASSERT_TRUE(vertex.expired());
   }
}

TEST_F(HypergraphTest, AddEdge)
{
   std::vector<std::weak_ptr<core::elements::Vertex>> vertices = hypergraph_->addVertices(3);
   std::weak_ptr<core::elements::Hyperedge> edge = hypergraph_->addEdge(vertices);

   ASSERT_TRUE(edge.lock());
   ASSERT_EQ(hypergraph_->getEdges().size(), 1);
   ASSERT_EQ(hypergraph_->getEdges().at(0).lock(), edge.lock());

   for (size_t i = 0; i < vertices.size() && i < edge.lock()->getVertices().size(); ++i)
   {
      ASSERT_EQ(vertices.at(i).lock(), edge.lock()->getVertices().at(i).lock());
   }
}

TEST_F(HypergraphTest, RemoveEdge)
{
   std::vector<std::weak_ptr<core::elements::Vertex>> vertices = hypergraph_->addVertices(3);
   std::weak_ptr<core::elements::Hyperedge> edge = hypergraph_->addEdge(vertices);
   hypergraph_->removeEdge(edge);

   ASSERT_TRUE(edge.expired());
   ASSERT_TRUE(hypergraph_->getEdges().empty());
}

TEST_F(HypergraphTest, RemoveEdges)
{
   std::vector<std::weak_ptr<core::elements::Vertex>> vertexSet_1 = hypergraph_->addVertices(3);
   std::vector<std::weak_ptr<core::elements::Vertex>> vertexSet_2 = hypergraph_->addVertices(3);

   std::weak_ptr<core::elements::Hyperedge> edge_1 = hypergraph_->addEdge(vertexSet_1);
   std::weak_ptr<core::elements::Hyperedge> edge_2 = hypergraph_->addEdge(vertexSet_2);

   hypergraph_->removeEdges({ edge_1, edge_2 });

   ASSERT_TRUE(edge_1.expired());
   ASSERT_TRUE(edge_2.expired());
   ASSERT_TRUE(hypergraph_->getEdges().empty());
}
}
}