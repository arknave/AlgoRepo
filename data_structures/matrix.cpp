// matrix exp
template <typename T>
struct Matrix {
    size_t n_;
    std::vector<T> data_;

    Matrix<T>(size_t n, T fill = T(0), T diag = T(0)) 
        : n_{n}
    {
        data_.resize(n_ * n_, fill);

        for (size_t i = 0; i < n_; ++i) {
            (*this)(i, i) = diag;
        }
    }

    const T& operator()(size_t i, size_t j) const {
        assert(0 <= i and i < n_);
        assert(0 <= j and j < n_);
        return data_[n_ * i + j];
    }

    T& operator()(size_t i, size_t j) {
        assert(0 <= i and i < n_);
        assert(0 <= j and j < n_);
        return data_[n_ * i + j];
    }

    Matrix<T> operator*(const Matrix<T>& b) const {
        Matrix<T> r(n_);

        for (size_t i = 0; i < n_; ++i)
            for (size_t j = 0; j < n_; ++j)
                for (size_t k = 0; k < n_; ++k)
                    r(i, j) += (*this)(i, k) * b(k, j);

        return r;
    }

    std::vector<T> operator*(const std::vector<T>& v) const {
        std::vector<T> r(n_, T(0));

        for (size_t i = 0; i < n_; ++i) {
            for (size_t j = 0; j < n_; ++j) {
                r[i] += (*this)(i, j) * v[j];
            }
        }

        return r;
    }

    Matrix<T> pow(uint64_t expo) const {
        if(!expo) return Matrix<T>(n_, T(0), T(1));
        Matrix<T> r = (*this * *this).pow(expo / 2);

        return (expo % 2) ? (r * *this) : r;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
        os << "{";
        for (size_t i = 0; i < m.n_; ++i) {
            if(i) os << "},\n ";
            os << "{";
            for (size_t j = 0; j < m.n_; ++j) {
                if(j) os << ", ";
                os << std::setw(00) << m(i, j) << std::setw(0);
            }
        }
        return os << "}}";
    }
};
