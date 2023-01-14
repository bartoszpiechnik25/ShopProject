cmake_minimum_required(VERSION 3.23)
project(ShopProjectQt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(LOGIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/login")
set(SHOP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shop")
set(SELL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sell")
set(SELL_PHONE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sell/sell_phone_dialog")
set(SELL_BOOK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sell/sell_book_dialog")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(CMAKE_PREFIX_PATH "C:/Qt/6.4.2/mingw_64")

find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(ShopProjectQt main.cpp)
target_link_libraries(ShopProjectQt
  Qt::Core
  Qt::Gui
  Qt::Widgets
)
target_sources(ShopProjectQt PRIVATE "${SRC_DIR}/book.cpp"
        "${SRC_DIR}/item.cpp" "${SRC_DIR}/database.cpp"
        "${SRC_DIR}/phone.cpp"
        "${LOGIN_DIR}/login.cpp" "${LOGIN_DIR}/login.ui"
        "${SHOP_DIR}/shop.cpp" "${SHOP_DIR}/shop.ui"
        "${SELL_PHONE_DIR}/selldialog.cpp" "${SELL_PHONE_DIR}/selldialog.ui"
        "${SELL_BOOK_DIR}/sellbookdialog.cpp" "${SELL_BOOK_DIR}/sellbookdialog.ui")

target_include_directories(ShopProjectQt PRIVATE ${INC_DIR} ${SHOP_DIR} ${LOGIN_DIR} ${SELL_DIR} ${SELL_PHONE_DIR} ${SELL_BOOK_DIR})


if(WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if(NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if(NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif()
    endif()
    if(EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif()
    foreach(QT_LIB Core Gui Widgets )
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach(QT_LIB)
endif()
