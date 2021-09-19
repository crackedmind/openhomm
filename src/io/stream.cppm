module;

export module openhomm.io;

import <cstdint>;
import <cstdio>;
import <cstring>;
import <string>;
import thirdparty.zlib;

export {
	namespace io {
		using streampos = long long;
		using streamoff = long long;

		class stream {
		public:
			enum class seek_origin {
				begin = 0,
				current,
				end
			};

			virtual ~stream() = default;

			virtual size_t read(void* dst, size_t size) = 0;
			virtual size_t write(const void* src, size_t size) = 0;

			virtual void seek(streamoff pos, seek_origin dir = seek_origin::begin) = 0;
			virtual streampos position() = 0;
			virtual void flush() = 0;

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
		};

		class memory_stream : public stream {
		protected:
			streampos position_ = 0;
			void* data_ = nullptr;
			size_t data_size_ = 0;
		public:
			memory_stream(void* ptr, size_t size) : data_(ptr), data_size_(size) {
			}

			~memory_stream() override = default;

			size_t read(void* dst, size_t size) override {
				memcpy(dst, (uint8_t*)data_ + position_, size);
				position_ += size;
				return size;
			}

			size_t write(const void* src, size_t size) override {
				memcpy((uint8_t*)data_ + position_, src, size);
				position_ += size;
				return size;
			}

			streampos position() override {
				return position_;
			}

			void flush() override {
			}

			void seek(streamoff pos, seek_origin dir = seek_origin::begin) override {

				switch (dir) {
				case seek_origin::begin:
					position_ = pos;
					break;
				case seek_origin::current:
				{
					streampos new_position = position_ + pos;
					position_ = new_position;
				}
				break;
				case seek_origin::end:
					position_ = data_size_ + pos;
					break;
				}
			}
		};

		class file_stream : public stream {
		protected:
			FILE* fhandle_{ nullptr };
			bool opened_{ false };
		public:

			enum stream_mode {
				ReadOnly,
				ReadWrite,
				WriteOnly
			};

			static constexpr stream_mode read_only = stream_mode::ReadOnly;
			static constexpr stream_mode read_write = stream_mode::ReadWrite;
			static constexpr stream_mode write_only = stream_mode::WriteOnly;

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

			bool is_open() { return opened_; }

			size_t read(void* dst, size_t size) override {
				return fread(dst, size, 1, fhandle_);
			}

			size_t write(const void* src, size_t size) override {
				return fwrite(src, size, 1, fhandle_);
			}

			streampos position() override {
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
		};

		class gzstream : public stream {
		protected:
			gzFile handle_ { nullptr };
			bool opened_{ false };
		public:
			enum stream_mode {
				ReadOnly,
				WriteOnly
			};

			static constexpr stream_mode read_only = stream_mode::ReadOnly;
			static constexpr stream_mode write_only = stream_mode::WriteOnly;

			gzstream(const std::string& filename, stream_mode mode) {
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

			streampos position() override {
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
				zng_gzflush(handle_, ZNG_FINISH);
			}
		};
	}
}