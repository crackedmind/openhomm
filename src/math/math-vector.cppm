module;

export module openhomm.math:vector;

import std;

export namespace math {
    template <typename T>
    struct vector2;

    template <typename T>
    struct vector3;

    template <typename T>
    struct vector4;

    namespace concepts {
        template <typename T>
        concept is_vector = requires {
            typename T::value_type;
        } && (std::is_same_v<T, vector4<typename T::value_type>> ||
              std::is_same_v<T, vector3<typename T::value_type>> ||
              std::is_same_v<T, vector2<typename T::value_type>>);
    }

    template <typename  T>
    struct vector2 final {
        using value_type = T;

        T x{}, y{};

        constexpr vector2() noexcept = default;
        ~vector2() noexcept = default;
        constexpr vector2(const vector2& other) noexcept = default;
        constexpr explicit vector2(T v) noexcept : x(v), y(v) {}
        constexpr vector2(T x, T y) noexcept : x(x), y(y) {}
        constexpr vector2(const vector3<T>& v) noexcept : x(v.x), y(v.y) {}
        constexpr vector2(const vector4<T>& v) noexcept : x(v.x), y(v.y) {}
        constexpr auto operator<=>(const vector2&) const = default;

        constexpr auto operator=(const vector2& other) noexcept -> vector2& = default;

        constexpr auto operator=(const vector3<T>& other) noexcept -> vector2& {
            this->x = other.x;
            this->y = other.y;
            return *this;
        }

        constexpr auto operator=(const vector4<T>& other) noexcept -> vector2& {
            this->x = other.x;
            this->y = other.y;
            return *this;
        }

        constexpr auto operator+(T scalar) const noexcept -> vector2 {
            return vector2{x + scalar, y + scalar};
        }

        constexpr auto operator-(T scalar) const noexcept -> vector2 {
            return vector2{x - scalar, y - scalar};
        }

        constexpr auto operator*(T scalar) const noexcept -> vector2 {
            return vector2{x * scalar, y * scalar};
        }

        constexpr auto operator/(T scalar) const noexcept -> vector2 {
            return vector2{x / scalar, y / scalar};
        }


        constexpr auto operator+(const vector2& other) const noexcept -> vector2 {
            return vector2(x + other.x, y + other.y);
        }

        constexpr auto operator-(const vector2& other) const noexcept -> vector2 {
            return vector2(x - other.x, y - other.y);
        }

        constexpr auto operator*(const vector2& other) const noexcept -> vector2 {
            return vector2(x * other.x, y * other.y);
        }

        constexpr auto operator/(const vector2& other) const noexcept -> vector2 {
            return vector2(x / other.x, y / other.y);
        }

        constexpr auto operator+=(T scalar) noexcept -> vector2& {
            this->x += scalar;
            this->y += scalar;
            return *this;
        }

        constexpr auto operator-=(T scalar) noexcept -> vector2& {
            this->x -= scalar;
            this->y -= scalar;
            return *this;
        }

        constexpr auto operator*=(T scalar) noexcept -> vector2& {
            this->x *= scalar;
            this->y *= scalar;
            return *this;
        }

        constexpr auto operator/=(T scalar) noexcept -> vector2& {
            this->x /= scalar;
            this->y /= scalar;
            return *this;
        }

        constexpr auto operator+=(const vector2& other) noexcept -> vector2& {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }

        constexpr auto operator-=(const vector2& other) noexcept -> vector2& {
            this->x -= other.x;
            this->y -= other.y;
            return *this;
        }

        constexpr auto operator*=(const vector2& other) noexcept -> vector2& {
            this->x *= other.x;
            this->y *= other.y;
            return *this;
        }

        constexpr auto operator/=(const vector2& other) noexcept -> vector2& {
            this->x /= other.x;
            this->y /= other.y;
            return *this;
        }
    };

    template <typename T>
    struct vector3 final {
        using value_type = T;

