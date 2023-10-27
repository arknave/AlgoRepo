template <typename T, int32_t DIMS>
class Tensor {
public:
    Tensor(std::array<int32_t, DIMS> dims, T unit = T{}): dims_(std::move(dims)) {
        int32_t total = std::accumulate(dims_.begin(), dims_.end(), 1, std::multiplies<int32_t>());

        data_.assign(total, unit);
    }


    template <typename Seq>
    T& operator[](const Seq& s) {
        int32_t idx = toIndex(s);

        return data_[idx];
    }

    template <typename Seq>
    const T& operator[](const Seq& s) const {
        int32_t idx = toIndex(s);

        return data_[idx];
    }

private:
    constexpr int32_t toIndex(std::array<int32_t, DIMS> idxs) const {
        int32_t val = 0;
        for (int32_t i = 0; i < dims_.size(); ++i) {
            val *= dims_[i];
            val += idxs[i];
        }

        return val;
    }

    std::array<int32_t, DIMS> dims_;
    std::vector<T> data_;
};

// utility class for multidimensional datasets. Trades off speed for memory
// locality. Ends up being quite slow in practice, do not use
template <typename T>
class Tensor {
public:
    Tensor(std::vector<int32_t> dims, T unit = T{}): dims_(std::move(dims)) {
        int32_t total = std::accumulate(dims_.begin(), dims_.end(), 1, std::multiplies<int32_t>());

        data_.assign(total, unit);
    }


    template <typename Seq>
    T& operator[](const Seq& s) {
        int32_t idx = toIndex(s);

        return data_[idx];
    }

    template <typename Seq>
    const T& operator[](const Seq& s) const {
        int32_t idx = toIndex(s);

        return data_[idx];
    }

private:
    template <typename Seq>
    int32_t toIndex(const Seq& s) const {
        assert(s.size() == dims_.size());
        int32_t val = 0;
        for (int32_t i = 0; i < dims_.size(); ++i) {
            val *= dims_[i];
            val += s[i];
        }

        return val;
    }

    std::vector<int32_t> dims_;
    std::vector<T> data_;
};


