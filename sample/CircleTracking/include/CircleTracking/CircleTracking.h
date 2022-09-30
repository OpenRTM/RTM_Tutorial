// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  CircleTracking.h
 * @brief Get Circles Position Component
 *
 * LGPL
 *
 */
// </rtc-template>

#ifndef CIRCLETRACKING_H
#define CIRCLETRACKING_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "InterfaceDataTypesStub.h"
#include "ExtendedDataTypesStub.h"

// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <opencv2/opencv.hpp>

// <rtc-template block="component_description">
/*!
 * @class CircleTracking
 * @brief Get Circles Position Component
 *
 * OpenCVのHoughCircles関数により円の座標を検出して、移動ロボットを
 * 追従するRTC
 *
 */
// </rtc-template>
class CircleTracking
    : public RTC::DataFlowComponentBase
{
public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  CircleTracking(RTC::Manager *manager);

  /*!
   * @brief destructor
   */
  ~CircleTracking() override;

  // <rtc-template block="public_attribute">

  // </rtc-template>

  // <rtc-template block="public_operation">

  // </rtc-template>

  // <rtc-template block="activity">
  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  RTC::ReturnCode_t onInitialize() override;

  /***
   *
   * The finalize action (on ALIVE->END transition)
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onFinalize() override;

  /***
   *
   * The startup action when ExecutionContext startup
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id) override;

  /***
   *
   * The shutdown action when ExecutionContext stop
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id) override;

  /***
   *
   * The activated action (Active state entry action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id) override;

  /***
   *
   * The deactivated action (Active state exit action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id) override;

  /***
   *
   * The execution action that is invoked periodically
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id) override;

  /***
   *
   * The aborting action when main logic error occurred.
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id) override;

  /***
   *
   * The error action in ERROR state
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onError(RTC::UniqueId ec_id) override;

  /***
   *
   * The reset action that is invoked resetting
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onReset(RTC::UniqueId ec_id) override;

  /***
   *
   * The state update action that is invoked after onExecute() action
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id) override;

  /***
   *
   * The action that is invoked when execution context's rate is changed
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id) override;
  // </rtc-template>

protected:
  // <rtc-template block="protected_attribute">

  // </rtc-template>

  // <rtc-template block="protected_operation">

  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   *
   * - Name:  speed_r
   * - DefaultValue: 1.0
   */
  double m_speed_r;
  /*!
   *
   * - Name:  houghcircles_dp
   * - DefaultValue: 2
   */
  double m_houghcircles_dp;
  /*!
   *
   * - Name:  houghcircles_minDist
   * - DefaultValue: 30
   */
  double m_houghcircles_minDist;
  /*!
   *
   * - Name:  houghcircles_param1
   * - DefaultValue: 100
   */
  double m_houghcircles_param1;
  /*!
   *
   * - Name:  houghcircles_param2
   * - DefaultValue: 100
   */
  double m_houghcircles_param2;
  /*!
   *
   * - Name:  houghcircles_minRadius
   * - DefaultValue: 0
   */
  int m_houghcircles_minRadius;
  /*!
   *
   * - Name:  houghcircles_maxRadius
   * - DefaultValue: 0
   */
  int m_houghcircles_maxRadius;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::CameraImage m_image_in;
  /*!
   */
  RTC::InPort<RTC::CameraImage> m_image_inIn;
  RTC::TimedVelocity2D m_velocity_in;
  /*!
   */
  RTC::InPort<RTC::TimedVelocity2D> m_velocity_inIn;

  // </rtc-template>

  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::CameraImage m_image_out;
  /*!
   */
  RTC::OutPort<RTC::CameraImage> m_image_outOut;
  RTC::TimedVelocity2D m_velocity_out;
  /*!
   */
  RTC::OutPort<RTC::TimedVelocity2D> m_velocity_outOut;

  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">

  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">

  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">

  // </rtc-template>

private:
  cv::Mat m_imageBuff;
  cv::Mat m_outputBuff;
  int m_direction;
  // <rtc-template block="private_attribute">

  // </rtc-template>

  // <rtc-template block="private_operation">

  // </rtc-template>
};

extern "C"
{
  DLL_EXPORT void CircleTrackingInit(RTC::Manager *manager);
};

#endif // CIRCLETRACKING_H
