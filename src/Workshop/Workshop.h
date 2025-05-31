#pragma once

#include "MCM/MCM.h"

namespace Workshop
{
	class PlacementMode :
		public REX ::Singleton<PlacementMode>,
		public RE::BSTEventSink<RE::MenuOpenCloseEvent>,
		public RE::BSTEventSink<RE::Workshop::ItemPlacedEvent>,
		public RE::BSTEventSink<RE::Workshop::WorkshopModeEvent>
	{
	public:
		class Hooks
		{
		private:
			// Disable selection in UI
			class hkCanNavigate
			{
			private:
				static bool CanNavigate()
				{
					return PlacementMode::IsActive() ? false : _Hook0();
				}

				inline static REL::Hook _Hook0{ REL::ID(119865), 0x37A, CanNavigate };
				inline static REL::Hook _Hook1{ REL::ID(119865), 0x3EA, CanNavigate };
				inline static REL::Hook _Hook2{ REL::ID(119865), 0x4C5, CanNavigate };
				inline static REL::Hook _Hook3{ REL::ID(119865), 0x768, CanNavigate };
				inline static REL::Hook _Hook4{ REL::ID(985073), 0x0C, CanNavigate };
				inline static REL::Hook _Hook5{ REL::ID(1130413), 0x0C, CanNavigate };
			};

			// Prevent Workshops marked as deleted as being valid
			class hkIsReferenceWithinBuildableArea
			{
			private:
				static bool IsReferenceWithinBuildableArea(const RE::TESObjectREFR& a_workshop, const RE::TESObjectREFR& a_refr)
				{
					if (PlacementMode::IsActive())
					{
						return true;
					}

					if (a_workshop.formFlags & 0x20)
					{
						return false;
					}

					return _Hook0(a_workshop, a_refr);
				}

				inline static REL::Hook _Hook0{ REL::ID(2562), 0x156, IsReferenceWithinBuildableArea };
				inline static REL::Hook _Hook1{ REL::ID(978467), 0x07E, IsReferenceWithinBuildableArea };
				inline static REL::Hook _Hook2{ REL::ID(90862), 0x039, IsReferenceWithinBuildableArea };
				inline static REL::Hook _Hook3{ REL::ID(939377), 0x090, IsReferenceWithinBuildableArea };
				inline static REL::Hook _Hook4{ REL::ID(552874), 0x024, IsReferenceWithinBuildableArea };
				inline static REL::Hook _Hook5{ REL::ID(525394), 0x017, IsReferenceWithinBuildableArea };
				inline static REL::Hook _Hook6{ REL::ID(311311), 0x0A6, IsReferenceWithinBuildableArea };
				inline static REL::Hook _Hook7{ REL::ID(566990), 0x05C, IsReferenceWithinBuildableArea };
				inline static REL::Hook _Hook8{ REL::ID(286947), 0x047, IsReferenceWithinBuildableArea };
				inline static REL::Hook _Hook9{ REL::ID(1371490), 0x091, IsReferenceWithinBuildableArea };
				inline static REL::Hook _HookA{ REL::ID(931840), 0x165, IsReferenceWithinBuildableArea };
				inline static REL::Hook _HookB{ REL::ID(1515428), 0x036, IsReferenceWithinBuildableArea };
			};

			// Disable Workshop Startup/End sounds
			class hkPlayMenuSound
			{
			private:
				static bool PlayMenuSound(const char* a_soundName)
				{
					if (PlacementMode::IsActive())
					{
						PlacementMode::GetSingleton()->m_hasSound = true;
						return _Hook0(nullptr);
					}

					if (PlacementMode::GetSingleton()->m_hasSound)
					{
						if (_stricmp(a_soundName, "UIWorkshopModeExit") == 0)
						{
							PlacementMode::GetSingleton()->m_hasSound = false;
							return _Hook0(nullptr);
						}
					}

					return _Hook0(a_soundName);
				}

				inline static REL::Hook _Hook0{ REL::ID(598489), 0x1195, PlayMenuSound };
				inline static REL::Hook _Hook1{ REL::ID(98443), 0x01B5, PlayMenuSound };
			};

			// Prevent tagging for search in FreeBuild mode
			class hkShouldShowTagForSearch
			{
			private:
				static std::uint64_t ShouldShowTagForSearch(RE::WorkshopMenu* a_this)
				{
					return PlacementMode::IsActive() ? 0 : _Hook0(a_this);
				}

				inline static REL::Hook _Hook0{ REL::ID(119865), 0xEBB, ShouldShowTagForSearch };
				inline static REL::Hook _Hook1{ REL::ID(1089189), 0x574, ShouldShowTagForSearch };
			};

			// Prevent a stupid textbox from showing up for a split second after placing an item
			class hkUpdateRequirements
			{
			private:
				static void UpdateRequirements(RE::WorkshopMenu* a_this, bool a_stringingWire)
				{
					if (PlacementMode::IsActive())
					{
						return;
					}

					_Hook0(a_this, a_stringingWire);
				}

				inline static REL::Hook _Hook0{ REL::ID(598489), 0x1144, UpdateRequirements };
				inline static REL::Hook _Hook1{ REL::ID(1280212), 0x1F0, UpdateRequirements };
				inline static REL::Hook _Hook2{ REL::ID(119865), 0x05C5, UpdateRequirements };
				inline static REL::Hook _Hook3{ REL::ID(119865), 0x0868, UpdateRequirements };
				inline static REL::Hook _Hook4{ REL::ID(119865), 0x0A16, UpdateRequirements };
				inline static REL::Hook _Hook5{ REL::ID(119865), 0x0A42, UpdateRequirements };
				inline static REL::Hook _Hook6{ REL::ID(119865), 0x0A65, UpdateRequirements };
				inline static REL::Hook _Hook7{ REL::ID(119865), 0x0A88, UpdateRequirements };
				inline static REL::Hook _Hook8{ REL::ID(119865), 0x0C64, UpdateRequirements };
				inline static REL::Hook _Hook9{ REL::ID(119865), 0x0CD4, UpdateRequirements };
				inline static REL::Hook _HookA{ REL::ID(119865), 0x0F53, UpdateRequirements };
				inline static REL::Hook _HookB{ REL::ID(119865), 0x10FD, UpdateRequirements };
				inline static REL::Hook _HookC{ REL::ID(119865), 0x1181, UpdateRequirements };
				inline static REL::Hook _HookD{ REL::ID(119865), 0x13F6, UpdateRequirements };
				inline static REL::Hook _HookE{ REL::ID(119865), 0x1764, UpdateRequirements };
			};

			// Prevent stored frames from stacking
			class hkCompareImpl
			{
			private:
				static bool CompareImpl(RE::ExtraStartingWorldOrCell* a_this, const RE::ExtraStartingWorldOrCell& a_compare)
				{
					if (!a_this)
					{
						return true;
					}

					if (a_this->type != RE::ExtraStartingWorldOrCell::TYPE ||
						a_compare.type != RE::ExtraStartingWorldOrCell::TYPE)
					{
						return true;
					}

					if (a_this->startingWorldOrCell->GetFormType() == RE::ENUM_FORM_ID::kCELL ||
						a_this->startingWorldOrCell->GetFormType() == RE::ENUM_FORM_ID::kWRLD ||
						a_compare.startingWorldOrCell->GetFormType() == RE::ENUM_FORM_ID::kCELL ||
						a_compare.startingWorldOrCell->GetFormType() == RE::ENUM_FORM_ID::kWRLD)
					{
						return false;
					}

					return a_this->startingWorldOrCell != a_compare.startingWorldOrCell;
				}

				inline static REL::HookVFT _CompareImpl{ RE::ExtraStartingWorldOrCell::VTABLE[0], 0x01, CompareImpl };
			};

			// Redirect Cancel input, block other buttons
			class hkHandleEvent
			{
			private:
				static void HandleEvent(RE::BSInputEventUser* a_this, RE::ButtonEvent* a_event)
				{
					if (a_event && PlacementMode::IsActive())
					{
						if (a_event->QUserEvent() == "XButton" ||
							a_event->QUserEvent() == "YButton" ||
							a_event->QUserEvent() == "LShoulder" ||
							a_event->QUserEvent() == "RShoulder" ||
							a_event->QUserEvent() == "LTrigger" ||
							a_event->QUserEvent() == "RTrigger" ||
							a_event->QUserEvent() == "Sprint" ||
							a_event->QUserEvent() == "Jump")
						{
							return;
						}

						if (a_event->QUserEvent() == "Cancel")
						{
							a_event->strUserEvent = "CloseMenu";
							return _HandleEvent(a_this, a_event);
						}
					}

					_HandleEvent(a_this, a_event);
				}

				inline static REL::HookVFT _HandleEvent{ RE::WorkshopMenu::VTABLE[1], 0x08, HandleEvent };
			};

			// Enable ExtraStartingWorldOrCell as a stacking condition
			class hkUIQualifier
			{
			private:
				static bool UIQualifier(const RE::BSExtraData* a_extra)
				{
					if (!a_extra)
					{
						return false;
					}

					switch (a_extra->type.get())
					{
					// case RE::EXTRA_DATA_TYPE::kPersistentCell:
					// case RE::EXTRA_DATA_TYPE::kKeywords:
					// case RE::EXTRA_DATA_TYPE::kStartingPosition:
					// case RE::EXTRA_DATA_TYPE::kReferenceHandle:
					// case RE::EXTRA_DATA_TYPE::kOwnership:
					// case RE::EXTRA_DATA_TYPE::kGlobal:
					// case RE::EXTRA_DATA_TYPE::kRank:
					case RE::EXTRA_DATA_TYPE::kHealth:
					// case RE::EXTRA_DATA_TYPE::kTimeLeft:
					case RE::EXTRA_DATA_TYPE::kCharge:
					// case RE::EXTRA_DATA_TYPE::kLevelItem:
					// case RE::EXTRA_DATA_TYPE::kScale:
					case RE::EXTRA_DATA_TYPE::kObjectInstance:
					case RE::EXTRA_DATA_TYPE::kCannotWear:
					case RE::EXTRA_DATA_TYPE::kPoison:
					case RE::EXTRA_DATA_TYPE::kBoundArmor:
					case RE::EXTRA_DATA_TYPE::kStartingWorldOrCell:
					// case RE::EXTRA_DATA_TYPE::kFavorite:
					// case RE::EXTRA_DATA_TYPE::kAliasInstanceArray:
					// case RE::EXTRA_DATA_TYPE::kPromotedRef:
					// case RE::EXTRA_DATA_TYPE::kOutfitItem:
					// case RE::EXTRA_DATA_TYPE::kFromAlias:
					// case RE::EXTRA_DATA_TYPE::kShouldWear:
					case RE::EXTRA_DATA_TYPE::kTextDisplayData:
					case RE::EXTRA_DATA_TYPE::kEnchantment:
					// case RE::EXTRA_DATA_TYPE::kUniqueID:
					// case RE::EXTRA_DATA_TYPE::kFlags:
					case RE::EXTRA_DATA_TYPE::kInstanceData:
					case RE::EXTRA_DATA_TYPE::kModRank:
						return true;

					default:
						return false;
					}
				}

			public:
				static void Install()
				{
					static REL::Relocation<std::uintptr_t> target{ REL::ID(179412) };
					target.replace_func(0x1C7, UIQualifier);
				}
			};

		public:
			static void Install()
			{
				hkUIQualifier::Install();
			}
		};

		static bool CreateToken(RE::TESObjectREFR* a_refr)
		{
			if (a_refr && a_refr->HasKeyword(RE::TESForm::GetFormByID<RE::BGSKeyword>(0x0003430B)))
			{
				auto token = Forms::PAFrameToken_DO->GetForm<RE::TESObjectARMO>();
				if (!token)
				{
					return false;
				}

				auto name = GetOverrideName(a_refr);
				auto extra = RE::BSTSmartPointer(new RE::ExtraDataList());
				extra->SetOverrideName(name.c_str());
				extra->SetStartingWorldOrCell(a_refr);

				auto PlayerCharacter = RE::PlayerCharacter::GetSingleton();
				if (a_refr->GetHandle() == PlayerCharacter->lastUsedPowerArmor)
				{
					PlayerCharacter->RemoveLastUsedPowerArmor();
				}

				if (auto DPM = RE::BGSDynamicPersistenceManager::GetSingleton())
				{
					DPM->PromoteReference(a_refr, PlayerCharacter);
				}

				RemoveScript(a_refr);

				const RE::PlayerCharacter::ScopedInventoryChangeMessageContext cmctx{ true, true };
				PlayerCharacter->AddObjectToContainer(
					token,
					extra,
					1,
					nullptr,
					RE::ITEM_REMOVE_REASON::kNone);
				PlayerCharacter->PlayPickUpSound(token, true, false);

				a_refr->Disable();
				return true;
			}

			return false;
		}

		static bool HandleToken(RE::TESObjectREFR* a_refr)
		{
			if (RE::PowerArmor::PlayerInPowerArmor())
			{
				const RE::PlayerCharacter::ScopedInventoryChangeMessageContext ctx{ true, true };
				RE::PlayerCharacter::GetSingleton()->PickUpObject(a_refr, 1, false);
				RE::SendHUDMessage::ShowHUDMessage(sPADisallowed->GetString().data(), nullptr, true, true);
				return false;
			}

			auto token = Forms::PAFrameToken_DO->GetForm<RE::TESObjectARMO>();
			if (!token)
			{
				return false;
			}

			if (a_refr && a_refr->data.objectReference && a_refr->data.objectReference == token)
			{
				if (!a_refr->extraList)
				{
					return false;
				}

				if (auto extra = a_refr->extraList->GetByType<RE::ExtraStartingWorldOrCell>())
				{
					if (auto p_refr = extra->startingWorldOrCell->As<RE::TESObjectREFR>())
					{
						SetTokenReference(a_refr);
						SetFrameReference(p_refr);
						a_refr->Disable();

						Start();
						return true;
					}
				}
			}

			return false;
		}

		static bool AttachScript(RE::TESObjectREFR* a_refr)
		{
			if (auto GameVM = RE::GameVM::GetSingleton())
			{
				if (auto IVirtualMachine = GameVM->GetVM())
				{
					auto                                      Handle = IVirtualMachine->GetObjectHandlePolicy().GetHandleForObject(a_refr->formType.underlying(), a_refr);
					RE::BSTSmartPointer<RE::BSScript::Object> Object;
					if (IVirtualMachine->CreateObject("BakaPowerArmorStoragePlacedScript"sv, Object))
					{
						IVirtualMachine->GetObjectBindPolicy().BindObject(Object, Handle);
						IVirtualMachine->DispatchMethodCall(Handle, "BakaPowerArmorStoragePlacedScript"sv, "DoRegister"sv, nullptr);
						return true;
					}
				}
			}

			return false;
		}

		static bool RemoveScript(RE::TESObjectREFR* a_refr)
		{
			if (auto GameVM = RE::GameVM::GetSingleton())
			{
				if (auto IVirtualMachine = GameVM->GetVM())
				{
					auto                                      Handle = IVirtualMachine->GetObjectHandlePolicy().GetHandleForObject(a_refr->formType.underlying(), a_refr);
					RE::BSTSmartPointer<RE::BSScript::Object> Object;
					if (IVirtualMachine->FindBoundObject(Handle, "BakaPowerArmorStoragePlacedScript", true, Object, true))
					{
						IVirtualMachine->GetObjectBindPolicy().UnbindObject(Object);
						return true;
					}
				}
			}

			return false;
		}

		virtual RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent& a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_source) override
		{
			if (a_event.menuName == RE::WorkshopMenu::MENU_NAME)
			{
				if (a_event.opening)
				{
					if (auto menu = RE::UI::GetSingleton()->GetMenu<RE::WorkshopMenu>())
					{
						menu->workshopMenuBase->itemName->SetMember("visible", false);
						menu->workshopMenuBase->selectionBracket->SetMember("visible", false);
						menu->workshopMenuBase->itemCounts->SetMember("visible", false);
						menu->workshopMenuBase->newRecipeIcon->SetMember("visible", false);
						menu->workshopMenuBase->rowBrackets->SetMember("visible", false);
						menu->workshopMenuBase->displayPath->SetMember("visible", false);
						menu->workshopMenuBase->descriptionBase->SetMember("visible", false);
						menu->workshopMenuBase->iconBackground->SetMember("visible", false);

						menu->workshopMenuBase->Invoke("HideRequirements");
						menu->workshopMenuBase->Invoke("HideIconCard");
						menu->workshopMenuBase->Invoke("HidePerkPanels");

						(*RE::Workshop::CurrentRow)++;

						menu->CheckAndSetItemForPlacement();
						menu->UpdateButtonText();

						if (auto& handle = *RE::Workshop::PlacementItem)
						{
							if (m_frameRefr && m_frameRefr->inventoryList)
							{
								handle.get()->CreateInventoryList(nullptr);

								const RE::BSAutoReadLock  lockR{ m_frameRefr->inventoryList->rwLock };
								const RE::BSAutoWriteLock lockW{ handle.get()->inventoryList->rwLock };
								for (auto& iter : m_frameRefr->inventoryList->data)
								{
									handle.get()->inventoryList->data.emplace_back(iter);
								}
							}
						}
					}
				}
				else
				{
					a_source->UnregisterSink(this);
				}
			}

			return RE::BSEventNotifyControl::kContinue;
		}

