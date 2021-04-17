/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_PAF_TOPLEVEL_H
#define _VDSUITE_USER_PAF_TOPLEVEL_H

#include <kernel.h>
#include <paf/resource.h>

namespace paf {

	namespace graphics {
		class Texture;
		class MemoryPool;
	}

	namespace widget {
		class Widget;
	}

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

			~RootWidgetInitParam() { };

			SceInt32 unk_00;
			SceInt32 unk_04;
			SceInt32 unk_08;
			SceUChar8 unk_0C[0x20];
		};

		class TemplateInitParam
		{
		public:

			TemplateInitParam();

			~TemplateInitParam() { };

			SceInt32 unk_00;
			SceInt32 unk_04;
		};

		static Plugin *GetByName(const char *pluginName);

		static SceVoid LoadTexture(paf::graphics::Texture *tex, Plugin *plugin, paf::Resource::Element *textureSearchParam);

		paf::widget::Widget *SetRootWidget(paf::Resource::Element *widgetInfo, RootWidgetInitParam *initParam);

		paf::widget::Widget *GetRootWidgetByHash(paf::Resource::Element *widgetInfo);

		SceInt32 AddWidgetFromTemplate(paf::widget::Widget *targetRoot, paf::Resource::Element *templateSearchParam, paf::Plugin::TemplateInitParam *param);

		SceUChar8 unk_00[0x4];
		char *name;
		SceUChar8 unk_08[0xA8];
		Resource *resource;

	private:

		SceUChar8 m_unk_B4[0x4]; //size is unknown

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
			SceInt32 screenWidth; //unused
			SceInt32 sceenHeight; //unused
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

			SceUChar8 unk_38[0x20];

			SceInt32 unk_58;

			SceUChar8 unk_5C[0xC];

			paf::String pluginPath;

			SceUChar8 unk_74[0x20];
		};

		typedef void(*LoadCRFinishCallback)();
		typedef void(*LoadPluginFinishCallback)(Plugin *plugin);
		typedef void(*UnloadPluginFinishCallback)(Plugin *plugin);

		Framework(InitParam *fwInitParam);

		~Framework();

		static SceVoid InitializeDefaultJobQueue();

		static SceUInt32 GetFwLangBySystemLang(SceUInt32 systemLanguage);

		static SceVoid LoadPluginAsync(PluginInitParam *initParam, LoadPluginFinishCallback finishCallback = SCE_NULL, UnloadPluginFinishCallback unloadFinishCallback = SCE_NULL);

		static SceVoid LoadPlugin(PluginInitParam *initParam, LoadPluginFinishCallback finishCallback = SCE_NULL, UnloadPluginFinishCallback unloadFinishCallback = SCE_NULL);

		static Framework *GetInstance();

		static paf::graphics::MemoryPool *GetDefaultGraphicsMemoryPool();

		static SceVoid LoadTexture(paf::graphics::Texture *tex, Framework *fw, paf::Resource::Element *searchParam);

		SceVoid _LoadPluginAsync(PluginInitParam *initParam, LoadPluginFinishCallback finishCallback = SCE_NULL, UnloadPluginFinishCallback unloadFinishCallback = SCE_NULL);

		SceInt32 EnterRenderingLoop();

		SceVoid ExitRenderingLoop();

		SceVoid LoadCommonResourceAsync(LoadCRFinishCallback finishCallback = SCE_NULL);

		SceVoid LoadCommonResourceAsync(CommonResourceInitParam *initParam, LoadCRFinishCallback finishCallback = SCE_NULL);

		SceVoid LoadCommonResource(LoadCRFinishCallback finishCallback = SCE_NULL);

		SceVoid LoadCommonResource(CommonResourceInitParam *initParam, LoadCRFinishCallback finishCallback = SCE_NULL);

		Plugin *FindPluginByName(const char *pluginName, SceBool enableSomeCheck = SCE_FALSE);

		ApplicationMode GetApplicationMode();

		SceInt32 Test2(SceFloat32, SceInt32, SceInt32);

		paf::widget::Widget *GetRootWidget();

		SceUChar8 unk_00[0x1C];

		Plugin *crPlugin;

		SceUChar8 unk_20[0x5C];
	};
}

#endif /* _VDSUITE_USER_PAF_TOPLEVEL_H */
