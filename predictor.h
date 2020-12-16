#include "daal.h"
#include "thread_safe_queue.h"

#define ONEDAL_WRAPPER_EXPORT 
#define PREALLOCATED_PREDICTORS 10

#ifdef SWIG
#define CAPI_EXPORT
#else
#if defined(_WIN32)
#ifdef ONEDAL_WRAPPER_EXPORT
#define CAPI_EXPORT __declspec(dllexport)
#else
#define CAPI_EXPORT __declspec(dllimport)
#endif  // TF_COMPILE_LIBRARY
#else
#define CAPI_EXPORT __attribute__((visibility("default")))
#endif  // _WIN32
#endif  // SWIG

#ifdef __cplusplus
extern "C" {
#endif

	using namespace daal::algorithms::gbt::regression;
	using namespace daal::data_management;

	ThreadsafeQueue<prediction::Batch<>*> predictors;

	CAPI_EXPORT extern ModelPtr build(ModelBuilder* builder);
	CAPI_EXPORT extern float predict(ModelPtr model, float fv[], size_t nFeatures);
	CAPI_EXPORT extern void destroy();

#ifdef __cplusplus
} /* end extern "C" */
#endif