        T x{}, y{}, z{};

        constexpr vector3() noexcept = default;
        ~vector3() = default;
        constexpr vector3(const vector3& other) noexcept = default;
        constexpr explicit vector3(T v) noexcept : x(v), y(v), z(v) {}
        constexpr vector3(T x, T y, T z) noexcept : x(x), y(y), z(z) {}
        constexpr vector3(const vector4<T>& v) noexcept : x(v.x), y(v.y), z(v.z) {}
        constexpr auto operator<=>(const vector3&) const = default;

        constexpr auto operator=(const vector3& other) noexcept -> vector3& = default;

        constexpr auto operator=(const vector4<T>& other) noexcept -> vector3& {
            this->x = other.x;
            this->y = other.y;
            this->z = other.z;
            return *this;
        }

        constexpr auto operator+(T scalar) const noexcept -> vector3 {
            return vector3(x + scalar, y + scalar, z + scalar);
        }

        constexpr auto operator-(T scalar) const noexcept -> vector3 {
            return vector3(x - scalar, y - scalar, z - scalar);
        }

        constexpr auto operator*(T scalar) const noexcept -> vector3 {
            return vector3(x * scalar, y * scalar, z * scalar);
        }

        constexpr auto operator/(T scalar) const noexcept -> vector3 {
            return vector3(x / scalar, y / scalar, z / scalar);
        }

        constexpr auto operator+(const vector3& other) const noexcept -> vector3 {
            return vector3(x + other.x, y + other.y, z + other.z);
        }

        constexpr auto operator-(const vector3& other) const noexcept -> vector3 {
            return vector3(x - other.x, y - other.y, z - other.z);
        }

        constexpr auto operator*(const vector3& other) const noexcept -> vector3 {
            return vector3(x * other.x, y * other.y, z * other.z);
        }

        constexpr auto operator/(const vector3& other) const noexcept -> vector3 {
            return vector3(x / other.x, y / other.y, z / other.z);
        }

        constexpr auto operator+=(T scalar) noexcept -> vector3& {
            this->x += scalar;
            this->y += scalar;
            this->z += scalar;
            return *this;
        }

        constexpr auto operator-=(T scalar) noexcept -> vector3& {
            this->x -= scalar;
            this->y -= scalar;
            this->z -= scalar;
            return *this;
        }

        constexpr auto operator*=(T scalar) noexcept -> vector3& {
            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;
            return *this;
        }

        constexpr auto operator/=(T scalar) noexcept -> vector3& {
            this->x /= scalar;
            this->y /= scalar;
            this->z /= scalar;
            return *this;
        }

        constexpr auto operator+=(const vector3& other) noexcept -> vector3& {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            return *this;
        }

        constexpr auto operator-=(const vector3& other) noexcept -> vector3& {
            this->x -= other.x;
            this->y -= other.y;
            this->z -= other.z;
            return *this;
        }

        constexpr auto operator*=(const vector3& other) noexcept -> vector3& {
            this->x *= other.x;
            this->y *= other.y;
            this->z *= other.z;
            return *this;
        }

        constexpr auto operator/=(const vector3& other) noexcept -> vector3& {
            this->x /= other.x;
            this->y /= other.y;
            this->z /= other.z;
            return *this;
        }
    };

    template <typename T>
    struct vector4 final {
        using value_type = T;

        T x{}, y{}, z{}, w{};

        constexpr vector4() noexcept = default;
        ~vector4() = default;
        constexpr vector4(const vector4& other) noexcept = default;
        constexpr explicit vector4(T v) noexcept : x(v), y(v), z(v), w(v) {}
        constexpr vector4(T x, T y, T z, T w) noexcept : x(x), y(y), z(z), w(w) {}
        constexpr auto operator=(const vector4& other) noexcept -> vector4& = default;
        constexpr auto operator<=>(const vector4&) const = default;

