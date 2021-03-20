/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_PAF_MISC_H
#define _VDSUITE_USER_PAF_MISC_H

#include <libsha1.h>

namespace paf {

	namespace misc {

		class Misc
		{
		public:

			Misc();

			~Misc();

			static SceBool IsDolce();
		};

		class Sha1
		{
		public:

			Sha1();

			~Sha1() { };

			SceInt32 BlockUpdate(const ScePVoid plain, SceUInt32 len);

			SceInt32 BlockResult(SceUChar8 *digest);

		private:

			SceSha1Context m_sha;

		};
	}
}

#endif /* _VDSUITE_USER_PAF_MISC_H */
