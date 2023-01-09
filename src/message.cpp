
#include "message.h"

Message::Message(User& from, User& to, string& content) :
        from{ from },
        to{ to },
        content{ content },
        sentTime{ chrono::system_clock::now() } {}