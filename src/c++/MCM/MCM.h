#pragma once

namespace MCM
{
	class Settings
	{
	public:
		class General
		{
		public:
			inline static bool bAutoAutoReturn{ true };
		};

		class Formatting
		{
		public:
			inline static std::string sPAAdded;
			inline static std::string sPAChassis;
			inline static std::string sPARecall;
			inline static std::string sPARecallTimer;
		};

		class Runtime
		{
		public:
			inline static std::int32_t iKeyCode;
		};

		static void Update()
		{
			if (m_FirstRun)
			{
				GetTranslationStrings();
				m_FirstRun = false;
			}

			m_ini_base.LoadFile("Data/MCM/Config/BakaPowerArmorStorage/settings.ini");
			m_ini_user.LoadFile("Data/MCM/Settings/BakaPowerArmorStorage.ini");

			GetModSettingBool("General", "bAutoAutoReturn", General::bAutoAutoReturn);

			HandleKeybinds();

			m_ini_base.Reset();
			m_ini_user.Reset();
		}

		inline static bool m_FirstRun{ true };

	private:
		static void GetModSettingChar(const std::string& a_section, const std::string& a_setting, std::string_view& a_value)
		{
			auto base = m_ini_base.GetValue(a_section.c_str(), a_setting.c_str(), a_value.data());
			auto user = m_ini_user.GetValue(a_section.c_str(), a_setting.c_str(), base);
			a_value = user;
		}

		static void GetModSettingBool(const std::string& a_section, const std::string& a_setting, bool& a_value)
		{
			auto base = m_ini_base.GetBoolValue(a_section.c_str(), a_setting.c_str(), a_value);
			auto user = m_ini_user.GetBoolValue(a_section.c_str(), a_setting.c_str(), base);
			a_value = user;
		}

		static void GetModSettingLong(const std::string& a_section, const std::string& a_setting, std::int32_t& a_value)
		{
			auto base = m_ini_base.GetLongValue(a_section.c_str(), a_setting.c_str(), a_value);
			auto user = m_ini_user.GetLongValue(a_section.c_str(), a_setting.c_str(), base);
			a_value = static_cast<std::int32_t>(user);
		}

		static void GetTranslationStrings()
		{
			if (auto BSScaleformManager = RE::BSScaleformManager::GetSingleton(); BSScaleformManager && BSScaleformManager->loader)
			{
				if (auto BSScaleformTranslator =
				        static_cast<RE::BSScaleformTranslator*>(
							BSScaleformManager->loader->GetStateAddRef(
								RE::Scaleform::GFx::State::StateType::kTranslator)))
				{
					auto FetchTranslation = [](RE::BSScaleformTranslator* a_trns, const wchar_t* a_key, std::string& a_output)
					{
						auto it = a_trns->translator.translationMap.find(a_key);
						if (it != a_trns->translator.translationMap.end())
						{
							a_output.resize(512);
							sprintf_s(a_output.data(), 512, "%ws", it->second.data());
						}
					};

					FetchTranslation(BSScaleformTranslator, L"$BakaPAS_Message_PAAdded", Formatting::sPAAdded);
					FetchTranslation(BSScaleformTranslator, L"$BakaPAS_Message_PAChassis", Formatting::sPAChassis);
					FetchTranslation(BSScaleformTranslator, L"$BakaPAS_Message_PARecall", Formatting::sPARecall);
					FetchTranslation(BSScaleformTranslator, L"$BakaPAS_Message_PARecallTimer", Formatting::sPARecallTimer);
				}
			}
		}

		static void HandleKeybinds()
		{
			try
			{
				std::ifstream fstream{ "Data/MCM/Settings/Keybinds.json" };
				nlohmann::json data =
					nlohmann::json::parse(fstream);
				fstream.close();

				for (auto& iter : data["keybinds"sv])
				{
					if (iter["id"sv] == "ModifierKey"
					    && iter["modName"sv] == "BakaPowerArmorStorage")
					{
						Runtime::iKeyCode = iter["keycode"sv];
						break;
					}
				}
			}
			catch (std::exception& a_exception)
			{
				Runtime::iKeyCode = 0;
				logger::debug("{:s}"sv, a_exception.what());
			}
		}

		inline static CSimpleIniA m_ini_base{ true };
		inline static CSimpleIniA m_ini_user{ true };
	};
}