        constexpr auto operator+(T scalar) const noexcept -> vector4 {
            return vector4(x + scalar, y + scalar, z + scalar, w + scalar);
        }

        constexpr auto operator-(T scalar) const noexcept -> vector4 {
            return vector4(x - scalar, y - scalar, z - scalar, w - scalar);
        }

        constexpr auto operator*(T scalar) const noexcept -> vector4 {
            return vector4(x * scalar, y * scalar, z * scalar, w * scalar);
        }

        constexpr auto operator/(T scalar) const noexcept -> vector4 {
            return vector4(x / scalar, y / scalar, z / scalar, w / scalar);
        }

        constexpr auto operator+(const vector4& other) const noexcept -> vector4 {
            return vector4(x + other.x, y + other.y, z + other.z, w + other.w);
        }

        constexpr auto operator-(const vector4& other) const noexcept -> vector4 {
            return vector4(x - other.x, y - other.y, z - other.z, w - other.w);
        }

        constexpr auto operator*(const vector4& other) const noexcept -> vector4 {
            return vector4(x * other.x, y * other.y, z * other.z, w * other.w);
        }

        constexpr auto operator/(const vector4& other) const noexcept -> vector4 {
            return vector4(x / other.x, y / other.y, z / other.z, w / other.w);
        }

        constexpr auto operator+=(T scalar) noexcept -> vector4& {
            this->x += scalar;
            this->y += scalar;
            this->z += scalar;
            this->w += scalar;
            return *this;
        }

        constexpr auto operator-=(T scalar) noexcept -> vector4& {
            this->x -= scalar;
            this->y -= scalar;
            this->z -= scalar;
            this->w -= scalar;
            return *this;
        }

        constexpr auto operator*=(T scalar) noexcept -> vector4& {
            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;
            this->w *= scalar;
            return *this;
        }

        constexpr auto operator/=(T scalar) noexcept -> vector4& {
            this->x /= scalar;
            this->y /= scalar;
            this->z /= scalar;
            this->w /= scalar;
            return *this;
        }

        constexpr auto operator+=(const vector4& other) noexcept -> vector4& {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            this->w += other.w;
            return *this;
        }

        constexpr auto operator-=(const vector4& other) noexcept -> vector4& {
            this->x -= other.x;
            this->y -= other.y;
            this->z -= other.z;
            this->w -= other.w;
            return *this;
        }

        constexpr auto operator*=(const vector4& other) noexcept -> vector4& {
            this->x *= other.x;
            this->y *= other.y;
            this->z *= other.z;
            this->w *= other.w;
            return *this;
        }

        constexpr auto operator/=(const vector4& other) noexcept -> vector4& {
            this->x /= other.x;
            this->y /= other.y;
            this->z /= other.z;
            this->w /= other.w;
            return *this;
        }
    };

    template<typename T>
    [[nodiscard]] constexpr auto dot(const vector2<T>& a, const vector2<T>& b) noexcept {
        return a.x * b.x + a.y * b.y;
    }

    template<typename T>
    [[nodiscard]] constexpr auto dot(const vector3<T>& a, const vector3<T>& b) noexcept {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    template<typename T>
    [[nodiscard]] constexpr auto dot(const vector4<T>& a, const vector4<T>& b) noexcept {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    template<typename T> requires(concepts::is_vector<T> && std::floating_point<typename T::value_type>)
    [[nodiscard]] constexpr auto length(const T & a) {
        return sqrt(dot(a, a));
    }

    using  vec2 = vector2<float>;
    using dvec2 = vector2<double>;
    using ivec2 = vector2<int>;
    using uvec2 = vector2<unsigned int>;

    using  vec3 = vector3<float>;
    using dvec3 = vector3<double>;
    using ivec3 = vector3<int>;
    using uvec3 = vector3<unsigned int>;

    using  vec4 = vector4<float>;
    using dvec4 = vector4<double>;
    using ivec4 = vector4<int>;
    using uvec4 = vector4<unsigned int>;
}
