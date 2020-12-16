#include "predictor.h"

extern "C" {
    ModelPtr build(ModelBuilder* builder)
    {
	for (int i = 0; i < PREALLOCATED_PREDICTORS; i++)
	{
	    prediction::Batch<>* algorithm = new prediction::Batch<>();
            predictors.push(algorithm);
	}
	return builder->getModel();
    }

    float predict(ModelPtr model, float fv[], size_t nFeatures)
    {
	prediction::Batch<>* algorithm = predictors.pop();
	NumericTablePtr table = NumericTablePtr(new HomogenNumericTable<float>(fv, nFeatures, 1));
	algorithm->input.set(prediction::model, model);
	algorithm->input.set(prediction::data, table);
        algorithm->compute();

        prediction::ResultPtr result = algorithm->getResult();
        NumericTablePtr resultTable = result->get(prediction::prediction);
        BlockDescriptor<DAAL_DATA_TYPE> block;
        resultTable->getBlockOfRows(0, 1, readOnly, block);
        float* scores = block.getBlockPtr();
        
	predictors.push(algorithm);
	
	return scores[0];
    }

    void destroy()
    {
	int size = predictors.size();
        std::cout << "Size: " << size << std::endl;
        for (int i = 0; i < size; i++)
	{
	    prediction::Batch<>* algorithm = predictors.pop();
            delete algorithm;
	}
        std::cout << "Size: " << predictors.size() << std::endl;
    }
}
