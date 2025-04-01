// -*- Java -*-
// <rtc-template block="description">
/*!
 * @file drawGraph.java
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
public static String drawgraph_conf[] = {
        "implementation_id", "drawGraph",
        "type_name",         "drawGraph",
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

/**
 * drawGraph
 * <p> 
 * Draw graph component
 */
public class drawGraph implements RtcNewFunc, RtcDeleteFunc, RegisterModuleFunc {

    public RTObject_impl createRtc(Manager mgr) {
        return new drawGraphImpl(mgr);
    }

    public void deleteRtc(RTObject_impl rtcBase) {
        rtcBase = null;
    }
    public void registerModule() {
        Properties prop = new Properties(drawgraph_conf);
        final Manager manager = Manager.instance();
        manager.registerFactory(prop, new drawGraph(), new drawGraph());
    }
}
