set(SRC_LIST usercoumser.cc ../user.pb.cc)

add_executable(coumser ${SRC_LIST})
target_link_libraries(coumser mprpc protobuf)