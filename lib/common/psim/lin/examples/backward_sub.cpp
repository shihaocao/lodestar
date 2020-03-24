// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include <core/core.hpp>
#include <algorithms/backward_sub.hpp>
#include <algorithms/qr.hpp>

#include <iostream>

/* Simple example program that solves a linear system using QR factorization
 * and backward substitution. */
int main()
{
  // Linear system we are solving is A * X = Y where X and Y don't need to be
  // vectors to be compatible with the library. Q and R are temporaries to hold
  // the QR factorization without overwriting A.
  lin::Matrix4x4d A, Q, R;
  lin::Matrix4x2d X, Y;

  std::cout << "\nBackward Substitution Example\n\n";

  A = lin::rands<lin::Matrix4x4d>();
  Y = lin::rands<lin::Matrix4x2d>();
  std::cout << "A =\n" << A << "\n";
  std::cout << "Y =\n" << Y << "\n";

  std::cout << "Solving A * X = Y\n";
 
  lin::qr(A, Q, R);
  lin::backward_sub(R, X, (lin::transpose(Q) * Y).eval());
  std::cout << "X =\n" << X << "\n";

  auto B = (A * X).eval();
  std::cout << "A * X =\n" << B << "\n";
  std::cout << "fro(Y - A * X) = " << lin::fro(Y - B) << std::endl;

  return 0;
}
