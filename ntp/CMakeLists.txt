cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(PICO C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

#seteo la board de Wifi
set(PICO_BOARD pico_w)

pico_sdk_init()

#add main.cpp
add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        WIFI_SSID=\"${WIFI_SSID}\"
        WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
)

pico_add_extra_outputs(${PROJECT_NAME})

#uart pins?
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

#extern libs
target_link_libraries(${PROJECT_NAME}
		pico_stdlib              # for core functionality
        #pico_cyw43_arch_none     # wen eed Wifi
        pico_cyw43_arch_lwip_poll
)