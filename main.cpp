#include "skse/PluginAPI.h"
#include "skse/skse_version.h"
#include "skse/SafeWrite.h"
#include "skse/GameData.h"
#include "skse/GameAPI.h"
#include "skse/GameRTTI.h"
#include "skse/GameForms.h"
#include "skse/GameObjects.h"
#include "skse/GameStreams.h"

#include "GameProxies.h"

#include <shlobj.h>

IDebugLog	gLog;

PluginHandle	g_pluginHandle = kPluginHandle_Invalid;

typedef UInt32 (__stdcall * _LoadSceneGraph)(void * sceneGraph);
_LoadSceneGraph LoadSceneGraph = (_LoadSceneGraph)0x00699100;


#ifdef _DEBUG
#pragma warning (push)
#pragma warning (disable : 4200)
struct RTTIType
{
	void	* typeInfo;
	UInt32	pad;
	char	name[0];
};

struct RTTILocator
{
	UInt32		sig, offset, cdOffset;
	RTTIType	* type;
};
#pragma warning (pop)

const char * GetObjectClassName(void * objBase)
{
	const char	* result = "<no rtti>";

	__try
	{
		void		** obj = (void **)objBase;
		RTTILocator	** vtbl = (RTTILocator **)obj[0];
		RTTILocator	* rtti = vtbl[-1];
		RTTIType	* type = rtti->type;

		// starts with ,?
		if((type->name[0] == '.') && (type->name[1] == '?'))
		{
			// is at most 100 chars long
			for(UInt32 i = 0; i < 100; i++)
			{
				if(type->name[i] == 0)
				{
					// remove the .?AV
					result = type->name + 4;
					break;
				}
			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		// return the default
	}

	return result;
}

void DumpClass(void * theClassPtr, UInt32 nIntsToDump)
{
	UInt32* basePtr = (UInt32*)theClassPtr;
	_MESSAGE("DumpClass: %X", basePtr);

	gLog.Indent();

	if (!theClassPtr) return;
	for (UInt32 ix = 0; ix < nIntsToDump; ix++ ) {
		UInt32* curPtr = basePtr+ix;
		const char* curPtrName = NULL;
		UInt32 otherPtr = 0;
		float otherFloat = 0.0;
		const char* otherPtrName = NULL;
		if (curPtr) {
			curPtrName = GetObjectClassName((void*)curPtr);

			__try
			{
				otherPtr = *curPtr;
				otherFloat = *(float*)(curPtr);
			}
			__except(EXCEPTION_EXECUTE_HANDLER)
			{
				//
			}

			if (otherPtr) {
				otherPtrName = GetObjectClassName((void*)otherPtr);
			}
		}

		_MESSAGE("%3d +%03X ptr: 0x%08X: %32s *ptr: 0x%08x | %f: %32s", ix, ix*4, curPtr, curPtrName, otherPtr, otherFloat, otherPtrName);
	}

	gLog.Outdent();
}
#endif

void RunScript(OOLUA::Script * script, std::string fixedPath, std::string modName, std::string fileName)
{
	std::string fullPath = fixedPath + modName + fileName;
	BSResourceNiBinaryStream file(fullPath.c_str());
	if (!file.IsValid()) {
		return;
	}

	_MESSAGE("Running script: %s", fullPath.c_str());

	// Read whole file from VFS
	std::string chunkData;
	SInt8 character;
	while(file.Read(&character, 1))
	{
		chunkData.append(1, character);
	}

	// Run script chunk
	script->run_chunk(chunkData);
	std::string lastError = OOLUA::get_last_error(*script).c_str();
	if(lastError.length() > 0)
		_MESSAGE("Error: %s", lastError.c_str());
}

std::map<UInt32, std::string> editorIDs;

UInt32 __stdcall LoadSceneGraphHook(void * sceneGraph)
{
	UInt32 ret = LoadSceneGraph(sceneGraph);

	OOLUA::Script * m_lua;
	m_lua = new OOLUA::Script;
	m_lua->register_class<BaseFormComponent>();
	m_lua->register_class<TESForm>();
	m_lua->register_class<TESObject>();
	m_lua->register_class<TESBoundObject>();

	m_lua->register_class<BGSKeyword>();
	m_lua->register_class<BGSListForm>();

	m_lua->register_class<MagicItem>();
	m_lua->register_class<EnchantmentItem>();

	m_lua->register_class<DataHandler>();
	m_lua->register_class<FormFactory>();
	m_lua->register_class<Debug>();
	

	m_lua->register_class_static<Debug>("trace", &OOLUA::Proxy_class<Debug>::trace);
	m_lua->register_class_static<DataHandler>("Get", &OOLUA::Proxy_class<DataHandler>::Get);
	m_lua->register_class_static<FormFactory>("CreateFormList", &OOLUA::Proxy_class<FormFactory>::CreateFormList);
	m_lua->register_class_static<FormFactory>("CreateKeyword", &OOLUA::Proxy_class<FormFactory>::CreateKeyword);

	// Probably want to read all the plugins to import EDIDs here
	// Build the FormID to EDID map here

	DataHandler * dataHandler = DataHandler::GetSingleton();
	if(dataHandler)
	{
		UInt8 modCount = dataHandler->modList.loadedModCount;
		for (UInt32 i = 0; i < modCount; i++)
		{
			ModInfo * modInfo = dataHandler->modList.loadedMods[i];
			std::string fixedPath = "data\\SKSE\\Plugins\\FormEngine\\";
			std::string modPath = modInfo->name;
			modPath.append("\\");

			RunScript(m_lua, fixedPath, modPath, "main.lua");
		}
	}

	std::map<UInt32, std::string>::iterator it = editorIDs.begin();
	for(it = editorIDs.begin(); it != editorIDs.end(); ++it)
	{
		_MESSAGE("Form %08X - %s", it->first, it->second.c_str());
	}

	// Cleanup lua
	delete m_lua;
	return ret;
}

class TESFileRecord
{
public:
	UInt32	unk00;
	UInt32	unk04;
	UInt32	unk08;
	UInt32	unk0C;
	UInt32	unk10;
	UInt32	unk23C[(0x23C - 0x10) >> 2];
	UInt32	unk240; // First record
	UInt32	unk244; // First record length
	UInt32	unk248;
	UInt32	unk24C;
	UInt32	unk250;
	UInt32	unk254;
	UInt32	unk258; // Next record
	UInt32	unk25C; // Next record length
	UInt32	unk260;
	UInt32	unk264;
	UInt32	unk268; // record bytes read?
	UInt32	unk26C; // subrecord bytes read?
	UInt32	unk270;
	UInt32	unk294[(0x294 - 0x270) >> 2];
	UInt8	unk298;
	UInt8	unk299;	// record read?
	UInt16	unk29A;
	UInt32	unk29C;
	UInt32	unk41C[(0x41C - 0x29C) >> 2];
	UInt32	unk420;
	UInt32	unk424;
	UInt32	unk428;
	UInt32	unk42C;

	MEMBER_FN_PREFIX(TESFileRecord);
	DEFINE_MEMBER_FN(GetNextRecord, UInt32, 0x00445B70);
	DEFINE_MEMBER_FN(HasMoreRecords, bool, 0x00444780);
	DEFINE_MEMBER_FN(GetRecordString, void, 0x00445340, char *, UInt32);
};

STATIC_ASSERT(offsetof(TESFileRecord, unk240) == 0x240);
STATIC_ASSERT(offsetof(TESFileRecord, unk420) == 0x420);
STATIC_ASSERT(offsetof(TESFileRecord, unk299) == 0x299);

void __stdcall PreLoadFormHook(TESForm * form, TESFileRecord * record)
{
	/*static bool preloaded = false;
	//_MESSAGE("Preload\t\ti240: %08X\t\ti244: %08X\t\ti268: %08X\t\ti26C: %08X\t\ti258: %08X\t\ti25C: %08X\t\ti420: %08X\t\ti424: %08X\t\ti428: %08X\t\ti42C: %08X\t\ti299: %d", record->unk240, record->unk244, record->unk268, record->unk26C, record->unk258, record->unk25C, record->unk420, record->unk424, record->unk428, record->unk42C, record->unk299);
	if(!preloaded) {
		DumpClass(record, sizeof(TESSubrecord)/4);
		preloaded = true;
	}*/
}

void __stdcall LoadFormHook(TESForm * form, TESFileRecord * record)
{
	//static bool loadRecord = false;
	//_MESSAGE("Loading form %08X", form->formID, record->unk268, record->unk244);
	//_MESSAGE("Posload\t\ti240: %08X\t\ti244: %08X\t\ti268: %08X\t\ti26C: %08X\t\ti258: %08X\t\ti25C: %08X\t\ti420: %08X\t\ti424: %08X\t\ti428: %08X\t\ti42C: %08X\t\ti299: %d", record->unk240, record->unk244, record->unk268, record->unk26C, record->unk258, record->unk25C, record->unk420, record->unk424, record->unk428, record->unk42C, record->unk299);

	/*static bool postloaded = false;
	if(!postloaded) {
		DumpClass(record, sizeof(TESSubrecord)/4);
		postloaded = true;
	}*/

	record->unk268 = 0;
	record->unk26C = 0;


	char buff[0x200];
	memset(buff, 0, 0x200);

	UInt32 type = CALL_MEMBER_FN(record, GetNextRecord)();
	do
	{
		//_MESSAGE("Record %08X", type);
		if(type == 0x44494445) {
			//_MESSAGE("Found EDID %08X", type);
			memset(buff, 0, 0x200);
			CALL_MEMBER_FN(record, GetRecordString)(buff, 0x200);
			//_MESSAGE("FormID: %08X - EDID: %s", form->formID, buff);
		}
		if(!CALL_MEMBER_FN(record, HasMoreRecords)())
			break;
		type = CALL_MEMBER_FN(record, GetNextRecord)();
	} while (type != 0);

	editorIDs.insert(std::pair<UInt32, std::string>(form->formID, std::string(buff)));
}

static const UInt32 kInstallLoadFormHook_Base = 0x0043B4A0 + 0x16;
static const UInt32 kInstallLoadFormHook_Entry_retn = kInstallLoadFormHook_Base + 0x05;

__declspec(naked) void InstallLoadFormHooks_Entry(void)
{
	__asm
	{
		// Debugging only, remove later
		pushad
		push	edi				// record
		push	esi				// Form
		call	PreLoadFormHook
		popad

		and		bl, 1
		call	edx

		pushad
		push	edi				// record
		push	esi				// Form
		call	LoadFormHook
		popad

		jmp		[kInstallLoadFormHook_Entry_retn]
	}
}

extern "C"
{

bool SKSEPlugin_Query(const SKSEInterface * skse, PluginInfo * info)
{
	gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim\\SKSE\\skse_formengine.log");
	_MESSAGE("skse_formengine");

	// populate info structure
	info->infoVersion =	PluginInfo::kInfoVersion;
	info->name =		"formengine";
	info->version =		1;

	// store plugin handle so we can identify ourselves later
	g_pluginHandle = skse->GetPluginHandle();

	if(skse->isEditor)
	{
		_MESSAGE("loaded in editor, marking as incompatible");

		return false;
	}
	else if(skse->runtimeVersion != RUNTIME_VERSION_1_9_32_0)
	{
		_MESSAGE("unsupported runtime version %08X", skse->runtimeVersion);

		return false;
	}

	// supported runtime version
	return true;
}

bool SKSEPlugin_Load(const SKSEInterface * skse)
{
	// 0069DB13 - 0069D1D0
	WriteRelJump(kInstallLoadFormHook_Base, (UInt32)InstallLoadFormHooks_Entry);
	WriteRelCall(0x00699960 + 0x0F, (UInt32)LoadSceneGraphHook);
	return true;
}

};
