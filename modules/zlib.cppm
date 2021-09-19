module;
#include <zlib-ng.h>
export module thirdparty.zlib;

export {
	// enums
	enum ZngFlushValues {
		ZNG_NO_FLUSH = Z_NO_FLUSH,
		ZNG_PARTIAL_FLUSH = Z_PARTIAL_FLUSH,
		ZNG_SYNC_FLUSH = Z_SYNC_FLUSH,
		ZNG_FULL_FLUSH = Z_FULL_FLUSH,
		ZNG_FINISH = Z_FINISH,
		ZNG_BLOCK = Z_BLOCK,
		ZNG_TREES = Z_TREES
	};

	enum ZngErrorCodes {
		ZNG_OK = Z_OK,
		ZNG_STREAM_END = Z_STREAM_END,
		ZNG_NEED_DICT = Z_NEED_DICT,
		ZNG_ERRNO = Z_ERRNO,
		ZNG_STREAM_ERROR = Z_STREAM_ERROR,
		ZNG_DATA_ERROR = Z_DATA_ERROR,
		ZNG_MEM_ERROR = Z_MEM_ERROR,
		ZNG_BUF_ERROR = Z_BUF_ERROR,
		ZNG_VERSION_ERROR = Z_VERSION_ERROR
	};

	enum ZngCompressionLevels {
		ZNG_NO_COMPRESSION = Z_NO_COMPRESSION,
		ZNG_BEST_SPEED = Z_BEST_SPEED,
		ZNG_BEST_COMPRESSION = Z_BEST_COMPRESSION,
		ZNG_DEFAULT_COMPRESSION = Z_DEFAULT_COMPRESSION
	};

	enum ZngCompressionStrategies {
		ZNG_FILTERED = Z_FILTERED,
		ZNG_HUFFMAN_ONLY = Z_HUFFMAN_ONLY,
		ZNG_RLE = Z_RLE,
		ZNG_FIXED = Z_FIXED,
		ZNG_DEFAULT_STRATEGY = Z_DEFAULT_STRATEGY
	};

	// types
	using ::zng_stream;
	using ::zng_gz_header;
	using ::gzFile;

	// functions
	using ::zng_uncompress;
	using ::zng_uncompress2;
	using ::zng_inflate;
	using ::zng_inflateInit_;
	using ::zng_inflateEnd;

	using ::zng_gzopen;
	using ::zng_gzbuffer;
	using ::zng_gzread;
	using ::zng_gzclose;
	using ::zng_gzwrite;
	using ::zng_gzseek;
	using ::zng_gzflush;
	using ::zng_gzrewind;
	using ::zng_gztell;
	using ::zng_gzoffset;
	using ::zng_gzeof;
	using ::zng_gzerror;
	using ::zng_gzclearerr;
}