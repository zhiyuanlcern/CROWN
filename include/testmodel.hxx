//Code generated automatically by TMVA for Inference of Model file [testmodel.h5] at [Thu Nov  9 07:32:30 2023] 

#ifndef TMVA_SOFIE_TESTMODEL
#define TMVA_SOFIE_TESTMODEL

#include<algorithm>
#include<cmath>
#include<vector>
#include "TMVA/SOFIE_common.hxx"
#include <fstream>

namespace TMVA_SOFIE_testmodel{
namespace BLAS{
	extern "C" void saxpy_(const int * n, const float * alpha, const float * x,
	                         const int * incx, float * y, const int * incy);
	extern "C" void scopy_(const int *n, const float* x, const int *incx, float* y, const int* incy);
	extern "C" void sgemv_(const char * trans, const int * m, const int * n, const float * alpha, const float * A,
	                       const int * lda, const float * X, const int * incx, const float * beta, const float * Y, const int * incy);
	extern "C" void sgemm_(const char * transa, const char * transb, const int * m, const int * n, const int * k,
	                       const float * alpha, const float * A, const int * lda, const float * B, const int * ldb,
	                       const float * beta, float * C, const int * ldc);
}//BLAS
struct Session {
std::vector<float> fTensor_dense12kernel0 = std::vector<float>(40000);
float * tensor_dense12kernel0 = fTensor_dense12kernel0.data();
std::vector<float> fTensor_dense13kernel0 = std::vector<float>(200);
float * tensor_dense13kernel0 = fTensor_dense13kernel0.data();
std::vector<float> fTensor_batchnormalization3movingmean0 = std::vector<float>(200);
float * tensor_batchnormalization3movingmean0 = fTensor_batchnormalization3movingmean0.data();
std::vector<float> fTensor_dense12bias0 = std::vector<float>(200);
float * tensor_dense12bias0 = fTensor_dense12bias0.data();
std::vector<float> fTensor_batchnormalization3gamma0 = std::vector<float>(200);
float * tensor_batchnormalization3gamma0 = fTensor_batchnormalization3gamma0.data();
std::vector<float> fTensor_batchnormalization3movingvariance0 = std::vector<float>(200);
float * tensor_batchnormalization3movingvariance0 = fTensor_batchnormalization3movingvariance0.data();
std::vector<float> fTensor_dense11bias0 = std::vector<float>(200);
float * tensor_dense11bias0 = fTensor_dense11bias0.data();
std::vector<float> fTensor_dense11kernel0 = std::vector<float>(40000);
float * tensor_dense11kernel0 = fTensor_dense11kernel0.data();
std::vector<float> fTensor_dense10bias0 = std::vector<float>(200);
float * tensor_dense10bias0 = fTensor_dense10bias0.data();
std::vector<float> fTensor_dense10kernel0 = std::vector<float>(40000);
float * tensor_dense10kernel0 = fTensor_dense10kernel0.data();
std::vector<float> fTensor_dense9kernel0 = std::vector<float>(40000);
float * tensor_dense9kernel0 = fTensor_dense9kernel0.data();
std::vector<float> fTensor_batchnormalization2movingvariance0 = std::vector<float>(200);
float * tensor_batchnormalization2movingvariance0 = fTensor_batchnormalization2movingvariance0.data();
std::vector<float> fTensor_dense3kernel0 = std::vector<float>(40000);
float * tensor_dense3kernel0 = fTensor_dense3kernel0.data();
std::vector<float> fTensor_batchnormalizationmovingmean0 = std::vector<float>(200);
float * tensor_batchnormalizationmovingmean0 = fTensor_batchnormalizationmovingmean0.data();
std::vector<float> fTensor_dense2bias0 = std::vector<float>(200);
float * tensor_dense2bias0 = fTensor_dense2bias0.data();
std::vector<float> fTensor_dense8bias0 = std::vector<float>(200);
float * tensor_dense8bias0 = fTensor_dense8bias0.data();
std::vector<float> fTensor_batchnormalizationbeta0 = std::vector<float>(200);
float * tensor_batchnormalizationbeta0 = fTensor_batchnormalizationbeta0.data();
std::vector<float> fTensor_batchnormalizationgamma0 = std::vector<float>(200);
float * tensor_batchnormalizationgamma0 = fTensor_batchnormalizationgamma0.data();
std::vector<float> fTensor_dense4kernel0 = std::vector<float>(40000);
float * tensor_dense4kernel0 = fTensor_dense4kernel0.data();
std::vector<float> fTensor_dense13bias0 = std::vector<float>(1);
float * tensor_dense13bias0 = fTensor_dense13bias0.data();
std::vector<float> fTensor_batchnormalizationmovingvariance0 = std::vector<float>(200);
float * tensor_batchnormalizationmovingvariance0 = fTensor_batchnormalizationmovingvariance0.data();
std::vector<float> fTensor_batchnormalization1gamma0 = std::vector<float>(200);
float * tensor_batchnormalization1gamma0 = fTensor_batchnormalization1gamma0.data();
std::vector<float> fTensor_batchnormalization3beta0 = std::vector<float>(200);
float * tensor_batchnormalization3beta0 = fTensor_batchnormalization3beta0.data();
std::vector<float> fTensor_dense3bias0 = std::vector<float>(200);
float * tensor_dense3bias0 = fTensor_dense3bias0.data();
std::vector<float> fTensor_dense2kernel0 = std::vector<float>(40000);
float * tensor_dense2kernel0 = fTensor_dense2kernel0.data();
std::vector<float> fTensor_dense1bias0 = std::vector<float>(200);
float * tensor_dense1bias0 = fTensor_dense1bias0.data();
std::vector<float> fTensor_dense1kernel0 = std::vector<float>(40000);
float * tensor_dense1kernel0 = fTensor_dense1kernel0.data();
std::vector<float> fTensor_batchnormalization2beta0 = std::vector<float>(200);
float * tensor_batchnormalization2beta0 = fTensor_batchnormalization2beta0.data();
std::vector<float> fTensor_densekernel0 = std::vector<float>(4200);
float * tensor_densekernel0 = fTensor_densekernel0.data();
std::vector<float> fTensor_dense4bias0 = std::vector<float>(200);
float * tensor_dense4bias0 = fTensor_dense4bias0.data();
std::vector<float> fTensor_dense8kernel0 = std::vector<float>(40000);
float * tensor_dense8kernel0 = fTensor_dense8kernel0.data();
std::vector<float> fTensor_batchnormalization2movingmean0 = std::vector<float>(200);
float * tensor_batchnormalization2movingmean0 = fTensor_batchnormalization2movingmean0.data();
std::vector<float> fTensor_densebias0 = std::vector<float>(200);
float * tensor_densebias0 = fTensor_densebias0.data();
std::vector<float> fTensor_dense5bias0 = std::vector<float>(200);
float * tensor_dense5bias0 = fTensor_dense5bias0.data();
std::vector<float> fTensor_dense7bias0 = std::vector<float>(200);
float * tensor_dense7bias0 = fTensor_dense7bias0.data();
std::vector<float> fTensor_batchnormalization1beta0 = std::vector<float>(200);
float * tensor_batchnormalization1beta0 = fTensor_batchnormalization1beta0.data();
std::vector<float> fTensor_batchnormalization1movingmean0 = std::vector<float>(200);
float * tensor_batchnormalization1movingmean0 = fTensor_batchnormalization1movingmean0.data();
std::vector<float> fTensor_batchnormalization1movingvariance0 = std::vector<float>(200);
float * tensor_batchnormalization1movingvariance0 = fTensor_batchnormalization1movingvariance0.data();
std::vector<float> fTensor_dense6bias0 = std::vector<float>(200);
float * tensor_dense6bias0 = fTensor_dense6bias0.data();
std::vector<float> fTensor_dense6kernel0 = std::vector<float>(40000);
float * tensor_dense6kernel0 = fTensor_dense6kernel0.data();
std::vector<float> fTensor_dense7kernel0 = std::vector<float>(40000);
float * tensor_dense7kernel0 = fTensor_dense7kernel0.data();
std::vector<float> fTensor_dense9bias0 = std::vector<float>(200);
float * tensor_dense9bias0 = fTensor_dense9bias0.data();
std::vector<float> fTensor_dense5kernel0 = std::vector<float>(40000);
float * tensor_dense5kernel0 = fTensor_dense5kernel0.data();
std::vector<float> fTensor_batchnormalization2gamma0 = std::vector<float>(200);
float * tensor_batchnormalization2gamma0 = fTensor_batchnormalization2gamma0.data();
std::vector<float> fTensor_leakyrelu12LeakyRelu0 = std::vector<float>(200);
float * tensor_leakyrelu12LeakyRelu0 = fTensor_leakyrelu12LeakyRelu0.data();
std::vector<float> fTensor_leakyrelu11LeakyRelu0 = std::vector<float>(200);
float * tensor_leakyrelu11LeakyRelu0 = fTensor_leakyrelu11LeakyRelu0.data();
std::vector<float> fTensor_dense13Dense = std::vector<float>(1);
float * tensor_dense13Dense = fTensor_dense13Dense.data();
std::vector<float> fTensor_batchnormalization3batchnormadd10 = std::vector<float>(200);
float * tensor_batchnormalization3batchnormadd10 = fTensor_batchnormalization3batchnormadd10.data();
std::vector<float> fTensor_dense11BiasAdd0 = std::vector<float>(200);
float * tensor_dense11BiasAdd0 = fTensor_dense11BiasAdd0.data();
std::vector<float> fTensor_leakyrelu10LeakyRelu0 = std::vector<float>(200);
float * tensor_leakyrelu10LeakyRelu0 = fTensor_leakyrelu10LeakyRelu0.data();
std::vector<float> fTensor_dense10BiasAdd0 = std::vector<float>(200);
float * tensor_dense10BiasAdd0 = fTensor_dense10BiasAdd0.data();
std::vector<float> fTensor_dense10bias0bcast = std::vector<float>(200);
float * tensor_dense10bias0bcast = fTensor_dense10bias0bcast.data();
std::vector<float> fTensor_dropout9Identity0 = std::vector<float>(200);
float * tensor_dropout9Identity0 = fTensor_dropout9Identity0.data();
std::vector<float> fTensor_leakyrelu9LeakyRelu0 = std::vector<float>(200);
float * tensor_leakyrelu9LeakyRelu0 = fTensor_leakyrelu9LeakyRelu0.data();
std::vector<float> fTensor_leakyrelu8LeakyRelu0 = std::vector<float>(200);
float * tensor_leakyrelu8LeakyRelu0 = fTensor_leakyrelu8LeakyRelu0.data();
std::vector<float> fTensor_batchnormalization2batchnormadd10 = std::vector<float>(200);
float * tensor_batchnormalization2batchnormadd10 = fTensor_batchnormalization2batchnormadd10.data();
std::vector<float> fTensor_dense8BiasAdd0 = std::vector<float>(200);
float * tensor_dense8BiasAdd0 = fTensor_dense8BiasAdd0.data();
std::vector<float> fTensor_dense8bias0bcast = std::vector<float>(200);
float * tensor_dense8bias0bcast = fTensor_dense8bias0bcast.data();
std::vector<float> fTensor_dropout12Identity0 = std::vector<float>(200);
float * tensor_dropout12Identity0 = fTensor_dropout12Identity0.data();
std::vector<float> fTensor_leakyrelu7LeakyRelu0 = std::vector<float>(200);
float * tensor_leakyrelu7LeakyRelu0 = fTensor_leakyrelu7LeakyRelu0.data();
std::vector<float> fTensor_dense7BiasAdd0 = std::vector<float>(200);
float * tensor_dense7BiasAdd0 = fTensor_dense7BiasAdd0.data();
std::vector<float> fTensor_dropout6Identity0 = std::vector<float>(200);
float * tensor_dropout6Identity0 = fTensor_dropout6Identity0.data();
std::vector<float> fTensor_dense13Sigmoid0 = std::vector<float>(1);
float * tensor_dense13Sigmoid0 = fTensor_dense13Sigmoid0.data();
std::vector<float> fTensor_dropout11Identity0 = std::vector<float>(200);
float * tensor_dropout11Identity0 = fTensor_dropout11Identity0.data();
std::vector<float> fTensor_dropout2Identity0 = std::vector<float>(200);
float * tensor_dropout2Identity0 = fTensor_dropout2Identity0.data();
std::vector<float> fTensor_dropout1Identity0 = std::vector<float>(200);
float * tensor_dropout1Identity0 = fTensor_dropout1Identity0.data();
std::vector<float> fTensor_dropout10Identity0 = std::vector<float>(200);
float * tensor_dropout10Identity0 = fTensor_dropout10Identity0.data();
std::vector<float> fTensor_leakyrelu1LeakyRelu0 = std::vector<float>(200);
float * tensor_leakyrelu1LeakyRelu0 = fTensor_leakyrelu1LeakyRelu0.data();
std::vector<float> fTensor_dense12BiasAdd0 = std::vector<float>(200);
float * tensor_dense12BiasAdd0 = fTensor_dense12BiasAdd0.data();
std::vector<float> fTensor_dense6bias0bcast = std::vector<float>(200);
float * tensor_dense6bias0bcast = fTensor_dense6bias0bcast.data();
std::vector<float> fTensor_dense7bias0bcast = std::vector<float>(200);
float * tensor_dense7bias0bcast = fTensor_dense7bias0bcast.data();
std::vector<float> fTensor_dense4bias0bcast = std::vector<float>(200);
float * tensor_dense4bias0bcast = fTensor_dense4bias0bcast.data();
std::vector<float> fTensor_dropout3Identity0 = std::vector<float>(200);
float * tensor_dropout3Identity0 = fTensor_dropout3Identity0.data();
std::vector<float> fTensor_dropout7Identity0 = std::vector<float>(200);
float * tensor_dropout7Identity0 = fTensor_dropout7Identity0.data();
std::vector<float> fTensor_dense1BiasAdd0 = std::vector<float>(200);
float * tensor_dense1BiasAdd0 = fTensor_dense1BiasAdd0.data();
std::vector<float> fTensor_dense1bias0bcast = std::vector<float>(200);
float * tensor_dense1bias0bcast = fTensor_dense1bias0bcast.data();
std::vector<float> fTensor_dense13bias0bcast = std::vector<float>(1);
float * tensor_dense13bias0bcast = fTensor_dense13bias0bcast.data();
std::vector<float> fTensor_dense9bias0bcast = std::vector<float>(200);
float * tensor_dense9bias0bcast = fTensor_dense9bias0bcast.data();
std::vector<float> fTensor_dense2BiasAdd0 = std::vector<float>(200);
float * tensor_dense2BiasAdd0 = fTensor_dense2BiasAdd0.data();
std::vector<float> fTensor_dropoutIdentity0 = std::vector<float>(200);
float * tensor_dropoutIdentity0 = fTensor_dropoutIdentity0.data();
std::vector<float> fTensor_batchnormalizationbatchnormadd10 = std::vector<float>(200);
float * tensor_batchnormalizationbatchnormadd10 = fTensor_batchnormalizationbatchnormadd10.data();
std::vector<float> fTensor_leakyrelu2LeakyRelu0 = std::vector<float>(200);
float * tensor_leakyrelu2LeakyRelu0 = fTensor_leakyrelu2LeakyRelu0.data();
std::vector<float> fTensor_dense12bias0bcast = std::vector<float>(200);
float * tensor_dense12bias0bcast = fTensor_dense12bias0bcast.data();
std::vector<float> fTensor_denseBiasAdd0 = std::vector<float>(200);
float * tensor_denseBiasAdd0 = fTensor_denseBiasAdd0.data();
std::vector<float> fTensor_dense2bias0bcast = std::vector<float>(200);
float * tensor_dense2bias0bcast = fTensor_dense2bias0bcast.data();
std::vector<float> fTensor_densebias0bcast = std::vector<float>(200);
float * tensor_densebias0bcast = fTensor_densebias0bcast.data();
std::vector<float> fTensor_dropout8Identity0 = std::vector<float>(200);
float * tensor_dropout8Identity0 = fTensor_dropout8Identity0.data();
std::vector<float> fTensor_dense3BiasAdd0 = std::vector<float>(200);
float * tensor_dense3BiasAdd0 = fTensor_dense3BiasAdd0.data();
std::vector<float> fTensor_dense9BiasAdd0 = std::vector<float>(200);
float * tensor_dense9BiasAdd0 = fTensor_dense9BiasAdd0.data();
std::vector<float> fTensor_dense3bias0bcast = std::vector<float>(200);
float * tensor_dense3bias0bcast = fTensor_dense3bias0bcast.data();
std::vector<float> fTensor_leakyrelu3LeakyRelu0 = std::vector<float>(200);
float * tensor_leakyrelu3LeakyRelu0 = fTensor_leakyrelu3LeakyRelu0.data();
std::vector<float> fTensor_dense11bias0bcast = std::vector<float>(200);
float * tensor_dense11bias0bcast = fTensor_dense11bias0bcast.data();
std::vector<float> fTensor_dense4BiasAdd0 = std::vector<float>(200);
float * tensor_dense4BiasAdd0 = fTensor_dense4BiasAdd0.data();
std::vector<float> fTensor_batchnormalization1batchnormadd10 = std::vector<float>(200);
float * tensor_batchnormalization1batchnormadd10 = fTensor_batchnormalization1batchnormadd10.data();
std::vector<float> fTensor_dense6BiasAdd0 = std::vector<float>(200);
float * tensor_dense6BiasAdd0 = fTensor_dense6BiasAdd0.data();
std::vector<float> fTensor_leakyreluLeakyRelu0 = std::vector<float>(200);
float * tensor_leakyreluLeakyRelu0 = fTensor_leakyreluLeakyRelu0.data();
std::vector<float> fTensor_leakyrelu4LeakyRelu0 = std::vector<float>(200);
float * tensor_leakyrelu4LeakyRelu0 = fTensor_leakyrelu4LeakyRelu0.data();
std::vector<float> fTensor_dropout4Identity0 = std::vector<float>(200);
float * tensor_dropout4Identity0 = fTensor_dropout4Identity0.data();
std::vector<float> fTensor_dense5bias0bcast = std::vector<float>(200);
float * tensor_dense5bias0bcast = fTensor_dense5bias0bcast.data();
std::vector<float> fTensor_dense5BiasAdd0 = std::vector<float>(200);
float * tensor_dense5BiasAdd0 = fTensor_dense5BiasAdd0.data();
std::vector<float> fTensor_leakyrelu5LeakyRelu0 = std::vector<float>(200);
float * tensor_leakyrelu5LeakyRelu0 = fTensor_leakyrelu5LeakyRelu0.data();
std::vector<float> fTensor_dropout5Identity0 = std::vector<float>(200);
float * tensor_dropout5Identity0 = fTensor_dropout5Identity0.data();
std::vector<float> fTensor_leakyrelu6LeakyRelu0 = std::vector<float>(200);
float * tensor_leakyrelu6LeakyRelu0 = fTensor_leakyrelu6LeakyRelu0.data();


Session(std::string filename ="") {
   if (filename.empty()) filename = "testmodel.dat";
   std::ifstream f;
   f.open(filename);
   if (!f.is_open()){
      throw std::runtime_error("tmva-sofie failed to open file for input weights");
   }
   std::string tensor_name;
   int length;
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense12kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense12kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 40000) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 40000 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense12kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense13kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense13kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense13kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization3movingmean0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization3movingmean0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization3movingmean0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense12bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense12bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense12bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization3gamma0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization3gamma0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization3gamma0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization3movingvariance0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization3movingvariance0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization3movingvariance0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense11bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense11bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense11bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense11kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense11kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 40000) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 40000 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense11kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense10bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense10bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense10bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense10kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense10kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 40000) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 40000 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense10kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense9kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense9kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 40000) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 40000 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense9kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization2movingvariance0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization2movingvariance0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization2movingvariance0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense3kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense3kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 40000) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 40000 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense3kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalizationmovingmean0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalizationmovingmean0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalizationmovingmean0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense2bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense2bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense2bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense8bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense8bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense8bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalizationbeta0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalizationbeta0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalizationbeta0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalizationgamma0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalizationgamma0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalizationgamma0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense4kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense4kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 40000) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 40000 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense4kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense13bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense13bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 1) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 1 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense13bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalizationmovingvariance0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalizationmovingvariance0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalizationmovingvariance0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization1gamma0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization1gamma0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization1gamma0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization3beta0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization3beta0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization3beta0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense3bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense3bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense3bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense2kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense2kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 40000) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 40000 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense2kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense1bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense1bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense1bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense1kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense1kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 40000) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 40000 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense1kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization2beta0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization2beta0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization2beta0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_densekernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_densekernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 4200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 4200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_densekernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense4bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense4bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense4bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense8kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense8kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 40000) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 40000 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense8kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization2movingmean0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization2movingmean0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization2movingmean0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_densebias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_densebias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_densebias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense5bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense5bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense5bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense7bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense7bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense7bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization1beta0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization1beta0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization1beta0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization1movingmean0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization1movingmean0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization1movingmean0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization1movingvariance0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization1movingvariance0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization1movingvariance0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense6bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense6bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense6bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense6kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense6kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 40000) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 40000 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense6kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense7kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense7kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 40000) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 40000 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense7kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense9bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense9bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense9bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense5kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense5kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 40000) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 40000 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense5kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization2gamma0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization2gamma0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 200) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 200 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization2gamma0[i];
   f.close();
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_densebias0,{ 200 }, { 1 , 200 });
      std::copy(data, data + 200, tensor_densebias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense1bias0,{ 200 }, { 1 , 200 });
      std::copy(data, data + 200, tensor_dense1bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense2bias0,{ 200 }, { 1 , 200 });
      std::copy(data, data + 200, tensor_dense2bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense3bias0,{ 200 }, { 1 , 200 });
      std::copy(data, data + 200, tensor_dense3bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense4bias0,{ 200 }, { 1 , 200 });
      std::copy(data, data + 200, tensor_dense4bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense5bias0,{ 200 }, { 1 , 200 });
      std::copy(data, data + 200, tensor_dense5bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense6bias0,{ 200 }, { 1 , 200 });
      std::copy(data, data + 200, tensor_dense6bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense7bias0,{ 200 }, { 1 , 200 });
      std::copy(data, data + 200, tensor_dense7bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense8bias0,{ 200 }, { 1 , 200 });
      std::copy(data, data + 200, tensor_dense8bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense9bias0,{ 200 }, { 1 , 200 });
      std::copy(data, data + 200, tensor_dense9bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense10bias0,{ 200 }, { 1 , 200 });
      std::copy(data, data + 200, tensor_dense10bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense11bias0,{ 200 }, { 1 , 200 });
      std::copy(data, data + 200, tensor_dense11bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense12bias0,{ 200 }, { 1 , 200 });
      std::copy(data, data + 200, tensor_dense12bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense13bias0,{ 1 }, { 1 , 1 });
      std::copy(data, data + 1, tensor_dense13bias0bcast);
      delete [] data;
   }
}

