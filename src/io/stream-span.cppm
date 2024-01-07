export module openhomm.io.stream:stream_span;

import <cstring>;
import :stream_base;

export namespace io {

	struct span_stream : stream {
	protected:
		streampos position_ = 0;
		void* data_ = nullptr;
		size_t data_size_ = 0;
	public:
		span_stream(void* ptr, size_t size) : data_(ptr), data_size_(size) {
			opened_ = true;
		}

		~span_stream() override {
			opened_ = false;
		}

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

		streampos position() const override {
			return position_;
		}

		void flush() override {
		}

		bool eof() const override {
			return position_ >= data_size_;
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
}
