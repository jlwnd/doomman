#include "client/Theme.h"

namespace DoomMan {

QString appStyleSheet(const QString& fontFamily) {
    return QStringLiteral("* { font-family: \"%1\"; }\n").arg(fontFamily) +
           QStringLiteral(R"(
        QMainWindow { background-color: #0d0908; }

        #MenuContainer, #LobbyContainer, #GameOverContainer {
            background-color: #14100e;
            border: 3px solid #7a1f14;
            border-radius: 8px;
        }

        #TitleLabel {
            color: #e23b2e;
            font-size: 26px;
            padding: 8px 4px 16px 4px;
        }

        #NickLabel {
            color: #f2a03d;
            font-size: 12px;
            background: transparent;
        }
        #NickEdit {
            color: #ffd9a0;
            font-size: 12px;
            background: #0d0908;
            border: 2px solid #5a3320;
            border-radius: 4px;
            padding: 9px 10px;
        }
        #NickEdit:focus { border-color: #e23b2e; }

        #PlayerList, #ScoreList {
            color: #f2a03d;
            font-size: 12px;
            background: #0d0908;
            border: 2px solid #5a3320;
            border-radius: 4px;
            padding: 10px;
        }
        #PlayerList::item, #ScoreList::item { padding: 6px 2px; }

        #MenuButton, #LobbyButton, #GameOverButton {
            color: #f0e0d0;
            font-size: 13px;
            background: #201612;
            border: 2px solid #7a1f14;
            border-radius: 4px;
            padding: 13px 20px;
            min-width: 240px;
        }
        #MenuButton:hover, #LobbyButton:hover:enabled, #GameOverButton:hover {
            background: #7a1f14;
            color: #ffffff;
        }
        #MenuButton:pressed, #LobbyButton:pressed, #GameOverButton:pressed {
            background: #e23b2e;
            border-color: #e23b2e;
        }
        #LobbyButton:disabled {
            color: #5a4a40;
            background: #16110f;
            border-color: #3a2a20;
        }

        #ScoreLabel {
            color: #f2a03d;
            font-size: 15px;
            padding: 8px;
        }
    )");
}

}  // namespace DoomMan
