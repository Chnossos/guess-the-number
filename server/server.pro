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
    Rules.hpp \
    WebSocketServer.hpp

include($$files(../*.pri))
