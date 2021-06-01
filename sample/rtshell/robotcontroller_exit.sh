#!/bin/sh

HOSTNAME=`hostname`
rtexit localhost/RaspberryPiMouseSimulator0.rtc
rtexit localhost/${HOSTNAME}.host_cxt/RobotController0.rtc
