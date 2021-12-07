export module openhomm.io:stream_file;

import <cstdio>;
import <string>;
import :stream_base;

export {
	namespace io {
		struct file_stream : stream {
		protected:
			FILE* fhandle_{ nullptr };
		public:
			file_stream(const std::string& filename, stream_mode mode) {
				const char* m = [mode]() {
					switch (mode) {
					case read_only:
						return "rb";
					case read_write:
						return "w+b";
					case write_only:
						return "wb";
					}
					return "rb";
				}();
#ifdef _WIN32
				errno_t err = fopen_s(&fhandle_, filename.c_str(), m);
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

			void seek(streamoff pos, seek_origin dir) override {
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
}