		virtual RE::BSEventNotifyControl ProcessEvent(const RE::Workshop::ItemPlacedEvent& a_event, RE::BSTEventSource<RE::Workshop::ItemPlacedEvent>*) override
		{
			if (a_event.workshop == m_workshop.get())
			{
				if (a_event.placedItem)
				{
					m_frameRefr->SetLocationOnReference(a_event.placedItem->data.location);
					m_frameRefr->SetAngleOnReference(a_event.placedItem->data.angle);

					if (auto frame3D = m_frameRefr->Get3D())
					{
						m_frameRefr->Update3DPosition(true);
						if (frame3D->flags.flags & 0x4000)
						{
							if (auto node = frame3D->IsFadeNode())
							{
								node->previousMaxA = 1.0f;
								node->currentDecalFade = 1.0f;
								node->currentFade = 1.0f;
								node->flags.flags |= 0x2000000000;
							}
						}
					}

					if (m_frameRefr->parentCell != a_event.placedItem->parentCell)
					{
						m_frameRefr->MoveRefToNewSpace(
							a_event.placedItem->parentCell,
							a_event.placedItem->parentCell->worldSpace);
						m_frameRefr->AddChange(0x400);
					}

					a_event.placedItem->SetDelete(true);
					a_event.placedItem->SetWantsDelete(true);
					a_event.placedItem->Disable();

					m_frameRefr->formFlags |= 0x8000000;
					m_frameRefr->Enable(false);

					if (auto DPM = RE::BGSDynamicPersistenceManager::GetSingleton())
					{
						DPM->DemoteReference(
							m_frameRefr.get(),
							RE::PlayerCharacter::GetSingleton());
					}

					if (MCM::Settings::General::bAutoAutoReturn)
					{
						AttachScript(m_frameRefr.get());
					}
				}

				m_tokenRefr->SetDelete(true);
				m_tokenRefr->SetWantsDelete(true);
				m_tokenRefr->Disable();

				RE::Workshop::RequestExitWorkshop(false);
			}

			return RE::BSEventNotifyControl::kContinue;
		}

