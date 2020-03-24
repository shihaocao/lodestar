// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include <core/core.hpp>

#include <cmath>
#include <gtest/gtest.h>

TEST(CoreTests, FixedSizeInitialization)
{
  lin::Matrix2x3f tensor({
    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f
  });
  // Check elements
  ASSERT_FLOAT_EQ(tensor(0, 0), 1.0f);
  ASSERT_FLOAT_EQ(tensor(1, 0), 4.0f);
  ASSERT_FLOAT_EQ(tensor(0, 1), 2.0f);
  ASSERT_FLOAT_EQ(tensor(1, 1), 5.0f);
  ASSERT_FLOAT_EQ(tensor(0, 2), 3.0f);
  ASSERT_FLOAT_EQ(tensor(1, 2), 6.0f);
  // Check dimensions
  ASSERT_EQ(tensor.rows(), 2u);
  ASSERT_EQ(tensor.cols(), 3u);
  ASSERT_EQ(tensor.size(), 6u);
}

TEST(CoreTests, StaticSizeInitialization)
{
  lin::Matrixf<0, 2, 5, 2> tensor(2, 2);
  tensor = {
    1.0f, 2.0f,
    3.0f, 4.0f
  };
  // Check elements
  ASSERT_FLOAT_EQ(tensor(0, 0), 1.0f);
  ASSERT_FLOAT_EQ(tensor(1, 0), 3.0f);
  ASSERT_FLOAT_EQ(tensor(0, 1), 2.0f);
  ASSERT_FLOAT_EQ(tensor(1, 1), 4.0f);
  // Check dimensions
  ASSERT_EQ(tensor.rows(), 2u);
  ASSERT_EQ(tensor.cols(), 2u);
  ASSERT_EQ(tensor.size(), 4u);
}

TEST(CoreTests, FixedSizeInitializerListAssignment)
{
  lin::Matrix2x3f tensor({
    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f
  });
  // Reassignment
  tensor = {
    6.0f, 5.0f, 4.0f,
    3.0f, 2.0f, 1.0f
  };
  // Check elements
  ASSERT_FLOAT_EQ(tensor(0, 0), 6.0f);
  ASSERT_FLOAT_EQ(tensor(1, 0), 3.0f);
  ASSERT_FLOAT_EQ(tensor(0, 1), 5.0f);
  ASSERT_FLOAT_EQ(tensor(1, 1), 2.0f);
  ASSERT_FLOAT_EQ(tensor(0, 2), 4.0f);
  ASSERT_FLOAT_EQ(tensor(1, 2), 1.0f);
  // Check dimensions
  ASSERT_EQ(tensor.rows(), 2u);
  ASSERT_EQ(tensor.cols(), 3u);
  ASSERT_EQ(tensor.size(), 6u);
}

TEST(CoreTests, FixedSizeSum)
{
  lin::Matrix2x2f a({
    0.0f, 1.0f,
    0.5f, -2.0f
  });
  lin::Matrix2x2f b({
    1.0f, 0.25f,
    0.0f, -1.0f
  });
  auto sum = a + b;
  // Check elements
  ASSERT_FLOAT_EQ(sum(0, 0), 1.0f);
  ASSERT_FLOAT_EQ(sum(1, 0), 0.5f);
  ASSERT_FLOAT_EQ(sum(0, 1), 1.25f);
  ASSERT_FLOAT_EQ(sum(1, 1), -3.0f);
  // Check dimensions
  ASSERT_EQ(sum.rows(), 2u);
  ASSERT_EQ(sum.cols(), 2u);
  ASSERT_EQ(sum.size(), 4u);
}

TEST(CoreTests, StaticSizeSum)
{
  lin::Matrixf<0, 0, 2, 2> a(1, 2);
  a = {
    1.0f, 2.0f
  };
  lin::Matrixf<0, 0, 2, 2> b(1, 2);
  b = {
    1.0f, -1.0f
  };
  auto sum = a + b;
  // Check elements
  ASSERT_FLOAT_EQ(sum(0, 0), 2.0f);
  ASSERT_FLOAT_EQ(sum(0, 1), 1.0f);
  // Check dimensions
  ASSERT_EQ(sum.rows(), 1u);
  ASSERT_EQ(sum.cols(), 2u);
  ASSERT_EQ(sum.size(), 2u);
}

