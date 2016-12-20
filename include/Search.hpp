#pragma once

#include <CreateVertexType.hpp>
#include <Search.hpp>
#include <queue>
#include <unordered_set>
#include <stack>

const int searchOp = 0x0010;
namespace pekalib {
    /**
     * @brief Search Class which implements basic search algorithms (BFS,DFS) in pekalib.
     */
    class Search {

        /**
         * @brief get_top its common interface for getting "out" item from both std::stack, std::queue.
         * @tparam T data structure used. (std::stack or std::queue)
         * @return "out" item in selected datastructure.
         */
        template <typename T>
        static T get_top(const T &);
        
        /**
         * @brief get_top template specialization for std::stack
         * @param st stack to get "out" item from.
         * @return "out" item in stack (LIFO)
         */
        template <typename T>
        inline static T get_top(const std::stack<T> &st) {
            return st.top();
        }

        /**
         * @beief get_top template specialization for std::queue
         * @param q queue to get "out" item from.
         * @return "out" item in queue (FIFO)
         */
        template <typename T>
        inline static T get_top(const std::queue<T> &q) {
            return q.front();
        }

        /**
         * @brief common implementation of both BFS,DFS.
         * @tparam DSType datastructure to store not-visited childrens of currently processed vertex.
         * @tparam reverso iff true, traverse childrens' vector from back to front.
         * @tparam VertexT vertex type in graph.
         * @tparam F callback type.
         * @param head "seed" vertex of search.
         * @param callback callback called with vertex when it's being marked as visited.
         */
        template <typename DSType, bool reverso, typename VertexT, typename F>
        static void depthBreadthSearch(VertexT *head, const F &callback) {
            DSType dstruc;
            const int hereCountStart = head->vertexSpecificData.wasHereCount;

            dstruc.push(head);
            head->vertexSpecificData.wasHereCount = hereCountStart + 1;
            while (!dstruc.empty()) {
                VertexT *processed = get_top(dstruc);
                dstruc.pop();

                callback(processed);

                const size_t N = processed->children().size();
                for (int i = (reverso ? N-1 : 0) ; i != (reverso ? -1 : N) ; i += (reverso ? -1 : 1)) {
                    VertexT *neigh = (VertexT *) (processed->children()[i]);
                    if (neigh->vertexSpecificData.wasHereCount == hereCountStart) {
                        dstruc.push(neigh);
                        neigh->vertexSpecificData.wasHereCount = hereCountStart + 1;
                    }
                }
            }
        }

    public:
        /**
          * @brief constant used for type-construction. Means DFS operation.
          */
        static const int depthFirstSearchOp = searchOp | 0x1;
        /**
          * @brief constant used for type-construction. Means BFS operation.
          */
        static const int breadthFirstSearchOp = searchOp | 0x2;

        /**
         * @brief DFS implementation.
         * @tparam VertexT vertex type in graph.
         * @tparam F callback type.
         * @param head "seed" vertex of search.
         * @param callback callback called with vertex when it's being marked as visited.
         */
        template <class VertexT, typename F>
        static void depthFirstSearch(VertexT* head, const F& callback) {
            depthBreadthSearch<std::stack<VertexT *>, true, VertexT, F>(head, callback);
        }

        /**
         * @brief BFS implementation.
         * @tparam VertexT vertex type in graph.
         * @tparam F callback type.
         * @param head "seed" vertex of search.
         * @param callback callback called with vertex when it's being marked as visited.
         */
        template <class VertexT, typename F>
        static void breadthFirstSearch(VertexT *head, const F &callback) {
            depthBreadthSearch<std::queue<VertexT *>, false, VertexT, F>(head, callback);
        }
    };
}