std::vector<float> infer(float* tensor_input1){
       // Print the input vector
    std::cout << "Input Vector: ";
    for (int i = 0; i < 21; ++i) { // Assuming 21 is the length of your input vector
        std::cout << tensor_input1[i] << " ";
    }
    std::cout << std::endl;

//--------- Gemm
   char op_0_transA = 'n';
   char op_0_transB = 'n';
   int op_0_m = 1;
   int op_0_n = 200;
   int op_0_k = 21;
   float op_0_alpha = 1;
   float op_0_beta = 1;
   int op_0_lda = 21;
   int op_0_ldb = 200;
   std::copy(tensor_densebias0bcast, tensor_densebias0bcast + 200, tensor_denseBiasAdd0);
   BLAS::sgemm_(&op_0_transB, &op_0_transA, &op_0_n, &op_0_m, &op_0_k, &op_0_alpha, tensor_densekernel0, &op_0_ldb, tensor_input1, &op_0_lda, &op_0_beta, tensor_denseBiasAdd0, &op_0_n);
   float op_1_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 200 ; id++){
      tensor_leakyreluLeakyRelu0[id] = ((tensor_denseBiasAdd0[id] >= 0 )? tensor_denseBiasAdd0[id] : op_1_alpha * tensor_denseBiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropoutIdentity0 = tensor_leakyreluLeakyRelu0;

//--------- Gemm
   char op_3_transA = 'n';
   char op_3_transB = 'n';
   int op_3_m = 1;
   int op_3_n = 200;
   int op_3_k = 200;
   float op_3_alpha = 1;
   float op_3_beta = 1;
   int op_3_lda = 200;
   int op_3_ldb = 200;
   std::copy(tensor_dense1bias0bcast, tensor_dense1bias0bcast + 200, tensor_dense1BiasAdd0);
   BLAS::sgemm_(&op_3_transB, &op_3_transA, &op_3_n, &op_3_m, &op_3_k, &op_3_alpha, tensor_dense1kernel0, &op_3_ldb, tensor_dropoutIdentity0, &op_3_lda, &op_3_beta, tensor_dense1BiasAdd0, &op_3_n);
   float op_4_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 200 ; id++){
      tensor_leakyrelu1LeakyRelu0[id] = ((tensor_dense1BiasAdd0[id] >= 0 )? tensor_dense1BiasAdd0[id] : op_4_alpha * tensor_dense1BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout1Identity0 = tensor_leakyrelu1LeakyRelu0;

//--------- Gemm
   char op_6_transA = 'n';
   char op_6_transB = 'n';
   int op_6_m = 1;
   int op_6_n = 200;
   int op_6_k = 200;
   float op_6_alpha = 1;
   float op_6_beta = 1;
   int op_6_lda = 200;
   int op_6_ldb = 200;
   std::copy(tensor_dense2bias0bcast, tensor_dense2bias0bcast + 200, tensor_dense2BiasAdd0);
   BLAS::sgemm_(&op_6_transB, &op_6_transA, &op_6_n, &op_6_m, &op_6_k, &op_6_alpha, tensor_dense2kernel0, &op_6_ldb, tensor_dropout1Identity0, &op_6_lda, &op_6_beta, tensor_dense2BiasAdd0, &op_6_n);
   constexpr int op_7_N =200;
   constexpr int op_7_incx = 1;
   constexpr int op_7_incy = 1;
   BLAS::scopy_(&op_7_N, tensor_dense2BiasAdd0, &op_7_incx,tensor_batchnormalizationbatchnormadd10, &op_7_incy);

   float op_7_alpha = -1;
   BLAS::saxpy_(&op_7_N, &op_7_alpha, tensor_batchnormalizationmovingmean0, &op_7_incx,tensor_batchnormalizationbatchnormadd10, &op_7_incy);

    for (size_t i = 0; i < 200; i++) {
      tensor_batchnormalizationbatchnormadd10[i] *= tensor_batchnormalizationgamma0[i] * tensor_batchnormalizationmovingvariance0[i]; 
   }
   op_7_alpha = 1;
   BLAS::saxpy_(&op_7_N, &op_7_alpha, tensor_batchnormalizationbeta0, &op_7_incx, tensor_batchnormalizationbatchnormadd10, &op_7_incy);

   float op_8_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 200 ; id++){
      tensor_leakyrelu2LeakyRelu0[id] = ((tensor_batchnormalizationbatchnormadd10[id] >= 0 )? tensor_batchnormalizationbatchnormadd10[id] : op_8_alpha * tensor_batchnormalizationbatchnormadd10[id]);
   }

//------ IDENTITY
      tensor_dropout2Identity0 = tensor_leakyrelu2LeakyRelu0;

//--------- Gemm
   char op_10_transA = 'n';
   char op_10_transB = 'n';
   int op_10_m = 1;
   int op_10_n = 200;
   int op_10_k = 200;
   float op_10_alpha = 1;
   float op_10_beta = 1;
   int op_10_lda = 200;
   int op_10_ldb = 200;
   std::copy(tensor_dense3bias0bcast, tensor_dense3bias0bcast + 200, tensor_dense3BiasAdd0);
   BLAS::sgemm_(&op_10_transB, &op_10_transA, &op_10_n, &op_10_m, &op_10_k, &op_10_alpha, tensor_dense3kernel0, &op_10_ldb, tensor_dropout2Identity0, &op_10_lda, &op_10_beta, tensor_dense3BiasAdd0, &op_10_n);
   float op_11_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 200 ; id++){
      tensor_leakyrelu3LeakyRelu0[id] = ((tensor_dense3BiasAdd0[id] >= 0 )? tensor_dense3BiasAdd0[id] : op_11_alpha * tensor_dense3BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout3Identity0 = tensor_leakyrelu3LeakyRelu0;

//--------- Gemm
   char op_13_transA = 'n';
   char op_13_transB = 'n';
   int op_13_m = 1;
   int op_13_n = 200;
   int op_13_k = 200;
   float op_13_alpha = 1;
   float op_13_beta = 1;
   int op_13_lda = 200;
   int op_13_ldb = 200;
   std::copy(tensor_dense4bias0bcast, tensor_dense4bias0bcast + 200, tensor_dense4BiasAdd0);
   BLAS::sgemm_(&op_13_transB, &op_13_transA, &op_13_n, &op_13_m, &op_13_k, &op_13_alpha, tensor_dense4kernel0, &op_13_ldb, tensor_dropout3Identity0, &op_13_lda, &op_13_beta, tensor_dense4BiasAdd0, &op_13_n);
   float op_14_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 200 ; id++){
      tensor_leakyrelu4LeakyRelu0[id] = ((tensor_dense4BiasAdd0[id] >= 0 )? tensor_dense4BiasAdd0[id] : op_14_alpha * tensor_dense4BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout4Identity0 = tensor_leakyrelu4LeakyRelu0;

//--------- Gemm
   char op_16_transA = 'n';
   char op_16_transB = 'n';
   int op_16_m = 1;
   int op_16_n = 200;
   int op_16_k = 200;
   float op_16_alpha = 1;
   float op_16_beta = 1;
   int op_16_lda = 200;
   int op_16_ldb = 200;
   std::copy(tensor_dense5bias0bcast, tensor_dense5bias0bcast + 200, tensor_dense5BiasAdd0);
   BLAS::sgemm_(&op_16_transB, &op_16_transA, &op_16_n, &op_16_m, &op_16_k, &op_16_alpha, tensor_dense5kernel0, &op_16_ldb, tensor_dropout4Identity0, &op_16_lda, &op_16_beta, tensor_dense5BiasAdd0, &op_16_n);
   constexpr int op_17_N =200;
   constexpr int op_17_incx = 1;
   constexpr int op_17_incy = 1;
   BLAS::scopy_(&op_17_N, tensor_dense5BiasAdd0, &op_17_incx,tensor_batchnormalization1batchnormadd10, &op_17_incy);

   float op_17_alpha = -1;
   BLAS::saxpy_(&op_17_N, &op_17_alpha, tensor_batchnormalization1movingmean0, &op_17_incx,tensor_batchnormalization1batchnormadd10, &op_17_incy);

    for (size_t i = 0; i < 200; i++) {
      tensor_batchnormalization1batchnormadd10[i] *= tensor_batchnormalization1gamma0[i] * tensor_batchnormalization1movingvariance0[i]; 
   }
   op_17_alpha = 1;
   BLAS::saxpy_(&op_17_N, &op_17_alpha, tensor_batchnormalization1beta0, &op_17_incx, tensor_batchnormalization1batchnormadd10, &op_17_incy);

   float op_18_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 200 ; id++){
      tensor_leakyrelu5LeakyRelu0[id] = ((tensor_batchnormalization1batchnormadd10[id] >= 0 )? tensor_batchnormalization1batchnormadd10[id] : op_18_alpha * tensor_batchnormalization1batchnormadd10[id]);
   }

//------ IDENTITY
      tensor_dropout5Identity0 = tensor_leakyrelu5LeakyRelu0;

//--------- Gemm
   char op_20_transA = 'n';
   char op_20_transB = 'n';
   int op_20_m = 1;
   int op_20_n = 200;
   int op_20_k = 200;
   float op_20_alpha = 1;
   float op_20_beta = 1;
   int op_20_lda = 200;
   int op_20_ldb = 200;
   std::copy(tensor_dense6bias0bcast, tensor_dense6bias0bcast + 200, tensor_dense6BiasAdd0);
   BLAS::sgemm_(&op_20_transB, &op_20_transA, &op_20_n, &op_20_m, &op_20_k, &op_20_alpha, tensor_dense6kernel0, &op_20_ldb, tensor_dropout5Identity0, &op_20_lda, &op_20_beta, tensor_dense6BiasAdd0, &op_20_n);
   float op_21_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 200 ; id++){
      tensor_leakyrelu6LeakyRelu0[id] = ((tensor_dense6BiasAdd0[id] >= 0 )? tensor_dense6BiasAdd0[id] : op_21_alpha * tensor_dense6BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout6Identity0 = tensor_leakyrelu6LeakyRelu0;

//--------- Gemm
   char op_23_transA = 'n';
   char op_23_transB = 'n';
   int op_23_m = 1;
   int op_23_n = 200;
   int op_23_k = 200;
   float op_23_alpha = 1;
   float op_23_beta = 1;
   int op_23_lda = 200;
   int op_23_ldb = 200;
   std::copy(tensor_dense7bias0bcast, tensor_dense7bias0bcast + 200, tensor_dense7BiasAdd0);
   BLAS::sgemm_(&op_23_transB, &op_23_transA, &op_23_n, &op_23_m, &op_23_k, &op_23_alpha, tensor_dense7kernel0, &op_23_ldb, tensor_dropout6Identity0, &op_23_lda, &op_23_beta, tensor_dense7BiasAdd0, &op_23_n);
   float op_24_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 200 ; id++){
      tensor_leakyrelu7LeakyRelu0[id] = ((tensor_dense7BiasAdd0[id] >= 0 )? tensor_dense7BiasAdd0[id] : op_24_alpha * tensor_dense7BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout7Identity0 = tensor_leakyrelu7LeakyRelu0;

//--------- Gemm
   char op_26_transA = 'n';
   char op_26_transB = 'n';
   int op_26_m = 1;
   int op_26_n = 200;
   int op_26_k = 200;
   float op_26_alpha = 1;
   float op_26_beta = 1;
   int op_26_lda = 200;
   int op_26_ldb = 200;
   std::copy(tensor_dense8bias0bcast, tensor_dense8bias0bcast + 200, tensor_dense8BiasAdd0);
   BLAS::sgemm_(&op_26_transB, &op_26_transA, &op_26_n, &op_26_m, &op_26_k, &op_26_alpha, tensor_dense8kernel0, &op_26_ldb, tensor_dropout7Identity0, &op_26_lda, &op_26_beta, tensor_dense8BiasAdd0, &op_26_n);
   constexpr int op_27_N =200;
   constexpr int op_27_incx = 1;
   constexpr int op_27_incy = 1;
   BLAS::scopy_(&op_27_N, tensor_dense8BiasAdd0, &op_27_incx,tensor_batchnormalization2batchnormadd10, &op_27_incy);

   float op_27_alpha = -1;
   BLAS::saxpy_(&op_27_N, &op_27_alpha, tensor_batchnormalization2movingmean0, &op_27_incx,tensor_batchnormalization2batchnormadd10, &op_27_incy);

    for (size_t i = 0; i < 200; i++) {
      tensor_batchnormalization2batchnormadd10[i] *= tensor_batchnormalization2gamma0[i] * tensor_batchnormalization2movingvariance0[i]; 
   }
   op_27_alpha = 1;
   BLAS::saxpy_(&op_27_N, &op_27_alpha, tensor_batchnormalization2beta0, &op_27_incx, tensor_batchnormalization2batchnormadd10, &op_27_incy);

   float op_28_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 200 ; id++){
      tensor_leakyrelu8LeakyRelu0[id] = ((tensor_batchnormalization2batchnormadd10[id] >= 0 )? tensor_batchnormalization2batchnormadd10[id] : op_28_alpha * tensor_batchnormalization2batchnormadd10[id]);
   }

//------ IDENTITY
      tensor_dropout8Identity0 = tensor_leakyrelu8LeakyRelu0;

//--------- Gemm
   char op_30_transA = 'n';
   char op_30_transB = 'n';
   int op_30_m = 1;
   int op_30_n = 200;
   int op_30_k = 200;
   float op_30_alpha = 1;
   float op_30_beta = 1;
   int op_30_lda = 200;
   int op_30_ldb = 200;
   std::copy(tensor_dense9bias0bcast, tensor_dense9bias0bcast + 200, tensor_dense9BiasAdd0);
   BLAS::sgemm_(&op_30_transB, &op_30_transA, &op_30_n, &op_30_m, &op_30_k, &op_30_alpha, tensor_dense9kernel0, &op_30_ldb, tensor_dropout8Identity0, &op_30_lda, &op_30_beta, tensor_dense9BiasAdd0, &op_30_n);
   float op_31_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 200 ; id++){
      tensor_leakyrelu9LeakyRelu0[id] = ((tensor_dense9BiasAdd0[id] >= 0 )? tensor_dense9BiasAdd0[id] : op_31_alpha * tensor_dense9BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout9Identity0 = tensor_leakyrelu9LeakyRelu0;

//--------- Gemm
   char op_33_transA = 'n';
   char op_33_transB = 'n';
   int op_33_m = 1;
   int op_33_n = 200;
   int op_33_k = 200;
   float op_33_alpha = 1;
   float op_33_beta = 1;
   int op_33_lda = 200;
   int op_33_ldb = 200;
   std::copy(tensor_dense10bias0bcast, tensor_dense10bias0bcast + 200, tensor_dense10BiasAdd0);
   BLAS::sgemm_(&op_33_transB, &op_33_transA, &op_33_n, &op_33_m, &op_33_k, &op_33_alpha, tensor_dense10kernel0, &op_33_ldb, tensor_dropout9Identity0, &op_33_lda, &op_33_beta, tensor_dense10BiasAdd0, &op_33_n);
   float op_34_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 200 ; id++){
      tensor_leakyrelu10LeakyRelu0[id] = ((tensor_dense10BiasAdd0[id] >= 0 )? tensor_dense10BiasAdd0[id] : op_34_alpha * tensor_dense10BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout10Identity0 = tensor_leakyrelu10LeakyRelu0;

//--------- Gemm
   char op_36_transA = 'n';
   char op_36_transB = 'n';
   int op_36_m = 1;
   int op_36_n = 200;
   int op_36_k = 200;
   float op_36_alpha = 1;
   float op_36_beta = 1;
   int op_36_lda = 200;
   int op_36_ldb = 200;
   std::copy(tensor_dense11bias0bcast, tensor_dense11bias0bcast + 200, tensor_dense11BiasAdd0);
   BLAS::sgemm_(&op_36_transB, &op_36_transA, &op_36_n, &op_36_m, &op_36_k, &op_36_alpha, tensor_dense11kernel0, &op_36_ldb, tensor_dropout10Identity0, &op_36_lda, &op_36_beta, tensor_dense11BiasAdd0, &op_36_n);
   constexpr int op_37_N =200;
   constexpr int op_37_incx = 1;
   constexpr int op_37_incy = 1;
   BLAS::scopy_(&op_37_N, tensor_dense11BiasAdd0, &op_37_incx,tensor_batchnormalization3batchnormadd10, &op_37_incy);

   float op_37_alpha = -1;
   BLAS::saxpy_(&op_37_N, &op_37_alpha, tensor_batchnormalization3movingmean0, &op_37_incx,tensor_batchnormalization3batchnormadd10, &op_37_incy);

    for (size_t i = 0; i < 200; i++) {
      tensor_batchnormalization3batchnormadd10[i] *= tensor_batchnormalization3gamma0[i] * tensor_batchnormalization3movingvariance0[i]; 
   }
   op_37_alpha = 1;
   BLAS::saxpy_(&op_37_N, &op_37_alpha, tensor_batchnormalization3beta0, &op_37_incx, tensor_batchnormalization3batchnormadd10, &op_37_incy);

   float op_38_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 200 ; id++){
      tensor_leakyrelu11LeakyRelu0[id] = ((tensor_batchnormalization3batchnormadd10[id] >= 0 )? tensor_batchnormalization3batchnormadd10[id] : op_38_alpha * tensor_batchnormalization3batchnormadd10[id]);
   }

//------ IDENTITY
      tensor_dropout11Identity0 = tensor_leakyrelu11LeakyRelu0;

//--------- Gemm
   char op_40_transA = 'n';
   char op_40_transB = 'n';
   int op_40_m = 1;
   int op_40_n = 200;
   int op_40_k = 200;
   float op_40_alpha = 1;
   float op_40_beta = 1;
   int op_40_lda = 200;
   int op_40_ldb = 200;
   std::copy(tensor_dense12bias0bcast, tensor_dense12bias0bcast + 200, tensor_dense12BiasAdd0);
   BLAS::sgemm_(&op_40_transB, &op_40_transA, &op_40_n, &op_40_m, &op_40_k, &op_40_alpha, tensor_dense12kernel0, &op_40_ldb, tensor_dropout11Identity0, &op_40_lda, &op_40_beta, tensor_dense12BiasAdd0, &op_40_n);
   float op_41_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 200 ; id++){
      tensor_leakyrelu12LeakyRelu0[id] = ((tensor_dense12BiasAdd0[id] >= 0 )? tensor_dense12BiasAdd0[id] : op_41_alpha * tensor_dense12BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout12Identity0 = tensor_leakyrelu12LeakyRelu0;

//--------- Gemm
   char op_43_transA = 'n';
   char op_43_transB = 'n';
   int op_43_m = 1;
   int op_43_n = 1;
   int op_43_k = 200;
   float op_43_alpha = 1;
   float op_43_beta = 1;
   int op_43_lda = 200;
   int op_43_ldb = 1;
   std::copy(tensor_dense13bias0bcast, tensor_dense13bias0bcast + 1, tensor_dense13Dense);
   BLAS::sgemm_(&op_43_transB, &op_43_transA, &op_43_n, &op_43_m, &op_43_k, &op_43_alpha, tensor_dense13kernel0, &op_43_ldb, tensor_dropout12Identity0, &op_43_lda, &op_43_beta, tensor_dense13Dense, &op_43_n);
	for (int id = 0; id < 1 ; id++){
		tensor_dense13Sigmoid0[id] = 1 / (1 + std::exp( - tensor_dense13Dense[id]));
	}
   std::vector<float> ret (tensor_dense13Sigmoid0, tensor_dense13Sigmoid0 + 1);
   return ret;
}
};
} //TMVA_SOFIE_testmodel

#endif  // TMVA_SOFIE_TESTMODEL
