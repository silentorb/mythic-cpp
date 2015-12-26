cmake_minimum_required(VERSION 3.3)

include(ios.cmake)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -arch arm7")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch arm7")

#string(REPLACE "-" "." FRIENDLY_PRODUCT_NAME ${PRODUCT_NAME:identifier})
set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.silentorb.cmake.sample")

project(cmake-sample)

add_executable(cmake-sample
  MACOSX_BUNDLE
	source/main.m
  source/AppDelegate.m
  source/AppDelegate.h
)

target_link_libraries(cmake-sample "-framework AudioToolbox -framework CoreGraphics -framework QuartzCore -framework UIKit")
set_xcode_property (cmake-sample IPHONEOS_DEPLOYMENT_TARGET "8.0")
set_xcode_property (cmake-sample CODE_SIGN_IDENTITY "iPhone Developer")
set_xcode_property (cmake-sample CODE_SIGN_IDENTITY[sdk=iphoneos*] "iPhone Developer")

#set_target_properties(${NAME} PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer: Christopher W. Johnson")
