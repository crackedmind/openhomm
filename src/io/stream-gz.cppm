export module openhomm.io.stream:stream_gz;

import std;
import <zlib-ng.h>;
import :stream_base;

export namespace io {
	struct gzstream : stream {
	protected:
		gzFile handle_{ nullptr };
		bool opened_{ false };
	public:

		gzstream(const std::string& filename, stream_mode mode) {
			using enum stream_mode;
			const char* m = [mode]() {
				switch (mode) {
				case read_only:
					return "rb";
				case write_only:
					return "wb";
				}
				return "rb";
			}();

			handle_ = zng_gzopen(filename.c_str(), m);

			if (handle_ != nullptr)
				opened_ = true;
		}

		~gzstream() {
			if (handle_) {
				zng_gzclose(handle_);
				opened_ = false;
			}
		}

		bool is_open() { return opened_; }

		size_t read(void* dst, size_t size) override {
			return zng_gzfread(dst, size, 1, handle_);
		}

		size_t write(const void* src, size_t size) override {
			return zng_gzfwrite(src, size, 1, handle_);
		}

		streampos position() const override {
			return zng_gzoffset(handle_);
		}

		void seek(streamoff pos, seek_origin dir) override {
			auto seek_ = [dir]() {
				switch (dir) {
				case seek_origin::begin:
					return SEEK_SET;
				case seek_origin::current:
					return SEEK_CUR;
				}

				return SEEK_SET;
			}();
			zng_gzseek(handle_, pos, seek_);
		}

		void flush() override {
			zng_gzflush(handle_, Z_FINISH);
		}

		bool eof() const override {
			return zng_gzeof(handle_);
		}
	};
}
