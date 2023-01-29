module;

export module openhomm.math:matrix;

import std;
import :vector;

export namespace math {
    template <typename T>
    struct matrix4 final {
        using value_type = T;
        using col_type = vector4<T>;

        col_type value[4] = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };

        constexpr matrix4() noexcept = default;
        constexpr matrix4(const matrix4& other) noexcept = default;
        constexpr matrix4& operator=(const matrix4& other) noexcept = default;
        constexpr matrix4(const T& x1, const T& y1, const T& z1, const T& w1,
                          const T& x2, const T& y2, const T& z2, const T& w2,
                          const T& x3, const T& y3, const T& z3, const T& w3,
                          const T& x4, const T& y4, const T& z4, const T& w4) noexcept
        : value{{x1, y1, z1, w1},
                {x2, y2, z2, w2},
                {x3, y3, z3, w3},
                {x4, y4, z4, w4}}
        {}

        constexpr matrix4(const col_type& r1, const col_type& r2, const col_type& r3, const col_type& r4) noexcept
        : value{r1, r2, r3, r4} {}
    };

    using  mat4 = matrix4<float>;
    using dmat4 = matrix4<double>;
}
