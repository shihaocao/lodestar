// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include <core/core.hpp>
#include <algorithms/backward_sub.hpp>
#include <algorithms/qr.hpp>

#include <gtest/gtest.h>

TEST(AlgorithmsTests, FixedSizeQR)
{
  lin::Matrix4x3f M, Q;
  lin::Matrix3x3f R;
  for (lin::size_t i = 0; i < 10; i++) {
    M = lin::rands<lin::Matrix4x3f>();
    lin::qr(M, Q, R);
    ASSERT_NEAR(0.0f, lin::fro(M - Q * R), 1e-4);
  }
}

TEST(AlgorithmsTests, StaticSizeQR)
{
  lin::Matrixd<0, 0, 9, 5> M(7, 4), Q;
  lin::Matrixd<0, 0, 5, 5> R;
  for (lin::size_t i = 0; i < 10; i++) {
    M = lin::rands<lin::Matrixd<0, 0, 9, 5>>(M.rows(), M.cols());
    lin::qr(M, Q, R);
    ASSERT_NEAR(0.0f, lin::fro(M - Q * R), 1e-10);
  }
}

TEST(AlgorithmsTests, FixedSizeLinSolveQRBackSub)
{
  lin::Matrix4x4f A, Q, R;
  lin::Matrix4x3f X, Y;
  for (lin::size_t i = 0; i < 10; i++) {
    A = lin::rands<lin::Matrix4x4f>();
    Y = lin::rands<lin::Matrix4x3f>();
    lin::qr(A, Q, R);
    lin::backward_sub(R, X, (lin::transpose(Q) * Y).eval());
    ASSERT_NEAR(0.0f, lin::fro(A * X - Y), 1e-4);
  }
}

TEST(AlgorithmsTests, StaticSizeLinSolveQRBackSub)
{
  lin::Matrixf<0, 0, 8, 8> A(6, 6), Q;
  lin::Matrixf<0, 0, 8, 8> R(6, 6);
  lin::Matrixf<0, 0, 8, 3> X, Y(6, 2);
  A = lin::rands<float, 0, 0, 8, 8>(6, 6);
  Y = lin::rands<float, 0, 0, 8, 3>(6, 2);
  lin::qr(A, Q, R);
  lin::backward_sub(R, X, (lin::transpose(Q) * Y).eval());
  ASSERT_NEAR(0.0f, lin::fro(A * X - Y), 1e-4);
}
