#include "stdafx.h"
#include "monPlugin.h"
#include <shared/Log.h>
#include <shared/plugin/yPluginApi/historization/Message.h>
#include <shared/plugin/ImplementationHelper.h>
#include <shared/exception/EmptyResult.hpp>
#include "Configuration.h"
#include <Poco/DateTime.h>

// Use this macro to define all necessary to make your DLL a Yadoms valid plugin.
// Note that you have to provide some extra files, like package.json, and icon.png
// This macro also defines the static PluginInformations value that can be used by plugin to get information values

IMPLEMENT_PLUGIN(CMonPlugin)

CMonPlugin::CMonPlugin()
   : m_deviceName("MonPlugin"), m_configuration(new CConfiguration()),
   m_temperatureKeyword("temperature", yApi::EKeywordAccessMode::kGetSet)
{
}

CMonPlugin::~CMonPlugin()
{}

// Event IDs
enum
{
   kSendSensorsStateTimerEventId = yApi::IYPluginApi::kPluginFirstEventId,   // Always start from yApi::IYPluginApi::kPluginFirstEventId
};

void CMonPlugin::doWork(boost::shared_ptr<yApi::IYPluginApi> context)
{
   try
   {
      YADOMS_LOG(information) << "CMonPlugin is starting...";


      m_configuration->initializeWith(context->getConfiguration());
      // Declaration of the device and Associated keywords
      declareDevice(context);

      // Timer used to send fake sensor states periodically
      boost::shared_ptr<shared::event::CEventTimer> timer = context->getEventHandler().createTimer(kSendSensorsStateTimerEventId, shared::event::CEventTimer::kPeriodic, boost::posix_time::seconds(m_configuration->getIntConfParam()));
      


      // the main loop
      YADOMS_LOG(information) << "CMonPlugin plugin is running...";

      
      context->setPluginState(yApi::historization::EPluginState::kRunning);

      while (1)
      {
         // Wait for an event
         switch (context->getEventHandler().waitForEvents())
         {
            case yApi::IYPluginApi::kEventUpdateConfiguration:
            {
               onUpdateConfiguration(context, context->getEventHandler().getEventData<shared::CDataContainer>());
               break;
            }

            case yApi::IYPluginApi::kEventDeviceCommand:
            {
               // Command received
               boost::shared_ptr<const yApi::IDeviceCommand> command = context->getEventHandler().getEventData<boost::shared_ptr<const yApi::IDeviceCommand> >();
               YADOMS_LOG(debug) << "Command received :" << command->toString();

               //do anything with commad values
            }
            break;

            case kSendSensorsStateTimerEventId:
            {
               // Timer used here to send sensors state to Yadoms periodically

               // Read sensor value and send data to Yadoms (temperatures, battery level, Rssi measure...)
               int second = Poco::DateTime().second(); //for example read data from device, (here get the current second in the now datetime)
               m_temperatureKeyword.set(second);


               YADOMS_LOG(debug) << "Send the periodically sensors state...";
               context->historizeData(m_deviceName, m_temperatureKeyword);
               break;
            }

            default:
            {
               YADOMS_LOG(error) << "Unknown message id";
               break;
            }
         }
      }
   }
   // Plugin must catch this end-of-thread exception to make its cleanup.
   // If no cleanup is necessary, still catch it, or Yadoms will consider
   // as a plugin failure.
   catch (boost::thread_interrupted&)
   {
      YADOMS_LOG(information) << "CMonPlugin is stopping..." << std::endl;
   }
}

void CMonPlugin::declareDevice(boost::shared_ptr<yApi::IYPluginApi> context)
{
   if (context->deviceExists(m_deviceName))
      return;

   // Declare the device
   context->declareDevice(m_deviceName, m_deviceName);

   // Declare associated keywords (= values managed by this device)
   context->declareKeyword(m_deviceName, m_temperatureKeyword);
}

void CMonPlugin::onUpdateConfiguration(boost::shared_ptr<yApi::IYPluginApi> context, const shared::CDataContainer& newConfigurationData)
{
   // Configuration was updated
   YADOMS_LOG(debug) << "Configuration was updated...";
   BOOST_ASSERT(!newConfigurationData.empty());  // newConfigurationData shouldn't be empty, or kEventUpdateConfiguration shouldn't be generated

   // Update configuration
   m_configuration->initializeWith(newConfigurationData);

   //update timer
   m_timer->stop();
   m_timer->start(boost::posix_time::seconds(m_configuration->getIntConfParam()));

}

