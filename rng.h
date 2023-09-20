#include <iostream>

inline uint64_t pow2(uint64_t num) {
    return num * num;
}

class RNG {
private:
    uint64_t x0_, x1_, x2_;
    uint64_t a_, b_, c_, d_, P_ = -1, N_ = -1;
    double Z_ = -1;

    [[nodiscard]] uint64_t x(uint64_t x0, uint64_t x1, uint64_t x2) const {
        return ((a_ * x2 % d_ + b_ * x1 % d_) % d_ + c_ * x0 % d_) % d_;
    }

public:
    RNG(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t x0, uint64_t x1, uint64_t x2):
            a_(a), b_(b), c_(c), d_(d), x0_(x0), x1_(x1), x2_(x2) {};

    uint64_t GetP() {
        if (P_ != - 1) {
            return P_;
        }
        P_ = 0;

        uint64_t x0 = x0_, x1 = x1_, x2 = x2_,
            y0 = x0_, y1 = x1_, y2 = x2_;

        do {
            uint64_t tmp = x(x0, x1, x2);
            x0 = x1;
            x1 = x2;
            x2 = tmp;

            uint64_t tmp1 = x(y0, y1, y2), tmp2 = x(y1, y2, tmp1);
            y0 = y2;
            y1 = tmp1;
            y2 = tmp2;

            ++P_;
        } while (x0 != y0 || x1 != y1 || x2 != y2);

        for (uint64_t i = 0; i < P_ / 2; ++i) {
            uint64_t tmp = x(x0, x1, x2);
            x0 = x1;
            x1 = x2;
            x2 = tmp;

            if (x0 == y0 && x1 == y1 && x2 == y2) {
                P_ = i + 1;
                break;
            }
        }

        return P_;
    }

    uint64_t GetN() {
        if (N_ != -1) {
            return N_;
        }
        N_ = 0;

        if (P_ == -1) {
            GetP();
        }

        uint64_t x0 = x0_, x1 = x1_ , x2 = x2_,
                y0 = x0_, y1 = x1_, y2 = x2_;

        for (uint64_t i = 0; i < P_; ++i) {
            uint64_t tmp = x(y0, y1, y2);
            y0 = y1;
            y1 = y2;
            y2 = tmp;
        }

        while (x0 != y0 || x1 != y1 || x2 != y2) {
            uint64_t tmp = x(x0, x1, x2);
            x0 = x1;
            x1 = x2;
            x2 = tmp;

            tmp = x(y0, y1, y2);
            y0 = y1;
            y1 = y2;
            y2 = tmp;

            ++N_;
        }

        return N_;
    }

    double GetZ() {
        if (Z_ != -1) {
            return Z_;
        }
        Z_ = 0;

        uint64_t x0 = x0_, x1 = x1_, x2 = x2_;
        uint64_t N[20];

        for (uint64_t & i : N) {
            i = 0;
        }

        for (uint64_t i = 0; i < 397; ++i) {
            ++N[static_cast<uint64_t>(static_cast<double>(x0) * 20 / static_cast<double>(d_))];

            uint64_t tmp = x(x0, x1, x2);
            x0 = x1;
            x1 = x2;
            x2 = tmp;
        }
        ++N[static_cast<uint64_t>(static_cast<double>(x0) / static_cast<double>(d_) * 20)];
        ++N[static_cast<uint64_t>(static_cast<double>(x1) / static_cast<double>(d_) * 20)];
        ++N[static_cast<uint64_t>(static_cast<double>(x2) / static_cast<double>(d_) * 20)];

        for (uint64_t i : N) {
            Z_ += static_cast<double>(pow2(i - 20)) / 400.;
        }

        return Z_;
    }

    [[maybe_unused]] void Print(uint64_t n) {
        uint64_t x0 = x0_, x1 = x1_, x2 = x2_;

        for (uint64_t i = 0; i < n - 3; ++i) {
            std::cout << x0 << std::endl << x2 << std::endl;
            uint64_t tmp = x(x0, x1, x2);
            x0 = x1;
            x1 = x2;
            x2 = tmp;
        }
        std::cout << x0 << std::endl << x1 << std::endl << x2 << std::endl;
   }
};