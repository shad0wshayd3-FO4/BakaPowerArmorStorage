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
		}

		inline static CSimpleIniA                                  ini_file{ true };
		inline static RE::BSTHashMap<RE::BGSKeyword*, std::string> map;
	};

	RE::BGSDefaultObject* PAFrameWorkshop_DO{ nullptr };
	RE::BGSDefaultObject* PAFrameToken_DO{ nullptr };
	RE::BGSDefaultObject* PAFramePerk_DO{ nullptr };
	RE::BGSKeyword*       ap_PowerArmor_BodyMod{ nullptr };

	namespace
	{
		RE::BGSDefaultObject* WorkshopItemPlaceFailSound{ nullptr };

		std::uint32_t hkDefaultObject()
		{
			// Initializer override
			WorkshopItemPlaceFailSound =
				RE::DefaultObjectFormFactory::Create(
					"WorkshopItemPlaceFailSound",
					"Default sound played when an item can not be placed.",
					RE::ENUM_FORM_ID::kSNDR);

			// Add new
			PAFrameWorkshop_DO =
				RE::DefaultObjectFormFactory::Create(
					"PAFrameWorkshop_DO",
					RE::ENUM_FORM_ID::kCONT);

			PAFrameToken_DO =
				RE::DefaultObjectFormFactory::Create(
					"PAFrameToken_DO",
					RE::ENUM_FORM_ID::kARMO);

			PAFramePerk_DO =
				RE::DefaultObjectFormFactory::Create(
					"PAFramePerk_DO",
					RE::ENUM_FORM_ID::kPERK);

			REX::DEBUG("Injected DefaultObjects."sv);
			return 1;
		}
	}

	void Install()
	{
		REL::Relocation<std::uintptr_t> target{ REL::ID(599538) };
		target.replace_func(0x2C, hkDefaultObject);
	}

	void InstallDataReady()
	{
		PANameScheme::Install();
		ap_PowerArmor_BodyMod = RE::TESForm::GetFormByID<RE::BGSKeyword>(0x00055F8C);
	}
};
