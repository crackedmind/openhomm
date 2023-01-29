module;

export module openhomm.math;

export import :matrix;
export import :vector;

import std;

export {
    namespace std {
        template <class T>
        struct formatter<math::vector2<T>> {
            template <typename ParseContext>
            auto parse(ParseContext& ctx) { return ctx.begin(); }

            template <typename FormatContext> requires(std::floating_point<T>)
            auto format(const math::vector2<T>& v, FormatContext& ctx) const {
                return std::format_to(ctx.out(), "vec2(x={:f}, y={:f})", v.x, v.y);
            }
            template <typename FormatContext> requires(std::integral<T>)
            auto format(const math::vector2<T>& v, FormatContext& ctx) const {
                return std::format_to(ctx.out(), "vec2(x={}, y={})", v.x, v.y);
            }
        };

        template <class T>
        struct formatter<math::vector3<T>> {
            template <typename ParseContext>
            auto parse(ParseContext& ctx) { return ctx.begin(); }

            template <typename FormatContext> requires(std::floating_point<T>)
            auto format(const math::vector3<T>& v, FormatContext& ctx) const {
                return std::format_to(ctx.out(), "vec3(x={:f}, y={:f}, z={:f})", v.x, v.y, v.z);
            }

            template <typename FormatContext> requires(std::integral<T>)
            auto format(const math::vector3<T>& v, FormatContext& ctx) const {
                return std::format_to(ctx.out(), "vec3(x={}, y={}, z={})", v.x, v.y, v.z);
            }
        };

        template <class T>
        struct formatter<math::vector4<T>> {
            template <typename ParseContext>
            auto parse(ParseContext& ctx) { return ctx.begin(); }

            template <typename FormatContext> requires(std::floating_point<T>)
            auto format(const math::vector4<T>& v, FormatContext& ctx) const {
                return std::format_to(ctx.out(), "vec4(x={:f}, y={:f}, z={:f}, w={:f})", v.x, v.y, v.z, v.w);
            }

            template <typename FormatContext> requires(std::integral<T>)
            auto format(const math::vector4<T>& v, FormatContext& ctx) const {
                return std::format_to(ctx.out(), "vec4(x={}, y={}, z={}, w={})", v.x, v.y, v.z, v.w);
            }
        };
    }
}
