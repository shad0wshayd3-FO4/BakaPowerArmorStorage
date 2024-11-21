#pragma once

namespace MCM
{
	class Settings
	{
	public:
		class General
		{
		public:
			inline static REX::INI::Bool bAutoAutoReturn{ "General", "bAutoAutoReturn", true };
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

		static void Update(bool a_firstRun)
		{
			if (a_firstRun)
			{
				GetTranslationStrings();
			}

			const auto ini = REX::INI::SettingStore::GetSingleton();
			ini->Init(
				"Data/MCM/Config/BakaPowerArmorStorage/settings.ini",
				"Data/MCM/Settings/BakaPowerArmorStorage.ini");
			ini->Load();

			HandleKeybinds();
		}

		inline static bool m_FirstRun{ true };

	private:
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
			/*
			try
			{
				std::ifstream fstream{ "Data/MCM/Settings/Keybinds.json" };
				nlohmann::json data =
					nlohmann::json::parse(fstream);
				fstream.close();

				for (auto& iter : data["keybinds"sv])
				{
					if (iter["id"sv] == "ModifierKey" && iter["modName"sv] == "BakaPowerArmorStorage")
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
			*/
		}
	};
}
