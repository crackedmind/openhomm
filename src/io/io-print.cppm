export module openhomm.io.print;

//import <format>;
import std;
import <cstdio>;

export {
    namespace io {
        // partial implementation of http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p2093r10.html
        // TODO: replace std::string
        // TODO: utf-8
        template<class... Args>
        void print(FILE* stream, std::string_view fmt, Args&&... args) {
            std::string buffer;
            std::vformat_to(std::back_inserter(buffer), fmt, std::make_format_args(std::forward<Args>(args)...));
            fwrite(buffer.data(), buffer.size(), 1, stream);
        }

        template<class... Args>
        void print(std::string_view fmt, Args&&... args) {
            print(stdout, fmt, std::forward<Args>(args)...);
        }

        template<class... Args>
        void println(FILE* stream, std::string_view fmt, Args&&... args) {
            std::string buffer;
            std::vformat_to(std::back_inserter(buffer), fmt, std::make_format_args(std::forward<Args>(args)...));
            buffer.push_back('\n');
            fwrite(buffer.data(), buffer.size(), 1, stream);
        }

        template<class... Args>
        void println(std::string_view fmt,  Args&&... args) {
            println(stdout, fmt, std::forward<Args>(args)...);
        }
    }
}
