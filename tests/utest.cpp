#include <gtest/gtest.h>
#include "pekalib.hpp"

struct TestVertex {
    std::vector<TestVertex*>& children() { //used by library
        return children_;
    }

    TestVertex() {}
    TestVertex(int d) : data(d) {}

    int data;

    std::vector<TestVertex*> children_;
};

TEST(Search, depthFirstSearch) {
    using ActualVertex = typename pecalib::CreateVertexType<TestVertex, pecalib::Search::depthFirstSearchOp, pecalib::GraphType::adjacency_list>::ActualVertexT;
    int magic[] = {213, 2421, 535, 117};
    ActualVertex head;
    ActualVertex child0;
    ActualVertex child00;
    ActualVertex child1;

    head.children().push_back(&child0);
    head.children().push_back(&child1);
    child0.children().push_back(&child00);

    int i = 0;
    pecalib::Search::depthFirstSearch(&head, [&](ActualVertex* v) {
        v->data = magic[i++];
    });

    ASSERT_EQ(head.data, magic[0]);
    ASSERT_EQ(child0.data, magic[1]);
    ASSERT_EQ(child00.data, magic[2]);
    ASSERT_EQ(child1.data, magic[3]);
}
