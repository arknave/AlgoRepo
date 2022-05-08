/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Self-explanatory methods for string hashing.
 * Status: stress-tested
 */
#pragma once

// Arithmetic mod 2^64-1. 2x slower than mod 2^64 and more
// code, but works on evil test data (e.g. Thue-Morse, where
// ABBA... and BAAB... of length 2^10 hash the same mod 2^64).
// "typedef ull H;" instead if you think test data is random,
// or work mod 10^9+7 if the Birthday paradox is not a problem.
struct H {
	typedef uint64_t ull;
	ull x; H(ull x=0) : x(x) {}
#define OP(O,A,B) H operator O(H o) const { ull r = x; asm \
	(A "addq %%rdx, %0\n adcq $0,%0" : "+a"(r) : B); return r; }
	OP(+,,"d"(o.x)) OP(*,"mul %1\n", "r"(o.x) : "rdx")
	H operator-(H o) const { return *this + ~o.x; }
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};

static const H C = (ll)1e11+3; // (order ~ 3e9; random also ok)

// Class for polynomial hashing.
// Computes the polynomial hash s[0] x^n + s[1] x^(n - 1) + ... s[n - 1]
// Pass in any number of xs, and it will use all the x values and types.
// Since the outputs are all tuples, they can be compared for equality.
// Tested on kattis:powerstrings, 
template<typename... Ts>
class Hasher {
public:
    using Val = std::tuple<Ts...>;

    template <typename Seq>
    Hasher(Seq seq, Ts... coeffs): n_(seq.size()), coeffs_(coeffs...) {
        pows_.reserve(seq.size() + 1);
        pows_.emplace_back(Ts(1)...);

        prefixes_.reserve(seq.size() + 1);
        prefixes_.emplace_back(Ts(0)...);

        for (auto c : seq) {
            pows_.emplace_back(linear(0, pows_.back(), coeffs...));
            prefixes_.emplace_back(linear(c, prefixes_.back(), coeffs...));
        }
    }

    /**
     * hash [a, b)
     */
    Val hashInterval(int a, int b) const {
        return compute(prefixes_[b], prefixes_[a], pows_[b - a]);
    }
private:
    template <typename T>
    static Val linear(T c, const Val& val, Ts... coeffs) {
        return linear_impl(
            c,
            val,
            std::make_index_sequence<std::tuple_size_v<Val>>(),
            coeffs...
        );
    }

    template <typename T, size_t... I>
    static Val linear_impl(T c, const Val& val, std::index_sequence<I...>, Ts... coeffs) {
        return Val((Ts(c) + std::get<I>(val) * coeffs)...);
    }

    // return a - b * c
    static Val compute(const Val& a, const Val& b, const Val& c) {
        return compute_impl(
            a,
            b,
            c,
            std::make_index_sequence<std::tuple_size_v<Val>>()
        );
    }

    template <size_t... I>
    static Val compute_impl(const Val& a, const Val& b, const Val& c, std::index_sequence<I...>) {
        return Val((std::get<I>(a) - std::get<I>(b) * std::get<I>(c))...);
    }

    size_t n_;
    Val coeffs_;
    std::vector<Val> pows_;
    std::vector<Val> prefixes_;
};
