CONFIG += cmdline c++14 strict_c++ no_include_pwd

DESTDIR = $$ROOT/bin

linux-g++: QMAKE_CXXFLAGS = \
    -pedantic \

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
