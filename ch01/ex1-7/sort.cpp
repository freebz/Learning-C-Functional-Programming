/* sort.cpp */
#include <vector>
#include <algorithm>
#include <iostream>

bool comparer(int a, int b)
{
  return (a > b);
}

auto main() -> int
{
  std::cout << "[sort.cpp]" << std::endl;

  // 여러 개의 정수로 벡터 초기화
  std::vector<int> vect = { 20, 43, 11, 78, 5, 96 };

  // 벡터의 각 요소 출력
  std::cout << "Original Data : ";
  for (auto v : vect)
    std::cout << v << " ";
  std::cout << std::endl;

  // 벡터 요소를 오름차순으로 정렬
  std::sort(std::begin(vect), std::end(vect));

  // 오름차순으로 정렬된 벡터 출력
  std::cout << "Ascending Sorted : ";
  for (auto v : vect)
    std::cout << v << " ";
  std::cout << std::endl;

  // compare를 사용해 내림차순으로 정렬
  std::sort(std::begin(vect), std::end(vect), comparer);

  // 내림차순으로 정렬된 벡터 출력
  std::cout << "Descending Sorted: ";
  for (auto v : vect)
    std::cout << v << " ";
  std::cout << std::endl;

  return 0;
}
