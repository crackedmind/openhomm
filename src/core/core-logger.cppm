export module openhomm.core:logger;

import std;
import <cstdint>;

import openhomm.io.print;

export namespace core {
    enum class log_level : uint8_t {
        trace,
        debug,
        info,
        warning,
        error,
        critical,
        none
    };


    template <typename... Ts>
    struct log
    {
        log(log_level level, std::string_view fmt, Ts&&... ts, const std::source_location& location = std::source_location::current()) {
            io::print("{:%F %T %z} [{}] ", std::chrono::utc_clock::now(), level);
            io::println(fmt, std::forward<Ts>(ts)...);
        }
    };

    template <typename... Ts>
    struct trace
    {
        trace(std::string_view fmt, Ts&&... ts, const std::source_location& location = std::source_location::current()) {
            log<Ts...>(log_level::trace, fmt, std::forward<Ts>(ts)..., location);
        }
    };

    template <typename... Ts>
    struct debug
    {
        debug(std::string_view fmt, Ts&&... ts, const std::source_location& location = std::source_location::current()) {
            log<Ts...>(log_level::debug, fmt, std::forward<Ts>(ts)..., location);
        }
    };

    template <typename... Ts>
    struct info
    {
        info(std::string_view fmt, Ts&&... ts, const std::source_location& location = std::source_location::current()) {
            log<Ts...>(log_level::info, fmt, std::forward<Ts>(ts)..., location);
        }
    };

    template <typename... Ts>
    struct warning
    {
        warning(std::string_view fmt, Ts&&... ts, const std::source_location& location = std::source_location::current()) {
            log<Ts...>(log_level::warning, fmt, std::forward<Ts>(ts)..., location);
        }
    };

    template <typename... Ts>
    struct error
    {
        error(std::string_view fmt, Ts&&... ts, const std::source_location& location = std::source_location::current()) {
            log<Ts...>(log_level::error, fmt, std::forward<Ts>(ts)..., location);
        }
    };

    template <typename... Ts>
    struct critical
    {
        critical(std::string_view fmt, Ts&&... ts, const std::source_location& location = std::source_location::current()) {
            log<Ts...>(log_level::critical, fmt, std::forward<Ts>(ts)..., location);
        }
    };

    template <typename... Ts>
    log(log_level level, std::format_string<Ts...> fmt, Ts&&...) -> log<Ts...>;

    template <typename... Ts>
    trace(std::string_view fmt, Ts&&...)->trace<Ts...>;
    template <typename... Ts>
    debug(std::string_view fmt, Ts&&...)->debug<Ts...>;
    template <typename... Ts>
    info(std::string_view fmt, Ts&&...)->info<Ts...>;
    template <typename... Ts>
    warning(std::string_view fmt, Ts&&...)->warning<Ts...>;
    template <typename... Ts>
    error(std::string_view fmt, Ts&&...)->error<Ts...>;
    template <typename... Ts>
    critical(std::string_view fmt, Ts&&...)->critical<Ts...>;
}

export template <>
struct std::formatter<core::log_level> : std::formatter<std::string_view> {
    template <typename FormatContext>
    auto format(core::log_level level, FormatContext& ctx) const {
        auto lvl = [level]() constexpr -> std::string_view {
            using enum core::log_level;
            switch (level) {
            case trace:     return "trace";
            case debug:     return "debug";
            case info:      return "info";
            case warning:   return "warning";
            case error:     return "error";
            case critical:  return "critical";
            default:        return "unknown";
            }
        }();
        return std::formatter<std::string_view>::format(lvl, ctx);
    }
};

export template <>
struct std::formatter<std::source_location>{
    template <typename ParseContext>
    auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const std::source_location &loc, FormatContext& ctx) const {
        return std::format_to(ctx.out(), "{}({},{})", loc.file_name(), loc.line(), loc.column());
    }
};