TEST(CoreTests, StaticSizeDifference)
{
  lin::Matrixf<0, 0, 2, 3> a(1, 3);
  a = {
    1.0f, 2.0f, 5.0f
  };
  lin::Matrixf<0, 0, 2, 3> b(1, 3);
  b = {
    1.0f, -1.0f, 0.0f
  };
  auto difference = a - b;
  // Check elements
  ASSERT_FLOAT_EQ(difference(0, 0), 0.0f);
  ASSERT_FLOAT_EQ(difference(0, 1), 3.0f);
  ASSERT_FLOAT_EQ(difference(0, 2), 5.0f);
  // Check dimensions
  ASSERT_EQ(difference.rows(), 1u);
  ASSERT_EQ(difference.cols(), 3u);
  ASSERT_EQ(difference.size(), 3u);
}

TEST(CoreTests, StaticSizeMultiple)
{
  lin::Matrixf<0, 0, 5, 7> tensor(2, 3);
  tensor = {
    5.0f, 2.0f, 0.5f,
    1.0f, -1.0f, 0.0f
  };
  auto multiple = 2.0f * tensor;
  // Check elements
  ASSERT_FLOAT_EQ(multiple(0, 0), 10.0f);
  ASSERT_FLOAT_EQ(multiple(1, 0), 2.0f);
  ASSERT_FLOAT_EQ(multiple(0, 1), 4.0f);
  ASSERT_FLOAT_EQ(multiple(1, 1), -2.0f);
  ASSERT_FLOAT_EQ(multiple(0, 2), 1.0f);
  ASSERT_FLOAT_EQ(multiple(1, 2), 0.0f);
  // Check dimensions
  ASSERT_EQ(multiple.rows(), 2u);
  ASSERT_EQ(multiple.cols(), 3u);
  ASSERT_EQ(multiple.size(), 6u);
}


TEST(CoreTests, FixedSizeTranspose)
{
  lin::Vector3f tensor({
    1.0f,
    2.0f,
    3.0f
  });
  auto trans = lin::transpose(tensor);
  // Check elements
  ASSERT_FLOAT_EQ(trans(0, 0), 1.0f);
  ASSERT_FLOAT_EQ(trans(0, 1), 2.0f);
  ASSERT_FLOAT_EQ(trans(0, 2), 3.0f);
  // Check dimensions
  ASSERT_EQ(trans.rows(), 1u);
  ASSERT_EQ(trans.cols(), 3u);
  ASSERT_EQ(trans.size(), 3u);
}

TEST(CoreTests, FixedSizeTransposeAssignment)
{
  lin::Matrix2x2f tensor({
    1.0f, 3.0f,
    2.0f, 4.0f
  });
  tensor = lin::transpose(tensor).eval();
  // Check elements
  ASSERT_FLOAT_EQ(tensor(0, 0), 1.0f);
  ASSERT_FLOAT_EQ(tensor(1, 0), 3.0f);
  ASSERT_FLOAT_EQ(tensor(0, 1), 2.0f);
  ASSERT_FLOAT_EQ(tensor(1, 1), 4.0f);
}

TEST(CoreTests, FixedSizeConstantReference)
{
  lin::Matrixf<5, 5> tensor({
    1.0f, 3.0f, 6.0f, 0.0f, 2.5f,
    2.6f, 3.2f, 5.5f, 6.0f, 3.0f,
    1.0f, 0.5f, 0.0f, 3.0f, 1.0f,
    0.0f, 1.1f, 2.6f, 3.1f, 9.9f,
    0.0f, 0.5f, 0.1f, 1.9f, 2.8f
  });
  auto reference = lin::ref<1, 3>(tensor, 2, 1);
  // Check elements
  ASSERT_FLOAT_EQ(reference(0, 0), 0.5f);
  ASSERT_FLOAT_EQ(reference(0, 1), 0.0f);
  ASSERT_FLOAT_EQ(reference(0, 2), 3.0f);
  // Check dimensions
  ASSERT_EQ(reference.rows(), 1u);
  ASSERT_EQ(reference.cols(), 3u);
  ASSERT_EQ(reference.size(), 3u);
}

