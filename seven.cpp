// Example program
#include <iostream>
#include <string>

int main()
{
  int n = 4;
  for(int l = 2; l <= n; l++)
  {
    for(int i = 1; i <= n - l + 1; i++)
    {
     int j = i + l - 1;
     for(int k = i; k <= j-1; k++)
     {
      std::cout << "i, k: " << i << ", " << k << "\n";
      std::cout << "k + 1, j: " << k + 1 << ", " << j << "\n";
      std::cout << "i, j: " << i << ", " << j << "\n";
      std::cout << std::endl;
     }
    }
  }
}