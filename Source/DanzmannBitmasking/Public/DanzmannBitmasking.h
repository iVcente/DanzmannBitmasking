// Copyright (C) 2025 Vicente Danzmann. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FDanzmannBitmaskingModule : public IModuleInterface
{
	public:
		/**
		 * @see more info in IModuleInterface. 
		 */
		virtual void StartupModule() override;

		/**
		 * @see more info in IModuleInterface. 
		 */
		virtual void ShutdownModule() override;
};
