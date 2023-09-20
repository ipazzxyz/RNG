#include "rng.h"

int main() {
    int a, b, c, d, x0, x1, x2;
    std::cin >> a >> b >> c >> d >> x0 >> x1 >> x2;
    RNG rng = RNG(a, b, c, d, x0, x1, x2);
    std::cout << "P = " << rng.GetP() << std::endl;
    std::cout << "N = " << rng.GetN() << std::endl;
    std::cout << "Z = " << rng.GetZ() << std::endl;
    return 0;
}