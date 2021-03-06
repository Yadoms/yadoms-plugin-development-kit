#pragma once
#include <shared/event/EventHandler.hpp>
#include <shared/plugin/information/IInformation.h>
#include <shared/StringExtension.h>
#include <shared/DataContainer.h>
#include "IDeviceCommand.h"
#include "IManuallyDeviceCreationData.h"
#include "IManuallyDeviceCreationTestData.h"
#include <shared/plugin/yPluginApi/StandardCapacity.h>
#include <shared/plugin/yPluginApi/KeywordAccessMode.h>
#include <shared/plugin/yPluginApi/KeywordDataType.h>
#include "historization/Historizers.h"


namespace shared { namespace plugin { namespace yPluginApi
{
   //-----------------------------------------------------
   ///\brief The API used by the plugins to interact with Yadoms
   //-----------------------------------------------------
   class IYPluginApi
   {
   public:
      //-----------------------------------------------------
      ///\brief Destructor
      //-----------------------------------------------------
      virtual ~IYPluginApi() {}

      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //--
      //-- Events
      //--
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------

      //-----------------------------------------------------
      ///\brief Events Id from Yadoms received by the plugin
      //-----------------------------------------------------
      enum
      {
         kEventUpdateConfiguration = event::kUserFirstId,         // Yadoms notify the plugin that its configuration was changed
         kEventDeviceCommand,                                     // Yadoms send a command to a device managed by this plugin
         kEventManuallyDeviceCreationTest,                        // Yadoms ask the plugin to test a device with provided parameters, before to create it
         kEventManuallyDeviceCreation,                            // Yadoms ask the plugin to create a device
         kBindingQuery,															// Yadoms ask the plugin a binding query
         kPluginFirstEventId                                      // The next usable event ID for the plugin code
      };

      //-----------------------------------------------------
      ///\brief Get the event handler associated to the plugin. The event handler is used
      ///       to received, wait for, or post events from/to Yadoms
      ///\return The plugin event handler
      //-----------------------------------------------------   
      virtual event::CEventHandler & getEventHandler() = 0;


      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //--
      //-- Plugin state
      //--
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------

      //-----------------------------------------------------
      ///\brief Set the current plugin state
      ///\param    [in]    state           The new state
      ///\param    [in]    customMessageId The associated message ID (translatable in the locales file of the plugin). Ignored if state != kCustom or kError.
      //-----------------------------------------------------
      virtual void setPluginState(const historization::EPluginState& state, const std::string & customMessageId = std::string()) = 0;


      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //--
      //-- Devices
      //--
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------

      //-----------------------------------------------------
      ///\brief Check if a device already exists for the server
      ///\param    [in]    device            The device name
      ///\return true if the device exists, false if not
      //-----------------------------------------------------
      virtual bool deviceExists(const std::string& device) const = 0;

      //-----------------------------------------------------
      ///\brief Get the details of a device
      ///\param    [in]    device            The device name
      ///\return the device details
      ///\throw shared::exception::CEmptyResult if device dosen't exist
      //-----------------------------------------------------
      virtual CDataContainer getDeviceDetails(const std::string& device) const = 0;

      //-----------------------------------------------------
      ///\brief Declare new device to Yadoms
      ///\param    [in]    device            The device name
      ///\param    [in]    model              The device model or description (ex : "Oregon Scientific CN185")
      ///\param    [in]    details           Device details
      ///\throw shared::exception::CEmptyResult if device already exist
      //-----------------------------------------------------
      virtual void declareDevice(const std::string& device, const std::string& model, const CDataContainer& details = CDataContainer::EmptyContainer) = 0;



      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////--
      ////-- Keywords
      ////--
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------


      //-----------------------------------------------------
      ///\brief Check if a keyword already exists for the device
      ///\param    [in]    device             The device name owner of the keyword
      ///\param    [in]    keyword            The keyword name
      ///\return true if the keyword exists, false if not
      //-----------------------------------------------------
      virtual bool keywordExists(const std::string& device, const std::string& keyword) const = 0;

