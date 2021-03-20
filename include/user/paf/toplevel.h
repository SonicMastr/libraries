/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_PAF_TOPLEVEL_H
#define _VDSUITE_USER_PAF_TOPLEVEL_H

#include <kernel.h>
#include <paf/common.h>
#include <paf/resource.h>
#include <paf/widget.h>

namespace paf {

	class Plugin
	{
	public:

		typedef void(*PluginCB)(Plugin *plugin);

		Plugin() {};

		~Plugin() {};

		class RootWidgetInitParam
		{
		public:

			RootWidgetInitParam();

			~RootWidgetInitParam() { } ;

			SceInt32 unk_00;
			SceInt32 unk_04;
			SceInt32 unk_08;
			SceUChar8 unk_0C[0x20];
		};

		static Plugin *GetByName(const char *pluginName);

		ui::Widget *SetRootWidget(paf::Resource::Element *widgetInfo, RootWidgetInitParam *initParam);

	private:

		SceUChar8 m_unk[0x4]; //size is unknown

	};

	class Framework
	{
	public:

		enum ApplicationMode
		{
			Mode_ApplicationDefault,
			Mode_Application,
			Mode_ApplicationA,
			Mode_ApplicationB,
			Mode_ApplicationC,
			Mode_ApplicationD
		};

		static Framework *s_frameworkInstance;

		class InitParam
		{
		public:

			InitParam();

			~InitParam() { };

			InitParam *LoadDefaultParams();

			SceUInt32 unk_00;
			SceUInt32 gxmParameterBufferSize;

			SceUChar8 unk0[0x10];

			SceUInt32 textSurfaceCacheSize;

			SceUChar8 unk1[0x40];

			SceUInt32 decodeHeapSize;
			SceUInt32 defaultPluginHeapSize;
			SceInt32 unused_68;
			SceInt32 unused_6C;
			ApplicationMode applicationMode;
			SceInt32 optionalFeatureFlags;
			SceInt32 language;
			SceInt32 enterButtonAssign;
			SceBool useAdditionalWidgetInit;
			ScePVoid unk_84;
			SceInt32 unused_88;
			SceInt32 graphicsFlags;

			SceUChar8 unk2[0x134];
		};

		class CommonResourceInitParam
		{
		public:

			CommonResourceInitParam();

			~CommonResourceInitParam() { };

			paf::String resourcePath;
			SceUChar8 unk_08[0x1C];
		};

		class PluginInitParam //0x94
		{
		public:

			PluginInitParam();

			~PluginInitParam() { };

			paf::String pluginName;
			paf::String scopeName;
			paf::Plugin::PluginCB loadCB1;
			paf::Plugin::PluginCB loadCB2;
			paf::Plugin::PluginCB loadCB3;
			paf::Plugin::PluginCB unloadCB1;
			paf::Plugin::PluginCB unloadCB2;
			paf::String resourcePath;

			SceUChar8 unk_38[0x5C];
		};

		typedef void(*LoadCRFinishCallback)();
		typedef void(*LoadPluginFinishCallback)(Plugin *plugin);
		typedef void(*UnloadPluginFinishCallback)(Plugin *plugin);

		Framework(InitParam *fwInitParam);

		~Framework();

		static SceUInt32 GetFwLangBySystemLang(SceUInt32 systemLanguage);

		static SceVoid LoadPluginAsync(PluginInitParam *initParam, LoadPluginFinishCallback finishCallback = SCE_NULL, UnloadPluginFinishCallback unloadFinishCallback = SCE_NULL);

		static SceVoid LoadPlugin(PluginInitParam *initParam, LoadPluginFinishCallback finishCallback = SCE_NULL, UnloadPluginFinishCallback unloadFinishCallback = SCE_NULL);

		SceVoid _LoadPluginAsync(PluginInitParam *initParam, LoadPluginFinishCallback finishCallback = SCE_NULL, UnloadPluginFinishCallback unloadFinishCallback = SCE_NULL);

		SceInt32 EnterRenderingLoop();

		SceVoid ExitRenderingLoop();

		SceVoid LoadCommonResourceAsync(LoadCRFinishCallback finishCallback = SCE_NULL);

		SceVoid LoadCommonResourceAsync(CommonResourceInitParam *initParam, LoadCRFinishCallback finishCallback = SCE_NULL);

		SceVoid LoadCommonResource(LoadCRFinishCallback finishCallback = SCE_NULL);

		SceVoid LoadCommonResource(CommonResourceInitParam *initParam, LoadCRFinishCallback finishCallback = SCE_NULL);

		Plugin *FindPluginByName(const char *pluginName, SceBool enableSomeCheck = SCE_FALSE);

	private:

		SceUChar8 m_work[0x7C];

	};
}

#endif /* _VDSUITE_USER_PAF_TOPLEVEL_H */
