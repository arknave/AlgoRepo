#include <bits/stdc++.h>

using C = std::complex<double>;
void fft(std::vector<C>& a) {
	int32_t n = a.size();
    int32_t L = 31 - __builtin_clz(n);
    // below is 10% faster if double, but less complex.
	static std::vector<std::complex<long double>> R(2, 1.0L);
	static std::vector<C> rt(2, 1.0);

	for (static int32_t k{2}; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = std::polar(1.0L, std::acos(-1.0L) / k);
        for (auto i{k}; i < 2 * k; ++i) {
            rt[i] = R[i] = (i & 1) ? R[i / 2] * x : R[i / 2];
        }
	}

    // reversed binary order
    std::vector<int32_t> rev(n, 0);
    for (auto i{0}; i < n; ++i) {
        rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    }
    for (auto i{0}; i < n; ++i) {
        if (i < rev[i])
            std::swap(a[i], a[rev[i]]);
    }

	for (auto k{1}; k < n; k *= 2) {
		for (auto i{0}; i < n; i += 2 * k) {
            for (auto j{0}; j < k; ++j) {
                // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)
                auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];
                C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
		}
    }
}

// See http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
// Given two real valued polynomials a and b, computes the convolution of a and b.
// Does so by making a new polynomial with real part a and complex part b and uses one fewer FFT operation.
std::vector<double> conv(const std::vector<double>& a, const std::vector<double>& b) {
	if (a.empty() || b.empty()) return {};
    std::vector<double> res(a.size() + b.size() - 1);

	int32_t L = 32 - __builtin_clz(static_cast<int32_t>(res.size()));
    int32_t n = 1 << L;

    std::vector<C> in(n), out(n);
    std::copy(a.begin(), a.end(), in.begin());
    for (auto i{0}; i < b.size(); ++i) {
        in[i].imag(b[i]);
    }

	fft(in);
	for (auto& x : in) {
        x *= x;
    }
    for (auto i{0}; i < n; ++i) {
        out[i] = in[-i & (n - 1)] - std::conj(in[i]);
    }
	fft(out);
    for (auto i{0}; i < res.size(); ++i) {
        res[i] = out[i].imag() / (4 * n);
    }

	return res;
}

std::vector<C> slowConv(const std::vector<C>& a, const std::vector<C>& b) {
    if (a.empty() || b.empty()) return {};
	int32_t L = 32 - __builtin_clz(static_cast<int32_t>(res.size()));
    int32_t n = 1 << L;

    std::vector<C> fullA(n, {}), fullB(n, {});

    std::copy(a.begin(), a.end(), fullA.begin());
    std::copy(b.begin(), b.end(), fullB.begin());

    fft(fullA);
    fft(fullB);

    for (auto i{0}; i < n; ++i) {
        fullA[i] *= fullB[i];
    }

    fft(fullA);

    std::vector<C> res(a.size() + b.size() - 1);
    for (auto i{0}; i < res.size(); ++i) {
        res[i] = fullA[i] / n;
    }

    return res;
}
