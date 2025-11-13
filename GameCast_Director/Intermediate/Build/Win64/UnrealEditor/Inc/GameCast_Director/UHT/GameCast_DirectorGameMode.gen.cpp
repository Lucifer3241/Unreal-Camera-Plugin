// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameCast_DirectorGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeGameCast_DirectorGameMode() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
GAMECAST_DIRECTOR_API UClass* Z_Construct_UClass_AGameCast_DirectorGameMode();
GAMECAST_DIRECTOR_API UClass* Z_Construct_UClass_AGameCast_DirectorGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_GameCast_Director();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AGameCast_DirectorGameMode ***********************************************
void AGameCast_DirectorGameMode::StaticRegisterNativesAGameCast_DirectorGameMode()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AGameCast_DirectorGameMode;
UClass* AGameCast_DirectorGameMode::GetPrivateStaticClass()
{
	using TClass = AGameCast_DirectorGameMode;
	if (!Z_Registration_Info_UClass_AGameCast_DirectorGameMode.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("GameCast_DirectorGameMode"),
			Z_Registration_Info_UClass_AGameCast_DirectorGameMode.InnerSingleton,
			StaticRegisterNativesAGameCast_DirectorGameMode,
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
	return Z_Registration_Info_UClass_AGameCast_DirectorGameMode.InnerSingleton;
}
UClass* Z_Construct_UClass_AGameCast_DirectorGameMode_NoRegister()
{
	return AGameCast_DirectorGameMode::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AGameCast_DirectorGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple GameMode for a first person game\n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "GameCast_DirectorGameMode.h" },
		{ "ModuleRelativePath", "GameCast_DirectorGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple GameMode for a first person game" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGameCast_DirectorGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AGameCast_DirectorGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_GameCast_Director,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AGameCast_DirectorGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AGameCast_DirectorGameMode_Statics::ClassParams = {
	&AGameCast_DirectorGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008003ADu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AGameCast_DirectorGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AGameCast_DirectorGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AGameCast_DirectorGameMode()
{
	if (!Z_Registration_Info_UClass_AGameCast_DirectorGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AGameCast_DirectorGameMode.OuterSingleton, Z_Construct_UClass_AGameCast_DirectorGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AGameCast_DirectorGameMode.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AGameCast_DirectorGameMode);
AGameCast_DirectorGameMode::~AGameCast_DirectorGameMode() {}
// ********** End Class AGameCast_DirectorGameMode *************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_divit_OneDrive_Documents_GitHub_Unreal_Camera_Plugin_GameCast_Director_Source_GameCast_Director_GameCast_DirectorGameMode_h__Script_GameCast_Director_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AGameCast_DirectorGameMode, AGameCast_DirectorGameMode::StaticClass, TEXT("AGameCast_DirectorGameMode"), &Z_Registration_Info_UClass_AGameCast_DirectorGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AGameCast_DirectorGameMode), 2981300334U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_divit_OneDrive_Documents_GitHub_Unreal_Camera_Plugin_GameCast_Director_Source_GameCast_Director_GameCast_DirectorGameMode_h__Script_GameCast_Director_428576476(TEXT("/Script/GameCast_Director"),
	Z_CompiledInDeferFile_FID_Users_divit_OneDrive_Documents_GitHub_Unreal_Camera_Plugin_GameCast_Director_Source_GameCast_Director_GameCast_DirectorGameMode_h__Script_GameCast_Director_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_divit_OneDrive_Documents_GitHub_Unreal_Camera_Plugin_GameCast_Director_Source_GameCast_Director_GameCast_DirectorGameMode_h__Script_GameCast_Director_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
