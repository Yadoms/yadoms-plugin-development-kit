#include "stdafx.h"
#include "Configuration.h"
#include <shared/StringExtension.h>
#include <shared/Log.h>
#include <shared/encryption/Xor.h>

CConfiguration::CConfiguration()
   : m_stringParam(""), m_intParam(0)
{}

CConfiguration::~CConfiguration()
{}

void CConfiguration::initializeWith(const shared::CDataContainer &data)
{
   try
   {
      m_stringParam = data.get<std::string>("myStringParamIdentifier");
      m_intParam = data.get<int>("myIntParamIdentifier");
   }
   catch (boost::thread_interrupted&)
   {
      YADOMS_LOG(error) << "ERROR : Plugin Mail Sender could not be loaded" << std::endl;
   }
}

std::string CConfiguration::getStringConfParam() const
{
   return m_stringParam;
}

int CConfiguration::getIntConfParam() const
{
   return m_intParam;
}


