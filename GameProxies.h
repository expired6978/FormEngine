#pragma once

#include "oolua.h"

#include "skse/GameFormComponents.h"
#include "skse/GameForms.h"
#include "skse/GameObjects.h"
#include "skse/GameData.h"

OOLUA_PROXY(BaseFormComponent)
OOLUA_TAGS(Abstract, No_public_destructor)
OOLUA_PROXY_END
OOLUA_EXPORT_NO_FUNCTIONS(BaseFormComponent)

OOLUA_PROXY(TESForm, BaseFormComponent)
OOLUA_TAGS(No_default_constructor, No_public_destructor)
OOLUA_MGET(formID, GetFormID)
OOLUA_MGET(formType, GetType)
OOLUA_MGET(flags, GetFlags)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(TESForm)
OOLUA_EXPORT_FUNCTIONS_CONST(TESForm
							 , GetFormID
							 , GetType
							 , GetFlags)

OOLUA_PROXY(TESGlobal, TESForm)
OOLUA_TAGS(No_default_constructor, No_public_destructor)
OOLUA_PROXY_END
OOLUA_EXPORT_NO_FUNCTIONS(TESGlobal)

OOLUA_PROXY(TESLeveledList, BaseFormComponent)
OOLUA_TAGS(No_default_constructor, No_public_destructor)
OOLUA_MGET(chanceValue, GetChanceValue)
OOLUA_MGET(length, GetLength)
OOLUA_MGET(flags, GetFlags)
OOLUA_MEM_FUNC(OOLUA::maybe_null<TESGlobal*>, GetChanceGlobal)
OOLUA_MEM_FUNC(OOLUA::maybe_null<TESForm*>, GetNthForm, UInt32)
OOLUA_MFUNC(GetNthCount)
OOLUA_MFUNC(GetNthLevel)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(TESLeveledList
					   , GetChanceGlobal
					   , GetNthForm
					   , GetNthCount
					   , GetNthLevel)
OOLUA_EXPORT_FUNCTIONS_CONST(TESLeveledList
							 , GetChanceValue
							 , GetLength
							 , GetFlags)

OOLUA_PROXY(BGSKeyword, TESForm)
OOLUA_TAGS(No_default_constructor, No_public_destructor)
OOLUA_MFUNC(GetKeywordName)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(BGSKeyword, GetKeywordName)
OOLUA_EXPORT_FUNCTIONS_CONST(BGSKeyword)

OOLUA_PROXY(BGSListForm, TESForm)
OOLUA_TAGS(No_default_constructor, No_public_destructor)
OOLUA_MFUNC(AddFormToFormList)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(BGSListForm
								  , AddFormToFormList)
OOLUA_EXPORT_FUNCTIONS_CONST(BGSListForm)

OOLUA_PROXY(TESObject, TESForm)
OOLUA_TAGS(No_default_constructor, No_public_destructor)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(TESObject)
OOLUA_EXPORT_FUNCTIONS_CONST(TESObject)

OOLUA_PROXY(TESBoundObject, TESObject)
OOLUA_TAGS(No_default_constructor, No_public_destructor)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(TESBoundObject)
OOLUA_EXPORT_FUNCTIONS_CONST(TESBoundObject)

OOLUA_PROXY(TESBoundAnimObject, TESBoundObject)
OOLUA_TAGS(No_default_constructor, No_public_destructor)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(TESBoundAnimObject)
OOLUA_EXPORT_FUNCTIONS_CONST(TESBoundAnimObject)

OOLUA_PROXY(MagicItem, TESBoundObject)
OOLUA_TAGS(No_default_constructor, No_public_destructor)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(MagicItem)
OOLUA_EXPORT_FUNCTIONS_CONST(MagicItem)

OOLUA_PROXY(EnchantmentItem, TESBoundObject)
OOLUA_TAGS(No_default_constructor, No_public_destructor)
OOLUA_MEM_FUNC(OOLUA::maybe_null<BGSListForm*>, GetRestrictions)
OOLUA_MFUNC(SetRestrictions)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(EnchantmentItem
					   , GetRestrictions
					   , SetRestrictions)
OOLUA_EXPORT_FUNCTIONS_CONST(EnchantmentItem)

OOLUA_PROXY(TESLevItem, TESBoundObject)
OOLUA_TAGS(No_default_constructor, No_public_destructor)
OOLUA_MFUNC(GetLeveledList)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(TESLevItem
					   , GetLeveledList)
OOLUA_EXPORT_FUNCTIONS_CONST(TESLevItem)

OOLUA_PROXY(TESLevSpell, TESBoundObject)
OOLUA_TAGS(No_default_constructor, No_public_destructor)
OOLUA_MFUNC(GetLeveledList)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(TESLevSpell
					   , GetLeveledList)
					   OOLUA_EXPORT_FUNCTIONS_CONST(TESLevSpell)

OOLUA_PROXY(TESLevCharacter, TESBoundAnimObject)
OOLUA_TAGS(No_default_constructor, No_public_destructor)
OOLUA_MFUNC(GetLeveledList)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(TESLevCharacter
					   , GetLeveledList)
					   OOLUA_EXPORT_FUNCTIONS_CONST(TESLevCharacter)

class Debug
{
public:
	static void trace(std::string msg)
	{
		_MESSAGE("%s", msg.c_str());
	}
};

OOLUA_PROXY(Debug)
OOLUA_TAGS(No_public_constructors)
OOLUA_SFUNC(trace)
OOLUA_PROXY_END
OOLUA_EXPORT_NO_FUNCTIONS(Debug)

class FormFactory
{
public:
	template<class T>
	static T * CreateForm()
	{
		IFormFactory	* factory = IFormFactory::GetFactoryForType(T::kTypeID);
		if(factory)
		{
			T * result = (T *)factory->Create();
			if(result)
			{
				result->Init();
				return result;
			}
		}

		return NULL;
	}

	static BGSListForm * CreateFormList() { return static_cast<BGSListForm *>(CreateForm<BGSListForm>()); };
	static BGSKeyword * CreateKeyword() { return static_cast<BGSKeyword *>(CreateForm<BGSKeyword>()); };
};

OOLUA_PROXY(FormFactory)
OOLUA_TAGS(No_public_constructors)
OOLUA_SFUNC(CreateFormList)
OOLUA_SFUNC(CreateKeyword)
OOLUA_PROXY_END
OOLUA_EXPORT_NO_FUNCTIONS(FormFactory)


OOLUA_PROXY(DataHandler)
OOLUA_TAGS(No_default_constructor, No_public_destructor)
OOLUA_SFUNC(Get)
OOLUA_MFUNC(GetNumEnchantments)
OOLUA_MEM_FUNC(OOLUA::maybe_null<EnchantmentItem*>, GetNthEnchantment, UInt32)
OOLUA_MFUNC(GetNumKeywords)
OOLUA_MEM_FUNC(OOLUA::maybe_null<BGSKeyword*>, GetNthKeyword, UInt32)
OOLUA_MFUNC(GetNumFormLists)
OOLUA_MEM_FUNC(OOLUA::maybe_null<BGSListForm*>, GetNthFormList, UInt32)
OOLUA_MFUNC(GetModName)
OOLUA_MEM_FUNC(OOLUA::maybe_null<TESForm*>, GetFormFromFile, UInt32, std::string)
OOLUA_PROXY_END
OOLUA_EXPORT_FUNCTIONS(DataHandler
								, GetNumEnchantments
								, GetNthEnchantment
								, GetNumKeywords
								, GetNthKeyword
								, GetNumFormLists
								, GetNthFormList)
OOLUA_EXPORT_FUNCTIONS_CONST(DataHandler)