#include "skse/GameForms.h"
#include "skse/GameObjects.h"

const _LookupFormByID LookupFormByID = (_LookupFormByID)0x00451A30;

void			TESForm::Unk_04(void) {};		// reset/init? would leak pointers if called on a live object
void			TESForm::Unk_05(void) {};		// release pointers?
bool			TESForm::LoadForm(UInt32 arg) { return false; };
bool			TESForm::Unk_07(UInt32 arg) { return false; };
bool			TESForm::Unk_08(UInt32 arg) { return false; };	// calls LoadForm
TESForm *		TESForm::Unk_09(UInt32 arg1, void * arg2) { return NULL; };
bool			TESForm::Unk_0A(UInt32 changed) { return false; };	// mark as changed?
void			TESForm::Unk_0B(UInt32 arg) {};
bool			TESForm::Unk_0C(UInt32 arg) { return false; };
void			TESForm::Unk_0D(UInt32 arg) {};
void			TESForm::Unk_0E(UInt32 arg) {};
void			TESForm::Unk_0F(void * arg) {};
void			TESForm::Unk_10(UInt32 arg) {};
void			TESForm::Unk_11(UInt32 arg) {};
void			TESForm::Unk_12(UInt32 arg) {};
void			TESForm::InitItem(void) {};		// called once all dependent forms are loaded
void			TESForm::Unk_14(void) {};
UInt32			TESForm::GetFormType(void) { return 0; };
void			TESForm::GetFormDesc(char * buf, UInt32 bufLen) {};
bool			TESForm::GetFlag00000040(void) { return false; };
bool			TESForm::GetFlag00010000(void) { return false; };
bool			TESForm::GetFlag00020000(void) { return false; };
bool			TESForm::GetFlag00080000(void) { return false; };
bool			TESForm::GetFlag02000000(void) { return false; };
bool			TESForm::Unk_1B(void) { return false; };
bool			TESForm::GetFlag00000200(void) { return false; };
bool			TESForm::GetFlag00000100(void) { return false; };
void			TESForm::SetFlag00000200(bool set) {};
bool			TESForm::Unk_20(void) { return false; };
void			TESForm::SetFlag00000020(bool set) {};
void			TESForm::SetFlag00000002(bool set) {};
void			TESForm::Unk_23(void) {};
void			TESForm::Unk_24(UInt32 arg) {};
bool			TESForm::Unk_25(void) { return false; };
bool			TESForm::Unk_26(void) { return false; };
bool			TESForm::Has3D(void) { return false; };
bool			TESForm::Unk_28(void) { return false; };
UInt32			TESForm::Unk_29(void) { return 0; };
UInt32			TESForm::Unk_2A(void) { return 0; };
UInt32			TESForm::Unk_2B(void) { return 0; };
const char *	TESForm::GetFullName(void) { return NULL; };
void			TESForm::CopyFrom(TESForm * srcForm) {};
bool			TESForm::Compare(TESForm * rhs) { return false; };
void			TESForm::Unk_2F(void * dst, UInt32 unk) {};
const char *	TESForm::GetName(void) { return NULL; };
bool			TESForm::SetName(const char * str) { return false; };
bool			TESForm::Unk_32(void) { return false; };
bool			TESForm::Unk_33(void) { return false; };
bool			TESForm::Unk_34(UInt32 arg) { return false; };
bool			TESForm::Unk_35(UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4) { return false; };
void			TESForm::SetFormID(UInt32 id, UInt32 generateID) {};
const char *	TESForm::Unk_37(void) { return NULL; };
bool			TESForm::Unk_38(void) { return false; };