file(GLOB libSrcs *.cc *.cpp)
file(GLOB libHdrs *.h *.hh *.hpp)

# Current library name
set(libNm qtbdbsql)


qt_add_plugin(${libNm}
    CLASS_NAME QSQLiteDriverPlugin
)

# Followings are needed to compile:
# sudo apt install qt6-tools-private-dev
# sudo apt install qt6-base-private-dev


#[[
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

target_include_directories(${libNm}
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    /usr/include/x86_64-linux-gnu/qt6/QtCore/6.2.4
    /usr/include/x86_64-linux-gnu/qt6/QtCore/6.2.4/QtCore
    /usr/include/x86_64-linux-gnu/qt6/QtSql/6.2.4
    /opt/TC/BdbSql/src
)

target_link_libraries(${libNm} PUBLIC Qt::Core Qt::Sql)
#-Qt::CorePrivate Qt::SqlPrivate)

#[[
install(
  TARGETS ${libNm}
  EXPORT ${TARGETS_EXPORT_NAME}
  ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT lib
  FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCDIR}
)
#]]

add_subdirectory(tst)