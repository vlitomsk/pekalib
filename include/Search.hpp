#pragma once

#include <CreateVertexType.hpp>
#include <Search.hpp>



const int searchOp = 0x0010;
namespace pecalib {
    class Search {
    public:
        static const int depthFirstSearchOp = searchOp | 0x1;

        template <class VertexT, typename F>
        static void depthFirstSearch(VertexT* head, const F& callback) {
            auto children = head->children();
            callback(head);
            for (auto& v : children)
                depthFirstSearch<VertexT, F>((VertexT*) v, callback);
        }
    };
}