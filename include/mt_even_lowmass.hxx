//Code generated automatically by TMVA for Inference of Model file [mt_even_lowmass.h5] at [Fri Nov 24 04:37:59 2023] 

#ifndef TMVA_SOFIE_MT_EVEN_LOWMASS
#define TMVA_SOFIE_MT_EVEN_LOWMASS

#include<algorithm>
#include<cmath>
#include<vector>
#include "TMVA/SOFIE_common.hxx"
#include <fstream>

namespace TMVA_SOFIE_mt_even_lowmass{
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
std::vector<float> fTensor_dense22kernel0 = std::vector<float>(150);
float * tensor_dense22kernel0 = fTensor_dense22kernel0.data();
std::vector<float> fTensor_batchnormalization6movingvariance0 = std::vector<float>(150);
float * tensor_batchnormalization6movingvariance0 = fTensor_batchnormalization6movingvariance0.data();
std::vector<float> fTensor_dense21bias0 = std::vector<float>(150);
float * tensor_dense21bias0 = fTensor_dense21bias0.data();
std::vector<float> fTensor_batchnormalization6movingmean0 = std::vector<float>(150);
float * tensor_batchnormalization6movingmean0 = fTensor_batchnormalization6movingmean0.data();
std::vector<float> fTensor_batchnormalization6beta0 = std::vector<float>(150);
float * tensor_batchnormalization6beta0 = fTensor_batchnormalization6beta0.data();
std::vector<float> fTensor_dense20bias0 = std::vector<float>(150);
float * tensor_dense20bias0 = fTensor_dense20bias0.data();
std::vector<float> fTensor_dense20kernel0 = std::vector<float>(22500);
float * tensor_dense20kernel0 = fTensor_dense20kernel0.data();
std::vector<float> fTensor_dense19bias0 = std::vector<float>(150);
float * tensor_dense19bias0 = fTensor_dense19bias0.data();
std::vector<float> fTensor_dense18bias0 = std::vector<float>(150);
float * tensor_dense18bias0 = fTensor_dense18bias0.data();
std::vector<float> fTensor_batchnormalization5movingvariance0 = std::vector<float>(150);
float * tensor_batchnormalization5movingvariance0 = fTensor_batchnormalization5movingvariance0.data();
std::vector<float> fTensor_dense9bias0 = std::vector<float>(150);
float * tensor_dense9bias0 = fTensor_dense9bias0.data();
std::vector<float> fTensor_dense7kernel0 = std::vector<float>(22500);
float * tensor_dense7kernel0 = fTensor_dense7kernel0.data();
std::vector<float> fTensor_dense6kernel0 = std::vector<float>(22500);
float * tensor_dense6kernel0 = fTensor_dense6kernel0.data();
std::vector<float> fTensor_batchnormalization1movingvariance0 = std::vector<float>(150);
float * tensor_batchnormalization1movingvariance0 = fTensor_batchnormalization1movingvariance0.data();
std::vector<float> fTensor_dense18kernel0 = std::vector<float>(22500);
float * tensor_dense18kernel0 = fTensor_dense18kernel0.data();
std::vector<float> fTensor_batchnormalization1movingmean0 = std::vector<float>(150);
float * tensor_batchnormalization1movingmean0 = fTensor_batchnormalization1movingmean0.data();
std::vector<float> fTensor_dense5bias0 = std::vector<float>(150);
float * tensor_dense5bias0 = fTensor_dense5bias0.data();
std::vector<float> fTensor_dense21kernel0 = std::vector<float>(22500);
float * tensor_dense21kernel0 = fTensor_dense21kernel0.data();
std::vector<float> fTensor_batchnormalization2movingmean0 = std::vector<float>(150);
float * tensor_batchnormalization2movingmean0 = fTensor_batchnormalization2movingmean0.data();
std::vector<float> fTensor_dense15kernel0 = std::vector<float>(22500);
float * tensor_dense15kernel0 = fTensor_dense15kernel0.data();
std::vector<float> fTensor_dense4bias0 = std::vector<float>(150);
float * tensor_dense4bias0 = fTensor_dense4bias0.data();
std::vector<float> fTensor_batchnormalization2beta0 = std::vector<float>(150);
float * tensor_batchnormalization2beta0 = fTensor_batchnormalization2beta0.data();
std::vector<float> fTensor_dense7bias0 = std::vector<float>(150);
float * tensor_dense7bias0 = fTensor_dense7bias0.data();
std::vector<float> fTensor_dense1kernel0 = std::vector<float>(22500);
float * tensor_dense1kernel0 = fTensor_dense1kernel0.data();
std::vector<float> fTensor_dense1bias0 = std::vector<float>(150);
float * tensor_dense1bias0 = fTensor_dense1bias0.data();
std::vector<float> fTensor_dense2kernel0 = std::vector<float>(22500);
float * tensor_dense2kernel0 = fTensor_dense2kernel0.data();
std::vector<float> fTensor_batchnormalization3beta0 = std::vector<float>(150);
float * tensor_batchnormalization3beta0 = fTensor_batchnormalization3beta0.data();
std::vector<float> fTensor_dense15bias0 = std::vector<float>(150);
float * tensor_dense15bias0 = fTensor_dense15bias0.data();
std::vector<float> fTensor_batchnormalization1gamma0 = std::vector<float>(150);
float * tensor_batchnormalization1gamma0 = fTensor_batchnormalization1gamma0.data();
std::vector<float> fTensor_batchnormalizationmovingvariance0 = std::vector<float>(150);
float * tensor_batchnormalizationmovingvariance0 = fTensor_batchnormalizationmovingvariance0.data();
std::vector<float> fTensor_dense13bias0 = std::vector<float>(150);
float * tensor_dense13bias0 = fTensor_dense13bias0.data();
std::vector<float> fTensor_batchnormalizationgamma0 = std::vector<float>(150);
float * tensor_batchnormalizationgamma0 = fTensor_batchnormalizationgamma0.data();
std::vector<float> fTensor_batchnormalization2gamma0 = std::vector<float>(150);
float * tensor_batchnormalization2gamma0 = fTensor_batchnormalization2gamma0.data();
std::vector<float> fTensor_batchnormalizationbeta0 = std::vector<float>(150);
float * tensor_batchnormalizationbeta0 = fTensor_batchnormalizationbeta0.data();
std::vector<float> fTensor_batchnormalization5movingmean0 = std::vector<float>(150);
float * tensor_batchnormalization5movingmean0 = fTensor_batchnormalization5movingmean0.data();
std::vector<float> fTensor_dense8bias0 = std::vector<float>(150);
float * tensor_dense8bias0 = fTensor_dense8bias0.data();
std::vector<float> fTensor_dense16kernel0 = std::vector<float>(22500);
float * tensor_dense16kernel0 = fTensor_dense16kernel0.data();
std::vector<float> fTensor_dense5kernel0 = std::vector<float>(22500);
float * tensor_dense5kernel0 = fTensor_dense5kernel0.data();
std::vector<float> fTensor_dense8kernel0 = std::vector<float>(22500);
float * tensor_dense8kernel0 = fTensor_dense8kernel0.data();
std::vector<float> fTensor_densekernel0 = std::vector<float>(3900);
float * tensor_densekernel0 = fTensor_densekernel0.data();
std::vector<float> fTensor_dense2bias0 = std::vector<float>(150);
float * tensor_dense2bias0 = fTensor_dense2bias0.data();
std::vector<float> fTensor_dense3bias0 = std::vector<float>(150);
float * tensor_dense3bias0 = fTensor_dense3bias0.data();
std::vector<float> fTensor_batchnormalizationmovingmean0 = std::vector<float>(150);
float * tensor_batchnormalizationmovingmean0 = fTensor_batchnormalizationmovingmean0.data();
std::vector<float> fTensor_dense3kernel0 = std::vector<float>(22500);
float * tensor_dense3kernel0 = fTensor_dense3kernel0.data();
std::vector<float> fTensor_batchnormalization2movingvariance0 = std::vector<float>(150);
float * tensor_batchnormalization2movingvariance0 = fTensor_batchnormalization2movingvariance0.data();
std::vector<float> fTensor_batchnormalization4movingvariance0 = std::vector<float>(150);
float * tensor_batchnormalization4movingvariance0 = fTensor_batchnormalization4movingvariance0.data();
std::vector<float> fTensor_dense9kernel0 = std::vector<float>(22500);
float * tensor_dense9kernel0 = fTensor_dense9kernel0.data();
std::vector<float> fTensor_dense14kernel0 = std::vector<float>(22500);
float * tensor_dense14kernel0 = fTensor_dense14kernel0.data();
std::vector<float> fTensor_dense17kernel0 = std::vector<float>(22500);
float * tensor_dense17kernel0 = fTensor_dense17kernel0.data();
std::vector<float> fTensor_dense10kernel0 = std::vector<float>(22500);
float * tensor_dense10kernel0 = fTensor_dense10kernel0.data();
std::vector<float> fTensor_batchnormalization4gamma0 = std::vector<float>(150);
float * tensor_batchnormalization4gamma0 = fTensor_batchnormalization4gamma0.data();
std::vector<float> fTensor_dense11kernel0 = std::vector<float>(22500);
float * tensor_dense11kernel0 = fTensor_dense11kernel0.data();
std::vector<float> fTensor_dense11bias0 = std::vector<float>(150);
float * tensor_dense11bias0 = fTensor_dense11bias0.data();
std::vector<float> fTensor_batchnormalization3movingvariance0 = std::vector<float>(150);
float * tensor_batchnormalization3movingvariance0 = fTensor_batchnormalization3movingvariance0.data();
std::vector<float> fTensor_batchnormalization3gamma0 = std::vector<float>(150);
float * tensor_batchnormalization3gamma0 = fTensor_batchnormalization3gamma0.data();
std::vector<float> fTensor_dense22bias0 = std::vector<float>(1);
float * tensor_dense22bias0 = fTensor_dense22bias0.data();
std::vector<float> fTensor_densebias0 = std::vector<float>(150);
float * tensor_densebias0 = fTensor_densebias0.data();
std::vector<float> fTensor_dense12bias0 = std::vector<float>(150);
float * tensor_dense12bias0 = fTensor_dense12bias0.data();
std::vector<float> fTensor_batchnormalization3movingmean0 = std::vector<float>(150);
float * tensor_batchnormalization3movingmean0 = fTensor_batchnormalization3movingmean0.data();
std::vector<float> fTensor_dense13kernel0 = std::vector<float>(22500);
float * tensor_dense13kernel0 = fTensor_dense13kernel0.data();
std::vector<float> fTensor_dense12kernel0 = std::vector<float>(22500);
float * tensor_dense12kernel0 = fTensor_dense12kernel0.data();
std::vector<float> fTensor_dense14bias0 = std::vector<float>(150);
float * tensor_dense14bias0 = fTensor_dense14bias0.data();
std::vector<float> fTensor_batchnormalization4beta0 = std::vector<float>(150);
float * tensor_batchnormalization4beta0 = fTensor_batchnormalization4beta0.data();
std::vector<float> fTensor_batchnormalization6gamma0 = std::vector<float>(150);
float * tensor_batchnormalization6gamma0 = fTensor_batchnormalization6gamma0.data();
std::vector<float> fTensor_batchnormalization4movingmean0 = std::vector<float>(150);
float * tensor_batchnormalization4movingmean0 = fTensor_batchnormalization4movingmean0.data();
std::vector<float> fTensor_dense16bias0 = std::vector<float>(150);
float * tensor_dense16bias0 = fTensor_dense16bias0.data();
std::vector<float> fTensor_batchnormalization1beta0 = std::vector<float>(150);
float * tensor_batchnormalization1beta0 = fTensor_batchnormalization1beta0.data();
std::vector<float> fTensor_dense17bias0 = std::vector<float>(150);
float * tensor_dense17bias0 = fTensor_dense17bias0.data();
std::vector<float> fTensor_dense19kernel0 = std::vector<float>(22500);
float * tensor_dense19kernel0 = fTensor_dense19kernel0.data();
std::vector<float> fTensor_dense4kernel0 = std::vector<float>(22500);
float * tensor_dense4kernel0 = fTensor_dense4kernel0.data();
std::vector<float> fTensor_batchnormalization5beta0 = std::vector<float>(150);
float * tensor_batchnormalization5beta0 = fTensor_batchnormalization5beta0.data();
std::vector<float> fTensor_dense6bias0 = std::vector<float>(150);
float * tensor_dense6bias0 = fTensor_dense6bias0.data();
std::vector<float> fTensor_dense10bias0 = std::vector<float>(150);
float * tensor_dense10bias0 = fTensor_dense10bias0.data();
std::vector<float> fTensor_batchnormalization5gamma0 = std::vector<float>(150);
float * tensor_batchnormalization5gamma0 = fTensor_batchnormalization5gamma0.data();
std::vector<float> fTensor_dense22Dense = std::vector<float>(1);
float * tensor_dense22Dense = fTensor_dense22Dense.data();
std::vector<float> fTensor_dense21BiasAdd0 = std::vector<float>(150);
float * tensor_dense21BiasAdd0 = fTensor_dense21BiasAdd0.data();
std::vector<float> fTensor_dropout20Identity0 = std::vector<float>(150);
float * tensor_dropout20Identity0 = fTensor_dropout20Identity0.data();
std::vector<float> fTensor_leakyrelu20LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu20LeakyRelu0 = fTensor_leakyrelu20LeakyRelu0.data();
std::vector<float> fTensor_leakyrelu19LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu19LeakyRelu0 = fTensor_leakyrelu19LeakyRelu0.data();
std::vector<float> fTensor_dense19bias0bcast = std::vector<float>(150);
float * tensor_dense19bias0bcast = fTensor_dense19bias0bcast.data();
std::vector<float> fTensor_dropout18Identity0 = std::vector<float>(150);
float * tensor_dropout18Identity0 = fTensor_dropout18Identity0.data();
std::vector<float> fTensor_dense21bias0bcast = std::vector<float>(150);
float * tensor_dense21bias0bcast = fTensor_dense21bias0bcast.data();
std::vector<float> fTensor_dense20bias0bcast = std::vector<float>(150);
float * tensor_dense20bias0bcast = fTensor_dense20bias0bcast.data();
std::vector<float> fTensor_leakyrelu18LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu18LeakyRelu0 = fTensor_leakyrelu18LeakyRelu0.data();
std::vector<float> fTensor_dense18BiasAdd0 = std::vector<float>(150);
float * tensor_dense18BiasAdd0 = fTensor_dense18BiasAdd0.data();
std::vector<float> fTensor_batchnormalization5batchnormadd10 = std::vector<float>(150);
float * tensor_batchnormalization5batchnormadd10 = fTensor_batchnormalization5batchnormadd10.data();
std::vector<float> fTensor_leakyrelu17LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu17LeakyRelu0 = fTensor_leakyrelu17LeakyRelu0.data();
std::vector<float> fTensor_dropout16Identity0 = std::vector<float>(150);
float * tensor_dropout16Identity0 = fTensor_dropout16Identity0.data();
std::vector<float> fTensor_dense19BiasAdd0 = std::vector<float>(150);
float * tensor_dense19BiasAdd0 = fTensor_dense19BiasAdd0.data();
std::vector<float> fTensor_leakyrelu16LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu16LeakyRelu0 = fTensor_leakyrelu16LeakyRelu0.data();
std::vector<float> fTensor_dense16bias0bcast = std::vector<float>(150);
float * tensor_dense16bias0bcast = fTensor_dense16bias0bcast.data();
std::vector<float> fTensor_dropout15Identity0 = std::vector<float>(150);
float * tensor_dropout15Identity0 = fTensor_dropout15Identity0.data();
std::vector<float> fTensor_leakyrelu15LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu15LeakyRelu0 = fTensor_leakyrelu15LeakyRelu0.data();
std::vector<float> fTensor_dense15BiasAdd0 = std::vector<float>(150);
float * tensor_dense15BiasAdd0 = fTensor_dense15BiasAdd0.data();
std::vector<float> fTensor_dense15bias0bcast = std::vector<float>(150);
float * tensor_dense15bias0bcast = fTensor_dense15bias0bcast.data();
std::vector<float> fTensor_dropout21Identity0 = std::vector<float>(150);
float * tensor_dropout21Identity0 = fTensor_dropout21Identity0.data();
std::vector<float> fTensor_dense16BiasAdd0 = std::vector<float>(150);
float * tensor_dense16BiasAdd0 = fTensor_dense16BiasAdd0.data();
std::vector<float> fTensor_batchnormalization4batchnormadd10 = std::vector<float>(150);
float * tensor_batchnormalization4batchnormadd10 = fTensor_batchnormalization4batchnormadd10.data();
std::vector<float> fTensor_dense14bias0bcast = std::vector<float>(150);
float * tensor_dense14bias0bcast = fTensor_dense14bias0bcast.data();
std::vector<float> fTensor_dropout5Identity0 = std::vector<float>(150);
float * tensor_dropout5Identity0 = fTensor_dropout5Identity0.data();
std::vector<float> fTensor_dense17bias0bcast = std::vector<float>(150);
float * tensor_dense17bias0bcast = fTensor_dense17bias0bcast.data();
std::vector<float> fTensor_dense13BiasAdd0 = std::vector<float>(150);
float * tensor_dense13BiasAdd0 = fTensor_dense13BiasAdd0.data();
std::vector<float> fTensor_dropout19Identity0 = std::vector<float>(150);
float * tensor_dropout19Identity0 = fTensor_dropout19Identity0.data();
std::vector<float> fTensor_dense5BiasAdd0 = std::vector<float>(150);
float * tensor_dense5BiasAdd0 = fTensor_dense5BiasAdd0.data();
std::vector<float> fTensor_dropout4Identity0 = std::vector<float>(150);
float * tensor_dropout4Identity0 = fTensor_dropout4Identity0.data();
std::vector<float> fTensor_leakyrelu21LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu21LeakyRelu0 = fTensor_leakyrelu21LeakyRelu0.data();
std::vector<float> fTensor_leakyrelu4LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu4LeakyRelu0 = fTensor_leakyrelu4LeakyRelu0.data();
std::vector<float> fTensor_dense6BiasAdd0 = std::vector<float>(150);
float * tensor_dense6BiasAdd0 = fTensor_dense6BiasAdd0.data();
std::vector<float> fTensor_dense17BiasAdd0 = std::vector<float>(150);
float * tensor_dense17BiasAdd0 = fTensor_dense17BiasAdd0.data();
std::vector<float> fTensor_batchnormalization1batchnormadd10 = std::vector<float>(150);
float * tensor_batchnormalization1batchnormadd10 = fTensor_batchnormalization1batchnormadd10.data();
std::vector<float> fTensor_leakyrelu3LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu3LeakyRelu0 = fTensor_leakyrelu3LeakyRelu0.data();
std::vector<float> fTensor_leakyrelu14LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu14LeakyRelu0 = fTensor_leakyrelu14LeakyRelu0.data();
std::vector<float> fTensor_dense14BiasAdd0 = std::vector<float>(150);
float * tensor_dense14BiasAdd0 = fTensor_dense14BiasAdd0.data();
std::vector<float> fTensor_dense3bias0bcast = std::vector<float>(150);
float * tensor_dense3bias0bcast = fTensor_dense3bias0bcast.data();
std::vector<float> fTensor_dense3BiasAdd0 = std::vector<float>(150);
float * tensor_dense3BiasAdd0 = fTensor_dense3BiasAdd0.data();
std::vector<float> fTensor_dropout8Identity0 = std::vector<float>(150);
float * tensor_dropout8Identity0 = fTensor_dropout8Identity0.data();
std::vector<float> fTensor_densebias0bcast = std::vector<float>(150);
float * tensor_densebias0bcast = fTensor_densebias0bcast.data();
std::vector<float> fTensor_dense2bias0bcast = std::vector<float>(150);
float * tensor_dense2bias0bcast = fTensor_dense2bias0bcast.data();
std::vector<float> fTensor_dense12bias0bcast = std::vector<float>(150);
float * tensor_dense12bias0bcast = fTensor_dense12bias0bcast.data();
std::vector<float> fTensor_batchnormalizationbatchnormadd10 = std::vector<float>(150);
float * tensor_batchnormalizationbatchnormadd10 = fTensor_batchnormalizationbatchnormadd10.data();
std::vector<float> fTensor_dropoutIdentity0 = std::vector<float>(150);
float * tensor_dropoutIdentity0 = fTensor_dropoutIdentity0.data();
std::vector<float> fTensor_dense2BiasAdd0 = std::vector<float>(150);
float * tensor_dense2BiasAdd0 = fTensor_dense2BiasAdd0.data();
std::vector<float> fTensor_dense22bias0bcast = std::vector<float>(1);
float * tensor_dense22bias0bcast = fTensor_dense22bias0bcast.data();
std::vector<float> fTensor_dense9bias0bcast = std::vector<float>(150);
float * tensor_dense9bias0bcast = fTensor_dense9bias0bcast.data();
std::vector<float> fTensor_dense13bias0bcast = std::vector<float>(150);
float * tensor_dense13bias0bcast = fTensor_dense13bias0bcast.data();
std::vector<float> fTensor_leakyrelu2LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu2LeakyRelu0 = fTensor_leakyrelu2LeakyRelu0.data();
std::vector<float> fTensor_dense1bias0bcast = std::vector<float>(150);
float * tensor_dense1bias0bcast = fTensor_dense1bias0bcast.data();
std::vector<float> fTensor_dropout13Identity0 = std::vector<float>(150);
float * tensor_dropout13Identity0 = fTensor_dropout13Identity0.data();
std::vector<float> fTensor_leakyrelu6LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu6LeakyRelu0 = fTensor_leakyrelu6LeakyRelu0.data();
std::vector<float> fTensor_dense4BiasAdd0 = std::vector<float>(150);
float * tensor_dense4BiasAdd0 = fTensor_dense4BiasAdd0.data();
std::vector<float> fTensor_dense9BiasAdd0 = std::vector<float>(150);
float * tensor_dense9BiasAdd0 = fTensor_dense9BiasAdd0.data();
std::vector<float> fTensor_dense1BiasAdd0 = std::vector<float>(150);
float * tensor_dense1BiasAdd0 = fTensor_dense1BiasAdd0.data();
std::vector<float> fTensor_dense20BiasAdd0 = std::vector<float>(150);
float * tensor_dense20BiasAdd0 = fTensor_dense20BiasAdd0.data();
std::vector<float> fTensor_dense5bias0bcast = std::vector<float>(150);
float * tensor_dense5bias0bcast = fTensor_dense5bias0bcast.data();
std::vector<float> fTensor_dropout3Identity0 = std::vector<float>(150);
float * tensor_dropout3Identity0 = fTensor_dropout3Identity0.data();
std::vector<float> fTensor_dense4bias0bcast = std::vector<float>(150);
float * tensor_dense4bias0bcast = fTensor_dense4bias0bcast.data();
std::vector<float> fTensor_dense7bias0bcast = std::vector<float>(150);
float * tensor_dense7bias0bcast = fTensor_dense7bias0bcast.data();
std::vector<float> fTensor_dense6bias0bcast = std::vector<float>(150);
float * tensor_dense6bias0bcast = fTensor_dense6bias0bcast.data();
std::vector<float> fTensor_dense12BiasAdd0 = std::vector<float>(150);
float * tensor_dense12BiasAdd0 = fTensor_dense12BiasAdd0.data();
std::vector<float> fTensor_dropout14Identity0 = std::vector<float>(150);
float * tensor_dropout14Identity0 = fTensor_dropout14Identity0.data();
std::vector<float> fTensor_dropout10Identity0 = std::vector<float>(150);
float * tensor_dropout10Identity0 = fTensor_dropout10Identity0.data();
std::vector<float> fTensor_dropout2Identity0 = std::vector<float>(150);
float * tensor_dropout2Identity0 = fTensor_dropout2Identity0.data();
std::vector<float> fTensor_dropout11Identity0 = std::vector<float>(150);
float * tensor_dropout11Identity0 = fTensor_dropout11Identity0.data();
std::vector<float> fTensor_leakyrelu13LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu13LeakyRelu0 = fTensor_leakyrelu13LeakyRelu0.data();
std::vector<float> fTensor_dropout6Identity0 = std::vector<float>(150);
float * tensor_dropout6Identity0 = fTensor_dropout6Identity0.data();
std::vector<float> fTensor_batchnormalization6batchnormadd10 = std::vector<float>(150);
float * tensor_batchnormalization6batchnormadd10 = fTensor_batchnormalization6batchnormadd10.data();
std::vector<float> fTensor_dense7BiasAdd0 = std::vector<float>(150);
float * tensor_dense7BiasAdd0 = fTensor_dense7BiasAdd0.data();
std::vector<float> fTensor_dropout7Identity0 = std::vector<float>(150);
float * tensor_dropout7Identity0 = fTensor_dropout7Identity0.data();
std::vector<float> fTensor_leakyrelu7LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu7LeakyRelu0 = fTensor_leakyrelu7LeakyRelu0.data();
std::vector<float> fTensor_leakyreluLeakyRelu0 = std::vector<float>(150);
float * tensor_leakyreluLeakyRelu0 = fTensor_leakyreluLeakyRelu0.data();
std::vector<float> fTensor_denseBiasAdd0 = std::vector<float>(150);
float * tensor_denseBiasAdd0 = fTensor_denseBiasAdd0.data();
std::vector<float> fTensor_dropout12Identity0 = std::vector<float>(150);
float * tensor_dropout12Identity0 = fTensor_dropout12Identity0.data();
std::vector<float> fTensor_leakyrelu5LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu5LeakyRelu0 = fTensor_leakyrelu5LeakyRelu0.data();
std::vector<float> fTensor_dense8bias0bcast = std::vector<float>(150);
float * tensor_dense8bias0bcast = fTensor_dense8bias0bcast.data();
std::vector<float> fTensor_dense8BiasAdd0 = std::vector<float>(150);
float * tensor_dense8BiasAdd0 = fTensor_dense8BiasAdd0.data();
std::vector<float> fTensor_leakyrelu8LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu8LeakyRelu0 = fTensor_leakyrelu8LeakyRelu0.data();
std::vector<float> fTensor_dense18bias0bcast = std::vector<float>(150);
float * tensor_dense18bias0bcast = fTensor_dense18bias0bcast.data();
std::vector<float> fTensor_dropout17Identity0 = std::vector<float>(150);
float * tensor_dropout17Identity0 = fTensor_dropout17Identity0.data();
std::vector<float> fTensor_leakyrelu9LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu9LeakyRelu0 = fTensor_leakyrelu9LeakyRelu0.data();
std::vector<float> fTensor_dropout9Identity0 = std::vector<float>(150);
float * tensor_dropout9Identity0 = fTensor_dropout9Identity0.data();
std::vector<float> fTensor_batchnormalization2batchnormadd10 = std::vector<float>(150);
float * tensor_batchnormalization2batchnormadd10 = fTensor_batchnormalization2batchnormadd10.data();
std::vector<float> fTensor_dense10bias0bcast = std::vector<float>(150);
float * tensor_dense10bias0bcast = fTensor_dense10bias0bcast.data();
std::vector<float> fTensor_leakyrelu1LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu1LeakyRelu0 = fTensor_leakyrelu1LeakyRelu0.data();
std::vector<float> fTensor_dense10BiasAdd0 = std::vector<float>(150);
float * tensor_dense10BiasAdd0 = fTensor_dense10BiasAdd0.data();
std::vector<float> fTensor_leakyrelu10LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu10LeakyRelu0 = fTensor_leakyrelu10LeakyRelu0.data();
std::vector<float> fTensor_dense11bias0bcast = std::vector<float>(150);
float * tensor_dense11bias0bcast = fTensor_dense11bias0bcast.data();
std::vector<float> fTensor_dense11BiasAdd0 = std::vector<float>(150);
float * tensor_dense11BiasAdd0 = fTensor_dense11BiasAdd0.data();
std::vector<float> fTensor_dropout1Identity0 = std::vector<float>(150);
float * tensor_dropout1Identity0 = fTensor_dropout1Identity0.data();
std::vector<float> fTensor_leakyrelu11LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu11LeakyRelu0 = fTensor_leakyrelu11LeakyRelu0.data();
std::vector<float> fTensor_dense22Sigmoid0 = std::vector<float>(1);
float * tensor_dense22Sigmoid0 = fTensor_dense22Sigmoid0.data();
std::vector<float> fTensor_batchnormalization3batchnormadd10 = std::vector<float>(150);
float * tensor_batchnormalization3batchnormadd10 = fTensor_batchnormalization3batchnormadd10.data();
std::vector<float> fTensor_leakyrelu12LeakyRelu0 = std::vector<float>(150);
float * tensor_leakyrelu12LeakyRelu0 = fTensor_leakyrelu12LeakyRelu0.data();


Session(std::string filename ="") {
   if (filename.empty()) filename = "data/pnn/mt_even_lowmass.dat";
   std::ifstream f;
   f.open(filename);
   if (!f.is_open()){
      throw std::runtime_error("tmva-sofie failed to open file for input weights");
   }
   std::string tensor_name;
   int length;
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense22kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense22kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense22kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization6movingvariance0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization6movingvariance0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization6movingvariance0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense21bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense21bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense21bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization6movingmean0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization6movingmean0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization6movingmean0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization6beta0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization6beta0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization6beta0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense20bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense20bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense20bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense20kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense20kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense20kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense19bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense19bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense19bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense18bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense18bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense18bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization5movingvariance0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization5movingvariance0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization5movingvariance0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense9bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense9bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense9bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense7kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense7kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense7kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense6kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense6kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense6kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization1movingvariance0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization1movingvariance0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization1movingvariance0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense18kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense18kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense18kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization1movingmean0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization1movingmean0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization1movingmean0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense5bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense5bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense5bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense21kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense21kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense21kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization2movingmean0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization2movingmean0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization2movingmean0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense15kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense15kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense15kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense4bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense4bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense4bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization2beta0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization2beta0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization2beta0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense7bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense7bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense7bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense1kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense1kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense1kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense1bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense1bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense1bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense2kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense2kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense2kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization3beta0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization3beta0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization3beta0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense15bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense15bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense15bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization1gamma0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization1gamma0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization1gamma0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalizationmovingvariance0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalizationmovingvariance0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalizationmovingvariance0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense13bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense13bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense13bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalizationgamma0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalizationgamma0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalizationgamma0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization2gamma0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization2gamma0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization2gamma0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalizationbeta0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalizationbeta0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalizationbeta0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization5movingmean0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization5movingmean0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization5movingmean0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense8bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense8bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense8bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense16kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense16kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense16kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense5kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense5kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense5kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense8kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense8kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense8kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_densekernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_densekernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 3900) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 3900 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_densekernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense2bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense2bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense2bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense3bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense3bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense3bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalizationmovingmean0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalizationmovingmean0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalizationmovingmean0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense3kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense3kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense3kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization2movingvariance0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization2movingvariance0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization2movingvariance0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization4movingvariance0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization4movingvariance0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization4movingvariance0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense9kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense9kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense9kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense14kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense14kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense14kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense17kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense17kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense17kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense10kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense10kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense10kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization4gamma0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization4gamma0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization4gamma0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense11kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense11kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense11kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense11bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense11bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense11bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization3movingvariance0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization3movingvariance0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization3movingvariance0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization3gamma0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization3gamma0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization3gamma0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense22bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense22bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 1) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 1 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense22bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_densebias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_densebias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_densebias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense12bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense12bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense12bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization3movingmean0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization3movingmean0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization3movingmean0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense13kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense13kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense13kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense12kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense12kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense12kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense14bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense14bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense14bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization4beta0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization4beta0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization4beta0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization6gamma0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization6gamma0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization6gamma0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization4movingmean0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization4movingmean0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization4movingmean0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense16bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense16bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense16bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization1beta0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization1beta0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization1beta0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense17bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense17bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense17bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense19kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense19kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense19kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense4kernel0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense4kernel0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 22500) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 22500 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense4kernel0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization5beta0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization5beta0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization5beta0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense6bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense6bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense6bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_dense10bias0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_dense10bias0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_dense10bias0[i];
   f >> tensor_name >> length;
   if (tensor_name != "tensor_batchnormalization5gamma0" ) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor name; expected name is tensor_batchnormalization5gamma0 , read " + tensor_name;
      throw std::runtime_error(err_msg);
    }
   if (length != 150) {
      std::string err_msg = "TMVA-SOFIE failed to read the correct tensor size; expected size is 150 , read " + std::to_string(length) ;
      throw std::runtime_error(err_msg);
    }
    for (int i =0; i < length; ++i) 
       f >> tensor_batchnormalization5gamma0[i];
   f.close();
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_densebias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_densebias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense1bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense1bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense2bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense2bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense3bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense3bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense4bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense4bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense5bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense5bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense6bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense6bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense7bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense7bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense8bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense8bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense9bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense9bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense10bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense10bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense11bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense11bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense12bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense12bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense13bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense13bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense14bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense14bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense15bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense15bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense16bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense16bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense17bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense17bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense18bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense18bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense19bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense19bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense20bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense20bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense21bias0,{ 150 }, { 1 , 150 });
      std::copy(data, data + 150, tensor_dense21bias0bcast);
      delete [] data;
   }
   {
      float * data = TMVA::Experimental::SOFIE::UTILITY::UnidirectionalBroadcast<float>(tensor_dense22bias0,{ 1 }, { 1 , 1 });
      std::copy(data, data + 1, tensor_dense22bias0bcast);
      delete [] data;
   }
}

