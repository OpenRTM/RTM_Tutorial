start "" /d C:\workspace\RobotController\build\src\Release RobotControllerComp.exe
start "" /d C:\work\RTM_Tutorial\EXE RaspberryPiMouseSimulatorComp.exe

timeout 2

rtresurrect C:\work\robotcontroller.xml
rtstart C:\work\robotcontroller.xml