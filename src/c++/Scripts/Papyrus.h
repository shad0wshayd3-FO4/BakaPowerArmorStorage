#pragma once

#include "Workshop/Workshop.h"

namespace Papyrus
{
	namespace BakaPowerArmorStorage
	{
		constexpr auto SCRIPT_NAME{ "BakaPowerArmorStorage"sv };

		bool CreateToken(std::monostate, RE::TESObjectREFR* a_refr)
		{
			return Workshop::PlacementMode::CreateToken(a_refr);
		}

		bool HandleToken(std::monostate, RE::TESObjectREFR* a_refr)
		{
			return Workshop::PlacementMode::HandleToken(a_refr);
		}

		bool RemoveScript(std::monostate, RE::TESObjectREFR* a_refr)
		{
			return Workshop::PlacementMode::RemoveScript(a_refr);
		}
	}

	bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_VM)
	{
		// BakaPowerArmorStorage
		a_VM->BindNativeMethod(BakaPowerArmorStorage::SCRIPT_NAME, "CreateToken", BakaPowerArmorStorage::CreateToken, true);
		a_VM->BindNativeMethod(BakaPowerArmorStorage::SCRIPT_NAME, "HandleToken", BakaPowerArmorStorage::HandleToken, true);
		a_VM->BindNativeMethod(BakaPowerArmorStorage::SCRIPT_NAME, "RemoveScript", BakaPowerArmorStorage::RemoveScript, true);

		return true;
	}
}
