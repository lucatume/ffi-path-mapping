/*
 * This file has been assembled based on the following repositories:
 * https://github.com/gabrielrcouto/awesome-php-ffi
 * https://github.com/lisachenko/z-engine
 * https://github.com/chopins/ffi-ext
 */

char *strdup(const char *s);

struct __sFile
{
		int unused;
};

typedef struct __sFILE FILE;

typedef uint64_t zend_ulong;
typedef int64_t zend_long;
typedef size_t (*zend_stream_fsizer_t)(void* handle);
typedef ssize_t (*zend_stream_reader_t)(void* handle, char *buf, size_t len);
typedef void   (*zend_stream_closer_t)(void* handle);
typedef struct _zend_array zend_array;
typedef struct _zend_array HashTable;
typedef struct _zval_struct zval;
typedef struct _zend_object zend_object;
typedef struct _zend_resource zend_resource;
typedef struct _zend_reference zend_reference;
typedef struct _zend_ast_ref    zend_ast_ref;
typedef struct _zend_class_entry     zend_class_entry;
typedef union  _zend_function        zend_function;
typedef unsigned char zend_uchar;
typedef void (*dtor_func_t)(zval *pDest);

typedef struct _zend_stream {
		void        *handle;
		int         isatty;
		zend_stream_reader_t   reader;
		zend_stream_fsizer_t   fsizer;
		zend_stream_closer_t   closer;
} zend_stream;

typedef struct _zend_refcounted_h {
		uint32_t         refcount;          /* reference counter 32-bit */
		union {
				uint32_t type_info;
		} u;
} zend_refcounted_h;

typedef struct _zend_string {
		zend_refcounted_h gc;
		zend_ulong        h;                /* hash value */
		size_t            len;
		char              val[1];
} zend_string;

typedef struct _zend_string zend_string;

struct _zval_struct {
		union {
				zend_long         lval;             /* long value */
				double            dval;             /* double value */
				zend_refcounted_h  *counted;
				zend_string      *str;
				zend_array       *arr;
				zend_object      *obj;
				zend_resource    *res;
				zend_reference   *ref;
				zend_ast_ref     *ast;
				zval             *zv;
				void             *ptr;
				zend_class_entry *ce;
				zend_function    *func;
				struct {
						uint32_t w1;
						uint32_t w2;
				} ww;
		} value;
		union {
				struct {
						zend_uchar    type;         /* active type */
						zend_uchar    type_flags;
						zend_uchar    const_flags;
						zend_uchar    reserved;     /* call info for EX(This) */
				} v;
				uint32_t type_info;
		} u1;
		union {
				uint32_t     var_flags;
				uint32_t     next;                 /* hash collision chain */
				uint32_t     cache_slot;           /* literal cache slot */
				uint32_t     lineno;               /* line number (for ast nodes) */
				uint32_t     num_args;             /* arguments number for EX(This) */
				uint32_t     fe_pos;               /* foreach position */
				uint32_t     fe_iter_idx;          /* foreach iterator index */
		} u2;
};

typedef struct _Bucket {
		zval              val;
		zend_ulong        h;                /* hash value (or numeric index)   */
		zend_string      *key;              /* string key or NULL for numerics */
} Bucket;

typedef struct _zend_array {
		zend_refcounted_h gc;
		union {
				struct {
						zend_uchar    flags;
						zend_uchar    _unused;
						zend_uchar    nIteratorsCount;
						zend_uchar    _unused2;
				} v;
				uint32_t flags;
		} u;
		uint32_t          nTableMask;
		Bucket           *arData;
		uint32_t          nNumUsed;
		uint32_t          nNumOfElements;
		uint32_t          nTableSize;
		uint32_t          nInternalPointer;
		zend_long         nNextFreeElement;
		dtor_func_t       pDestructor;
};

typedef enum {
		ZEND_HANDLE_FILENAME,
		ZEND_HANDLE_FP,
		ZEND_HANDLE_STREAM
} zend_stream_type;

typedef unsigned char zend_bool;

typedef struct _zend_file_handle {
		union {
				FILE          *fp;
				zend_stream   stream;
		} handle;
		const char        *filename;
		zend_string       *opened_path;
		zend_stream_type  type;
		/* free_filename is used by wincache */
		/* TODO: Clean up filename vs opened_path mess */
		zend_bool         free_filename;
		char              *buf;
		size_t            len;
} zend_file_handle;

typedef int (*zend_stream_open_function_func_t)(const char *filename, zend_file_handle *handle);

extern zend_stream_open_function_func_t zend_stream_open_function;
extern zend_array *zend_rebuild_symbol_table(void);
HashTable*  zend_array_dup(HashTable *source);
