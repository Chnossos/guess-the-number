QT = core websockets

SOURCES += \
        Application.cpp \
        Client.cpp \
        Game.cpp \
        WebSocketServer.cpp \
        main.cpp

HEADERS += \
    Application.hpp \
    Client.hpp \
    Game.hpp \
    Log.hpp \
    WebSocketServer.hpp

include($$files(../*.pri))
