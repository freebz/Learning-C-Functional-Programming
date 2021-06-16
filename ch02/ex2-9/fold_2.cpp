/* fold_2.cpp */
#include <vector>
#include <numeric>
#include <functional>
#include <iostream>

using namespace std;

// 함수 처리 흐름을 로깅하기 위한 함수
int addition(const int& x, const int& y)
{
  cout << x << " + " << y << endl;
  return x + y;
}

int main()
{
  cout << "[fold_2.cpp]" << endl;

  // 몇 개의 정수를 벡터에 추가한다
  vector<int> numbers = { 0, 1, 2, 3, 4 };

  // 벡터의 각 요소의 합을
  // 왼쪽부터, foldl 타입으로 계산한다
  cout << "foldl" << endl;
  auto foldl = accumulate(
    begin(numbers),
    end(numbers),
    0,
    addition);

  // 벡터의 각 요소의 합을
  // 오른쪽부터, foldr 타입으로 계산한다
  cout << endl << "foldr" << endl;
  auto foldr = accumulate(
    rbegin(numbers),
    rend(numbers),
    0,
    addition);

  cout << endl;
  
  // 계산 결과를 출력한다
  cout << "foldl result = " << foldl << endl;
  cout << "foldr result = " << foldr << endl;

  return 0;
}
