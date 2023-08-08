#pragma once

namespace Forms
{
	RE::BGSDefaultObject* PAFrameWorkshop_DO{ nullptr };
	RE::BGSDefaultObject* PAFrameToken_DO{ nullptr };
	RE::BGSDefaultObject* PAFramePerk_DO{ nullptr };
	RE::BGSDefaultObject* PAFrameMessage_DO{ nullptr };

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

			PAFrameMessage_DO =
				RE::DefaultObjectFormFactory::Create(
					"PAFrameMessage_DO",
					RE::ENUM_FORM_ID::kMESG);

			logger::debug("Injected DefaultObjects."sv);
			return 1;
		}
	}

	void Install()
	{
		REL::Relocation<std::uintptr_t> targetDFOB{ REL::ID(599538) };
		stl::asm_replace(targetDFOB.address(), 0x2C, reinterpret_cast<std::uintptr_t>(hkDefaultObject));
	}
};