      //-----------------------------------------------------
      ///\brief Check if a keyword already exists for the device
      ///\param    [in]    device             The device name owner of the keyword
      ///\param    [in]    keyword            The keyword name
      ///\return true if the keyword exists, false if not
      //-----------------------------------------------------
      virtual bool keywordExists(const std::string& device, const historization::IHistorizable& keyword) const = 0;

      //-----------------------------------------------------
      ///\brief Declare a standard keyword
      ///\param    [in]    device             The device name owner of the keyword
      ///\param    [in]    keyword            The keyword
      ///\param    [in]    details            The keyword details (JSON string, optional. Can be used to declare specific properties like min/max values)
      ///\throw shared::exception::CEmptyResult if keyword already exist
      //-----------------------------------------------------   
      virtual void declareKeyword(const std::string& device, const historization::IHistorizable& keyword, const CDataContainer& details = CDataContainer::EmptyContainer) = 0;



      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////--
      ////-- Recipient
      ////--
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------
      ////----------------------------------------------------------------------------------------------------------------


      //-----------------------------------------------------
      ///\brief Get a field value for a recipient ID
      ///\param    [in]    recipientId       The recipient ID containing the field
      ///\param    [in]    fieldName         The expected field ("phone", "email", etc...)
      ///\return                             The field value for specified recipient ID
      ///\throw shared::exception::CEmptyResult if recipient ID not found or field not found in recipient
      //-----------------------------------------------------
      virtual std::string getRecipientValue(int recipientId, const std::string& fieldName) const = 0;

      //-----------------------------------------------------
      ///\brief Find recipients from a specific field value
      ///\param    [in]    fieldName         The field name ("phone", "email", etc...) where searching
      ///\param    [in]    expectedFieldValue The expected field value
      ///\return                             A list containing found recipient IDs, where this expectedFieldValue was found for fieldName
      //-----------------------------------------------------
      virtual std::vector<int> findRecipientsFromField(const std::string& fieldName, const std::string& expectedFieldValue) const = 0;

      //--------------------------------------------------------------
      /// \brief                    Check if a field exists
      /// \param [in] fieldName     The field name
      /// \return                   true if field exists
      //--------------------------------------------------------------
      virtual bool recipientFieldExists(const std::string& fieldName) const = 0;



      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //--
      //-- Data recording
      //--
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------

      //-----------------------------------------------------
      ///\brief Historize a new data
      ///\param    [in]    device            The device name
      ///\param    [in]    data              The historizable data
      ///\note If you need to historize several keyword at a time, prefer the historizeData method with vector, for better performances
      //-----------------------------------------------------     
      virtual void historizeData(const std::string& device, const historization::IHistorizable& data) = 0;

      //-----------------------------------------------------
      ///\brief Historize a list of new data
      ///\param    [in]    device            The device name
      ///\param    [in]    datalist          The list of historizable data
      //-----------------------------------------------------    
      virtual void historizeData(const std::string& device, const std::vector<boost::shared_ptr<historization::IHistorizable> > & dataVect) = 0;

      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //--
      //-- Plugin information
      //--
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------

      //-----------------------------------------------------
      ///\brief Get the current plugin information (extracted from package.json file)
      ///\return The current plugin information
      //-----------------------------------------------------      
      virtual const information::IInformation& getInformation() const = 0;

      //-----------------------------------------------------
      ///\brief Get the plugin binary path
      ///\return the plugin binary path
      //-----------------------------------------------------      
      virtual const boost::filesystem::path getPluginPath() const = 0;


      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //--
      //-- Plugin configuration
      //--
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------
      //----------------------------------------------------------------------------------------------------------------

      //-----------------------------------------------------
      ///\brief Get the current plugin configuration
      ///\return The current plugin configuration
      //-----------------------------------------------------      
      virtual CDataContainer getConfiguration() const = 0;
   };

} } } // namespace shared::plugin::yPluginApi	

