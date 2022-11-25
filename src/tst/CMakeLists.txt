file(GLOB appSrcs *.cc *.cpp)
file(GLOB appHdrs *.h *.hh *.hpp)

# Current test executable name
set(appNm qtbdbsqlpi_test)


add_executable(${appNm} ${appSrcs})
add_test(NAME ${appNm} COMMAND ${appNm})


target_include_directories(${appNm}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${PrjSrc}
)

target_link_libraries(${appNm} PUBLIC Qt::Core Qt::Sql GTest::gtest)
