file(GLOB libSrcs *.cc *.cpp)
file(GLOB libHdrs *.h *.hh *.hpp)

# Current library name
set(libNm qtbdbsql)


qt_add_plugin(${libNm}
    CLASS_NAME QSQLiteDriverPlugin
)

# Followings are needed to compile on Linux
# sudo apt install qt6-tools-private-dev
# sudo apt install qt6-base-private-dev


#[[ ERASE later
qt_internal_add_plugin(QSQLiteDriverPlugin
    OUTPUT_NAME qsqlite
    PLUGIN_TYPE sqldrivers
    SOURCES
        qsql_sqlite.cpp qsql_sqlite_p.h
        smain.cpp
    DEFINES
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_TO_ASCII
    LIBRARIES
        Qt::Core
        Qt::CorePrivate
        Qt::SqlPrivate
)
#]]

target_sources(${libNm}
    PRIVATE ${libSrcs}
    PUBLIC FILE_SET HEADERS FILES ${libHdrs}
)


if(WIN32)
 target_include_directories(${libNm}
  PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}
   ${CMAKE_SOURCE_DIR}/../BdbSql/src
   D:/QT/6.3.2/msvc2019_64/include/QtCore/6.3.2
   D:/QT/6.3.2/msvc2019_64/include/QtCore/6.3.2/QtCore
   D:/QT/6.3.2/msvc2019_64/include/QtSql/6.3.2
   D:/QT/6.3.2/msvc2019_64/include/QtSql/6.3.2/QtSql
 )
 target_link_libraries(${libNm} PUBLIC Qt::Core Qt::Sql bdblib bdbsqllib)
else()
 target_include_directories(${libNm}
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    /usr/include/x86_64-linux-gnu/qt6/QtCore/6.2.4
    /usr/include/x86_64-linux-gnu/qt6/QtCore/6.2.4/QtCore
    /usr/include/x86_64-linux-gnu/qt6/QtSql/6.2.4
    ${_opt_TC}/BdbSql/src
 )

 target_link_libraries(${libNm} PUBLIC Qt::Core Qt::Sql)
endif()

target_link_libraries(${libNm} PUBLIC Qt::Core Qt::Sql)

#[[ Evaluate later

install(
  TARGETS ${libNm}
  EXPORT ${TARGETS_EXPORT_NAME}
  ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT lib
  FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCDIR}
)
#]]

add_subdirectory(tst)