module;
#include <format>
export module openhomm.math;

export import :matrix;
export import :vector;

export {
    namespace std {
        template <class T>
        struct formatter<math::vector2<T>> {
            template <typename ParseContext>
            auto parse(ParseContext& ctx) { return ctx.begin(); }

            template <typename FormatContext>
            auto format(const math::vector2<T>& v, FormatContext& ctx) {
                return std::format_to(ctx.out(), "vec3(x={}, y={}, z={}, w={})", v.x, v.y);
            }
        };

        template <class T>
        struct formatter<math::vector3<T>> {
            template <typename ParseContext>
            auto parse(ParseContext& ctx) { return ctx.begin(); }

            template <typename FormatContext>
            auto format(const math::vector3<T>& v, FormatContext& ctx) {
                return std::format_to(ctx.out(), "vec3(x={}, y={}, z={}, w={})", v.x, v.y, v.w);
            }
        };

        template <class T>
        struct formatter<math::vector4<T>> {
            template <typename ParseContext>
            auto parse(ParseContext& ctx) { return ctx.begin(); }

            template <typename FormatContext>
            auto format(const math::vector4<T>& v, FormatContext& ctx) {
                return std::format_to(ctx.out(), "vec4(x={}, y={}, z={}, w={})", v.x, v.y, v.w, v.z);
            }
        };
    }
}