#include "gbt_builder.h"
#include "predictor.h"
#include <string>
#include <iostream>

#define N_FEATURES 3

int main(int argc, char* argv[])
{
    ModelBuilder* builder = createBuilder(N_FEATURES, 1);
    size_t treeid = createTree(builder, 7);
    size_t rootid = addSplitNode(builder, treeid, ModelBuilder::noParent, 0, 0, 0.13);
    size_t split1 = addSplitNode(builder, treeid, rootid, 0, 1, 0.2);
    size_t split2 = addSplitNode(builder, treeid, rootid, 1, 1, 0.22);
    size_t leaf1 = addLeafNode(builder, treeid, split1, 0, 0.13);
    size_t leaf2 = addLeafNode(builder, treeid, split1, 1, 0.133);
    size_t leaf3 = addLeafNode(builder, treeid, split2, 0, 0.1333);
    size_t leaf4 = addLeafNode(builder, treeid, split2, 1, 0.13333);

    create(builder, N_FEATURES);
    float fv[N_FEATURES] = { 0.133, 0.222 };
    float scores = predict(fv);
    std::cout << "Score: " << scores << std::endl;

    fv[0] = 0.12;
    fv[1] = 0.3;
    scores = predict(fv);
    std::cout << "Score: " << scores << std::endl;

    deleteBuilder(builder);

    return 0;
}
