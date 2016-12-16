#pragma once

#include <CreateVertexType.hpp>
#include <Search.hpp>
#include <queue>
#include <unordered_set>
#include <stack>

const int searchOp = 0x0010;
namespace pekalib {
    class Search {
        template <typename T>
        static T get_top(const T &);

        template <typename T>
        inline static T get_top(const std::stack<T> &st) {
            return st.top();
        }

        template <typename T>
        inline static T get_top(const std::queue<T> &q) {
            return q.front();
        }

        template <typename DSType, bool reverso, typename VertexT, typename F>
        static void depthBreadthSearch(VertexT *head, const F &callback) {
            DSType dstruc;
            dstruc.push(head);
            std::unordered_set<const VertexT *> used;
            while (!dstruc.empty()) {
                VertexT *processed = get_top(dstruc);
                dstruc.pop();
                callback(processed);
                used.insert(processed);
                const size_t N = processed->children().size();
                for (int i = (reverso ? N-1 : 0) ; i != (reverso ? -1 : N) ; i += (reverso ? -1 : 1)) {
                    VertexT *neigh = (VertexT *) (processed->children()[i]);
                    if (!used.count(neigh)) {
                        dstruc.push(neigh);
                    }
                }
            }
        }

    public:
        static const int depthFirstSearchOp = searchOp | 0x1;
        static const int breadthFirstSearchOp = searchOp | 0x2;

        template <class VertexT, typename F>
        static void depthFirstSearch(VertexT* head, const F& callback) {
            depthBreadthSearch<std::stack<VertexT *>, true, VertexT, F>(head, callback);
        }

        template <class VertexT, typename F>
        static void breadthFirstSearch(VertexT *head, const F &callback) {
            depthBreadthSearch<std::queue<VertexT *>, false, VertexT, F>(head, callback);
        }
    };
}