		virtual RE::BSEventNotifyControl ProcessEvent(const RE::Workshop::WorkshopModeEvent& a_event, RE::BSTEventSource<RE::Workshop::WorkshopModeEvent>*) override
		{
			if (a_event.start)
			{
				RE::UI::GetSingleton()->RegisterSink<RE::MenuOpenCloseEvent>(this);
				RE::Workshop::RegisterForItemPlaced(this);
			}
			else
			{
				RE::Workshop::UnregisterForItemPlaced(this);
				RE::Workshop::UnregisterForWorkshopModeEvent(this);

				m_workshop.get()->SetDelete(true);
				m_workshop.get()->SetWantsDelete(true);
				m_workshop.get()->Disable();
				m_workshop.reset();

				if (m_tokenRefr && !m_tokenRefr->GetDelete())
				{
					const RE::PlayerCharacter::ScopedInventoryChangeMessageContext ctx{ true, true };
					RE::PlayerCharacter::GetSingleton()->AddObjectToContainer(
						m_tokenRefr->data.objectReference,
						m_tokenRefr->extraList,
						1,
						nullptr,
						RE::ITEM_REMOVE_REASON::kNone);

					m_tokenRefr->SetDelete(true);
					m_tokenRefr->SetWantsDelete(true);
					m_tokenRefr->Disable();
				}

				m_tokenRefr.reset();
				m_frameRefr.reset();
				m_isActive = false;
			}

			return RE::BSEventNotifyControl::kContinue;
		}

