cmake_minimum_required(VERSION 3.18.0)
project(saitek CXX C)

if(DEFINED XPVERSION)
  message("XPVERSION=" ${XPVERSION})
else()
  set(XPVERSION, "0.4.2")
  message("XPVERSION=" ${XPVERSION})
endif()
add_compile_definitions(XPVERSION="${XPVERSION}")

# SETS
# set(XPLANE11PLUGIN true)
# set(PERFORMANCE true)
# set(USB true)
#set(DEBUG true)

set(SDK_PATH  "SDK")
message("SDK_PATH=" ${SDK_PATH})

set(HID_PATH "hidapi")
message("HID_PATH=" ${HID_PATH})

if(APPLE)
	set(HIDAPI ${HID_PATH}/mac/hid.c)
elseif(UNIX)
	set(HIDAPI ${HID_PATH}/linux/hid.c)
elseif(WIN32)
  # TODO LOW / features / NOT SUPPORT
  # WINDOWS NOT SUPPORT
  # USE VISUAL CODE
	set(HIDAPI ${HID_PATH}/windows/hid.c)
endif()
message("HIDAPI=" ${HIDAPI})


set(DIR
  src/
  src/source/
  src/range/
  src/color/
  src/output/
  src/action/
  src/display/
  src/loader/
  src/libs/
  src/radio/
  src/autopilot/
  src/panel/
  src/form/
  tests/
  ${HID_PATH}/hidapi/
)
if(DEFINED XPLANE11PLUGIN)
  set(DIR "${DIR}"
    ${SDK_PATH}/CHeaders/XPLM
    ${SDK_PATH}/CHeaders/Wrappers
    ${SDK_PATH}/CHeaders/Widgets
  )
endif()


set(CODE 
  src/libs/spec.cpp
  src/libs/debug.cpp
  src/libs/line.cpp

  src/loader/content.cpp
  src/loader/reader.cpp

  src/display/data.cpp
  src/display/dataDiv.cpp
  src/display/dataFloat.cpp
  src/display/dataInt.cpp
  src/display/dataInt1.cpp
  src/display/dataInt2.cpp
  src/display/dataMInt.cpp
  src/display/dataShort.cpp
  src/display/monitor.cpp

  src/output/customRef.cpp
  src/output/customWrite.cpp

  src/source/command.cpp
  src/source/value.cpp
  src/source/const.cpp
  src/source/dataref.cpp
  src/source/array.cpp

  src/range/range.cpp
  src/range/rangeOr.cpp
  src/range/rangeAnd.cpp
  src/range/rangeValue.cpp
  src/range/rangeLoader.cpp

  src/color/cell.cpp
  src/color/color.cpp

  src/action/sw.cpp
  src/action/swoff.cpp
  src/action/swon.cpp
  src/action/swcmd.cpp
  src/action/swpush.cpp
  src/action/swset.cpp
  src/action/swdec.cpp
  src/action/swrun.cpp

  src/radio/mode.cpp
  src/radio/modeOff.cpp
  src/radio/modeIf.cpp
  src/radio/modeDefault.cpp
  src/radio/modeDual.cpp
  src/radio/modeAdd.cpp
  src/radio/modeTimeout.cpp
  src/radio/modeValue.cpp
  src/radio/modeShow.cpp
  src/radio/modeCommand.cpp
  src/radio/modeHold.cpp
  src/radio/modeExec.cpp
  src/radio/modePush.cpp
  src/radio/modeList.cpp

  src/autopilot/ap.cpp
  src/autopilot/apCmd.cpp
  src/autopilot/apOff.cpp
  src/autopilot/apIf.cpp
  src/autopilot/apAdd.cpp
  src/autopilot/apCopy.cpp
  src/autopilot/apRadio.cpp
  src/autopilot/apDisplay.cpp
  src/autopilot/apQuad.cpp
  src/autopilot/apList.cpp

  src/form/form.cpp
  src/form/APForm.cpp
  src/form/RadioForm.cpp
  src/form/SWForm.cpp
  src/form/BIPForm.cpp

  src/form/item.cpp
  src/form/apCaption.cpp

  src/panel/panel.cpp
  src/panel/bip.cpp
  src/panel/swith.cpp
  src/panel/radio.cpp
  src/panel/multi.cpp
  src/panel/panels.cpp
  src/plugin.cpp
)
if(NOT DEFINED XPLANE11PLUGIN)
  set(CODE "${CODE}"
    tests/main.cpp
  )
endif()

set(HEADER src/plugin.h)
message("HEADER=" ${HEADER})

set(ALL ${CODE} ${HIDAPI} ${HEADER})

if(APPLE)
	add_executable(saitek ${ALL})
elseif(UNIX)
  if(DEFINED XPLANE11PLUGIN)
    add_library(saitek SHARED ${ALL})
  else()
    add_executable(saitek ${ALL})
  endif()
