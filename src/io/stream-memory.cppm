export module openhomm.io.stream:stream_memory;

import :stream_base;
import std;
import <cstring>;


export namespace io {
    struct memory_stream : stream {
    protected:
        using container_type = int8_t;
        streampos position_ = 0;
        std::vector<int8_t> data_;
        size_t data_size_ = 0;
    public:
        memory_stream() = default;

        memory_stream(size_t size) : data_size_(size) {
            data_.resize(size);

            opened_ = true;
        }

        memory_stream(void* ptr, size_t size) : data_size_(size) {
            data_.resize(size);

            auto ptr_cast = static_cast<uint8_t*>(ptr);

            data_.assign(ptr_cast, ptr_cast + size);

            opened_ = true;
        }

        memory_stream(std::vector<int8_t>&& data) noexcept {
            data_ = std::move(data);
        }

        void set_data(std::vector<int8_t>&& data) {
            data_size_ = data.size();
            data_ = std::move(data);
        }

        int8_t* get_data() {
            return data_.data();
        }

        const int8_t* get_data() const {
            return data_.data();
        }

        virtual size_t read(void* dst, size_t size) override {
            memcpy(dst, data_.data(), size);
            position_ += size;
            return 0;
        }

        virtual size_t write(const void* src, size_t size) override {
            return 0;
        }

        virtual void seek(streamoff pos, seek_origin dir = seek_origin::begin) override {
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

        virtual streampos position() const override {
            return position_;
        }

        virtual void flush() override {}

        virtual bool eof() const override {
            return position_ >= data_size_;
        }
    };
}
