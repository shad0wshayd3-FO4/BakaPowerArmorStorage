#pragma once

namespace Forms
{
	class PANameScheme
	{
	public:
		static void Install()
		{
			map.clear();
			LoadSetting();
		}

		static std::string Get(RE::TESObjectARMO* a_armo)
		{
			for (auto& [kywd, name] : map)
			{
				if (a_armo->HasKeyword(kywd))
				{
					return name;
				}
			}

			return std::string{};
		}

	private:
		static void LoadSetting()
		{
			const auto root = std::filesystem::path{ "Data/F4SE/plugins/BakaPowerArmorStorage/"sv };
			if (auto TESDataHandler = RE::TESDataHandler::GetSingleton())
			{
				for (auto iter : TESDataHandler->compiledFileCollection.files)
				{
					auto path = root / iter->GetFilename();
					path.replace_extension("ini"sv);
					LoadSetting(path);
				}

				for (auto iter : TESDataHandler->compiledFileCollection.smallFiles)
				{
					auto path = root / iter->GetFilename();
					path.replace_extension("ini"sv);
					LoadSetting(path);
				}
			}
		}

		static void LoadSetting(std::filesystem::path& a_path)
		{
			/*
			if (!std::filesystem::exists(a_path))
			{
				return;
			}

			ini_file.LoadFile(a_path.c_str());
			std::list<CSimpleIniA::Entry> Sections;
			ini_file.GetAllSections(Sections);

			bool bActive{ false };
			for (auto& iter : Sections)
			{
				if (auto form = ini_file.GetValue(iter.pItem, "keyword", nullptr))
				{
					if (auto kywd = RE::TESForm::GetFormByEditorID<RE::BGSKeyword>(form))
					{
						map.emplace(kywd, iter.pItem);
						bActive = true;
					}
				}
			}

			if (bActive)
			{
				F4SE::log::info("Loaded from: {:s}"sv, a_path.string());
			}

			ini_file.Reset();
			*/
		}

		inline static RE::BSTHashMap<RE::BGSKeyword*, std::string> map;
	};

	RE::TESObjectCONT* PAFrameWorkshop{ nullptr };
	RE::TESObjectARMO* PAFrameToken{ nullptr };
	RE::BGSPerk*       PAFramePerk{ nullptr };
	RE::BGSKeyword*    ap_PowerArmor_BodyMod{ nullptr };

	void InstallDataReady()
	{
		PANameScheme::Install();
		if (auto TESDataHandler = RE::TESDataHandler::GetSingleton())
		{
			PAFrameToken = TESDataHandler->LookupForm<RE::TESObjectARMO>(0xC00, "BakaPowerArmorStorage.esm");
			PAFrameWorkshop = TESDataHandler->LookupForm<RE::TESObjectCONT>(0xA00, "BakaPowerArmorStorage.esm");
			PAFramePerk = TESDataHandler->LookupForm<RE::BGSPerk>(0xA02, "BakaPowerArmorStorage.esm");
		}
		ap_PowerArmor_BodyMod = RE::TESForm::GetFormByID<RE::BGSKeyword>(0x00055F8C);
	}
};
