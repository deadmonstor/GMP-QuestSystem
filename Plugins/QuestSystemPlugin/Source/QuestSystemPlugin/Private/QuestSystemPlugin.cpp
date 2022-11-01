// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestSystemPlugin.h"

#include "QuestSystemPlugin/MyCustomizationTest.h"

#define LOCTEXT_NAMESPACE "FQuestSystemModule"
	DEFINE_LOG_CATEGORY(LogQuestSystemModule)
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuestSystemModule, QuestSystemPlugin)

void FQuestSystemModule::StartupModule()
{
	IModuleInterface::StartupModule();

	auto& PropertyModule = FModuleManager::LoadModuleChecked< FPropertyEditorModule >("PropertyEditor");

	PropertyModule.RegisterCustomClassLayout(
		"QuestSettings",
		FOnGetDetailCustomizationInstance::CreateStatic(&FMyCustomizationTest::MakeInstance)
	);

	PropertyModule.NotifyCustomizationModuleChanged();
}

void FQuestSystemModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();

	if(FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
    {
        auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    
        PropertyModule.UnregisterCustomClassLayout("QuestSettings");
    }
}
