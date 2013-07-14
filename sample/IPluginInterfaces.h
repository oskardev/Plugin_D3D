/* pluginInterfaces - for licensing and copyright see license.txt */

#include <IPluginBase.h>

#pragma once

/**
 * @brief pluginInterfaces Namespace
 */
namespace pluginInterfaces
{
    /**
     * @brief plugin test concrete interface
     */
    struct IPluginInterfaces
    {
        /**
         * @brief Get Plugin base interface
         */
        virtual PluginManager::IPluginBase* GetBase() = 0;

        /**
         * @brief Update func called by game
         */
        virtual void Update() = 0;
    };
};