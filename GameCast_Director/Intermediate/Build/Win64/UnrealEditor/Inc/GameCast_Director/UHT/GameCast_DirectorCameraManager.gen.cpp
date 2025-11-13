// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameCast_DirectorCameraManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeGameCast_DirectorCameraManager() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_APlayerCameraManager();
GAMECAST_DIRECTOR_API UClass* Z_Construct_UClass_AGameCast_DirectorCameraManager();
GAMECAST_DIRECTOR_API UClass* Z_Construct_UClass_AGameCast_DirectorCameraManager_NoRegister();
UPackage* Z_Construct_UPackage__Script_GameCast_Director();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AGameCast_DirectorCameraManager ******************************************
void AGameCast_DirectorCameraManager::StaticRegisterNativesAGameCast_DirectorCameraManager()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AGameCast_DirectorCameraManager;
UClass* AGameCast_DirectorCameraManager::GetPrivateStaticClass()
{
	using TClass = AGameCast_DirectorCameraManager;
	if (!Z_Registration_Info_UClass_AGameCast_DirectorCameraManager.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("GameCast_DirectorCameraManager"),
			Z_Registration_Info_UClass_AGameCast_DirectorCameraManager.InnerSingleton,
			StaticRegisterNativesAGameCast_DirectorCameraManager,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_AGameCast_DirectorCameraManager.InnerSingleton;
}
UClass* Z_Construct_UClass_AGameCast_DirectorCameraManager_NoRegister()
{
	return AGameCast_DirectorCameraManager::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AGameCast_DirectorCameraManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Basic First Person camera manager.\n *  Limits min/max look pitch.\n */" },
#endif
		{ "IncludePath", "GameCast_DirectorCameraManager.h" },
		{ "ModuleRelativePath", "GameCast_DirectorCameraManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Basic First Person camera manager.\nLimits min/max look pitch." },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGameCast_DirectorCameraManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AGameCast_DirectorCameraManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerCameraManager,
	(UObject* (*)())Z_Construct_UPackage__Script_GameCast_Director,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AGameCast_DirectorCameraManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AGameCast_DirectorCameraManager_Statics::ClassParams = {
	&AGameCast_DirectorCameraManager::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008003ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AGameCast_DirectorCameraManager_Statics::Class_MetaDataParams), Z_Construct_UClass_AGameCast_DirectorCameraManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AGameCast_DirectorCameraManager()
{
	if (!Z_Registration_Info_UClass_AGameCast_DirectorCameraManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AGameCast_DirectorCameraManager.OuterSingleton, Z_Construct_UClass_AGameCast_DirectorCameraManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AGameCast_DirectorCameraManager.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AGameCast_DirectorCameraManager);
AGameCast_DirectorCameraManager::~AGameCast_DirectorCameraManager() {}
// ********** End Class AGameCast_DirectorCameraManager ********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_divit_OneDrive_Documents_GitHub_Unreal_Camera_Plugin_GameCast_Director_Source_GameCast_Director_GameCast_DirectorCameraManager_h__Script_GameCast_Director_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AGameCast_DirectorCameraManager, AGameCast_DirectorCameraManager::StaticClass, TEXT("AGameCast_DirectorCameraManager"), &Z_Registration_Info_UClass_AGameCast_DirectorCameraManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AGameCast_DirectorCameraManager), 1330091267U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_divit_OneDrive_Documents_GitHub_Unreal_Camera_Plugin_GameCast_Director_Source_GameCast_Director_GameCast_DirectorCameraManager_h__Script_GameCast_Director_3081684766(TEXT("/Script/GameCast_Director"),
	Z_CompiledInDeferFile_FID_Users_divit_OneDrive_Documents_GitHub_Unreal_Camera_Plugin_GameCast_Director_Source_GameCast_Director_GameCast_DirectorCameraManager_h__Script_GameCast_Director_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_divit_OneDrive_Documents_GitHub_Unreal_Camera_Plugin_GameCast_Director_Source_GameCast_Director_GameCast_DirectorCameraManager_h__Script_GameCast_Director_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
