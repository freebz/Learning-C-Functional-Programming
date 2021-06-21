/* prime_lazy.cpp */
#include <iostream>
#include <cmath>
#include "../lazyevaluation/lazyevaluation.h"

using namespace std;

Row<void*> PrimeCheck(int i)
{
  // 2를 제외한 모든 짝수는 소수가 아니다.
  if ((i % 2) == 0)
  {
    if (i == 2)
      return Row<void*>(nullptr);
    else
      return Row<void*>();
  }

  // i의 제곱근을 구한다
  int sqr = sqrt(i);

  // 9보다 작은 수 중, 소수는 홀수이며,
  // 9이상의 수 중 소수는 제곱수를 제외한 홀수다
  for (int t = 3; t <= sqr; t += 2)
  {
    if (i % t == 0)
    {
      return Row<void*>();
    }
  }

  // 1은 소수가 아니다
  if (i == 1)
    return Row<void*>();
  else
    return Row<void*>(nullptr);
}

Row<int> GenerateInfiniteIntRow(int initialNumber)
{
  return Row<int>([initialNumber]()
  {
    return Chunk<int>(
      initialNumber,
      GenerateInfiniteIntRow(
        initialNumber + 1));
  });
}

template<class T, class U>
auto MappingRow(
  Row<T> row, U func) -> Row<decltype(
    func(row.Fetch()))>
{
  using V = decltype(func(row.Fetch()));

  if (row.IsEmpty())
    return Row<V>();
  
  return Row<V>([row, func]()
  {
    return Chunk<V>(func(
      row.Fetch()),
      MappingRow(
        row.ShiftLastToFirst(),
	func));
  });
}

  
template<class T, class U>
auto MappingRowByValue(
  Row<T> row, U func) -> Row<decltype(func())>
{
  using V = decltype(func());

  if (row.IsEmpty())
    return Row<V>();

  return Row<V>([row, func]()
  {
    return Chunk<V>(
      func(),
      MappingRowByValue(
        row.ShiftLastToFirst(),
	func));
  });
}

template<class T> Row<T>
ConvertChunkToRow(
  T value)
{
  return Row<T>([value]()
  {
    return Chunk<T>(value);
  });
}

template<class T> Row<T>
JoiningAllRows(
  Row<Row<T>> rowOfRows)
{
  while (!rowOfRows.IsEmpty() &&
    rowOfRows.Fetch().IsEmpty())
  {
    rowOfRows = rowOfRows.ShiftLastToFirst();
  }

  if (rowOfRows.IsEmpty())
    return Row<T>();

  return Row<T>([rowOfRows]()
  {
    Row<T> row = rowOfRows.Fetch();

    return Chunk<T>(
      row.Fetch(),
      ConcatenateRows(
        row.ShiftLastToFirst(),
	JoiningAllRows(
          rowOfRows.ShiftLastToFirst())));
  });
}

template<class T, class U> Row<T>
Binding(Row<T> row, U func)
{
  return JoiningAllRows(MappingRow(row, func));
}

template<class T, class U>
auto JoiningPrimeNumber(
  Row<T> row, U func) -> decltype(func())
{
  return JoiningAllRows(
    MappingRowByValue(row, func));
}

Row<int> GenerateInfinitePrimeRow()
{
  return Binding(
    GenerateInfiniteIntRow(1),
    [](int i)
    {
      return JoiningPrimeNumber(
        PrimeCheck(i),
	[i]()
	{
	  return ConvertChunkToRow(i);
	});
    });
}

auto main() -> int
{
  cout << "[prime_lazy.cpp]" << endl;

  // 무한 소수 리스트를 생성한다
  Row<int> r = GenerateInfinitePrimeRow();

  // 무한 소수 리스트에서 처음 100개의 요소를 가져온다
  Row<int> firstAHundredPrimeNumbers = r.Pick(100);

  // 100개의 소수를 출력한다
  cout << "List of the first 100 prime numbers:" << endl;
  ForEach(
    move(firstAHundredPrimeNumbers),
    [](int const & i)
    {
      cout << i << "\t";
    });
  
  return 0;
}
