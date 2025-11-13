// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameCast_Director_init() {}
	GAMECAST_DIRECTOR_API UFunction* Z_Construct_UDelegateFunction_GameCast_Director_BulletCountUpdatedDelegate__DelegateSignature();
	GAMECAST_DIRECTOR_API UFunction* Z_Construct_UDelegateFunction_GameCast_Director_DamagedDelegate__DelegateSignature();
	GAMECAST_DIRECTOR_API UFunction* Z_Construct_UDelegateFunction_GameCast_Director_PawnDeathDelegate__DelegateSignature();
	GAMECAST_DIRECTOR_API UFunction* Z_Construct_UDelegateFunction_GameCast_Director_SprintStateChangedDelegate__DelegateSignature();
	GAMECAST_DIRECTOR_API UFunction* Z_Construct_UDelegateFunction_GameCast_Director_UpdateSprintMeterDelegate__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_GameCast_Director;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_GameCast_Director()
	{
		if (!Z_Registration_Info_UPackage__Script_GameCast_Director.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_GameCast_Director_BulletCountUpdatedDelegate__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_GameCast_Director_DamagedDelegate__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_GameCast_Director_PawnDeathDelegate__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_GameCast_Director_SprintStateChangedDelegate__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_GameCast_Director_UpdateSprintMeterDelegate__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/GameCast_Director",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x4A312063,
				0xC6B46D8B,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_GameCast_Director.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_GameCast_Director.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_GameCast_Director(Z_Construct_UPackage__Script_GameCast_Director, TEXT("/Script/GameCast_Director"), Z_Registration_Info_UPackage__Script_GameCast_Director, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x4A312063, 0xC6B46D8B));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
