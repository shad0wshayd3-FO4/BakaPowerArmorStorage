#pragma once

#include "MCM/MCM.h"
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
			if (a_time < 0)
			{
				RE::SendHUDMessage::ShowHUDMessage(
					MCM::Settings::Formatting::sPAAdded.c_str(),
					nullptr,
					true,
					true);
			}
			else if (a_time == 0)
			{
				RE::SendHUDMessage::ShowHUDMessage(
					MCM::Settings::Formatting::sPARecall.c_str(),
					nullptr,
					false,
					true);
			}
			else
			{
				auto msg = fmt::format(fmt::runtime(MCM::Settings::Formatting::sPARecallTimer), a_time);
				RE::SendHUDMessage::ShowHUDMessage(
					msg.c_str(),
					nullptr,
					false,
					true);
			}
		}

		void UpdateSettings(std::monostate)
		{
			MCM::Settings::Update();
		}

		std::int32_t GetKeyCode(std::monostate)
		{
			return MCM::Settings::Runtime::iKeyCode;
		}

		void FunctionStub(std::monostate)
		{
			return;
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
		a_VM->BindNativeMethod(BakaPowerArmorStorage::SCRIPT_NAME, "UpdateSettings", BakaPowerArmorStorage::UpdateSettings, true);
		a_VM->BindNativeMethod(BakaPowerArmorStorage::SCRIPT_NAME, "GetKeyCode", BakaPowerArmorStorage::GetKeyCode, true);
		a_VM->BindNativeMethod(BakaPowerArmorStorage::SCRIPT_NAME, "FunctionStub", BakaPowerArmorStorage::FunctionStub, true);

		return true;
	}
}
