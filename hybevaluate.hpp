/****************************************************************************
 *
 * ALPS DMFT Project
 *
 * Copyright (C) 2012 by Hartmut Hafermann <hafermann@cpht.polytechnique.fr>
 *                       Emanuel Gull <gull@pks.mpg.de>,
 *
 *  based on an earlier version by Philipp Werner and Emanuel Gull
 *
 *
 * This software is part of the ALPS Applications, published under the ALPS
 * Application License; you can use, redistribute it and/or modify it under
 * the terms of the license, either version 1 or (at your option) any later
 * version.
 * 
 * You should have received a copy of the ALPS Application License along with
 * the ALPS Applications; see the file LICENSE.txt. If not, the license is also
 * available from http://alps.comp-phys.org/.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT 
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE 
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************/
#ifndef HYB_EVALUATE
#define HYB_EVALUATE
#include <boost/math/special_functions/bessel.hpp>
#include <alps/gf/gf.hpp>
#include <alps/gf/tail.hpp>
#include <alps/gf/fourier.hpp>
#include <alps/mc/api.hpp>

void evaluate_basics(const alps::accumulators::result_set &results, const alps::params &parms, alps::hdf5::archive &solver_output);
void evaluate_gtau(const alps::accumulators::result_set &results, const alps::params &parms, alps::hdf5::archive &solver_output);
void evaluate_freq(const alps::accumulators::result_set &results, const alps::params &parms, alps::hdf5::archive &solver_output);
void evaluate_legendre(const alps::accumulators::result_set &results, const alps::params &parms, alps::hdf5::archive &solver_output);
void evaluate_nnt(const alps::accumulators::result_set &results, const alps::params &parms, alps::hdf5::archive &solver_output);
void evaluate_nnw(const alps::accumulators::result_set &results, const alps::params &parms, alps::hdf5::archive &solver_output);
void evaluate_sector_statistics(const alps::accumulators::result_set &results, const alps::params &parms, alps::hdf5::archive &solver_output);
void evaluate_2p(const alps::accumulators::result_set &results, const alps::params &parms, alps::hdf5::archive &solver_output);

inline std::complex<double> t(int n, int l){//transformation matrix from Legendre to Matsubara basis
  std::complex<double> i_c(0., 1.);
  return (std::sqrt(2*l+1)/std::sqrt(2*n+1)) * std::exp(i_c*(n+0.5)*M_PI) * std::pow(i_c,l) * boost::math::cyl_bessel_j(l+0.5,(n+0.5)*M_PI);
}

struct jackson{//the Jackson kernel
  jackson(int N_l_):N_l(N_l_){};
  double operator()(int n){ return (1./(N_l+1.))*((N_l-n+1)*std::cos(M_PI*n/(N_l+1.))+std::sin(M_PI*n/(N_l+1.))/std::tan(M_PI/(N_l+1.))); }
  int N_l;
};

alps::gf::omega_sigma_gf_with_tail translate_Gw_to_h5gf(matsubara_green_function_t Gw,const alps::params &parms);
alps::gf::itime_sigma_gf_with_tail translate_Gt_to_h5gf(itime_green_function_t Gtau, const alps::params &parms);
#endif