	public:
		static void Install()
		{
			Hooks::Install();
		}

		static void AddPerkToPlayer()
		{
			if (auto Player = RE::TESForm::GetFormByID(0x00000007)->As<RE::TESNPC>())
			{
				if (auto PowerArmorPerk = Forms::PAFramePerk_DO->GetForm<RE::BGSPerk>())
				{
					Player->AddPerk(PowerArmorPerk, 1);
				}
			}
		}

	private:
		inline static REL::Relocation<RE::SettingT<RE::GameSettingCollection>*> sPADisallowed{ REL::ID(1053596) };

	protected:
		[[nodiscard]] static RE::ObjectRefHandle CreateWorkbench(RE::TESBoundObject* a_workbench)
		{
			if (auto PlayerCharacter = RE::PlayerCharacter::GetSingleton())
			{
				auto data = RE::NEW_REFR_DATA();
				data.location = PlayerCharacter->data.location;
				data.direction = PlayerCharacter->data.angle;
				data.interior = PlayerCharacter->parentCell;
				data.world = data.interior ? data.interior->worldSpace : nullptr;
				data.object = a_workbench;

				if (auto TESDataHandler = RE::TESDataHandler::GetSingleton())
				{
					return TESDataHandler->CreateReferenceAtLocation(data);
				}
			}

			return RE::ObjectRefHandle();
		}

