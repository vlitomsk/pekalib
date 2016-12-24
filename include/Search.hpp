#pragma once

#include <CreateVertexType.hpp>
#include <Search.hpp>
#include <queue>
#include <unordered_set>
#include <stack>

/** @defgroup m1 Search module
 *  @{
 */

const int searchOp = 0x0010;
namespace pekalib {
    /**
     * @brief Search Class which implements basic search algorithms (BFS, DFS, Dijkstra) in pekalib.
     */
    class Search {

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
         * @tparam EF getting elements callback type.
         * @tparam F callback type.
         * @param head "seed" vertex of search.
         * @param getting elements callback.
         * @param callback callback called with vertex when it's being marked as visited.
         */
        template <class VertexPtrT, typename EF, typename F>
        static void depthFirstSearch(VertexPtrT head, const EF& children, const F& callback) {
            depthBreadthSearch<std::stack<VertexPtrT>, true, VertexPtrT, EF, F>(head, children, callback);
        }

        /**
         * @brief BFS implementation.
         * @tparam VertexT vertex type in graph.
         * @tparam F callback type.
         * @param head "seed" vertex of search.
         * @param getting elements callback.
         * @param callback callback called with vertex when it's being marked as visited.
         */
        template <class VertexPtrT, typename EF, typename F>
        static void breadthFirstSearch(VertexPtrT head, const EF& children, const F& callback) {
            depthBreadthSearch<std::queue<VertexPtrT>, false, VertexPtrT, EF, F>(head, children, callback);
        }

        /**
         * @brief Dijkstra implementation.
         * @tparam VertexT vertex type in graph.
         * @tparam EF getting elements callback type.
         * @tparam GetD getting the vertex dist callback type.
         * @tparam SetD setting the vertex dist callback type.
         * @tparam GetL getting the edge weight callback type.
         * @param head "seed" vertex of search.
         * @param getting elements callback.
         * @param setd getting the vertex dist callback.
         * @param getd setting the vertex dist callback.
         * @param getl getting the edge weight.
         */
        template <class VertexPtrT, typename EF, typename GetD, typename SetD, typename GetL>
        static void Dijkstra(VertexPtrT head, const EF& children, const GetD& getd, const SetD& setd, const GetL& getl) {
            breadthFirstSearch(head, children, [&](VertexPtrT v) {
                setd(v, INT32_MAX);
            });
            setd(head, 0);

            auto compare = [&](const VertexPtrT a, const VertexPtrT b) {
                return getd(a) > getd(b);
            };
            std::priority_queue<VertexPtrT, std::vector<VertexPtrT>, decltype(compare)>  vertexesPQueue(compare);
            vertexesPQueue.push(head);

            while (!vertexesPQueue.empty()) {
                VertexPtrT vertex = vertexesPQueue.top();
                vertexesPQueue.pop();

                auto childs = children(vertex);
                for (auto neigh : childs) {
                    auto length = getl(vertex, neigh);

                    //  If there is shorted path to v through u.
                    if (getd(neigh) > getd(vertex) + length) {
                        // Updating the distance of v
                        setd(neigh, getd(vertex) + length);
                        vertexesPQueue.push(neigh);
                    }
                }
            }
        }

    private:

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
         * @tparam EF getting elements callback type.
         * @tparam F callback type.
         * @param head "seed" vertex of search.
         * @param getting elements callback.
         * @param callback callback called with vertex when it's being marked as visited.
         */
        template <class DSType, bool reverso, class VertexPtrT, typename EF, typename F>
        static void depthBreadthSearch(VertexPtrT head, const EF& children, const F &callback) {
            DSType dstruc;
            const int hereCountStart = head->vertexSpecificData.wasHereCount;

            dstruc.push(head);
            head->vertexSpecificData.wasHereCount = hereCountStart + 1;
            while (!dstruc.empty()) {
                auto processed = get_top(dstruc);
                dstruc.pop();

                callback(processed);

                auto childs = children(processed);
                const size_t N = childs.size();
                for (int i = (reverso ? N-1 : 0) ; i != (reverso ? -1 : N) ; i += (reverso ? -1 : 1)) {
                    auto neigh = childs[i];
                    if (neigh->vertexSpecificData.wasHereCount == hereCountStart) {
                        dstruc.push(neigh);
                        neigh->vertexSpecificData.wasHereCount = hereCountStart + 1;
                    }
                }
            }
        }
    };
}


/** @} */
