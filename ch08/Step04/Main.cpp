/* Main.cpp - Step04 */
#include <iostream>
#include "Customer.h"

using namespace std;

vector<Customer> RegisterCustomers()
{
  int i = 0;
  bool b = false;

  vector<Customer> returnValue;

  // 고객 이름으로 nameList 초기화
  vector<string> nameList =
  {
    "William",
    "Aiden",
    "Rowan",
    "Jamie",
    "Quinn",
    "Haiden",
    "Logan",
    "Emerson",
    "Sherlyn",
    "Molly"
  };

  for (auto name : nameList)
  {
    // Customer 객체를 생성하고
    // 각 멤버 변수 값을 채운다
    Customer c;
    c.id = i++;
    c.name = name;
    c.address = "somewhere";
    c.phoneNumber = "0123";
    c.email = name + "@xyz.com";
    c.isActive = b;

    // NOT 비트 연산자를 사용해서
    // false, true를 번갈아 가며 저장함
    b = !b;

    // 생성한 Customer 객체를 벡터 returnValue에 저장
    returnValue.push_back(c);
  }

  return returnValue;
}

auto main() -> int
{
  cout << "[Step04]" << endl;
  cout << "--------" << endl;

  // Customer 객체
  Customer customer;

  // 계약이 체결된 고객의 이름 목록을 구해서 콘솔에 출력
  cout << "List of active customer names:" << endl;
  vector<string> activeCustomerNames =
    customer.GetActiveCustomerNames(
      RegisterCustomers());
  for (auto &name : activeCustomerNames)
  {
    cout << name << endl;
  }

  return 0;
}
