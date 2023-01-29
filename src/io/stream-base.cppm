export module openhomm.io.stream:stream_base;

import <cstdint>;
import std;

export namespace io {
	using streampos = size_t;
	using streamoff = size_t;

	enum class seek_origin {
		begin = 0,
		current,
		end
	};

	enum class stream_mode {
		read_only,
		read_write,
		write_only
	};

	struct stream {
		virtual ~stream() = default;

		virtual bool is_open() { return opened_; }

		virtual size_t read(void* dst, size_t size) = 0;
		virtual size_t write(const void* src, size_t size) = 0;

		virtual void seek(streamoff pos, seek_origin dir = seek_origin::begin) = 0;
		virtual streampos position() const = 0;
		virtual void flush() = 0;
		virtual bool eof() const = 0;

		template<typename T>
		T read() {
			T t{};
			read(&t, sizeof(T));
			return t;
		}

		int8_t read_s8() {
			return read<int8_t>();
		}
		uint8_t read_u8() {
			return read<uint8_t>();
		}

		int16_t read_s16() {
			return read<int16_t>();
		}

		uint16_t read_u16() {
			return read<uint16_t>();
		}

		int32_t read_s32() {
			return read<int32_t>();
		}

		uint32_t read_u32() {
			return read<uint32_t>();
		}

		int64_t read_s64() {
			return read<int64_t>();
		}

		uint64_t read_u64() {
			return read<uint64_t>();
		}

		float read_float() {
			return read<float>();
		}

		double read_double() {
			return read<double>();
		}

        void write_s8(int8_t v) {
            write(&v, sizeof(v));
        }

        void write_u8(uint8_t v) {
            write(&v, sizeof(v));
        }

        void write_s16(int16_t v) {
            write(&v, sizeof(v));
        }

        void write_u16(uint16_t v) {
            write(&v, sizeof(v));
        }

        void write_s32(int32_t v) {
            write(&v, sizeof(v));
        }

        void write_u32(uint32_t v) {
            write(&v, sizeof(v));
        }

        void write_s64(int64_t v) {
            write(&v, sizeof(v));
        }

        void write_u64(uint64_t v) {
            write(&v, sizeof(v));
        }

        void write_float(float v) {
            write(&v, sizeof(v));
        }

        void write_double(double v) {
            write(&v, sizeof(v));
        }

	protected:
		bool opened_{ false };
	};
}
