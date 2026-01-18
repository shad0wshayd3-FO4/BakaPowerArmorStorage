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
			Workshop::PlacementMode::Install();
			break;
		case F4SE::MessagingInterface::kGameLoaded:
			Workshop::PlacementMode::AddPerkToPlayer();
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

F4SE_PLUGIN_LOAD(const F4SE::LoadInterface* a_f4se)
{
	F4SE::Init(a_f4se, { .trampoline = true, .trampolineSize = 512 });
	F4SE::GetMessagingInterface()->RegisterListener(MessageCallback);
	F4SE::GetPapyrusInterface()->Register(Papyrus::RegisterFunctions);
	return true;
}
