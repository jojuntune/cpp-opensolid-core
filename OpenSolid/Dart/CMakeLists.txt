if(EXISTS "$ENV{DART_SDK_DIR}/include/dart_api.h")
    include_directories("$ENV{DART_SDK_DIR}/include")

    
else()
    message(SEND_ERROR "DART_SDK_DIR environment variable is not set to a valid Dart SDK directory")
endif()
