#pragma once

enum GraphType { adjacency_list }; //adjacency_list == VertexT has a method VPtrContainer children()


template <class VertexT, int ops, GraphType type>
class CreateVertexType {
    struct SystemPrivateVertexT : public VertexT {
        union {
            int wasHereCount = 0;
        } vertexSpecificData;

        const GraphType graphType = type;
    };

    using ActualVertexT = SystemPrivateVertexT;
};
