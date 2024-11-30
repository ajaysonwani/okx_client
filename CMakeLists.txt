cmake_minimum_required(VERSION 3.10)
project(OKXOrderSystem)

set(CMAKE_CXX_STANDARD 17)

# Explicitly set the OpenSSL root directory for macOS
if(APPLE)
    set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl@3)
    set(OPENSSL_INCLUDE_DIR ${OPENSSL_ROOT_DIR}/include)
    set(OPENSSL_LIBRARIES ${OPENSSL_ROOT_DIR}/lib)
    include_directories(${OPENSSL_INCLUDE_DIR})
    link_directories(${OPENSSL_LIBRARIES})
    
    # Use pkg-config to ensure proper linking
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(OPENSSL REQUIRED openssl)
else()
    find_package(OpenSSL REQUIRED)
endif()

find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

include_directories(${CURL_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIRS})

# Specify OKXOrderSystem.cpp instead of main.cpp
add_executable(okx_order_system OKXOrderSystem.cpp okx_client.cpp)

target_link_libraries(okx_order_system 
    PRIVATE 
    ${CURL_LIBRARIES} 
    ${OPENSSL_LIBRARIES}
    nlohmann_json::nlohmann_json
)