/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_PAF_WIDGET_H
#define _VDSUITE_USER_PAF_WIDGET_H

#include <scetypes.h>
#include <paf/resource.h>

namespace paf {
	namespace ui {

		class Widget
		{
		public:

			enum Error //placeholder names
			{
				SCE_PAF_ERROR_UI_WIDGET_COLOR_ERROR = 0x80AF0022
			};

			class EventCallback
			{
			public:

				enum Error
				{
					SCE_PAF_ERROR_UI_WIDGET_EVENT_CALLBACK_UNHANDLED = 0x80AF4101
				};

				typedef void(*EventHandler)(SceInt32 eventId, Widget *self, SceInt32, ScePVoid pUserData);

				EventCallback() : state(2), pUserData(SCE_NULL)
				{

				};

				virtual ~EventCallback()
				{

				};

				virtual SceInt32 HandleEvent(SceInt32 eventId, Widget *self, SceInt32 a3)
				{
					SceInt32 ret;

					if ((this->state & 1) == 0) {
						if (this->eventHandler != 0) {
							this->eventHandler(eventId, self, a3, this->pUserData);
						}
						ret = 0;
					}
					else {
						ret = SCE_PAF_ERROR_UI_WIDGET_EVENT_CALLBACK_UNHANDLED;
					}

					return ret;
				};

				virtual EventHandler f2()
				{
					return this->eventHandler;
				};

				SceInt32 state;
				ScePVoid pUserData;
				EventHandler eventHandler;

			};

			class Color
			{
			public:

				enum Type
				{
					Unk0,
					Unk1,
					Text,
					TextShadow,
					Background,
					Unk5
				};

				Color() :  r(0.0), g(0.0), b(0.0), a(0.0)
				{

				};

				~Color()
				{

				};

				SceFloat32 r;
				SceFloat32 g;
				SceFloat32 b;
				SceFloat32 a;
			};

			Widget() {};

			~Widget() {};

			SceInt32 SetColor(Color::Type type, SceInt32 a2, SceInt32 a3, const Color *pColor);

			enum Option
			{
				TextBold = 0x7,
				TextShadow = 0xC,
				TextExternalLine = 0xD
			};

			SceInt32 SetOption(Option option, SceInt32 a2, SceInt32 a3, SceBool enable);

			SceInt32 SetFontSize(SceFloat32 size, SceInt32 a2, SceSize pos, SceSize len);

			Widget *FindByHash(paf::Resource::Element *widgetInfo, SceUInt32 param); //param can be 0,1,2

			SceInt32 SetPosition(SceFVector4 *position, SceFloat32 a2, SceInt32 a3, SceInt32 a4, SceInt32 a5, SceInt32 a6, SceInt32 a7);

			SceInt32 SetSize(SceFVector4 *size, SceFloat32 a2, SceInt32 a3, SceInt32 a4, SceInt32 a5, SceInt32 a6, SceInt32 a7);

			SceInt32 RegisterEventCallback(SceInt32 eventId, EventCallback *cb, SceBool a3);

			SceInt32 UnregisterEventCallback(SceInt32 eventId, SceInt32 a2, SceInt32 a3);

			SceInt32 RegisterLoopEventCallback(SceInt32 eventId, EventCallback *cb);

			SceInt32 AddEffect(SceInt32 effId, SceInt32 a2);

			//ScePafWidget_44B22ACA static
			//ScePafWidget_F1176ACC
			/*SceInt32 Test1(SceInt32, SceInt32, SceInt32);
			static SceInt32 Test2(SceInt32, Widget*, SceInt32, SceInt32, SceInt32);

			SceInt32 Test3(SceInt32);

			SceInt32 Test4(SceFVector4 *size, SceInt32 a2, SceInt32 a3);*/

		private:

			SceUChar8 unk[0x2D4];

		};

		class Label : public Widget
		{
		public:

