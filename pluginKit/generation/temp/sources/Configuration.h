#pragma once

#include <shared/DataContainer.h>

//--------------------------------------------------------------
/// \brief	Configuration of the plugin
//--------------------------------------------------------------
class CConfiguration 
{
public:

   //--------------------------------------------------------------
   /// \brief	    Constructor
   //--------------------------------------------------------------
   CConfiguration();

   //--------------------------------------------------------------
   /// \brief	    Destructor
   //--------------------------------------------------------------
   virtual ~CConfiguration();

   virtual void initializeWith(const shared::CDataContainer &data);
   virtual std::string getStringConfParam() const;
   virtual int getIntConfParam() const;

private:
   //--------------------------------------------------------------
   /// \brief	    string parameter
   //--------------------------------------------------------------
   std::string m_stringParam;

   //--------------------------------------------------------------
   /// \brief	    int parameter
   //--------------------------------------------------------------
   int m_intParam;
};
