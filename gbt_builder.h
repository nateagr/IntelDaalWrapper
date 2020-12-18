#include "daal.h"

#define ONEDAL_WRAPPER_EXPORT 

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

	CAPI_EXPORT extern ModelBuilder* createBuilder(size_t nFeatures, size_t nTrees);
	CAPI_EXPORT extern size_t createTree(ModelBuilder* builder, size_t nNodes);
	CAPI_EXPORT extern size_t addLeafNode(ModelBuilder* builder, size_t treeId, size_t parentId, size_t position, double response);
	CAPI_EXPORT extern size_t addRoot(ModelBuilder* builder, size_t treeId, size_t featureIndex, double featureValue);
	CAPI_EXPORT extern size_t addSplitNode(ModelBuilder* builder, size_t treeId, size_t parentId, size_t position, size_t featureIndex, double featureValue);
	CAPI_EXPORT extern ModelPtr* build(ModelBuilder* builder);
	CAPI_EXPORT extern void deleteBuilder(ModelBuilder* builder);

#ifdef __cplusplus
} /* end extern "C" */
#endif