TEST(CoreTests, StaticSizeConstantReference)
{
  lin::Matrixf<0, 0, 5, 5> tensor(3, 3);
  tensor = {
    1.0f, 3.0f, 6.0f,
    0.0f, 2.5f, 2.6f,
    3.2f, 5.5f, 6.0f
  };
  auto reference = lin::ref<0, 0, 3, 3>(tensor, 0, 0, 2, 2);
  // Check elements
  ASSERT_FLOAT_EQ(reference(0, 0), 1.0f);
  ASSERT_FLOAT_EQ(reference(1, 0), 0.0f);
  ASSERT_FLOAT_EQ(reference(0, 1), 3.0f);
  ASSERT_FLOAT_EQ(reference(1, 1), 2.5f);
  // Check dimensions
  ASSERT_EQ(reference.rows(), 2u);
  ASSERT_EQ(reference.cols(), 2u);
  ASSERT_EQ(reference.size(), 4u);
}

TEST(CoreTests, FixedSizeReferenceReassignment)
{
  lin::Matrix3x3f tensor({
    1.0f, 3.0f, 6.0f,
    0.9f, 2.5f, 2.6f,
    3.2f, 5.5f, 6.0f
  });
  auto reference = lin::ref<2, 2>(tensor, 1, 1);
  reference(0, 0) = -1.0f;
  // Check elements
  ASSERT_FLOAT_EQ(tensor(1, 1), -1.0f);
}

TEST(CoreTests, FixedSizeReferenceTranpose)
{
  lin::Matrix3x3f tensor({
    1.0f, 3.0f, 6.0f,
    0.0f, 2.5f, 2.6f,
    3.2f, 5.5f, 6.0f
  });
  auto trans = lin::transpose(lin::ref<2, 2>(tensor, 1, 1));
  // Check elements
  ASSERT_FLOAT_EQ(trans(0, 0), 2.5f);
  ASSERT_FLOAT_EQ(trans(1, 0), 2.6f);
  ASSERT_FLOAT_EQ(trans(0, 1), 5.5f);
  ASSERT_FLOAT_EQ(trans(1, 1), 6.0f);
  // Check dimensions
  ASSERT_EQ(trans.rows(), 2u);
  ASSERT_EQ(trans.cols(), 2u);
  ASSERT_EQ(trans.size(), 4u);
}

TEST(CoreTests, FixedSizeReferenceMultipleReassignment)
{
  lin::Matrix3x3f tensor({
    1.0f, 3.0f, 6.0f,
    0.0f, 2.5f, 2.6f,
    3.2f, 5.5f, 6.0f
  });
  lin::ref<2, 2>(tensor, 1, 1) = 2.0f * lin::ref<2, 2>(tensor, 1, 1);
  // Check tensor elements
  ASSERT_FLOAT_EQ(tensor(0, 0), 1.0f);
  ASSERT_FLOAT_EQ(tensor(1, 0), 0.0f);
  ASSERT_FLOAT_EQ(tensor(2, 0), 3.2f);
  ASSERT_FLOAT_EQ(tensor(0, 1), 3.0f);
  ASSERT_FLOAT_EQ(tensor(1, 1), 5.0f);
  ASSERT_FLOAT_EQ(tensor(2, 1), 11.0f);
  ASSERT_FLOAT_EQ(tensor(0, 2), 6.0f);
  ASSERT_FLOAT_EQ(tensor(1, 2), 5.2f);
  ASSERT_FLOAT_EQ(tensor(2, 2), 12.0f);
}

TEST(CoreTests, FixedSizeMultiplication)
{
  lin::Matrix2x3f a({
    1.0f, 0.0f, 3.0f,
    2.0f, 1.0f, 5.0f
  });
  lin::Matrix3x2f b({
    3.0f, 2.0f,
    0.0f, 0.0f,
    1.0f, 5.0f
  });
  auto result = a * b;
  // Check elements
  ASSERT_FLOAT_EQ(result(0, 0), 6.0f);
  ASSERT_FLOAT_EQ(result(1, 0), 11.0f);
  ASSERT_FLOAT_EQ(result(0, 1), 17.0f);
  ASSERT_FLOAT_EQ(result(1, 1), 29.0f);
  // Check dimensions
  ASSERT_EQ(result.rows(), 2u);
  ASSERT_EQ(result.cols(), 2u);
  ASSERT_EQ(result.size(), 4u);
}

