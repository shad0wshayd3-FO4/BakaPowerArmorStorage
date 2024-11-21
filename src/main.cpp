#include "Forms/Forms.h"
#include "MCM/MCM.h"
#include "Scripts/Papyrus.h"
#include "Workshop/Workshop.h"

namespace
{
	void MessageCallback(F4SE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type)
		{
		case F4SE::MessagingInterface::kPostLoad:
			Forms::Install();
			Workshop::PlacementMode::Hooks::Install();
			break;
		case F4SE::MessagingInterface::kGameLoaded:
			Workshop::PlacementMode::ApplyPerk();
			break;
		case F4SE::MessagingInterface::kGameDataReady:
			Forms::InstallDataReady();
			MCM::Settings::Update(true);
			break;
		default:
			break;
		}
	}
}

F4SEPluginLoad(const F4SE::LoadInterface* a_F4SE)
{
	F4SE::Init(a_F4SE);

	F4SE::AllocTrampoline(1u << 10);
	F4SE::GetMessagingInterface()->RegisterListener(MessageCallback);
	F4SE::GetPapyrusInterface()->Register(Papyrus::RegisterFunctions);

	return true;
}
