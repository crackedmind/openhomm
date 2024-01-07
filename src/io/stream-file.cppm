export module openhomm.io.stream:stream_file;

import std;
import <cstdio>;
import :stream_base;

#ifdef _WIN32
    #define _W(x) L##x
#else
    #define _W(x) x
#endif

export namespace io {
	struct file_stream : stream {
	protected:
		FILE* fhandle_{ nullptr };
	public: 
		file_stream(const std::filesystem::path& filename, stream_mode mode) {
            using enum stream_mode;
			auto m = [mode]() {
				switch (mode) {
				case read_only:
					return _W("rb");
				case read_write:
					return _W("w+b");
				case write_only:
					return _W("wb");
				}
				return _W("rb");
			}();
#ifdef _WIN32
			errno_t err = _wfopen_s(&fhandle_, filename.c_str(), m);
			if (err == 0)
#else
			fhandle_ = fopen(filename.c_str(), m);
			if (fhandle_ != nullptr)
#endif
				opened_ = true;
		}
		~file_stream() override {
			if (fhandle_) {
				fclose(fhandle_);
				opened_ = false;
			}
		}

		size_t read(void* dst, size_t size) override {
			return fread(dst, size, 1, fhandle_);
		}

		size_t write(const void* src, size_t size) override {
			return fwrite(src, size, 1, fhandle_);
		}

		streampos position() const override {
#ifdef _WIN32
			return _ftelli64(fhandle_);
#else
			return ftello(fhandle_);
#endif
		}

		void seek(streamoff pos, seek_origin dir = seek_origin::begin) override {
			auto seek_ = [dir]() {
				switch (dir) {
				case seek_origin::begin:
					return SEEK_SET;
				case seek_origin::current:
					return SEEK_CUR;
				case seek_origin::end:
					return SEEK_END;
				}

				return SEEK_SET;
			};
#ifdef _WIN32
			_fseeki64(fhandle_, pos, seek_());
#else
			fseeko64(fhandle_, pos, seek_());
#endif
		}

		void flush() override {
			fflush(fhandle_);
		}

		bool eof() const override {
			return feof(fhandle_);
		}
	};
}
