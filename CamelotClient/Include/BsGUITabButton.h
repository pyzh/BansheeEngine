#pragma once

#include "BsEditorPrerequisites.h"
#include "BsGUIToggle.h"
#include "BsGUIToggleGroup.h"
#include "BsImageSprite.h"
#include "boost/signal.hpp"

namespace BansheeEditor
{
	class GUITabButton : public BS::GUIToggle
	{
	public:
		static const CM::String& getGUITypeName();

		static GUITabButton* create(BS::GUIWidget& parent, GUITabbedTitleBar* titleBar, CM::UINT32 index, const CM::HString& text, const BS::GUIElementStyle* style = nullptr);
		static GUITabButton* create(BS::GUIWidget& parent, const BS::GUIOptions& layoutOptions, GUITabbedTitleBar* titleBar, CM::UINT32 index, const CM::HString& text, const BS::GUIElementStyle* style = nullptr);
	
		static GUITabButton* create(BS::GUIWidget& parent, GUITabbedTitleBar* titleBar, CM::UINT32 index, const BS::GUIContent& content, const BS::GUIElementStyle* style = nullptr);
		static GUITabButton* create(BS::GUIWidget& parent, const BS::GUIOptions& layoutOptions, GUITabbedTitleBar* titleBar, CM::UINT32 index, const BS::GUIContent& content, const BS::GUIElementStyle* style = nullptr);

		CM::UINT32 getIndex() const { return mIndex; }

		boost::signal<void(CM::UINT32)> onDragged;
	protected:
		virtual bool mouseEvent(const BS::GUIMouseEvent& ev);

	private:
		GUITabbedTitleBar* mTitleBar;
		CM::UINT32 mIndex;
		CM::Int2 mDragStartPosition;

		static const CM::UINT32 DRAG_MIN_DISTANCE;

		GUITabButton(BS::GUIWidget& parent, const BS::GUIElementStyle* style, GUITabbedTitleBar* titleBar, CM::UINT32 index, const BS::GUIContent& content, const BS::GUILayoutOptions& layoutOptions);
	};
}