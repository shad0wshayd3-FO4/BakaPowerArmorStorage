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

		bool AttachScript(std::monostate, RE::TESObjectREFR* a_refr)
		{
			return Workshop::PlacementMode::AttachScript(a_refr);
		}

		bool RemoveScript(std::monostate, RE::TESObjectREFR* a_refr)
		{
			return Workshop::PlacementMode::RemoveScript(a_refr);
		}

		void ShowNotification(std::monostate, std::int32_t a_time)
		{
			if (a_time == 0)
			{
				RE::SendHUDMessage::ShowHUDMessage(
					"Power Armor has been recalled to your inventory.",
					nullptr,
					false,
					true);
			}
			else
			{
				auto msg = fmt::format("Power Armor will be recalled in {:d} seconds.", a_time);
				RE::SendHUDMessage::ShowHUDMessage(
					msg.c_str(),
					nullptr,
					false,
					true);
			}
		}
	}

	bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_VM)
	{
		// BakaPowerArmorStorage
		a_VM->BindNativeMethod(BakaPowerArmorStorage::SCRIPT_NAME, "CreateToken", BakaPowerArmorStorage::CreateToken, true);
		a_VM->BindNativeMethod(BakaPowerArmorStorage::SCRIPT_NAME, "HandleToken", BakaPowerArmorStorage::HandleToken, true);
		a_VM->BindNativeMethod(BakaPowerArmorStorage::SCRIPT_NAME, "AttachScript", BakaPowerArmorStorage::AttachScript, true);
		a_VM->BindNativeMethod(BakaPowerArmorStorage::SCRIPT_NAME, "RemoveScript", BakaPowerArmorStorage::RemoveScript, true);
		a_VM->BindNativeMethod(BakaPowerArmorStorage::SCRIPT_NAME, "ShowNotification", BakaPowerArmorStorage::ShowNotification, true);

		return true;
	}
}
