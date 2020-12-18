#include "gbt_builder.h"
#include "predictor.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define N_FEATURES 3

int main(int argc, char* argv[])
{
    srand(time(NULL));	

    ModelBuilder* builder = createBuilder(N_FEATURES, 1);
    size_t treeid = createTree(builder, 7);
    size_t rootid = addSplitNode(builder, treeid, ModelBuilder::noParent, 0, 0, 0.13);
    size_t split1 = addSplitNode(builder, treeid, rootid, 0, 1, 0.2);
    size_t split2 = addSplitNode(builder, treeid, rootid, 1, 1, 0.22);
    size_t leaf1 = addLeafNode(builder, treeid, split1, 0, 0.13);
    size_t leaf2 = addLeafNode(builder, treeid, split1, 1, 0.133);
    size_t leaf3 = addLeafNode(builder, treeid, split2, 0, 0.1333);
    size_t leaf4 = addLeafNode(builder, treeid, split2, 1, 0.13333);

    ModelPtr* model = build(builder);
    prediction::Batch<>* predictor1 = createPredictor(model, N_FEATURES); 
    prediction::Batch<>* predictor2 = createPredictor(model, N_FEATURES);

    float fv[N_FEATURES];
    for (int i = 0; i < 100; i++)
    {
        fv[0] = (rand() % 100) / 100.0;
        fv[1] = (rand() % 100) / 100.0;
        float scores = predict(predictor1, fv);
        std::cout << "FV: {" << fv[0] << "; " << fv[1] << "}; Score: " << scores << std::endl;
    }
 
    deleteBuilder(builder);
    deletePredictor(predictor1);
    deletePredictor(predictor2);
    deleteModel(model);

    return 0;
}
