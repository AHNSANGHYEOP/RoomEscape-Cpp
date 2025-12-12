// Game.h
#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

// 1. 게임 상태 (Inventory & Flags)
struct GameState {
    bool hasFlashlight = false; // 비상용 손전등
    bool hasOldKey = false;     // 낡은 열쇠 (침대 밑)
    bool hasMasterKey = false;  // 만능 열쇠 (금고)
    bool hasMemo = false;       // 쪽지 (책상 위)
    bool triedDoor = false;     // 방문 시도 여부
    bool isSafeOpen = false;    // 금고 열림 여부
};

// 2. 이벤트 정의
enum EventType {
    CHECK_DRAWER,       // 1. 서랍
    CHECK_BED,          // 2. 침대
    CHECK_DESK,         // 3. 책상
    TRY_DOOR,           // 4. 방문
    CHECK_BESIDE_DOOR   // 4-2. 문 옆 (히든)
};

// 선택지 구조체
struct Option {
    std::string text;
    EventType type;
};

// 게임 로직을 담담하는 클래스
class RoomEscapeGame {
private:
    GameState state; // 현재 게임 상태
    bool escaped;    // 탈출 성공 여부

    // 내부 로직 함수들
    std::vector<Option> getOptions() const;
    void tryOpenSafe();
    void processEvent(EventType event);

public:
    RoomEscapeGame(); 
    void run();       // 게임 실행 함수
};

#endif // GAME_H