/* taili_recursion_goto.cpp */
#include <iostream>

using namespace std;

void displayNumber(long long n)
{
 loop:
  // 현재 n 값을 출력한다
  cout << n << endl;

  // n값을 증가시키고, 재귀 호출을 goto로 대체한다
  n++;
  goto loop;
}

auto main() -> int
{
  cout << "[taili_recursion_goto.cpp]" << endl;

  // goto를 사용하는 displayNumber() 함수를 호출한다
  displayNumber(0);

  return 0;
}