		static void Start()
		{
			if (auto workbench = Forms::PAFrameWorkshop_DO->GetForm<RE::TESObjectCONT>())
			{
				auto singleton = GetSingleton();
				if (singleton->m_workshop = CreateWorkbench(workbench))
				{
					if (auto UI = RE::UI::GetSingleton())
					{
						if (UI->GetMenuOpen<RE::PipboyMenu>())
						{
							RE::UIMessageQueue::GetSingleton()->AddMessage("PipboyMenu"sv, RE::UI_MESSAGE_TYPE::kHide);
						}

						if (UI->GetMenuOpen<RE::ContainerMenu>())
						{
							RE::UIMessageQueue::GetSingleton()->AddMessage("ContainerMenu"sv, RE::UI_MESSAGE_TYPE::kHide);
						}
					}

					singleton->m_isActive = true;
					RE::Workshop::RegisterForWorkshopModeEvent(singleton);
					RE::Workshop::StartWorkshop(singleton->m_workshop.get().get());
				}
			}
		}

		static void SetFrameReference(RE::TESObjectREFR* a_refr)
		{
			GetSingleton()->m_frameRefr.reset(a_refr);
		}

		static void SetTokenReference(RE::TESObjectREFR* a_refr)
		{
			GetSingleton()->m_tokenRefr.reset(a_refr);
		}

