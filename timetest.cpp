#include <ctime>
#include <iostream>

using namespace std;

int main()
{
    time_t result = time(nullptr);
    // std::cout << std::asctime(std::localtime(&result))
    //           << result << " seconds since the Epoch\n";

    cout << result << endl;
}
