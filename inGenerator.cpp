#include <iostream>
#include <fstream>
#include <cassert>

int main(int argc, char* argv[])
{
  std::fstream it;
  it.open("iterator", std::fstream::in);
  assert(it.good());
  int n, i;
  it >> n >> i; 
  it.close();

  std::cout << "0" << std::endl;
  std::cout << "2000.0" << std::endl;
  std::cout << n << std::endl;
  std::cout << "2" << std::endl;
  std::cout << "1" << std::endl;
  std::cout << "1000" << std::endl;
  std::cout << "25" << std::endl;
  std::cout << "500" << std::endl;
  std::cout << "0.5" << std::endl;
  std::cout << "3.0" << std::endl;
  std::cout << "1.0" << std::endl;
  std::cout << "100.0 1.0" << std::endl;
  std::cout << "-2.0";
  for(int i = 1; i < n; ++i)
    std::cout << " 0.0";
  std::cout << std::endl;
  std::cout << "200.0 1.0" << std::endl;
  std::cout << -2.0+i*0.1;
  for(int i = 1; i < n; ++i)
    std::cout << " 0.0";
  std::cout << std::endl;

  i++;
  if(i > 40)
  {
    i = 1;
    n++;
  }

  std::fstream up;
  up.open("iterator", std::fstream::out);
  assert(up.good());
  up << n << " " << i;
  up.close();
}
