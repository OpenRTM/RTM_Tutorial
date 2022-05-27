﻿#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file RaspberryPiMouseIo.py
 @brief RaspberryPi Mouse Controller for Choreonoid Simulator
 @date $Date$

 @author n-miyamoto@aist.go.jp

 LGPL

"""
import OpenRTM_aist
import RTC
import sys
import time
sys.path.append(".")

# Import RTM module


# Import Service implementation class
# <rtc-template block="service_impl">

# </rtc-template>

# Import Service stub modules
# <rtc-template block="consumer_import">
# </rtc-template>


# This module's spesification
# <rtc-template block="module_spec">
raspberrypimouseio_spec = ["implementation_id", "RaspberryPiMouseIo",
                           "type_name",         "RaspberryPiMouseIo",
                           "description",       "RaspberryPi Mouse Controller for Choreonoid Simulator",
                           "version",           "1.0.0",
                           "vendor",            "AIST",
                           "category",          "Simulator",
                           "activity_type",     "STATIC",
                           "max_instance",      "1",
                           "language",          "Python",
                           "lang_type",         "SCRIPT",
                           ""]
# </rtc-template>

##
# @class RaspberryPiMouseIo
# @brief RaspberryPi Mouse Controller for Choreonoid Simulator
#
# Choreonoid用Raspberry Pi Mouse入出力コンポーネント
#
#


class RaspberryPiMouseIo(OpenRTM_aist.DataFlowComponentBase):

    ##
    # @brief constructor
    # @param manager Maneger Object
    #
    def __init__(self, manager):
        OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

        self._d_velocity = OpenRTM_aist.instantiateDataType(
            RTC.TimedVelocity2D)
        """
		直進速度、回転速度
		 - Type: RTC::Velocity2D
		 - Unit: m/s, rad/s
		"""
        self._velocityIn = OpenRTM_aist.InPort("velocity", self._d_velocity)
        self._d_ir_sensor = OpenRTM_aist.instantiateDataType(RTC.TimedShortSeq)
        """
		距離センサのデータ
		 - Type: RTC::TimedShortSeq
		 - Number: 4
		"""
        self._ir_sensorOut = OpenRTM_aist.OutPort(
            "ir_sensor", self._d_ir_sensor)
        self._d_distance = OpenRTM_aist.instantiateDataType(RTC.TimedDoubleSeq)
        """
		距離センサで計測した距離。
		 - Type: RTC::TimedDoubleSeq
		 - Number: 4
		 - Unit: m
		"""
        self._distanceOut = OpenRTM_aist.OutPort("distance", self._d_distance)

        # initialize of configuration-data.
        # <rtc-template block="init_conf_param">

        # </rtc-template>

    ##
    #
    # The initialize action (on CREATED->ALIVE transition)
    # formaer rtc_init_entry()
    #
    # @return RTC::ReturnCode_t
    #
    #

    def onInitialize(self):
        # Bind variables and configuration variable

        # Set InPort buffers
        self.addInPort("velocity", self._velocityIn)

        # Set OutPort buffers
        #self.addOutPort("ir_sensor", self._ir_sensorOut)
        #self.addOutPort("distance", self._distanceOut)

        # Set service provider to Ports

        # Set service consumers to Ports

        # Set CORBA Service Ports

        return RTC.RTC_OK

    ###
    ##
    # The finalize action (on ALIVE->END transition)
    # formaer rtc_exiting_entry()
    ##
    # @return RTC::ReturnCode_t
    #
    ##
    # def onFinalize(self):
    #
    #	return RTC.RTC_OK

    ###
    ##
    # The startup action when ExecutionContext startup
    # former rtc_starting_entry()
    ##
    # @param ec_id target ExecutionContext Id
    ##
    # @return RTC::ReturnCode_t
    ##
    ##
    # def onStartup(self, ec_id):
    #
    #	return RTC.RTC_OK

    ###
    ##
    # The shutdown action when ExecutionContext stop
    # former rtc_stopping_entry()
    ##
    # @param ec_id target ExecutionContext Id
    ##
    # @return RTC::ReturnCode_t
    ##
    ##
    # def onShutdown(self, ec_id):
    #
    #	return RTC.RTC_OK

    ###
    ##
    # The activated action (Active state entry action)
    # former rtc_active_entry()
    ##
    # @param ec_id target ExecutionContext Id
    ##
    # @return RTC::ReturnCode_t
    ##
    ##
    # def onActivated(self, ec_id):
    #
    #	return RTC.RTC_OK

    ###
    ##
    # The deactivated action (Active state exit action)
    # former rtc_active_exit()
    ##
    # @param ec_id target ExecutionContext Id
    ##
    # @return RTC::ReturnCode_t
    ##
    ##
    # def onDeactivated(self, ec_id):
    #
    #	return RTC.RTC_OK

    ###
    ##
    # The execution action that is invoked periodically
    # former rtc_active_do()
    ##
    # @param ec_id target ExecutionContext Id
    ##
    # @return RTC::ReturnCode_t
    ##
    ##
    # def onExecute(self, ec_id):
    #
    #	return RTC.RTC_OK

    ###
    ##
    # The aborting action when main logic error occurred.
    # former rtc_aborting_entry()
    ##
    # @param ec_id target ExecutionContext Id
    ##
    # @return RTC::ReturnCode_t
    ##
    ##
    # def onAborting(self, ec_id):
    #
    #	return RTC.RTC_OK

    ###
    ##
    # The error action in ERROR state
    # former rtc_error_do()
    ##
    # @param ec_id target ExecutionContext Id
    ##
    # @return RTC::ReturnCode_t
    ##
    ##
    # def onError(self, ec_id):
    #
    #	return RTC.RTC_OK

    ###
    ##
    # The reset action that is invoked resetting
    # This is same but different the former rtc_init_entry()
    ##
    # @param ec_id target ExecutionContext Id
    ##
    # @return RTC::ReturnCode_t
    ##
    ##
    # def onReset(self, ec_id):
    #
    #	return RTC.RTC_OK

    ###
    ##
    # The state update action that is invoked after onExecute() action
    # no corresponding operation exists in OpenRTm-aist-0.2.0
    ##
    # @param ec_id target ExecutionContext Id
    ##
    # @return RTC::ReturnCode_t
    ##

    ##
    # def onStateUpdate(self, ec_id):
    #
    #	return RTC.RTC_OK

    ###
    ##
    # The action that is invoked when execution context's rate is changed
    # no corresponding operation exists in OpenRTm-aist-0.2.0
    ##
    # @param ec_id target ExecutionContext Id
    ##
    # @return RTC::ReturnCode_t
    ##
    ##
    # def onRateChanged(self, ec_id):
    #
    #	return RTC.RTC_OK

    def setBody(self, body):
        self.ioBody = body
        self.wheelR = self.ioBody.link("RIGHT_WHEEL")
        self.wheelL = self.ioBody.link("LEFT_WHEEL")

    def outputToSimulator(self):
        pass

    def inputFromSimulator(self):
        if self._velocityIn.isNew():
            data = self._velocityIn.read()

            vx = data.data.vx
            va = data.data.va

            wheel_distance = 0.0425
            wheel_radius = 0.04
            rms = (vx + va*wheel_distance)/wheel_radius
            lms = (vx - va*wheel_distance)/wheel_radius

            self.wheelR.dq = rms
            self.wheelL.dq = lms


def RaspberryPiMouseIoInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=raspberrypimouseio_spec)
    manager.registerFactory(profile,
                            RaspberryPiMouseIo,
                            OpenRTM_aist.Delete)


def MyModuleInit(manager):
    RaspberryPiMouseIoInit(manager)

    # Create a component
    comp = manager.createComponent("RaspberryPiMouseIo")


def main():
    mgr = OpenRTM_aist.Manager.init(sys.argv)
    mgr.setModuleInitProc(MyModuleInit)
    mgr.activateManager()
    mgr.runManager()


if __name__ == "__main__":
    main()
