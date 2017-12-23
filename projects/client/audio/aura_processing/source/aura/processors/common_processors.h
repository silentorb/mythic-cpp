#pragma once

//#include <cmath>


namespace aura {
  void initialize_db();
  float to_db(float value);

//	constexpr float manual_exp(float x, int n)
//	{
//		return n == 0 ? 1 :
//			n % 2 == 0 ? manual_exp(x * x, n / 2) :
//			manual_exp(x * x, (n - 1) / 2) * x;
//	};
//
//	constexpr size_t log2(size_t n)
//	{
//		return ((n<2) ? 1 : 1 + log2(n / 2));
//	}
//
//	constexpr double euler_number = 2.71828182845904523536;
//
//  constexpr float manual_pow(float x, float y) {
//    return manual_exp(euler_number, y * log2(x));
//  }
//
//  constexpr float const_db(float value) {
//    return (manual_pow(10, value) - 1) / (10 - 1);
//  }
}