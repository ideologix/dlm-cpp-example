# Digital License Manager C++ Example

This is simple example that covers all the required operations to successfully show, activate, validate and deactivate a license key.

### Getting started

To get started using this first clone the project:

```
git clone --recursive https://github.com/ideologix/dlm-cpp-example.git
```

Then follow the steps:

1. Install required libcpr library as explained in **Requirements**.
2. Set up the API connection in main.cpp with your api details
3. Set up SampleKey variable in main.cpp with your key
4. To run the projects, execute the following:

```
cmake build .
bash dlm_examples
```

Sample output:

```
====== Digital License Manager Example ======
Checking License Key
- License is K2CH-GIG1-IGC3-2N1K valid.
Activating token
- License K2CH-GIG1-IGC3-2N1K activated...
- Token a12fdde7d50aee0123d7741c351c55a8c45cc129 SET.
Validating token
- Token a12fdde7d50aee0123d7741c351c55a8c45cc129 is valid...
- License K2CH-GIG1-IGC3-2N1K is valid.
Deactivating token
- Token a12fdde7d50aee0123d7741c351c55a8c45cc129 deactivated...
```

### Requirements

#### 1. libcpr 

The libcpr library is required, to install follow the guide bellow:

```
git clone https://github.com/libcpr/cpr.git
cd cpr && mkdir build && cd build
cmake .. -DCPR_USE_SYSTEM_CURL=ON
cmake --build . --parallel
sudo cmake --install .
```

#### 2. dlm-cpp

The [dlm-cpp](https://github.com/ideologix/dlm-cpp) class library is required. 

**Note**: The library is already included in this project, so no further action is needed.

#### 3. rapidjson

The rapidjson json parser library is required.

**Note**: The library is already included in this project, so no further action is needed.


### License

```
Copyright (C) 2024 - Darko Gjorgjijoski
Copyright (C) 2024 - IDEOLOGIX MEDIA DOOEL

Licensed under GPLv2

```
