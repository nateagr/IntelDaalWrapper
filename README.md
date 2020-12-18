# Intel Daal Wrapper (GBT only)

Simple C-like wrapper to build GBT models and compute scores

## Prerequisites

Intel Daal libraries. The easiest way is to install oneAPI base toolkit: https://software.intel.com/content/www/us/en/develop/tools/oneapi/base-toolkit/download.html

## Installation

Update variable DAAL_DIR in Makefile to point to your Intel Daal installation directory
```
make build
```
LD_LIBRARY_PATH=/directory to libonedal_wrapper.so:$LD_LIBRARY_PATH

## Run tests

```
./tests/test_wrapper
```
