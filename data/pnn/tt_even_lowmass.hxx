//Code generated automatically by TMVA for Inference of Model file [tt_even_lowmass.h5] at [Thu Feb 22 08:31:53 2024] 

#ifndef TMVA_SOFIE_TT_EVEN_LOWMASS
#define TMVA_SOFIE_TT_EVEN_LOWMASS

#include<algorithm>
#include<cmath>
#include<vector>
#include "TMVA/SOFIE_common.hxx"
#include <fstream>

namespace TMVA_SOFIE_tt_even_lowmass{
namespace BLAS{
	extern "C" void sgemv_(const char * trans, const int * m, const int * n, const float * alpha, const float * A,
	                       const int * lda, const float * X, const int * incx, const float * beta, const float * Y, const int * incy);
	extern "C" void sgemm_(const char * transa, const char * transb, const int * m, const int * n, const int * k,
	                       const float * alpha, const float * A, const int * lda, const float * B, const int * ldb,
	                       const float * beta, float * C, const int * ldc);
}//BLAS
struct Session {
std::vector<float> fTensor_dense2bias0 = std::vector<float>(1);
float * tensor_dense2bias0 = fTensor_dense2bias0.data();
std::vector<float> fTensor_dense2kernel0 = std::vector<float>(1000);
float * tensor_dense2kernel0 = fTensor_dense2kernel0.data();
std::vector<float> fTensor_dense1bias0 = std::vector<float>(1000);
float * tensor_dense1bias0 = fTensor_dense1bias0.data();
std::vector<float> fTensor_dense1kernel0 = std::vector<float>(1000000);
float * tensor_dense1kernel0 = fTensor_dense1kernel0.data();
std::vector<float> fTensor_densebias0 = std::vector<float>(1000);
float * tensor_densebias0 = fTensor_densebias0.data();
std::vector<float> fTensor_densekernel0 = std::vector<float>(26000);
float * tensor_densekernel0 = fTensor_densekernel0.data();
std::vector<float> fTensor_dense2Dense = std::vector<float>(1);
float * tensor_dense2Dense = fTensor_dense2Dense.data();
std::vector<float> fTensor_dense2Sigmoid0 = std::vector<float>(1);
float * tensor_dense2Sigmoid0 = fTensor_dense2Sigmoid0.data();
std::vector<float> fTensor_dropout1Identity0 = std::vector<float>(1000);
float * tensor_dropout1Identity0 = fTensor_dropout1Identity0.data();
std::vector<float> fTensor_dense1BiasAdd0 = std::vector<float>(1000);
float * tensor_dense1BiasAdd0 = fTensor_dense1BiasAdd0.data();
std::vector<float> fTensor_dense1bias0bcast = std::vector<float>(1000);
float * tensor_dense1bias0bcast = fTensor_dense1bias0bcast.data();
std::vector<float> fTensor_leakyrelu1LeakyRelu0 = std::vector<float>(1000);
float * tensor_leakyrelu1LeakyRelu0 = fTensor_leakyrelu1LeakyRelu0.data();
std::vector<float> fTensor_dropoutIdentity0 = std::vector<float>(1000);
float * tensor_dropoutIdentity0 = fTensor_dropoutIdentity0.data();
std::vector<float> fTensor_leakyreluLeakyRelu0 = std::vector<float>(1000);
float * tensor_leakyreluLeakyRelu0 = fTensor_leakyreluLeakyRelu0.data();
std::vector<float> fTensor_denseBiasAdd0 = std::vector<float>(1000);
float * tensor_denseBiasAdd0 = fTensor_denseBiasAdd0.data();
std::vector<float> fTensor_dense2bias0bcast = std::vector<float>(1);
float * tensor_dense2bias0bcast = fTensor_dense2bias0bcast.data();
std::vector<float> fTensor_densebias0bcast = std::vector<float>(1000);
float * tensor_densebias0bcast = fTensor_densebias0bcast.data();


Session(std::string filename ="") {
   if (filename.empty()) filename = "tt_even_lowmass.dat";
   std::ifstream f;
   f.open(filename);
   if (!f.is_open()){
      throw std::runtime_error("tmva-sofie failed to open file for input weights");
   }
   std::string tensor_name;
   int length;
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense2bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense2bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 1) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 1 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense2bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense2kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense2kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 1000) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 1000 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense2kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense1bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense1bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 1000) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 1000 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense1bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense1kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense1kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 1000000) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 1000000 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense1kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_densebias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_densebias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 1000) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 1000 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_densebias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_densekernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_densekernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 26000) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 26000 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_densekernel0[i];
   f.close();
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_densebias0,{ 1000 }, { 1 , 1000 });
      std::copy(data, data + 1000, tensor_densebias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense1bias0,{ 1000 }, { 1 , 1000 });
      std::copy(data, data + 1000, tensor_dense1bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense2bias0,{ 1 }, { 1 , 1 });
      std::copy(data, data + 1, tensor_dense2bias0bcast);
      delete [] data;
   }
}

