#pragma once // 헤더 파일 중복 포함 방지
#include <vector>
#include <string>

using namespace std;

// 게임 상태 구조체
struct GameState {
    bool hasFlashlight = false;
    bool hasOldKey = false;
    bool hasMasterKey = false;
    bool hasMemo = false;
    bool triedDoor = false;
    bool isSafeOpen = false;
};

// 이벤트 타입
enum EventType {
    CHECK_DRAWER, CHECK_BED, CHECK_DESK, TRY_DOOR, CHECK_BESIDE_DOOR
};

// 선택지 구조체
struct Option {
    string text;
    EventType type;
};

// Game 클래스 (엔진 역할)
class Game {
private:
    GameState state;
    bool escaped;

public:
    Game(); // 생성자 (초기화)
    void Run(); // 게임 실행 함수

private:
    // 내부적으로 쓰이는 도우미 함수들
    vector<Option> getOptions();
    void tryOpenSafe();
    void processEvent(EventType event);
};