elseif(WIN32)
  # TODO LOW / features / NOT SUPPORT
  # WINDOWS NOT SUPPORT
  # USE VISUAL CODE
	add_library(saitek MODULE ${ALL})
endif()

if(APPLE)
  if(DEFINED XPLANE11PLUGIN)
    set(OUTPUT_NAME "mac.xpl")
    set(PREFIX "")
    set(SUFFIX "")
  else()
    set(OUTPUT_NAME "check_mac64_intel")
    set(PREFIX "")
    set(SUFFIX "")
  endif()
elseif(UNIX)
  if(DEFINED XPLANE11PLUGIN)
    set(OUTPUT_NAME "lin.xpl")
    set(PREFIX "")
    set(SUFFIX "")
  else()
    set(OUTPUT_NAME "check_lin64_amd64")
    set(PREFIX "")
    set(SUFFIX "")
  endif()
elseif(WIN32)
  # TODO LOW / features / NOT SUPPORT
  # WINDOWS NOT SUPPORT
  # USE VISUAL CODE
  if(DEFINED XPLANE11PLUGIN)
  	set(OUTPUT_NAME "win.xpl")
  else()
    set(OUTPUT_NAME "check.exe")
  endif()
endif()
message("OUTPUT_NAME=" ${OUTPUT_NAME})

set_target_properties(saitek PROPERTIES PREFIX "${PREFIX}")
set_target_properties(saitek PROPERTIES SUFFIX "${SUFFIX}")
set_target_properties(saitek PROPERTIES OUTPUT_NAME "${OUTPUT_NAME}")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DXPLM200=1 -DXPLM210=1 -DXPLM300=1 -DXPLM301=1 -DXPLM303")
if(DEFINED XPLANE11PLUGIN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DXPLANE11PLUGIN=true")
endif()
if(DEFINED DEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG=true")
endif()
if(DEFINED USB)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSB=true")
endif()
if(DEFINED PERFORMANCE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPERFORMANCE=true")
endif()
if(APPLE)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-deprecated")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch x86_64")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra --std=c++11")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAPL=1 -DIBM=0 -DLIN=0")
elseif(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra --std=c++11")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAPL=0 -DIBM=0 -DLIN=1")
elseif(WIN32)
  # WINDOWS NOT SUPPORT
  # USE VISUAL CODE
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MD")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAPL=0 -DIBM=1 -DLIN=0")
endif()

include_directories(saitek ${DIR})

if(APPLE)
  if(DEFINED XPLANE11PLUGIN)
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${SDK_PATH}/Libraries/Mac/)
    FIND_LIBRARY(XPLM_LIBRARY XPLM ${SDK_PATH}/Libraries/Mac/)
    FIND_LIBRARY(XPWIDGETS_LIBRARY XPWidgets ${SDK_PATH}/Libraries/Mac/)
    target_link_libraries(saitek ${XPLM_LIBRARY} ${XPWIDGETS_LIBRARY})
  endif()
elseif(WIN32)
  # WINDOWS NOT SUPPORT
  # USE VISUAL CODE
  # add_compile_options(-fexceptions)
  # add_compile_options(-fvisibility=hidden)
  # add_compile_options(-Wall -Wpedantic -Wshadow -Wfloat-equal -Wextra)
  # add_compile_options(-Wno-unused)
  # target_link_libraries(saitek -static-libgcc -static-libstdc++)
  # target_link_libraries(saitek -static)
elseif(UNIX)
  find_library(HIDAPIDEPS_LIBRARY NAMES setupapi udev HINTS ${CMAKE_C_IMPLICIT_LINK_DIRECTORIES})
  target_link_libraries(saitek ${HIDAPIDEPS_LIBRARY})
endif()

link_libraries(m)

if(APPLE)
  if(DEFINED XPLANE11PLUGIN)
    SET_TARGET_PROPERTIES(saitek PROPERTIES LINK_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}  -fPIC -fvisibility=hidden -bundle -framework OpenGL -framework Cocoa -framework OpenGL -framework XPLM -framework XPWidgets -framework IOKit")
  else()
  	SET_TARGET_PROPERTIES(saitek PROPERTIES LINK_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}  -fPIC -fvisibility=hidden -framework Cocoa -framework IOKit")
  endif()
elseif(WIN32)
  # TODO LOW / features / NOT SUPPORT
elseif(UNIX)
  #LIBS += `pkg-config libudev --libs`
  if(DEFINED XPLANE11PLUGIN)
  	SET_TARGET_PROPERTIES(saitek PROPERTIES LINK_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}  -fPIC -fvisibility=hidden ")
  else()
    SET_TARGET_PROPERTIES(saitek PROPERTIES LINK_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}  -fPIC -fvisibility=hidden ")
  endif() 
  # -shared -rdynamic -nodefaultlibs -undefined_warning
endif()
