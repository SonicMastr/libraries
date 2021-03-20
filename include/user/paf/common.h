/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_PAF_COMMON_H
#define _VDSUITE_USER_PAF_COMMON_H

#include <scetypes.h>
#include <paf/stdc.h>

namespace paf {

	class String;
	class WString;

	namespace common {

		enum CesFlags
		{
			AllowIllegalCode	= 0x2,
			AllowOutOfCodeRange	= 0x4,
			AllowInvalidEncode	= 0x8,
			AllowSrcBufferEnd	= 0x10
		};

	}


	class String
	{
	public:

		String() : data(SCE_NULL), length(0)
		{

		}

		~String()
		{
			if (data != SCE_NULL)
				delete data;
		}

		static SceSSize ToWString(const char *src, paf::WString *dst);

		static SceSSize ToWString(const char *src, paf::WString *dst, SceUInt32 flags);

		static String *WCharToNewString(const SceWChar16 *src, String *dst);

		SceSSize ToWString(paf::WString *dst);

		SceSSize ToWString(paf::WString *dst, SceUInt32 flags);

		String *Set(const char *s, SceSize srcLength)
		{
			if (data == s)
				return this;

			if (data != SCE_NULL)
				delete data;

			if (srcLength == 0 || s == SCE_NULL || s[0] == 0) {
				data = SCE_NULL;
				length = 0;
				return this;
			}

			data = new char[srcLength + 1];
			length = srcLength;
			sce_paf_memcpy(data, s, length);
			data[length] = 0;

			return this;
		}

		String *Set(const char *s)
		{
			return Set(s, sce_paf_strlen(s));
		}

		String *operator=(const String *s)
		{
			if (data == s->data)
				return this;

			if (s->length == 0) {
				data = SCE_NULL;
				length = 0;
				return this;
			}

			data = new char[s->length + 1];
			length = s->length;
			sce_paf_memcpy(data, s->data, s->length + 1);

			return this;
		}

		String *operator+(const String *s) const
		{
			String *newStr = new String;

			if (!length && !s->length)
			{
				return newStr;
			}

			newStr->data = new char[s->length + length + 1];
			newStr->length = s->length + length;
			sce_paf_memcpy(newStr->data, data, length);
			sce_paf_memcpy(&newStr->data[length], s->data, s->length + 1);
			newStr->data[newStr->length] = 0;
			return newStr;
		}

		SceBool operator==(const String *s) const
		{
			if (s->length != length)
				return SCE_FALSE;

			if (!sce_paf_strncmp(s->data, data, length))
				return SCE_TRUE;
			else
				return SCE_FALSE;
		}

		SceVoid Clear()
		{
			if (data != SCE_NULL) {
				delete data;
				data = SCE_NULL;
			}
		}

		char *data;
		SceSize length;

	private:

		SceUInt32 m_work;

	};

	class WString
	{
	public:

		WString() : data(SCE_NULL), length(0)
		{

		}

		~WString()
		{
			if (data != SCE_NULL)
				delete data;
		}

		static SceSSize ToString(const SceWChar16 *src, String *dst);

		static SceSSize ToString(const SceWChar16 *src, String *dst, SceUInt32 flags);

		static WString *CharToNewWString(const char *src, WString *dst);

		SceSSize ToString(String *dst);

		SceSSize ToString(String *dst, SceUInt32 flags);

		WString *Set(const SceWChar16 *s, SceSize srcLength)
		{
			if (data == s)
				return this;

			if (data != SCE_NULL)
				delete data;

			if (srcLength == 0 || s == SCE_NULL || s[0] == 0) {
				data = SCE_NULL;
				length = 0;
				return this;
			}

			data = new SceWChar16[srcLength + 1];
			length = srcLength;
			sce_paf_wmemcpy((wchar_t*)data, (wchar_t*)s, length);
			data[length] = 0;

			return this;
		}

		WString *Set(const SceWChar16 *s)
		{
			return Set(s, sce_paf_wcslen((wchar_t*)s));
		}

		WString *operator=(const WString *s)
		{
			if (data == s->data)
				return this;

			if (s->length == 0) {
				data = SCE_NULL;
				length = 0;
				return this;
			}

			data = new SceWChar16[s->length + 1];
			length = s->length;
			sce_paf_wmemcpy((wchar_t*)data, (wchar_t*)s->data, s->length + 1);

			return this;
		}

		WString *operator+(const String *s) const
		{
			WString *newStr = new WString;

			if (!length && !s->length)
			{
				return newStr;
			}

			newStr->data = new SceWChar16[s->length + length + 1];
			newStr->length = s->length + length;
			sce_paf_wmemcpy((wchar_t*)newStr->data, (wchar_t*)data, length);
			sce_paf_wmemcpy((wchar_t*)&newStr->data[length], (wchar_t*)s->data, s->length + 1);
			newStr->data[newStr->length] = 0;
			return newStr;
		}

		SceBool operator==(const WString *s) const
		{
			if (s->length != length)
				return SCE_FALSE;

			if (!sce_paf_wcsncmp((wchar_t*)s->data, (wchar_t*)data, length))
				return SCE_TRUE;
			else
				return SCE_FALSE;
		}

		SceVoid Clear()
		{
			if (data != SCE_NULL)
				delete data;
		}

		SceWChar16 *data;
		SceSize length;

	private:

		SceUInt32 m_work;
	};

	namespace common {

		class Utils
		{
		public:

			typedef void(*MainThreadTaskEntryFunction)(void *pArgBlock);

			Utils();

			~Utils();

			static SceVoid AddMainThreadTask(MainThreadTaskEntryFunction entry, ScePVoid pArgBlock);
		};

	}
}

#endif /* _VDSUITE_USER_PAF_COMMON_H */
