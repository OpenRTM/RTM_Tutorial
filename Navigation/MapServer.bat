@set PATH=%RTM_ROOT%jre\bin;%PATH%
@set RTM_JAVA_ROOT=%~dp0
@call set rtm_java_root=%RTM_JAVA_ROOT%
@set JAR_BASE=%RTM_JAVA_ROOT%\jar\
@for /F %%A in ('dir "%JAR_BASE%OpenRTM*" /B') do (set FILE1=%%A)
@for /F %%A in ('dir "%JAR_BASE%commons-cli*" /B') do (set FILE2=%%A)
@for /F %%A in ('dir "%JAR_BASE%jna-?.?.?.*" /B') do (set FILE3=%%A)
@for /F %%A in ('dir "%JAR_BASE%jna-platform-?.?.?.*" /B') do (set FILE4=%%A)
@for /F %%A in ('dir "MapServer\jyaml-?.?.*" /B') do (set FILE5=%%A)
@set CLASSPATH=.;%JAR_BASE%%FILE1%;%JAR_BASE%%FILE2%;%JAR_BASE%%FILE3%;%JAR_BASE%%FILE4%;MapServer\%FILE5%;MapServer

java MapServerComp -f rtc.conf %*
pause;