TEST(CoreTests, DotProduct)
{
  lin::Vector3f u({
    0.0f, 2.0f, 1.0f
  });
  lin::Vector3f v({
    1.0f, 1.5f, 3.0f
  });
  // Check result
  ASSERT_FLOAT_EQ(lin::dot(u, v), 6.0f);
  ASSERT_FLOAT_EQ(lin::dot(v, u), 6.0f);
  ASSERT_FLOAT_EQ(lin::dot(lin::transpose(u), v), 6.0f);
  ASSERT_FLOAT_EQ(lin::dot(u, lin::transpose(v)), 6.0f);
  ASSERT_FLOAT_EQ(lin::dot(lin::transpose(u), lin::transpose(v)), 6.0f);
}

TEST(CoreTests, Fro)
{
  lin::Vector3f u({
    3.0f, 0.0f, 4.0f
  });
  // Check two norm squared result
  ASSERT_FLOAT_EQ(lin::fro(u), 25.0f);
  ASSERT_FLOAT_EQ(lin::fro(lin::transpose(u)), 25.0f);
}

TEST(CoreTests, Norm)
{
  lin::Vector3f u({
    3.0f, 0.0f, 4.0f
  });
  // Check two norm result
  ASSERT_FLOAT_EQ(lin::norm(u), 5.0f);
  ASSERT_FLOAT_EQ(lin::norm(lin::transpose(u)), 5.0f);
}

TEST(CoreTests, ZerosTest)
{
  lin::Matrix2x2f a = lin::zeros<float, 2, 2>();
  // Check elements
  ASSERT_FLOAT_EQ(a(0, 0), 0.0f);
  ASSERT_FLOAT_EQ(a(1, 0), 0.0f);
  ASSERT_FLOAT_EQ(a(0, 1), 0.0f);
  ASSERT_FLOAT_EQ(a(1, 1), 0.0f);
  // Check dimensions
  ASSERT_EQ(a.rows(), 2u);
  ASSERT_EQ(a.cols(), 2u);
  ASSERT_EQ(a.size(), 4u);
}

TEST(CoreTests, OnesTest)
{
  lin::Matrix2x2f a = lin::ones<float, 2, 2>();
  // Check elements
  ASSERT_FLOAT_EQ(a(0, 0), 1.0f);
  ASSERT_FLOAT_EQ(a(1, 0), 1.0f);
  ASSERT_FLOAT_EQ(a(0, 1), 1.0f);
  ASSERT_FLOAT_EQ(a(1, 1), 1.0f);
  // Check dimensions
  ASSERT_EQ(a.rows(), 2u);
  ASSERT_EQ(a.cols(), 2u);
  ASSERT_EQ(a.size(), 4u);
}

TEST(CoreTests, NansTest)
{
  lin::Matrix2x2f a = lin::nans<float, 2, 2>();
  // Check elements
  ASSERT_TRUE(std::isnan(a(0, 0)));
  // Check dimensions
  ASSERT_EQ(a.rows(), 2u);
  ASSERT_EQ(a.cols(), 2u);
  ASSERT_EQ(a.size(), 4u);
}

TEST(CoreTests, CrossTest)
{
  lin::Vector3f a = {4.0f, 2.0f, -1.0f};
  lin::Vector3f b = {-1.0f, 0.0f, 2.0f};
  auto const c = lin::cross(a, b);
  // Check elements
  ASSERT_FLOAT_EQ(c(0), 4.0f);
  ASSERT_FLOAT_EQ(c(1), -7.0f);
  ASSERT_FLOAT_EQ(c(2), 2.0f);
  // Check dimensions
  ASSERT_EQ(c.rows(), 3u);
  ASSERT_EQ(c.cols(), 1u);
  ASSERT_EQ(c.size(), 3u);
}
