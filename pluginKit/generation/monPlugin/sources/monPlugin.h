#pragma once
#include <shared/plugin/IPlugin.h>
#include "Configuration.h"

// Shortcut to yPluginApi namespace
namespace yApi = shared::plugin::yPluginApi;

//--------------------------------------------------------------
/// \brief	This class is the MailSender plugin
/// \note   This plugin send a mail when receive a notification
//--------------------------------------------------------------
class CMonPlugin : public shared::plugin::IPlugin
{
public:
   //--------------------------------------------------------------
   /// \brief	Constructor
   //--------------------------------------------------------------
   CMonPlugin();

   //--------------------------------------------------------------
   /// \brief	Destructor
   //--------------------------------------------------------------
   virtual ~CMonPlugin();

   // IPlugin implementation
   virtual void doWork(boost::shared_ptr<yApi::IYPluginApi> context);
   // [END] IPlugin implementation

   //--------------------------------------------------------------
   /// \brief Declare the device and all keywords associated
   /// \param[in] context               pointer to the API
   //--------------------------------------------------------------
   void declareDevice(boost::shared_ptr<yApi::IYPluginApi> context);

   //--------------------------------------------------------------
   /// \brief Update the configuration of the plugin after a change
   /// \param[in] context               pointer to the API
   /// \param[in] newConfigurationData  The new configuration of the module
   //--------------------------------------------------------------
   void onUpdateConfiguration(boost::shared_ptr<yApi::IYPluginApi> context, const shared::CDataContainer& newConfigurationData);

private:
   //--------------------------------------------------------------
   /// \brief The device name
   //--------------------------------------------------------------
   std::string m_deviceName;

   //--------------------------------------------------------------
   /// \brief	The plugin configuration
   //--------------------------------------------------------------
   boost::shared_ptr<CConfiguration> m_configuration;

   //--------------------------------------------------------------
   /// \brief	    Message historization object
   //--------------------------------------------------------------
   yApi::historization::CTemperature m_temperatureKeyword;

   boost::shared_ptr<shared::event::CEventTimer> m_timer;
};
