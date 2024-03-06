cmake_minimum_required(VERSION 3.10)
project(OmniCorba)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(/opt/homebrew/Cellar/omniorb/4.3.2/include)

link_directories(/opt/homebrew/Cellar/omniorb/4.3.2/lib)

add_executable(server mserver.cpp SimpleIDLSK.cc)
target_link_libraries(server omniORB4 omniDynamic4 omnithread omniCodeSets4)

add_executable(client mclient.cpp SimpleIDLSK.cc)
target_link_libraries(client omniORB4 omniDynamic4 omnithread omniCodeSets4)