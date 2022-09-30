// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  CircleTracking.cpp
 * @brief Get Circles Position Component
 *
 * LGPL
 *
 */
// </rtc-template>

#include "CircleTracking.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char *const circletracking_spec[] =
#else
static const char *circletracking_spec[] =
#endif
    {
        "implementation_id", "CircleTracking",
        "type_name", "CircleTracking",
        "description", "Get Circles Position Component",
        "version", "1.0.0",
        "vendor", "AIST",
        "category", "ImageProcessiong",
        "activity_type", "PERIODIC",
        "kind", "DataFlowComponent",
        "max_instance", "1",
        "language", "C++",
        "lang_type", "compile",
        // Configuration variables
        "conf.default.speed_r", "0.5",
        "conf.default.houghcircles_dp", "2",
        "conf.default.houghcircles_minDist", "30",
        "conf.default.houghcircles_param1", "100",
        "conf.default.houghcircles_param2", "100",
        "conf.default.houghcircles_minRadius", "0",
        "conf.default.houghcircles_maxRadius", "0",

        // Widget
        "conf.__widget__.speed_r", "slider.0.01",
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

        ""};
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
CircleTracking::CircleTracking(RTC::Manager *manager)
    // <rtc-template block="initializer">
    : RTC::DataFlowComponentBase(manager),
      m_image_inIn("image_in", m_image_in),
      m_velocity_inIn("velocity_in", m_velocity_in),
      m_image_outOut("image_out", m_image_out),
      m_velocity_outOut("velocity_out", m_velocity_out)
// </rtc-template>
{
}

/*!
 * @brief destructor
 */
CircleTracking::~CircleTracking()
{
}

RTC::ReturnCode_t CircleTracking::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("image_in", m_image_inIn);
  addInPort("velocity_in", m_velocity_inIn);

  // Set OutPort buffer
  addOutPort("image_out", m_image_outOut);
  addOutPort("velocity_out", m_velocity_outOut);

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
RTC::ReturnCode_t CircleTracking::onFinalize()
{
  return RTC::RTC_OK;
}
*/

// RTC::ReturnCode_t CircleTracking::onStartup(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t CircleTracking::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

RTC::ReturnCode_t CircleTracking::onActivated(RTC::UniqueId /*ec_id*/)
{
  // OutPortの画面サイズを0に設定
  m_image_out.width = 0;
  m_image_out.height = 0;

  //進行方向を0(回転方向を指定しない)に設定
  m_direction = 0;
  return RTC::RTC_OK;
}

RTC::ReturnCode_t CircleTracking::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  if (!m_outputBuff.empty())
  {
    // 画像用メモリの解放
    m_imageBuff.release();
    m_outputBuff.release();
  }

  return RTC::RTC_OK;
}

RTC::ReturnCode_t CircleTracking::onExecute(RTC::UniqueId /*ec_id*/)
{
  if (m_image_inIn.isNew())
  {
    cv::Mat gray;
    std::vector<cv::Vec3f> circles;
    // 画像データの読み込み
    m_image_inIn.read();

    // InPortとOutPortの画面サイズ処理およびイメージ用メモリの確保
    if (m_image_in.width != m_image_out.width || m_image_in.height != m_image_out.height)
    {
      m_image_out.width = m_image_in.width;
      m_image_out.height = m_image_in.height;

      m_imageBuff.create(cv::Size(m_image_in.width, m_image_in.height), CV_8UC3);
      m_outputBuff.create(cv::Size(m_image_in.width, m_image_in.height), CV_8UC3);
    }

    // InPortの画像データをm_imageBuffにコピー
    std::memcpy(m_imageBuff.data,
                (void *)&(m_image_in.pixels[0]),
                m_image_in.pixels.length());

    //カラー画像をグレースケールに変換
    cv::cvtColor(m_imageBuff, gray, cv::COLOR_BGR2GRAY);

    // HoughCircles関数で円を検出する
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, m_houghcircles_dp,
                     m_houghcircles_minDist, m_houghcircles_param1,
                     m_houghcircles_param2, m_houghcircles_minRadius,
                     m_houghcircles_maxRadius);

    //円を検出できた場合の処理
    if (!circles.empty())
    {
      //円の位置が画像の左側の場合は左回りに回転するように設定
      if (circles[0][0] < gray.cols / 2)
      {
        m_direction = 1;
      }
      //円の位置が画像の右側の場合は右回りに回転するように設定
      else
      {
        m_direction = 2;
      }
    }
    //円を検出できなかった場合は回転方向の指定をしないように設定
    else
    {
      m_direction = 0;
    }

    //元のカラー画像をコピーして円の情報を画像に追加
    std::memcpy(m_outputBuff.data, (void *)&(m_image_in.pixels[0]), m_image_in.pixels.length());

    for (auto circle : circles)
    {
      cv::circle(m_outputBuff, cv::Point(static_cast<int>(circle[0]), static_cast<int>(circle[1])), static_cast<int>(circle[2]), cv::Scalar(0, 0, 255), 2);
    }

    // 画像データのサイズ取得
    int len = m_outputBuff.channels() * m_outputBuff.cols * m_outputBuff.rows;
    m_image_out.pixels.length(len);

    // 円の情報を付加した画像データをOutPortにコピー
    std::memcpy((void *)&(m_image_out.pixels[0]), m_outputBuff.data, len);
    //画像データを出力
    m_image_outOut.write();
  }

  if (m_velocity_inIn.isNew())
  {
    //速度指令値を読み込み
    m_velocity_inIn.read();
    m_velocity_out = m_velocity_in;

    //円が画像の左側にある場合、左回りに回転する
    if (m_direction == 1)
    {
      m_velocity_out.data.va = m_speed_r;
    }
    //円が画像の右側にある場合、右回りに回転する
    else if (m_direction == 2)
    {
      m_velocity_out.data.va = -m_speed_r;
    }
    //速度指令値を出力
    m_velocity_outOut.write();
  }
  return RTC::RTC_OK;
}

// RTC::ReturnCode_t CircleTracking::onAborting(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t CircleTracking::onError(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t CircleTracking::onReset(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t CircleTracking::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t CircleTracking::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

extern "C"
{

  void CircleTrackingInit(RTC::Manager *manager)
  {
    coil::Properties profile(circletracking_spec);
    manager->registerFactory(profile,
                             RTC::Create<CircleTracking>,
                             RTC::Delete<CircleTracking>);
  }
}
