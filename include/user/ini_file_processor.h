/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_INI_FILE_PROCESSOR_H
#define _VDSUITE_USER_INI_FILE_PROCESSOR_H

#define SCE_INI_FILE_PROCESSOR_ERROR_NO_MEMORY			(-2138832895) /* 0x80840001 */
#define SCE_INI_FILE_PROCESSOR_ERROR_UNINITIALIZED		(-2138832894) /* 0x80840002 */
#define SCE_INI_FILE_PROCESSOR_ERROR_EOF				(-2138832891) /* 0x80840005 */
#define SCE_INI_FILE_PROCESSOR_ERROR_INVALID_ARGUMENT	(-2138832890) /* 0x80840006 */
#define SCE_INI_FILE_PROCESSOR_ERROR_READ_ONLY			(-2138832889) /* 0x80840007 */
#define SCE_INI_FILE_PROCESSOR_ERROR_FILE_NOT_FOUND		(-2138832887) /* 0x80840009 */
#define SCE_INI_FILE_PROCESSOR_ERROR_INVALID_KEY		(-2138832882) /* 0x8084000E */
#define SCE_INI_FILE_PROCESSOR_ERROR_KEY_NOT_FOUND		(-2138832880) /* 0x80840010 */

#define SCE_INI_FILE_PROCESSOR_PARSE_COMPLETED			(0x840001)

#define SCE_INI_FILE_PROCESSOR_OPEN_FLAG_UNK_20			(1 << 20) /* Sets sceIoOpen flag to 0x10001 */
#define SCE_INI_FILE_PROCESSOR_OPEN_FLAG_WITH_MODE		(1 << 21) /* Sets sceIoOpen mode to (flags & 0xFFFF) */

#define SCE_INI_FILE_PROCESSOR_KEY_BUFFER_SIZE			(0x80)

#ifdef __cplusplus

#include <stddef.h>

namespace sce {
namespace Ini {

class MemAllocator {
public:
	typedef void* (*Allocator)(size_t size);
	typedef void (*Deallocator)(void* ptr);

	Allocator allocate;
	Deallocator deallocate;
};

class InitParameter {
public:
	InitParameter();

	int unk_0x0; // size or mode? usually 0, seen: 0x1000, 0x2000
	int unk_0x4; // size or mode? usually 0, seen: 0x1000, 0x2000
	MemAllocator* allocator; // can be NULL
	int unk_0xc;
};

class IniFileProcessor {
public:
	IniFileProcessor();
	virtual ~IniFileProcessor();

	/**
	 * Initialize INI file processor to work with file
	 *
	 * @param[in] param - ::InitParameter
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int initialize(const InitParameter* param);

	/**
	 * Terminate INI file processor
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int terminate();

	/**
	 * Returns the last IO error number.
	 *
	 * @return 0 or error number.
	 */
	int getLastIoError();

	/**
	 * Serialize INI data into a string
	 *
	 * @param[out] ini - string data
	 * @param[out] size - length of the output string
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int serialize(const char** ini, size_t* size);

	/**
	 * Frees the memory allocated for serialize.
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int free();

	/**
	 * Deserialize INI data from a string
	 *
	 * @param[in] ini - string data
	 * @param[in] size - length of the input string
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int deserialize(const char* ini, size_t size);

	/**
	 * Create a new INI file or open an existing INI file.
	 *
	 * @param[in] path - path to the INI file to open
	 * @param[in] mode - file open mode, "r" or "rw"
	 * @param[in] flags - bitwise OR of open flags
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int open(const char* path, const char* mode, int flags);

	/**
	 * Create new INI file. If the file already exists, it will be truncated.
	 *
	 * @param[in] path - path to the INI file to open
	 * @param[in] mode - set to "rw", this argument has no effect
	 * @param[in] flags - bitwise OR of open flags
	 *
	 * @return 0 on success, < 0 on error.
	 *
	 */
	int openNew(const char* path, const char* mode, int flags);

	/**
	 * Close INI file
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int close();

	/**
	 * Flush changes to file.
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int flush();

	/**
	 * Get total number of keys in the opened INI file
	 *
	 * @return toatal number of keys, < 0 on error.
	 */
	int size();

	/**
	 * Add key and set value for it
	 *
	 * @param[in] key - key string
	 * @param[in] value - value string
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int add(const char* key, const char* value);

	/**
	 * Delete key and corresponding value from INI file
	 *
	 * @param[in] key - key string
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int del(const char* key);

	/**
	 * Set value corresponding to set key
	 *
	 * @param[in] key - key string
	 * @param[in] value - value string
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int set(const char* key, const char* value);

	/**
	 * Find value corresponding to set key
	 *
	 * @param[in] key - key string
	 * @param[out] val - buffer to store value string if found
	 * @param[in] size - size of the output buffer
	 * @param[in] offset - offset into the value corresponding to key
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int get(const char* key, char* val, size_t size, size_t offset);

	/**
	 * Parse key and corresponding value, one key per call until eof
	 *
	 * @param[out] key - buffer to store key string
	 * @param[out] val - buffer to store value string
	 * @param[in] size - size of the output value buffer
	 *
	 * @return 0 on success, < 0 on error.
	 *
	 */
	int parse(char* key, char* val, size_t size);

	/**
	 * Reset parser to the beginning of the file
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int reset();

private:
	void *m_impl;
};

} // namespace Ini
} // namespace sce

#endif // __cplusplus

#endif // _VDSUITE_USER_INI_FILE_PROCESSOR_H