		static bool IsActive()
		{
			return GetSingleton()->m_isActive;
		}

		static RE::BSFixedString GetOverrideName(RE::TESObjectREFR* a_refr)
		{
			std::string  name;
			std::int32_t count{ 0 };
			if (a_refr->inventoryList)
			{
				const RE::BSAutoReadLock lock{ a_refr->inventoryList->rwLock };
				for (auto& iter : a_refr->inventoryList->data)
				{
					if (!iter.object)
					{
						continue;
					}

					switch (iter.object->formType.get())
					{
					case RE::ENUM_FORM_ID::kARMO:
						count++;
						if (iter.object)
						{
							if (auto armo = iter.object->As<RE::TESObjectARMO>())
							{
								if (armo->attachParents.HasKeyword(Forms::ap_PowerArmor_BodyMod))
								{
									name = Forms::PANameScheme::Get(armo);
								}
							}
						}
						break;

					default:
						break;
					}
				}
			}

			std::stringstream stream;
			stream << MCM::Settings::Formatting::sPAChassis;

			if (!name.empty())
			{
				stream << " ["sv << name << "]"sv;
			}

			if (count > 0)
			{
				stream << " ["sv << count << "pc]"sv;
			}

			return stream.str();
		}

		RE::ObjectRefHandle                                                         m_workshop;
		RE::BSTSmartPointer<RE::TESObjectREFR, RE::BSTSmartPointerGamebryoRefCount> m_frameRefr;
		RE::BSTSmartPointer<RE::TESObjectREFR, RE::BSTSmartPointerGamebryoRefCount> m_tokenRefr;
		bool                                                                        m_isActive{ false };
		bool                                                                        m_hasSound{ false };
	};
}
