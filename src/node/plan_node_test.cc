
#include "node_memory.h"
#include "plan_node.h"
#include "gtest/gtest.h"

namespace fesql {
namespace node {

// TODO: add ut: 检查SQL的语法树节点预期 2019.10.23
class PlanNodeTest : public ::testing::Test {

public:
    PlanNodeTest() {
        manager_ = new NodeManager();
    }

    ~PlanNodeTest() {
        delete manager_;
    }
protected:
    NodeManager *manager_;
};


TEST_F(PlanNodeTest, LeafPlanNodeTest) {

    PlanNode *node_ptr = manager_->MakeLeafPlanNode(kUnknowPlan);
    ASSERT_EQ(0, node_ptr->GetChildrenSize());
    ASSERT_EQ(false, node_ptr->AddChild(node_ptr));
    ASSERT_EQ(0, node_ptr->GetChildrenSize());
}


TEST_F(PlanNodeTest, UnaryPlanNodeTest) {
    PlanNode *node_ptr = manager_->MakeLeafPlanNode(kUnknowPlan);

    PlanNode *unary_node_ptr = manager_->MakeUnaryPlanNode(kUnknowPlan);
    ASSERT_EQ(true, unary_node_ptr->AddChild(node_ptr));
    ASSERT_EQ(1, unary_node_ptr->GetChildrenSize());

    ASSERT_EQ(false, unary_node_ptr->AddChild(node_ptr));
    ASSERT_EQ(1, unary_node_ptr->GetChildrenSize());

}

TEST_F(PlanNodeTest, BinaryPlanNodeTest) {
    PlanNode *node_ptr = manager_->MakeLeafPlanNode(kUnknowPlan);
    ASSERT_EQ(0, node_ptr->GetChildrenSize());

    PlanNode *binary_node_ptr = manager_->MakeBinaryPlanNode(kUnknowPlan);
    ASSERT_EQ(true, binary_node_ptr->AddChild(node_ptr));
    ASSERT_EQ(1, binary_node_ptr->GetChildrenSize());

    ASSERT_EQ(true, binary_node_ptr->AddChild(node_ptr));
    ASSERT_EQ(2, binary_node_ptr->GetChildrenSize());


    ASSERT_EQ(false, binary_node_ptr->AddChild(node_ptr));
    ASSERT_EQ(2, binary_node_ptr->GetChildrenSize());

}

TEST_F(PlanNodeTest, MultiPlanNodeTest) {
    PlanNode *node_ptr = manager_->MakeLeafPlanNode(kUnknowPlan);
    ASSERT_EQ(0, node_ptr->GetChildrenSize());

    PlanNode *multi_node_ptr = manager_->MakeMultiPlanNode(kUnknowPlan);
    ASSERT_EQ(true, multi_node_ptr->AddChild(node_ptr));
    ASSERT_EQ(1, multi_node_ptr->GetChildrenSize());

    ASSERT_EQ(true, multi_node_ptr->AddChild(node_ptr));
    ASSERT_EQ(2, multi_node_ptr->GetChildrenSize());

    ASSERT_EQ(true, multi_node_ptr->AddChild(node_ptr));
    ASSERT_EQ(3, multi_node_ptr->GetChildrenSize());

}

}
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}