#include "MyCustomizationTest.h"
#include "DataAssets/UQuestStep.h"
#include "PropertyEditing.h"

TSharedRef< IDetailCustomization > FMyCustomizationTest::MakeInstance()
{
	return MakeShareable(new FMyCustomizationTest);
}

void FMyCustomizationTest::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	// This is where the core of the customization code will go.
}