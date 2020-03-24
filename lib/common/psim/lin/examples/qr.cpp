// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include <core/core.hpp>
#include <algorithms/qr.hpp>

#include <iostream>

/* Simple example program that takes the QR factorization of a matrix randomly
 * generated at runtime. */
int main()
{
  lin::Matrix4x3d A, Q;
  lin::Matrix3x3d R;

  std::cout << "\nQR Factorization Example\n\n";

  A = lin::rands<lin::Matrix4x3d>();
  std::cout << "A =\n" << A << "\n\n";
 
  lin::qr(A, Q, R);
  std::cout << "Q =\n" << Q << "\n";
  std::cout << "R =\n" << R << "\n";

  auto B = (Q * R).eval();
  std::cout << "Q * R =\n" << B << "\n";
  std::cout << "fro(A - Q * R) = " << lin::fro(A - B) << std::endl;

  return 0;
}
