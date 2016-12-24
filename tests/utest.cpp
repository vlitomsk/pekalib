#include <gtest/gtest.h>
#include <CreateVertexType.hpp>
#include "pekalib.hpp"

struct TestVertex {

    TestVertex() {}
    explicit TestVertex(int d) : data(d) {}

    int data = 0;

    std::vector<TestVertex*> children;
};

TEST(Search, depthFirstSearch) {
    using ActualVertex = typename pekalib::CreateVertexType<TestVertex, pekalib::Search::depthFirstSearchOp, pekalib::GraphType::adjacency_list>::ActualVertexT;
    int magic[] = {213, 2421, 535, 117};
    ActualVertex head;
    ActualVertex child0;
    ActualVertex child00;
    ActualVertex child1;

    /*ASSERT_EQ(head.vertexSpecificData.wasHereCount, 0);
    ASSERT_EQ(child0.vertexSpecificData.wasHereCount, 0);
    ASSERT_EQ(child00.vertexSpecificData.wasHereCount, 0);
    ASSERT_EQ(child00.vertexSpecificData.wasHereCount, 0);*/

    head.children = {&child0, &child1};
    child0.children = {&child00};
    child00.children = {&head};

    for (int j = 0; j < 1000000; j++) {
    int i = 0;
    pekalib::Search::depthFirstSearch(&head, [](ActualVertex *v) {
        return *(std::vector<ActualVertex*>*)(&v->children);
    }, [&](ActualVertex *v) {
        v->data = magic[i++];
    });
}

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

    head.children = { &child0, &child1 };
    child0.children = { &child00 };
    child00.children = { &head };

    int i = 0;
    pekalib::Search::breadthFirstSearch(&head, [](ActualVertex *v) {
        return *(std::vector<ActualVertex*>*)(&v->children);
    }, [&](ActualVertex *v) {
        v->data = magic[i++];
    });

    ASSERT_EQ(head.data, magic[0]);
    ASSERT_EQ(child0.data, magic[1]);
    ASSERT_EQ(child1.data, magic[2]);
    ASSERT_EQ(child00.data, magic[3]);
}

struct TestDijkstraVertex {
    TestDijkstraVertex() {}
    explicit TestDijkstraVertex(int d) : data(d) {}

    int data = 0;
    int computedData = 0;

    std::vector<TestDijkstraVertex*> children;
};

TEST(Search, Dijkstra) {
    using ActualVertex = typename pekalib::CreateVertexType<TestDijkstraVertex, pekalib::Search::depthFirstSearchOp, pekalib::GraphType::adjacency_list>::ActualVertexT;
    ActualVertex head;
    ActualVertex child0;
    ActualVertex child00;
    ActualVertex child1;

    head.children = { &child0, &child1 };
    child0.children = { &child00 };
    child00.children = { &head };

    head.data = 323;
    child0.data = 954;
    child00.data = 4323;
    child1.data = 32;

    int i = 0;
    pekalib::Search::Dijkstra(&head, [](ActualVertex *v) {
        return *(std::vector<ActualVertex*>*)(&v->children);
    }, [&](const ActualVertex* v) {
        return v->computedData;
    }, [&](ActualVertex* v, int cData) {
        v->computedData = cData;
    }, [&](const ActualVertex* v1, const ActualVertex* v2) {
        return std::abs(v1->data - v2->data);
    });

    ASSERT_EQ(0, head.computedData);
    ASSERT_EQ(631, child0.computedData);
    ASSERT_EQ(4000, child00.computedData);
    ASSERT_EQ(291, child1.computedData);
}

