#include "predictor.h"

extern "C" {
    void create(ModelBuilder* builder, size_t _nFeatures)
    {
        nFeatures = _nFeatures;
        model = builder->getModel();
    }

    float predict(float fv[])
    {
        NumericTablePtr table = NumericTablePtr(new HomogenNumericTable<float>(fv, nFeatures, 1));
        prediction::Batch<> algorithm;
        algorithm.input.set(prediction::model, model);
        algorithm.input.set(prediction::data, table);
        algorithm.compute();

        prediction::ResultPtr result = algorithm.getResult();
        NumericTablePtr resultTable = result->get(prediction::prediction);
        BlockDescriptor<DAAL_DATA_TYPE> block;
        resultTable->getBlockOfRows(0, 1, readOnly, block);
        float* scores = block.getBlockPtr();
        return scores[0];
    }
}
