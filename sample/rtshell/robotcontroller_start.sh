#!/bin/sh

cd ~/workspace/RobotController/build/src/
./RobotControllerComp&
cd ~/RasPiMouseSimulatorRTC/build
src/RaspberryPiMouseSimulatorComp&
sleep 2

rtresurrect ~/work/robotcontroller.xml
rtstart ~/work/robotcontroller.xml
