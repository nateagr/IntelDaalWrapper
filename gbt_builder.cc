#include "gbt_builder.h"

extern "C" {

    ModelBuilder* createBuilder(size_t nFeatures, size_t nTrees)
    {
        return new ModelBuilder(nFeatures, nTrees);
    }

    size_t createTree(ModelBuilder* builder, size_t nNodes)
    {
        return builder->createTree(nNodes);
    }

    size_t addLeafNode(ModelBuilder* builder, size_t treeId, size_t parentId, size_t position, double response)
    {
        return builder->addLeafNode(treeId, parentId, position, response);
    }

    size_t addSplitNode(ModelBuilder* builder, size_t treeId, size_t parentId, size_t position, size_t featureIndex, double featureValue)
    {
        return builder->addSplitNode(treeId, parentId, position, featureIndex, featureValue);
    }

    size_t addRoot(ModelBuilder* builder, size_t treeId, size_t featureIndex, double featureValue)
    {
        return builder->addSplitNode(treeId, ModelBuilder::noParent, 0, featureIndex, featureValue);
    }

    void deleteBuilder(ModelBuilder* builder)
    {
        delete builder;
    }
}