			Label(Widget *parentWidget, SceInt32 flags); //flags: 0,2 or 4

			virtual ~Label();

			//109 virtual functions here
			virtual int unkFun_008();
			virtual int unkFun_00C();
			virtual int unkFun_010();
			virtual int unkFun_014();
			virtual int unkFun_018();
			virtual int unkFun_01C();
			virtual int unkFun_020();
			virtual int unkFun_024();
			virtual int unkFun_028();
			virtual int unkFun_02C();
			virtual int unkFun_030();
			virtual int unkFun_034();
			virtual int unkFun_038();
			virtual int unkFun_03C();
			virtual int unkFun_040();
			virtual int unkFun_044();
			virtual int unkFun_048();
			virtual int unkFun_04C();
			virtual int unkFun_050();
			virtual int unkFun_054();
			virtual int unkFun_058();
			virtual int unkFun_05C();
			virtual int unkFun_060();
			virtual int unkFun_064();
			virtual int unkFun_068();
			virtual int unkFun_06C();
			virtual int unkFun_070();
			virtual int unkFun_074();
			virtual int unkFun_078();
			virtual int unkFun_07C();
			virtual int unkFun_080();
			virtual int unkFun_084();
			virtual int unkFun_088();
			virtual int unkFun_08C();
			virtual int unkFun_090();
			virtual int unkFun_094();
			virtual int unkFun_098();
			virtual int unkFun_09C();
			virtual int unkFun_0A0();
			virtual int unkFun_0A4();
			virtual int unkFun_0A8();
			virtual int unkFun_0AC();
			virtual int unkFun_0B0();
			virtual int unkFun_0B4();
			virtual int unkFun_0B8();
			virtual int unkFun_0BC();
			virtual int unkFun_0C0();
			virtual int unkFun_0C4();
			virtual int unkFun_0C8();
			virtual int unkFun_0CC();
			virtual int unkFun_0D0();
			virtual int unkFun_0D4();
			virtual int unkFun_0D8();
			virtual int unkFun_0DC();
			virtual int unkFun_0E0();
			virtual int unkFun_0E4();
			virtual int unkFun_0E8();
			virtual int unkFun_0EC();
			virtual int unkFun_0F0();
			virtual int unkFun_0F4();
			virtual int unkFun_0F8();
			virtual int unkFun_0FC();
			virtual int unkFun_100();
			virtual int unkFun_104();
			virtual int unkFun_108();
			virtual int unkFun_10C();
			virtual int unkFun_110();
			virtual int unkFun_114();
			virtual int unkFun_118();
			virtual SceInt32 SetText(paf::WString *text); //ScePafWidget_922FF349
			virtual int unkFun_120();
			virtual int unkFun_124();
			virtual int unkFun_128();
			virtual int unkFun_12C();
			virtual int unkFun_130();
			virtual int unkFun_134();
			virtual int unkFun_138();
			virtual int unkFun_13C();
			virtual int unkFun_140();
			virtual int unkFun_144();
			virtual int unkFun_148();
			virtual int unkFun_14C();
			virtual int unkFun_150();
			virtual int unkFun_154();
			virtual int unkFun_158();
			virtual int unkFun_15C();
			virtual int unkFun_160();
			virtual int unkFun_164();
			virtual int unkFun_168();
			virtual int unkFun_16C();
			virtual int unkFun_170();
			virtual int unkFun_174();
			virtual int unkFun_178();
			virtual int unkFun_17C();
			virtual int unkFun_180();
			virtual int unkFun_184();
			virtual int unkFun_188();
			virtual int unkFun_18C();
			virtual int unkFun_190();
			virtual int unkFun_194();
			virtual int unkFun_198();
			virtual int unkFun_19C();
			virtual int unkFun_1A0();
			virtual int unkFun_1A4();
			virtual int unkFun_1A8();

		};
	}
}

#endif /* _VDSUITE_USER_PAF_WIDGET_H */
