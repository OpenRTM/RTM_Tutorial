﻿// -*- C++ -*-
/*!
 * @file  testARToolKit.cpp
 * @brief test ARToolKitPlus
 * @date $Date$
 *
 * @author 宮本　信彦　n-miyamoto@aist.go.jp
 * 産業技術総合研究所　ロボットイノベーション研究センター
 * ロボットソフトウエアプラットフォーム研究チーム
 *
 * $Id$
 */

#include "testARToolKit.h"

// Module specification
// <rtc-template block="module_spec">
static const char* testartoolkit_spec[] =
  {
    "implementation_id", "testARToolKit",
    "type_name",         "testARToolKit",
    "description",       "test ARToolKitPlus",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "Sample",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.x_distance", "0.5",
    "conf.default.y_distance", "0",
    "conf.default.x_speed", "0.1",
    "conf.default.r_speed", "0.2",
    "conf.default.error_range_x", "0.1",
    "conf.default.error_range_y", "0.05",

    // Widget
    "conf.__widget__.x_distance", "text",
    "conf.__widget__.y_distance", "text",
    "conf.__widget__.x_speed", "text",
    "conf.__widget__.r_speed", "text",
    "conf.__widget__.error_range_x", "text",
    "conf.__widget__.error_range_y", "text",
    // Constraints

    "conf.__type__.x_distance", "double",
    "conf.__type__.y_distance", "double",
    "conf.__type__.x_speed", "double",
    "conf.__type__.r_speed", "double",
    "conf.__type__.error_range_x", "double",
    "conf.__type__.error_range_y", "double",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
testARToolKit::testARToolKit(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_marker_posIn("marker_pos", m_marker_pos),
    m_target_velOut("target_vel", m_target_vel)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
testARToolKit::~testARToolKit()
{
}



RTC::ReturnCode_t testARToolKit::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("marker_pos", m_marker_posIn);
  
  // Set OutPort buffer
  addOutPort("target_vel", m_target_velOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("x_distance", m_x_distance, "0.5");
  bindParameter("y_distance", m_y_distance, "0");
  bindParameter("x_speed", m_x_speed, "0.1");
  bindParameter("r_speed", m_r_speed, "0.2");
  bindParameter("error_range_x", m_error_range_x, "0.1");
  bindParameter("error_range_y", m_error_range_y, "0.05");
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testARToolKit::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testARToolKit::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testARToolKit::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testARToolKit::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testARToolKit::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testARToolKit::onExecute(RTC::UniqueId ec_id)
{
	//新規データの確認
	if (m_marker_posIn.isNew())
	{
		m_target_vel.data.vx = 0;
		m_target_vel.data.vy = 0;
		m_target_vel.data.va = 0;

		//データの読み込み
		m_marker_posIn.read();
		//マーカーの位置(X軸)が目標距離(X軸)よりも大きい場合
		if (m_marker_pos.data.position.x > m_x_distance + m_error_range_x/2.0)
		{
			m_target_vel.data.vx = m_x_speed;
		}
		//マーカーの位置(X軸)が目標距離(X軸)よりも小さい場合
		else if (m_marker_pos.data.position.x < m_x_distance - m_error_range_x/2.0)
		{
			m_target_vel.data.vx = -m_x_speed;
		}
		//マーカーの位置(Y軸)が目標距離(Y軸)よりも大きい場合
		else if (m_marker_pos.data.position.y > m_y_distance + m_error_range_y/2.0)
		{
			m_target_vel.data.va = m_r_speed;
		}
		//マーカーの位置(Y軸)が目標距離(Y軸)よりも小さい場合
		else if (m_marker_pos.data.position.y < m_y_distance - m_error_range_y/2.0)
		{
			m_target_vel.data.va = -m_r_speed;
		}
		setTimestamp(m_target_vel);
		//データ書き込み
		m_target_velOut.write();
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testARToolKit::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testARToolKit::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testARToolKit::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testARToolKit::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testARToolKit::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void testARToolKitInit(RTC::Manager* manager)
  {
    coil::Properties profile(testartoolkit_spec);
    manager->registerFactory(profile,
                             RTC::Create<testARToolKit>,
                             RTC::Delete<testARToolKit>);
  }
  
};


