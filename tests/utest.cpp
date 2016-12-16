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
    using ActualVertex = typename pekalib::CreateVertexType<TestVertex, pekalib::Search::depthFirstSearchOp, pekalib::GraphType::adjacency_list>::ActualVertexT;
    int magic[] = {213, 2421, 535, 117};
    ActualVertex head;
    ActualVertex child0;
    ActualVertex child00;
    ActualVertex child1;

    head.children() = { &child0, &child1 };
    child0.children() = { &child00 };
    child00.children() = { &head };

    int i = 0;
    pekalib::Search::depthFirstSearch(&head, [&](ActualVertex* v) {
        v->data = magic[i++];
    });

    ASSERT_EQ(head.data, magic[0]);
    ASSERT_EQ(child0.data, magic[1]);
    ASSERT_EQ(child00.data, magic[2]);
    ASSERT_EQ(child1.data, magic[3]);
}

TEST(Search, breadthFirstSearch) {
    using ActualVertex = typename pekalib::CreateVertexType<TestVertex, pekalib::Search::depthFirstSearchOp, pekalib::GraphType::adjacency_list>::ActualVertexT;
    int magic[] = {213, 2421, 535, 117};
    ActualVertex head;
    ActualVertex child0;
    ActualVertex child00;
    ActualVertex child1;

    head.children() = { &child0, &child1 };
    child0.children() = { &child00 };
    child00.children() = { &head };

    int i = 0;
    pekalib::Search::breadthFirstSearch(&head, [&](ActualVertex* v) {
        v->data = magic[i++];
    });

    ASSERT_EQ(head.data, magic[0]);
    ASSERT_EQ(child0.data, magic[1]);
    ASSERT_EQ(child1.data, magic[2]);
    ASSERT_EQ(child00.data, magic[3]);
}

