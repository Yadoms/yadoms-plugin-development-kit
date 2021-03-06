#pragma once
#include <shared/Export.h>
#include "SingleHistorizableData.hpp"
#include "typeInfo/DoubleTypeInfo.h"

namespace shared { namespace plugin { namespace yPluginApi { namespace historization
{   
   //-----------------------------------------------------
   ///\brief A speed historizable object
   //-----------------------------------------------------
   class YADOMS_SHARED_EXPORT CSpeed : public CSingleHistorizableData<double>
   {
   public:
      //-----------------------------------------------------
      ///\brief                     Constructor
      ///\param[in] keywordName     Yadoms keyword name
      ///\param[in] accessMode      The access mode
      ///\param[in] measureType     The measure type (normally kAbsolute)
      //-----------------------------------------------------
      CSpeed(const std::string& keywordName, const EKeywordAccessMode& accessMode = EKeywordAccessMode::kGet, const EMeasureType& measureType = EMeasureType::kAbsolute, typeInfo::CDoubleTypeInfo & additionalInfo = typeInfo::CDoubleTypeInfo::Empty);

      //-----------------------------------------------------
      ///\brief                     Destructor
      //-----------------------------------------------------
      virtual ~CSpeed();
   };



} } } } // namespace shared::plugin::yPluginApi::historization

