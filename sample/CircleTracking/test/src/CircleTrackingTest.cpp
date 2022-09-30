// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  CircleTrackingTest.cpp
 * @brief Get Circles Position Component (test code)
 *
 * LGPL
 *
 */
// </rtc-template>

#include "CircleTrackingTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const circletracking_spec[] =
#else
static const char* circletracking_spec[] =
#endif
  {
    "implementation_id", "CircleTrackingTest",
    "type_name",         "CircleTrackingTest",
    "description",       "Get Circles Position Component",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "ImageProcessiong",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.speed_r", "0.5",
    "conf.default.houghcircles_dp", "2",
    "conf.default.houghcircles_minDist", "30",
    "conf.default.houghcircles_param1", "100",
    "conf.default.houghcircles_param2", "100",
    "conf.default.houghcircles_minRadius", "0",
    "conf.default.houghcircles_maxRadius", "0",

    // Widget
    "conf.__widget__.speed_r", "text",
    "conf.__widget__.houghcircles_dp", "text",
    "conf.__widget__.houghcircles_minDist", "text",
    "conf.__widget__.houghcircles_param1", "text",
    "conf.__widget__.houghcircles_param2", "text",
    "conf.__widget__.houghcircles_minRadius", "text",
    "conf.__widget__.houghcircles_maxRadius", "text",
    // Constraints
    "conf.__constraints__.speed_r", "0.0<x<2.0",

    "conf.__type__.speed_r", "double",
    "conf.__type__.houghcircles_dp", "double",
    "conf.__type__.houghcircles_minDist", "double",
    "conf.__type__.houghcircles_param1", "double",
    "conf.__type__.houghcircles_param2", "double",
    "conf.__type__.houghcircles_minRadius", "int",
    "conf.__type__.houghcircles_maxRadius", "int",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
CircleTrackingTest::CircleTrackingTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_image_inOut("image_in", m_image_in),
    m_velocity_inOut("velocity_in", m_velocity_in),
    m_velocity_outIn("velocity_out", m_velocity_out),
    m_image_outIn("image_out", m_image_out)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
CircleTrackingTest::~CircleTrackingTest()
{
}



RTC::ReturnCode_t CircleTrackingTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("velocity_out", m_velocity_outIn);
  addInPort("image_out", m_image_outIn);
  
  // Set OutPort buffer
  addOutPort("image_in", m_image_inOut);
  addOutPort("velocity_in", m_velocity_inOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("speed_r", m_speed_r, "0.5");
  bindParameter("houghcircles_dp", m_houghcircles_dp, "2");
  bindParameter("houghcircles_minDist", m_houghcircles_minDist, "30");
  bindParameter("houghcircles_param1", m_houghcircles_param1, "100");
  bindParameter("houghcircles_param2", m_houghcircles_param2, "100");
  bindParameter("houghcircles_minRadius", m_houghcircles_minRadius, "0");
  bindParameter("houghcircles_maxRadius", m_houghcircles_maxRadius, "0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CircleTrackingTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t CircleTrackingTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t CircleTrackingTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t CircleTrackingTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CircleTrackingTest::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CircleTrackingTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t CircleTrackingTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t CircleTrackingTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t CircleTrackingTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t CircleTrackingTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t CircleTrackingTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool CircleTrackingTest::runTest()
{
    return true;
}


extern "C"
{
 
  void CircleTrackingTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(circletracking_spec);
    manager->registerFactory(profile,
                             RTC::Create<CircleTrackingTest>,
                             RTC::Delete<CircleTrackingTest>);
  }
  
}
