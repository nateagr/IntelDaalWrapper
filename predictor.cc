#include "predictor.h"

extern "C" {
    prediction::Batch<>* createPredictor(ModelPtr* model, size_t nFeatures)
    {
        NumericTablePtr table = NumericTablePtr(new HomogenNumericTable<float>(0, nFeatures, 1));
        prediction::Batch<>* algorithm = new prediction::Batch<>();
        algorithm->input.set(prediction::model, ModelPtr(*model));
        algorithm->input.set(prediction::data, table);
        return algorithm;
    }

    float predict(prediction::Batch<>* predictor, float fv[])
    {
        NumericTablePtr nt = predictor->input.get(prediction::data);
        ((HomogenNumericTable<float>*)(nt.get()))->setArray(fv, 1);
        predictor->compute();

        prediction::ResultPtr result = predictor->getResult();
        NumericTablePtr resultTable = result->get(prediction::prediction);
        BlockDescriptor<DAAL_DATA_TYPE> block;
        resultTable->getBlockOfRows(0, 1, readOnly, block);
        float* scores = block.getBlockPtr();
        return scores[0];
    }

    void deletePredictor(prediction::Batch<>* predictor)
    {
        delete predictor;
    }

    void deleteModel(ModelPtr* model)
    {
        delete model;
    }
}