std::vector<float> infer(float* tensor_input1){

std::cout << "Even model Input Vector: ";
    for (int i = 0; i < 26; ++i) { // Assuming 26 is the length of your input vector
        std::cout << tensor_input1[i] << " ";
    }
    std::cout << std::endl;
//--------- Gemm
   char op_0_transA = 'n';
   char op_0_transB = 'n';
   int op_0_m = 1;
   int op_0_n = 150;
   int op_0_k = 26;
   float op_0_alpha = 1;
   float op_0_beta = 1;
   int op_0_lda = 26;
   int op_0_ldb = 150;
   std::copy(tensor_densebias0bcast, tensor_densebias0bcast + 150, tensor_denseBiasAdd0);
   BLAS::sgemm_(&op_0_transB, &op_0_transA, &op_0_n, &op_0_m, &op_0_k, &op_0_alpha, tensor_densekernel0, &op_0_ldb, tensor_input1, &op_0_lda, &op_0_beta, tensor_denseBiasAdd0, &op_0_n);
   float op_1_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyreluLeakyRelu0[id] = ((tensor_denseBiasAdd0[id] >= 0 )? tensor_denseBiasAdd0[id] : op_1_alpha * tensor_denseBiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropoutIdentity0 = tensor_leakyreluLeakyRelu0;

//--------- Gemm
   char op_3_transA = 'n';
   char op_3_transB = 'n';
   int op_3_m = 1;
   int op_3_n = 150;
   int op_3_k = 150;
   float op_3_alpha = 1;
   float op_3_beta = 1;
   int op_3_lda = 150;
   int op_3_ldb = 150;
   std::copy(tensor_dense1bias0bcast, tensor_dense1bias0bcast + 150, tensor_dense1BiasAdd0);
   BLAS::sgemm_(&op_3_transB, &op_3_transA, &op_3_n, &op_3_m, &op_3_k, &op_3_alpha, tensor_dense1kernel0, &op_3_ldb, tensor_dropoutIdentity0, &op_3_lda, &op_3_beta, tensor_dense1BiasAdd0, &op_3_n);
   float op_4_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu1LeakyRelu0[id] = ((tensor_dense1BiasAdd0[id] >= 0 )? tensor_dense1BiasAdd0[id] : op_4_alpha * tensor_dense1BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout1Identity0 = tensor_leakyrelu1LeakyRelu0;

//--------- Gemm
   char op_6_transA = 'n';
   char op_6_transB = 'n';
   int op_6_m = 1;
   int op_6_n = 150;
   int op_6_k = 150;
   float op_6_alpha = 1;
   float op_6_beta = 1;
   int op_6_lda = 150;
   int op_6_ldb = 150;
   std::copy(tensor_dense2bias0bcast, tensor_dense2bias0bcast + 150, tensor_dense2BiasAdd0);
   BLAS::sgemm_(&op_6_transB, &op_6_transA, &op_6_n, &op_6_m, &op_6_k, &op_6_alpha, tensor_dense2kernel0, &op_6_ldb, tensor_dropout1Identity0, &op_6_lda, &op_6_beta, tensor_dense2BiasAdd0, &op_6_n);
   float op_7_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu2LeakyRelu0[id] = ((tensor_dense2BiasAdd0[id] >= 0 )? tensor_dense2BiasAdd0[id] : op_7_alpha * tensor_dense2BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout2Identity0 = tensor_leakyrelu2LeakyRelu0;
   constexpr int op_9_N =150;
   constexpr int op_9_incx = 1;
   constexpr int op_9_incy = 1;
   BLAS::scopy_(&op_9_N, tensor_dropout2Identity0, &op_9_incx,tensor_batchnormalizationbatchnormadd10, &op_9_incy);

   float op_9_alpha = -1;
   BLAS::saxpy_(&op_9_N, &op_9_alpha, tensor_batchnormalizationmovingmean0, &op_9_incx,tensor_batchnormalizationbatchnormadd10, &op_9_incy);

    for (size_t i = 0; i < 150; i++) {
      tensor_batchnormalizationbatchnormadd10[i] *= tensor_batchnormalizationgamma0[i] * tensor_batchnormalizationmovingvariance0[i]; 
   }
   op_9_alpha = 1;
   BLAS::saxpy_(&op_9_N, &op_9_alpha, tensor_batchnormalizationbeta0, &op_9_incx, tensor_batchnormalizationbatchnormadd10, &op_9_incy);


//--------- Gemm
   char op_10_transA = 'n';
   char op_10_transB = 'n';
   int op_10_m = 1;
   int op_10_n = 150;
   int op_10_k = 150;
   float op_10_alpha = 1;
   float op_10_beta = 1;
   int op_10_lda = 150;
   int op_10_ldb = 150;
   std::copy(tensor_dense3bias0bcast, tensor_dense3bias0bcast + 150, tensor_dense3BiasAdd0);
   BLAS::sgemm_(&op_10_transB, &op_10_transA, &op_10_n, &op_10_m, &op_10_k, &op_10_alpha, tensor_dense3kernel0, &op_10_ldb, tensor_batchnormalizationbatchnormadd10, &op_10_lda, &op_10_beta, tensor_dense3BiasAdd0, &op_10_n);
   float op_11_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu3LeakyRelu0[id] = ((tensor_dense3BiasAdd0[id] >= 0 )? tensor_dense3BiasAdd0[id] : op_11_alpha * tensor_dense3BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout3Identity0 = tensor_leakyrelu3LeakyRelu0;

//--------- Gemm
   char op_13_transA = 'n';
   char op_13_transB = 'n';
   int op_13_m = 1;
   int op_13_n = 150;
   int op_13_k = 150;
   float op_13_alpha = 1;
   float op_13_beta = 1;
   int op_13_lda = 150;
   int op_13_ldb = 150;
   std::copy(tensor_dense4bias0bcast, tensor_dense4bias0bcast + 150, tensor_dense4BiasAdd0);
   BLAS::sgemm_(&op_13_transB, &op_13_transA, &op_13_n, &op_13_m, &op_13_k, &op_13_alpha, tensor_dense4kernel0, &op_13_ldb, tensor_dropout3Identity0, &op_13_lda, &op_13_beta, tensor_dense4BiasAdd0, &op_13_n);
   float op_14_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu4LeakyRelu0[id] = ((tensor_dense4BiasAdd0[id] >= 0 )? tensor_dense4BiasAdd0[id] : op_14_alpha * tensor_dense4BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout4Identity0 = tensor_leakyrelu4LeakyRelu0;

//--------- Gemm
   char op_16_transA = 'n';
   char op_16_transB = 'n';
   int op_16_m = 1;
   int op_16_n = 150;
   int op_16_k = 150;
   float op_16_alpha = 1;
   float op_16_beta = 1;
   int op_16_lda = 150;
   int op_16_ldb = 150;
   std::copy(tensor_dense5bias0bcast, tensor_dense5bias0bcast + 150, tensor_dense5BiasAdd0);
   BLAS::sgemm_(&op_16_transB, &op_16_transA, &op_16_n, &op_16_m, &op_16_k, &op_16_alpha, tensor_dense5kernel0, &op_16_ldb, tensor_dropout4Identity0, &op_16_lda, &op_16_beta, tensor_dense5BiasAdd0, &op_16_n);
   float op_17_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu5LeakyRelu0[id] = ((tensor_dense5BiasAdd0[id] >= 0 )? tensor_dense5BiasAdd0[id] : op_17_alpha * tensor_dense5BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout5Identity0 = tensor_leakyrelu5LeakyRelu0;
   constexpr int op_19_N =150;
   constexpr int op_19_incx = 1;
   constexpr int op_19_incy = 1;
   BLAS::scopy_(&op_19_N, tensor_dropout5Identity0, &op_19_incx,tensor_batchnormalization1batchnormadd10, &op_19_incy);

   float op_19_alpha = -1;
   BLAS::saxpy_(&op_19_N, &op_19_alpha, tensor_batchnormalization1movingmean0, &op_19_incx,tensor_batchnormalization1batchnormadd10, &op_19_incy);

    for (size_t i = 0; i < 150; i++) {
      tensor_batchnormalization1batchnormadd10[i] *= tensor_batchnormalization1gamma0[i] * tensor_batchnormalization1movingvariance0[i]; 
   }
   op_19_alpha = 1;
   BLAS::saxpy_(&op_19_N, &op_19_alpha, tensor_batchnormalization1beta0, &op_19_incx, tensor_batchnormalization1batchnormadd10, &op_19_incy);


//--------- Gemm
   char op_20_transA = 'n';
   char op_20_transB = 'n';
   int op_20_m = 1;
   int op_20_n = 150;
   int op_20_k = 150;
   float op_20_alpha = 1;
   float op_20_beta = 1;
   int op_20_lda = 150;
   int op_20_ldb = 150;
   std::copy(tensor_dense6bias0bcast, tensor_dense6bias0bcast + 150, tensor_dense6BiasAdd0);
   BLAS::sgemm_(&op_20_transB, &op_20_transA, &op_20_n, &op_20_m, &op_20_k, &op_20_alpha, tensor_dense6kernel0, &op_20_ldb, tensor_batchnormalization1batchnormadd10, &op_20_lda, &op_20_beta, tensor_dense6BiasAdd0, &op_20_n);
   float op_21_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu6LeakyRelu0[id] = ((tensor_dense6BiasAdd0[id] >= 0 )? tensor_dense6BiasAdd0[id] : op_21_alpha * tensor_dense6BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout6Identity0 = tensor_leakyrelu6LeakyRelu0;

//--------- Gemm
   char op_23_transA = 'n';
   char op_23_transB = 'n';
   int op_23_m = 1;
   int op_23_n = 150;
   int op_23_k = 150;
   float op_23_alpha = 1;
   float op_23_beta = 1;
   int op_23_lda = 150;
   int op_23_ldb = 150;
   std::copy(tensor_dense7bias0bcast, tensor_dense7bias0bcast + 150, tensor_dense7BiasAdd0);
   BLAS::sgemm_(&op_23_transB, &op_23_transA, &op_23_n, &op_23_m, &op_23_k, &op_23_alpha, tensor_dense7kernel0, &op_23_ldb, tensor_dropout6Identity0, &op_23_lda, &op_23_beta, tensor_dense7BiasAdd0, &op_23_n);
   float op_24_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu7LeakyRelu0[id] = ((tensor_dense7BiasAdd0[id] >= 0 )? tensor_dense7BiasAdd0[id] : op_24_alpha * tensor_dense7BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout7Identity0 = tensor_leakyrelu7LeakyRelu0;

//--------- Gemm
   char op_26_transA = 'n';
   char op_26_transB = 'n';
   int op_26_m = 1;
   int op_26_n = 150;
   int op_26_k = 150;
   float op_26_alpha = 1;
   float op_26_beta = 1;
   int op_26_lda = 150;
   int op_26_ldb = 150;
   std::copy(tensor_dense8bias0bcast, tensor_dense8bias0bcast + 150, tensor_dense8BiasAdd0);
   BLAS::sgemm_(&op_26_transB, &op_26_transA, &op_26_n, &op_26_m, &op_26_k, &op_26_alpha, tensor_dense8kernel0, &op_26_ldb, tensor_dropout7Identity0, &op_26_lda, &op_26_beta, tensor_dense8BiasAdd0, &op_26_n);
   float op_27_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu8LeakyRelu0[id] = ((tensor_dense8BiasAdd0[id] >= 0 )? tensor_dense8BiasAdd0[id] : op_27_alpha * tensor_dense8BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout8Identity0 = tensor_leakyrelu8LeakyRelu0;
   constexpr int op_29_N =150;
   constexpr int op_29_incx = 1;
   constexpr int op_29_incy = 1;
   BLAS::scopy_(&op_29_N, tensor_dropout8Identity0, &op_29_incx,tensor_batchnormalization2batchnormadd10, &op_29_incy);

   float op_29_alpha = -1;
   BLAS::saxpy_(&op_29_N, &op_29_alpha, tensor_batchnormalization2movingmean0, &op_29_incx,tensor_batchnormalization2batchnormadd10, &op_29_incy);

    for (size_t i = 0; i < 150; i++) {
      tensor_batchnormalization2batchnormadd10[i] *= tensor_batchnormalization2gamma0[i] * tensor_batchnormalization2movingvariance0[i]; 
   }
   op_29_alpha = 1;
   BLAS::saxpy_(&op_29_N, &op_29_alpha, tensor_batchnormalization2beta0, &op_29_incx, tensor_batchnormalization2batchnormadd10, &op_29_incy);


//--------- Gemm
   char op_30_transA = 'n';
   char op_30_transB = 'n';
   int op_30_m = 1;
   int op_30_n = 150;
   int op_30_k = 150;
   float op_30_alpha = 1;
   float op_30_beta = 1;
   int op_30_lda = 150;
   int op_30_ldb = 150;
   std::copy(tensor_dense9bias0bcast, tensor_dense9bias0bcast + 150, tensor_dense9BiasAdd0);
   BLAS::sgemm_(&op_30_transB, &op_30_transA, &op_30_n, &op_30_m, &op_30_k, &op_30_alpha, tensor_dense9kernel0, &op_30_ldb, tensor_batchnormalization2batchnormadd10, &op_30_lda, &op_30_beta, tensor_dense9BiasAdd0, &op_30_n);
   float op_31_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu9LeakyRelu0[id] = ((tensor_dense9BiasAdd0[id] >= 0 )? tensor_dense9BiasAdd0[id] : op_31_alpha * tensor_dense9BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout9Identity0 = tensor_leakyrelu9LeakyRelu0;

//--------- Gemm
   char op_33_transA = 'n';
   char op_33_transB = 'n';
   int op_33_m = 1;
   int op_33_n = 150;
   int op_33_k = 150;
   float op_33_alpha = 1;
   float op_33_beta = 1;
   int op_33_lda = 150;
   int op_33_ldb = 150;
   std::copy(tensor_dense10bias0bcast, tensor_dense10bias0bcast + 150, tensor_dense10BiasAdd0);
   BLAS::sgemm_(&op_33_transB, &op_33_transA, &op_33_n, &op_33_m, &op_33_k, &op_33_alpha, tensor_dense10kernel0, &op_33_ldb, tensor_dropout9Identity0, &op_33_lda, &op_33_beta, tensor_dense10BiasAdd0, &op_33_n);
   float op_34_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu10LeakyRelu0[id] = ((tensor_dense10BiasAdd0[id] >= 0 )? tensor_dense10BiasAdd0[id] : op_34_alpha * tensor_dense10BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout10Identity0 = tensor_leakyrelu10LeakyRelu0;

//--------- Gemm
   char op_36_transA = 'n';
   char op_36_transB = 'n';
   int op_36_m = 1;
   int op_36_n = 150;
   int op_36_k = 150;
   float op_36_alpha = 1;
   float op_36_beta = 1;
   int op_36_lda = 150;
   int op_36_ldb = 150;
   std::copy(tensor_dense11bias0bcast, tensor_dense11bias0bcast + 150, tensor_dense11BiasAdd0);
   BLAS::sgemm_(&op_36_transB, &op_36_transA, &op_36_n, &op_36_m, &op_36_k, &op_36_alpha, tensor_dense11kernel0, &op_36_ldb, tensor_dropout10Identity0, &op_36_lda, &op_36_beta, tensor_dense11BiasAdd0, &op_36_n);
   float op_37_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu11LeakyRelu0[id] = ((tensor_dense11BiasAdd0[id] >= 0 )? tensor_dense11BiasAdd0[id] : op_37_alpha * tensor_dense11BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout11Identity0 = tensor_leakyrelu11LeakyRelu0;
   constexpr int op_39_N =150;
   constexpr int op_39_incx = 1;
   constexpr int op_39_incy = 1;
   BLAS::scopy_(&op_39_N, tensor_dropout11Identity0, &op_39_incx,tensor_batchnormalization3batchnormadd10, &op_39_incy);

   float op_39_alpha = -1;
   BLAS::saxpy_(&op_39_N, &op_39_alpha, tensor_batchnormalization3movingmean0, &op_39_incx,tensor_batchnormalization3batchnormadd10, &op_39_incy);

    for (size_t i = 0; i < 150; i++) {
      tensor_batchnormalization3batchnormadd10[i] *= tensor_batchnormalization3gamma0[i] * tensor_batchnormalization3movingvariance0[i]; 
   }
   op_39_alpha = 1;
   BLAS::saxpy_(&op_39_N, &op_39_alpha, tensor_batchnormalization3beta0, &op_39_incx, tensor_batchnormalization3batchnormadd10, &op_39_incy);


//--------- Gemm
   char op_40_transA = 'n';
   char op_40_transB = 'n';
   int op_40_m = 1;
   int op_40_n = 150;
   int op_40_k = 150;
   float op_40_alpha = 1;
   float op_40_beta = 1;
   int op_40_lda = 150;
   int op_40_ldb = 150;
   std::copy(tensor_dense12bias0bcast, tensor_dense12bias0bcast + 150, tensor_dense12BiasAdd0);
   BLAS::sgemm_(&op_40_transB, &op_40_transA, &op_40_n, &op_40_m, &op_40_k, &op_40_alpha, tensor_dense12kernel0, &op_40_ldb, tensor_batchnormalization3batchnormadd10, &op_40_lda, &op_40_beta, tensor_dense12BiasAdd0, &op_40_n);
   float op_41_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu12LeakyRelu0[id] = ((tensor_dense12BiasAdd0[id] >= 0 )? tensor_dense12BiasAdd0[id] : op_41_alpha * tensor_dense12BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout12Identity0 = tensor_leakyrelu12LeakyRelu0;

//--------- Gemm
   char op_43_transA = 'n';
   char op_43_transB = 'n';
   int op_43_m = 1;
   int op_43_n = 150;
   int op_43_k = 150;
   float op_43_alpha = 1;
   float op_43_beta = 1;
   int op_43_lda = 150;
   int op_43_ldb = 150;
   std::copy(tensor_dense13bias0bcast, tensor_dense13bias0bcast + 150, tensor_dense13BiasAdd0);
   BLAS::sgemm_(&op_43_transB, &op_43_transA, &op_43_n, &op_43_m, &op_43_k, &op_43_alpha, tensor_dense13kernel0, &op_43_ldb, tensor_dropout12Identity0, &op_43_lda, &op_43_beta, tensor_dense13BiasAdd0, &op_43_n);
   float op_44_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu13LeakyRelu0[id] = ((tensor_dense13BiasAdd0[id] >= 0 )? tensor_dense13BiasAdd0[id] : op_44_alpha * tensor_dense13BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout13Identity0 = tensor_leakyrelu13LeakyRelu0;

//--------- Gemm
   char op_46_transA = 'n';
   char op_46_transB = 'n';
   int op_46_m = 1;
   int op_46_n = 150;
   int op_46_k = 150;
   float op_46_alpha = 1;
   float op_46_beta = 1;
   int op_46_lda = 150;
   int op_46_ldb = 150;
   std::copy(tensor_dense14bias0bcast, tensor_dense14bias0bcast + 150, tensor_dense14BiasAdd0);
   BLAS::sgemm_(&op_46_transB, &op_46_transA, &op_46_n, &op_46_m, &op_46_k, &op_46_alpha, tensor_dense14kernel0, &op_46_ldb, tensor_dropout13Identity0, &op_46_lda, &op_46_beta, tensor_dense14BiasAdd0, &op_46_n);
   float op_47_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu14LeakyRelu0[id] = ((tensor_dense14BiasAdd0[id] >= 0 )? tensor_dense14BiasAdd0[id] : op_47_alpha * tensor_dense14BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout14Identity0 = tensor_leakyrelu14LeakyRelu0;
   constexpr int op_49_N =150;
   constexpr int op_49_incx = 1;
   constexpr int op_49_incy = 1;
   BLAS::scopy_(&op_49_N, tensor_dropout14Identity0, &op_49_incx,tensor_batchnormalization4batchnormadd10, &op_49_incy);

   float op_49_alpha = -1;
   BLAS::saxpy_(&op_49_N, &op_49_alpha, tensor_batchnormalization4movingmean0, &op_49_incx,tensor_batchnormalization4batchnormadd10, &op_49_incy);

    for (size_t i = 0; i < 150; i++) {
      tensor_batchnormalization4batchnormadd10[i] *= tensor_batchnormalization4gamma0[i] * tensor_batchnormalization4movingvariance0[i]; 
   }
   op_49_alpha = 1;
   BLAS::saxpy_(&op_49_N, &op_49_alpha, tensor_batchnormalization4beta0, &op_49_incx, tensor_batchnormalization4batchnormadd10, &op_49_incy);


//--------- Gemm
   char op_50_transA = 'n';
   char op_50_transB = 'n';
   int op_50_m = 1;
   int op_50_n = 150;
   int op_50_k = 150;
   float op_50_alpha = 1;
   float op_50_beta = 1;
   int op_50_lda = 150;
   int op_50_ldb = 150;
   std::copy(tensor_dense15bias0bcast, tensor_dense15bias0bcast + 150, tensor_dense15BiasAdd0);
   BLAS::sgemm_(&op_50_transB, &op_50_transA, &op_50_n, &op_50_m, &op_50_k, &op_50_alpha, tensor_dense15kernel0, &op_50_ldb, tensor_batchnormalization4batchnormadd10, &op_50_lda, &op_50_beta, tensor_dense15BiasAdd0, &op_50_n);
   float op_51_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu15LeakyRelu0[id] = ((tensor_dense15BiasAdd0[id] >= 0 )? tensor_dense15BiasAdd0[id] : op_51_alpha * tensor_dense15BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout15Identity0 = tensor_leakyrelu15LeakyRelu0;

//--------- Gemm
   char op_53_transA = 'n';
   char op_53_transB = 'n';
   int op_53_m = 1;
   int op_53_n = 150;
   int op_53_k = 150;
   float op_53_alpha = 1;
   float op_53_beta = 1;
   int op_53_lda = 150;
   int op_53_ldb = 150;
   std::copy(tensor_dense16bias0bcast, tensor_dense16bias0bcast + 150, tensor_dense16BiasAdd0);
   BLAS::sgemm_(&op_53_transB, &op_53_transA, &op_53_n, &op_53_m, &op_53_k, &op_53_alpha, tensor_dense16kernel0, &op_53_ldb, tensor_dropout15Identity0, &op_53_lda, &op_53_beta, tensor_dense16BiasAdd0, &op_53_n);
   float op_54_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu16LeakyRelu0[id] = ((tensor_dense16BiasAdd0[id] >= 0 )? tensor_dense16BiasAdd0[id] : op_54_alpha * tensor_dense16BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout16Identity0 = tensor_leakyrelu16LeakyRelu0;

//--------- Gemm
   char op_56_transA = 'n';
   char op_56_transB = 'n';
   int op_56_m = 1;
   int op_56_n = 150;
   int op_56_k = 150;
   float op_56_alpha = 1;
   float op_56_beta = 1;
   int op_56_lda = 150;
   int op_56_ldb = 150;
   std::copy(tensor_dense17bias0bcast, tensor_dense17bias0bcast + 150, tensor_dense17BiasAdd0);
   BLAS::sgemm_(&op_56_transB, &op_56_transA, &op_56_n, &op_56_m, &op_56_k, &op_56_alpha, tensor_dense17kernel0, &op_56_ldb, tensor_dropout16Identity0, &op_56_lda, &op_56_beta, tensor_dense17BiasAdd0, &op_56_n);
   float op_57_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu17LeakyRelu0[id] = ((tensor_dense17BiasAdd0[id] >= 0 )? tensor_dense17BiasAdd0[id] : op_57_alpha * tensor_dense17BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout17Identity0 = tensor_leakyrelu17LeakyRelu0;
   constexpr int op_59_N =150;
   constexpr int op_59_incx = 1;
   constexpr int op_59_incy = 1;
   BLAS::scopy_(&op_59_N, tensor_dropout17Identity0, &op_59_incx,tensor_batchnormalization5batchnormadd10, &op_59_incy);

   float op_59_alpha = -1;
   BLAS::saxpy_(&op_59_N, &op_59_alpha, tensor_batchnormalization5movingmean0, &op_59_incx,tensor_batchnormalization5batchnormadd10, &op_59_incy);

    for (size_t i = 0; i < 150; i++) {
      tensor_batchnormalization5batchnormadd10[i] *= tensor_batchnormalization5gamma0[i] * tensor_batchnormalization5movingvariance0[i]; 
   }
   op_59_alpha = 1;
   BLAS::saxpy_(&op_59_N, &op_59_alpha, tensor_batchnormalization5beta0, &op_59_incx, tensor_batchnormalization5batchnormadd10, &op_59_incy);


//--------- Gemm
   char op_60_transA = 'n';
   char op_60_transB = 'n';
   int op_60_m = 1;
   int op_60_n = 150;
   int op_60_k = 150;
   float op_60_alpha = 1;
   float op_60_beta = 1;
   int op_60_lda = 150;
   int op_60_ldb = 150;
   std::copy(tensor_dense18bias0bcast, tensor_dense18bias0bcast + 150, tensor_dense18BiasAdd0);
   BLAS::sgemm_(&op_60_transB, &op_60_transA, &op_60_n, &op_60_m, &op_60_k, &op_60_alpha, tensor_dense18kernel0, &op_60_ldb, tensor_batchnormalization5batchnormadd10, &op_60_lda, &op_60_beta, tensor_dense18BiasAdd0, &op_60_n);
   float op_61_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu18LeakyRelu0[id] = ((tensor_dense18BiasAdd0[id] >= 0 )? tensor_dense18BiasAdd0[id] : op_61_alpha * tensor_dense18BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout18Identity0 = tensor_leakyrelu18LeakyRelu0;

//--------- Gemm
   char op_63_transA = 'n';
   char op_63_transB = 'n';
   int op_63_m = 1;
   int op_63_n = 150;
   int op_63_k = 150;
   float op_63_alpha = 1;
   float op_63_beta = 1;
   int op_63_lda = 150;
   int op_63_ldb = 150;
   std::copy(tensor_dense19bias0bcast, tensor_dense19bias0bcast + 150, tensor_dense19BiasAdd0);
   BLAS::sgemm_(&op_63_transB, &op_63_transA, &op_63_n, &op_63_m, &op_63_k, &op_63_alpha, tensor_dense19kernel0, &op_63_ldb, tensor_dropout18Identity0, &op_63_lda, &op_63_beta, tensor_dense19BiasAdd0, &op_63_n);
   float op_64_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu19LeakyRelu0[id] = ((tensor_dense19BiasAdd0[id] >= 0 )? tensor_dense19BiasAdd0[id] : op_64_alpha * tensor_dense19BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout19Identity0 = tensor_leakyrelu19LeakyRelu0;

//--------- Gemm
   char op_66_transA = 'n';
   char op_66_transB = 'n';
   int op_66_m = 1;
   int op_66_n = 150;
   int op_66_k = 150;
   float op_66_alpha = 1;
   float op_66_beta = 1;
   int op_66_lda = 150;
   int op_66_ldb = 150;
   std::copy(tensor_dense20bias0bcast, tensor_dense20bias0bcast + 150, tensor_dense20BiasAdd0);
   BLAS::sgemm_(&op_66_transB, &op_66_transA, &op_66_n, &op_66_m, &op_66_k, &op_66_alpha, tensor_dense20kernel0, &op_66_ldb, tensor_dropout19Identity0, &op_66_lda, &op_66_beta, tensor_dense20BiasAdd0, &op_66_n);
   float op_67_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu20LeakyRelu0[id] = ((tensor_dense20BiasAdd0[id] >= 0 )? tensor_dense20BiasAdd0[id] : op_67_alpha * tensor_dense20BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout20Identity0 = tensor_leakyrelu20LeakyRelu0;
   constexpr int op_69_N =150;
   constexpr int op_69_incx = 1;
   constexpr int op_69_incy = 1;
   BLAS::scopy_(&op_69_N, tensor_dropout20Identity0, &op_69_incx,tensor_batchnormalization6batchnormadd10, &op_69_incy);

   float op_69_alpha = -1;
   BLAS::saxpy_(&op_69_N, &op_69_alpha, tensor_batchnormalization6movingmean0, &op_69_incx,tensor_batchnormalization6batchnormadd10, &op_69_incy);

    for (size_t i = 0; i < 150; i++) {
      tensor_batchnormalization6batchnormadd10[i] *= tensor_batchnormalization6gamma0[i] * tensor_batchnormalization6movingvariance0[i]; 
   }
   op_69_alpha = 1;
   BLAS::saxpy_(&op_69_N, &op_69_alpha, tensor_batchnormalization6beta0, &op_69_incx, tensor_batchnormalization6batchnormadd10, &op_69_incy);


//--------- Gemm
   char op_70_transA = 'n';
   char op_70_transB = 'n';
   int op_70_m = 1;
   int op_70_n = 150;
   int op_70_k = 150;
   float op_70_alpha = 1;
   float op_70_beta = 1;
   int op_70_lda = 150;
   int op_70_ldb = 150;
   std::copy(tensor_dense21bias0bcast, tensor_dense21bias0bcast + 150, tensor_dense21BiasAdd0);
   BLAS::sgemm_(&op_70_transB, &op_70_transA, &op_70_n, &op_70_m, &op_70_k, &op_70_alpha, tensor_dense21kernel0, &op_70_ldb, tensor_batchnormalization6batchnormadd10, &op_70_lda, &op_70_beta, tensor_dense21BiasAdd0, &op_70_n);
   float op_71_alpha = 0.100000001;

//------ LEAKY RELU
   for (int id = 0; id < 150 ; id++){
      tensor_leakyrelu21LeakyRelu0[id] = ((tensor_dense21BiasAdd0[id] >= 0 )? tensor_dense21BiasAdd0[id] : op_71_alpha * tensor_dense21BiasAdd0[id]);
   }

//------ IDENTITY
      tensor_dropout21Identity0 = tensor_leakyrelu21LeakyRelu0;

//--------- Gemm
   char op_73_transA = 'n';
   char op_73_transB = 'n';
   int op_73_m = 1;
   int op_73_n = 1;
   int op_73_k = 150;
   float op_73_alpha = 1;
   float op_73_beta = 1;
   int op_73_lda = 150;
   int op_73_ldb = 1;
   std::copy(tensor_dense22bias0bcast, tensor_dense22bias0bcast + 1, tensor_dense22Dense);
   BLAS::sgemm_(&op_73_transB, &op_73_transA, &op_73_n, &op_73_m, &op_73_k, &op_73_alpha, tensor_dense22kernel0, &op_73_ldb, tensor_dropout21Identity0, &op_73_lda, &op_73_beta, tensor_dense22Dense, &op_73_n);
	for (int id = 0; id < 1 ; id++){
		tensor_dense22Sigmoid0[id] = 1 / (1 + std::exp( - tensor_dense22Dense[id]));
	}
   std::vector<float> ret (tensor_dense22Sigmoid0, tensor_dense22Sigmoid0 + 1);
   return ret;
}
};
} //TMVA_SOFIE_mt_even_lowmass

#endif  // TMVA_SOFIE_MT_EVEN_LOWMASS
