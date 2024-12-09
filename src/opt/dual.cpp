#include <iostream>
#include <vector>

// 自動微分のための構造体
struct Dual {
  double value;       // 関数の値
  double derivative;  // 導関数の値

  Dual(double value) : value(value), derivative(0.) {}

  // キャストを定義
  Dual(double value, double derivative)
      : value(value), derivative(derivative) {}

  // 演算子オーバーロードで微分規則を定義
  Dual operator+(const Dual& other) const {
    return Dual(value + other.value, derivative + other.derivative);
  }

  Dual operator-(const Dual& other) const {
    return Dual(value - other.value, derivative - other.derivative);
  }

  Dual operator*(const Dual& other) const {
    return Dual(value * other.value,
                value * other.derivative + derivative * other.value);
  }

  Dual operator/(const Dual& other) const {
    return Dual(value / other.value,
                (derivative * other.value - value * other.derivative) /
                    (other.value * other.value));
  }
};

// テンプレートで関数定義をすれば微分可能
template <typename T>
T f(const T& x) {
  return x * x + T(2.0) * x + T(1.0);
}

int main() {
  // double での計算
  const double x_double = 3.0;
  const auto y_double = f<decltype(x_double)>(x_double);
  std::cout << "f(x_double) = " << y_double << std::endl;

  // Dual での計算
  const Dual x_dual(3.0, 1.0);  // x = 3.0 の点で関数 f(x) の値と導関数を計算
  const auto y_dual = f<decltype(x_dual)>(x_dual);

  std::cout << "f(x_dual) = " << y_dual.value << std::endl;
  std::cout << "f'(x_dual) = " << y_dual.derivative << std::endl;

  return 0;
}
