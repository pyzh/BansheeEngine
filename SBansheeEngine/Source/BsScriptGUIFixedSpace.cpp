#include "BsScriptGUIFixedSpace.h"
#include "BsScriptMeta.h"
#include "BsMonoField.h"
#include "BsMonoClass.h"
#include "BsMonoManager.h"
#include "BsSpriteTexture.h"
#include "BsMonoUtil.h"
#include "BsGUILayout.h"
#include "BsGUISpace.h"
#include "BsScriptGUILayout.h"

using namespace CamelotFramework;

namespace BansheeEngine
{
	ScriptGUIFixedSpace::ScriptGUIFixedSpace(GUIFixedSpace& fixedSpace, GUILayout* parentLayout)
		:mFixedSpace(fixedSpace), mParentLayout(parentLayout), mIsDestroyed(false)
	{

	}

	void ScriptGUIFixedSpace::initMetaData()
	{
		metaData = ScriptMeta(BansheeEngineAssemblyName, "BansheeEngine", "GUIFixedSpace", &ScriptGUIFixedSpace::initRuntimeData);

		MonoManager::registerScriptType(&metaData);
	}

	void ScriptGUIFixedSpace::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_CreateInstance", &ScriptGUIFixedSpace::internal_createInstance);
		metaData.scriptClass->addInternalCall("Internal_DestroyInstance", &ScriptGUIFixedSpace::internal_destroyInstance);

		metaData.scriptClass->addInternalCall("Internal_Destroy", &ScriptGUIFixedSpace::internal_destroy);
		metaData.scriptClass->addInternalCall("Internal_SetVisible", &ScriptGUIFixedSpace::internal_setVisible);
		metaData.scriptClass->addInternalCall("Internal_SetParent", &ScriptGUIFixedSpace::internal_setParent);
	}

	void ScriptGUIFixedSpace::destroy()
	{
		if(!mIsDestroyed)
		{
			mParentLayout->removeSpace(mFixedSpace);
			mParentLayout = nullptr;

			mIsDestroyed = true;
		}
	}

	void ScriptGUIFixedSpace::internal_createInstance(MonoObject* instance, MonoObject* parentLayout, UINT32 size)
	{
		ScriptGUILayout* scriptLayout = ScriptGUILayout::toNative(parentLayout);
		GUILayout* nativeLayout = scriptLayout->getInternalValue();
		GUIFixedSpace& space = nativeLayout->addSpace(size);

		ScriptGUIFixedSpace* nativeInstance = new (cm_alloc<ScriptGUIFixedSpace>()) ScriptGUIFixedSpace(space, nativeLayout);
		nativeInstance->createInstance(instance);

		metaData.thisPtrField->setValue(instance, &nativeInstance);
	}

	void ScriptGUIFixedSpace::internal_destroyInstance(ScriptGUIFixedSpace* nativeInstance)
	{
		nativeInstance->destroy();
		cm_delete(nativeInstance);
	}

	void ScriptGUIFixedSpace::internal_destroy(ScriptGUIFixedSpace* nativeInstance)
	{
		nativeInstance->destroy();
	}

	void ScriptGUIFixedSpace::internal_setVisible(ScriptGUIFixedSpace* nativeInstance, bool visible)
	{
		if(visible)
			nativeInstance->mFixedSpace.enableRecursively();
		else
			nativeInstance->mFixedSpace.disableRecursively();
	}

	void ScriptGUIFixedSpace::internal_setParent(ScriptGUIFixedSpace* nativeInstance, MonoObject* parentLayout)
	{
		// FixedSpace parent is static, so do nothing
	}
}