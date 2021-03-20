/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_PAF_RESOURCE_H
#define _VDSUITE_USER_PAF_RESOURCE_H

#include <kernel.h>
#include <paf/common.h>

namespace paf {

	class Resource
	{
	public:

		Resource();

		~Resource();

		class Element
		{
		public:

			Element() : hash(0)
			{

			}

			~Element()
			{

			}

			SceUInt32 GetHashByName(Element *src);

			paf::String name;
			SceUInt32 hash;
		};
	};

}

#endif /* _VDSUITE_USER_PAF_RESOURCE_H */
