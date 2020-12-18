CXX := g++

WRAPPER_SRC = $(wildcard *.cc)
WRAPPER_TEST_SRC = $(wildcard tests/*.cc)

DAAL_DIR = /home/g.racic/sync/intel/

DAAL_CFLAGS = -I$(DAAL_DIR)oneapi/dal/latest/include
DAAL_LFLAGS = -L$(DAAL_DIR)oneapi/dal/latest/lib/intel64 -l:libonedal_core.a -l:libonedal_sequential.a
WRAPPER_LIB_CFLAGS = -I.
WRAPPER_LIB_LFLAGS = -L. -lonedal_wrapper
WRAPPER_CFLAGS = $(DAAL_CFLAGS) -DONEAPI_DAAL_USE_MKL_GPU_GEMM -Wl,--start-group -std=c++11 -lpthread -ldl -lOpenCL -Wl,--end-group -c -fpic
WRAPPER_LFLAGS = -shared $(DAAL_LFLAGS)
WRAPPER_TEST_CFLAGS = $(WRAPPER_LIB_LFLAGS) $(DAAL_CFLAGS) $(WRAPPER_LIB_CFLAGS) -std=c++11 -lpthread -ldl 

WRAPPER_LIB = libonedal_wrapper.so
WRAPPER_OBJS = gbt_builder.o predictor.o
WRAPPER_TEST = tests/test_wrapper

$(WRAPPER_OBJS): $(WRAPPER_SRC)
	$(CXX) $(WRAPPER_CFLAGS) $^

$(WRAPPER_LIB): $(WRAPPER_OBJS)
	$(CXX) -v -o $@ $^ $(WRAPPER_LFLAGS)

$(WRAPPER_TEST): $(WRAPPER_LIB) $(WRAPPER_TEST_SRC)
	$(CXX) -v -o $@ $(WRAPPER_TEST_CFLAGS) $^

build: $(WRAPPER_LIB) $(WRAPPER_TEST)

clean:
	rm -f $(WRAPPER_LIB) $(WRAPPER_OBJS) $(WRAPPER_TEST)
