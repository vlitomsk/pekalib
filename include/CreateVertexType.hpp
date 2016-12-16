#pragma once

namespace pecalib {

    enum GraphType {
        adjacency_list
    }; //adjacency_list == VertexT has a method VPtrContainer children()


    template<class VertexT, int ops, GraphType type>
    class CreateVertexType {
    public:
        struct SystemPrivateVertexT : public VertexT {
            using VertexT::VertexT;

            union {
                int wasHereCount = 0;
            } vertexSpecificData;

            const GraphType graphType = type;
        };

        using ActualVertexT = SystemPrivateVertexT;
    };

}