std::vector<float> infer(float* tensor_input1){

//--------- Gemm
   char op_0_transA = 'n';
   char op_0_transB = 'n';
   int op_0_m = 1;
   int op_0_n = 1000;
   int op_0_k = 26;
   float op_0_alpha = 1;
   float op_0_beta = 1;
   int op_0_lda = 26;
   int op_0_ldb = 1000;
   std::copy(tensor_densebias0bcast, tensor_densebias0bcast + 1000, tensor_denseBiasAdd0);
   BLAS::sgemm_(&op_0_transB, &op_0_transA, &op_0_n, &op_0_m, &op_0_k, &op_0_alpha, tensor_densekernel0, &op_0_ldb, tensor_input1, &op_0_lda, &op_0_beta, tensor_denseBiasAdd0, &op_0_n);
   float op_1_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 1000 ; id++){
      tensor_leakyreluLeakyRelu0[id] = ((tensor_denseBiasAdd0[id] >= 0 )? tensor_denseBiasAdd0[id] : op_1_alpha * tensor_denseBiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropoutIdentity0 = tensor_leakyreluLeakyRelu0;

//--------- Gemm
   char op_3_transA = 'n';
   char op_3_transB = 'n';
   int op_3_m = 1;
   int op_3_n = 1000;
   int op_3_k = 1000;
   float op_3_alpha = 1;
   float op_3_beta = 1;
   int op_3_lda = 1000;
   int op_3_ldb = 1000;
   std::copy(tensor_dense1bias0bcast, tensor_dense1bias0bcast + 1000, tensor_dense1BiasAdd0);
   BLAS::sgemm_(&op_3_transB, &op_3_transA, &op_3_n, &op_3_m, &op_3_k, &op_3_alpha, tensor_dense1kernel0, &op_3_ldb, tensor_dropoutIdentity0, &op_3_lda, &op_3_beta, tensor_dense1BiasAdd0, &op_3_n);
   float op_4_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 1000 ; id++){
      tensor_leakyrelu1LeakyRelu0[id] = ((tensor_dense1BiasAdd0[id] >= 0 )? tensor_dense1BiasAdd0[id] : op_4_alpha * tensor_dense1BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout1Identity0 = tensor_leakyrelu1LeakyRelu0;

//--------- Gemm
   char op_6_transA = 'n';
   char op_6_transB = 'n';
   int op_6_m = 1;
   int op_6_n = 1;
   int op_6_k = 1000;
   float op_6_alpha = 1;
   float op_6_beta = 1;
   int op_6_lda = 1000;
   int op_6_ldb = 1;
   std::copy(tensor_dense2bias0bcast, tensor_dense2bias0bcast + 1, tensor_dense2Dense);
   BLAS::sgemm_(&op_6_transB, &op_6_transA, &op_6_n, &op_6_m, &op_6_k, &op_6_alpha, tensor_dense2kernel0, &op_6_ldb, tensor_dropout1Identity0, &op_6_lda, &op_6_beta, tensor_dense2Dense, &op_6_n);
	for (int id = 0; id < 1 ; id++){
		tensor_dense2Sigmoid0[id] = 1 / (1 + std::exp( - tensor_dense2Dense[id]));
	}
   std::vector<float> ret (tensor_dense2Sigmoid0, tensor_dense2Sigmoid0 + 1);
   return ret;
}
};
} //TMVA_SOFIE_tt_even_lowmass

#endif  // TMVA_SOFIE_TT_EVEN_LOWMASS
