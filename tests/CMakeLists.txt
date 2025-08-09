add_executable(test_block tests/test_block.cpp ${CMAKE_SOURCE_DIR}/src/core/Block.cpp ${CMAKE_SOURCE_DIR}/src/core/CryptoUtils.cpp)
target_include_directories(test_block PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/utils)
add_test(NAME test_block COMMAND test_block)

add_executable(test_blockchain tests/test_blockchain.cpp ${CMAKE_SOURCE_DIR}/src/core/Blockchain.cpp ${CMAKE_SOURCE_DIR}/src/core/Block.cpp ${CMAKE_SOURCE_DIR}/src/core/CryptoUtils.cpp)
target_include_directories(test_blockchain PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/utils)
add_test(NAME test_blockchain COMMAND test_blockchain)
