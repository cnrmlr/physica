#include <gtest/gtest.h>
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
   hypergraph_->addVertex();
   ASSERT_EQ(hypergraph_->getVertices().size(), 1);
}
}
}