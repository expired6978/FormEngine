#include "skse/GameObjects.h"
#include "skse/GameData.h"
#include "skse/GameRTTI.h"

UInt32	TESObject::Unk_39(void) { return 0; };
bool	TESObject::Unk_3A(void) { return false; };
UInt32	TESObject::Unk_3B(void) { return 0; };
bool	TESObject::Unk_3C(void) { return false; };
void	TESObject::Unk_3D(UInt32 arg) {};
UInt32	TESObject::Unk_3E(UInt32 arg0, UInt32 arg1) { return 0; };
void	TESObject::Unk_3F(void * arg) {};
bool	TESObject::Unk_40(void) { return false; };
bool	TESObject::Unk_41(void) { return false; };
void	TESObject::Unk_42(void) {};
void	TESObject::Unk_43(UInt32 arg0, UInt32 arg1) {};
UInt32	TESObject::Unk_44(void) { return 0; };
UInt32	TESObject::Unk_45(void) { return 0; };
void *	TESObject::Unk_46(void) { return NULL; };

void	TESBoundObject::Unk_47(UInt32 arg) {};
UInt32	TESBoundObject::Unk_48(void) { return 0; };
UInt32	TESBoundObject::Unk_49(UInt32 arg) { return 0; };	// return Unk_3E(arg, 0) {};
bool	TESBoundObject::Unk_4A(void) { return false; };
bool	TESBoundObject::Unk_4B(void * arg0, BSString * dst) { return false; };	// steal/take string
bool	TESBoundObject::Unk_4C(void * arg0, UInt8 arg1, UInt32 arg2, float arg3) { return false; };
void	TESBoundObject::Unk_4D(UInt32 arg) {};
void	TESBoundObject::Unk_4E(UInt32 arg) {};
void	TESBoundObject::Unk_4F(void) {};
void	TESBoundObject::Unk_50(void) {};
void	TESBoundObject::Unk_51(void) {};

UInt32	MagicItem::Unk_52(void) { return 0; };	// pure
void	MagicItem::Unk_53(UInt32 arg) {};
UInt32	MagicItem::Unk_54(void) { return 0; };	// pure
void	MagicItem::Unk_55(UInt32 arg) {};
UInt32	MagicItem::Unk_56(void) { return 0; };	// pure
bool	MagicItem::Unk_57(UInt32 arg) { return false; };
float	MagicItem::Unk_58(void) { return 0.0; };
float	MagicItem::Unk_59(void) { return 0.0; };
bool	MagicItem::Unk_5A(void) { return false; };
bool	MagicItem::Unk_5B(void) { return false; };
bool	MagicItem::Unk_5C(void) { return false; };
bool	MagicItem::Unk_5D(void) { return false; };
bool	MagicItem::Unk_5E(void) { return false; };
bool	MagicItem::Unk_5F(UInt32 arg) { return false; };
bool	MagicItem::Unk_60(void) { return false; };
bool	MagicItem::Unk_61(void) { return false; };
void	MagicItem::Unk_62(UInt32 arg0, UInt32 arg1) {};
float	MagicItem::Unk_63(void) { return 0.0; };
UInt32	MagicItem::Unk_64(void) { return 0; };
UInt32	MagicItem::Unk_65(void) { return 0; };
bool	MagicItem::Unk_66(void) { return false; };
UInt32	MagicItem::Unk_67(void) { return 0; };	// pure, returns char code
void	MagicItem::Unk_68(MagicItem * src) {};	// pure, copy data if possible?
void	MagicItem::Unk_69(UInt32 arg0, UInt32 arg1) {};	// loading-related
void	MagicItem::Unk_6A(UInt32 arg) {};
void *	MagicItem::Unk_6B(void) { return NULL; };	// pure, returns data
void *	MagicItem::Unk_6C(void) { return NULL; };	// pure, returns data
UInt32	MagicItem::Unk_6D(void) { return 0; };	// pure, return size of data
void	MagicItem::Unk_6E(void) {};	// pure, byteswap?