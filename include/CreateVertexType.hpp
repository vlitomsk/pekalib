#pragma once


/** @defgroup m0 Core module
 *  @{
 */

namespace pekalib {

    enum GraphType {
        adjacency_list  ///< VertexT has a children list
    };


    /**
     * @brief CreateVertexType Allows to define a pekalib vertex type
     * @details a pekalib vertex type neaded by pekalib graph operations
     * @tparam VertexT user vertex type
     * @tparam ops used operations mask (used for unsafe optimizations)
     * @tparam type a graph scheme (used for safe optimizations)
     */
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

        /// Result type
        using ActualVertexT = SystemPrivateVertexT;
    };

}


/** @} */
