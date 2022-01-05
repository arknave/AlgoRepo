namespace std {
    template <>
    struct hash<my_class> {
        size_t operator()(my_class v) const {
            // do something smarter here
            return v.a ^ v.b;
        }
    };
}
