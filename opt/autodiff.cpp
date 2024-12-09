#include <iostream>
#include <vector>

// 自動微分のための構造体
struct Dual {
  double value;       // 関数の値
  double derivative;  // 導関数の値

  Dual(double value, double derivative)
      : value(value), derivative(derivative) {}

  // 演算子オーバーロード
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

// 関数の定義
Dual f(const Dual& x) { return x * x + Dual(2.0, 0.0) * x + Dual(1.0, 0.0); }

int main() {
  // x = 3.0 の点で関数 f(x) の値と導関数を計算
  Dual x(3.0, 1.0);  // xの初期値と導関数の初期値
  Dual result = f(x);

  std::cout << "f(x) = " << result.value << std::endl;
  std::cout << "f'(x) = " << result.derivative << std::endl;

  return 0;
}
