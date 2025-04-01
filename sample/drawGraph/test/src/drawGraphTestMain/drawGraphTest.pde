// -*- Java -*-
// <rtc-template block="description">
/*!
 * @file drawGraphTest.java
 * @date $Date$
 *
 * $Id$
 */
// </rtc-template>

import jp.go.aist.rtm.RTC.Manager;
import jp.go.aist.rtm.RTC.RTObject_impl;
import jp.go.aist.rtm.RTC.RtcDeleteFunc;
import jp.go.aist.rtm.RTC.RtcNewFunc;
import jp.go.aist.rtm.RTC.RegisterModuleFunc;
import jp.go.aist.rtm.RTC.util.Properties;

//  Module specification
//  <rtc-template block="module_spec">
public static String drawgraphtest_conf[] = {
	    "implementation_id", "drawGraphTest",
	    "type_name",         "drawGraphTest",
	    "description",       "Draw graph component",
	    "version",           "1.0.0",
	    "vendor",            "AIST",
	    "category",          "Sample",
	    "activity_type",     "STATIC",
	    "max_instance",      "1",
	    "language",          "Java",
	    "lang_type",         "compile",
	    ""
};
//  </rtc-template>

/*!
 * @class drawGraphTest
 * @brief Draw graph component
 */
public class drawGraphTest implements RtcNewFunc, RtcDeleteFunc, RegisterModuleFunc {

    public RTObject_impl createRtc(Manager mgr) {
        return new drawGraphTestImpl(mgr);
    }

    public void deleteRtc(RTObject_impl rtcBase) {
        rtcBase = null;
    }
    public void registerModule() {
        Properties prop = new Properties(drawgraphtest_conf);
        final Manager manager = Manager.instance();
        manager.registerFactory(prop, new drawGraphTest(), new drawGraphTest());
    }
}
