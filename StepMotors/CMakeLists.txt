cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(StepsMotors C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

#seteo la board de Wifi
#capas no cambie nada en este proyecto, comentar si no es la Wifi
set(PICO_BOARD pico_w)

#sdk de pico
pico_sdk_init()

#agregar main.cpp
add_executable(${PROJECT_NAME} 
    main.cpp
)

# Crear C header con el nombre <pio program>.pio.h
pico_generate_pio_header(${PROJECT_NAME}  
        ${CMAKE_CURRENT_LIST_DIR}/steps.pio
)

#creacion de uf2
pico_add_extra_outputs(${PROJECT_NAME})

#extern libs
target_link_libraries(${PROJECT_NAME}
		pico_stdlib
        hardware_pio
)

#uart off , usb on??
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)