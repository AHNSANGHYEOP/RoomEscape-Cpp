#include "Game.h"
#include <iostream>
#include <limits>

Game::Game() : escaped(false) {}

vector<Option> Game::getOptions() {
    vector<Option> options;
    options.push_back({"서랍을 열어본다.", CHECK_DRAWER});
    options.push_back({"침대 밑을 살펴본다.", CHECK_BED});
    options.push_back({"책상 위를 살펴본다.", CHECK_DESK});
    options.push_back({"방문을 열어본다.", TRY_DOOR});

    if (state.triedDoor && !state.hasFlashlight) {
        options.push_back({"문 옆을 자세히 살펴본다.", CHECK_BESIDE_DOOR});
    }
    return options;
}

// 금고 로직
void Game::tryOpenSafe() {
    if (state.isSafeOpen) {
        cout << "\n>> 이미 금고를 열어 아이템을 챙겼습니다." << endl;
        return;
    }
    string inputPassword;
    cout << "\n[ 금고 잠금 장치 ]\n>> 4자리 비밀번호: ";
    cin >> inputPassword;

    if (inputPassword == "1024") {
        cout << "\n>> 띠리릭-! [만능 열쇠] 획득!" << endl;
        state.hasMasterKey = true;
        state.isSafeOpen = true;
    } else {
        cout << "\n>> 비밀번호가 틀렸습니다." << endl;
    }
}

// 이벤트 처리 로직
void Game::processEvent(EventType event) {
    switch (event) {
        case CHECK_DRAWER:
            if (!state.hasOldKey) cout << "\n>> 서랍이 잠겨있습니다." << endl;
            else {
                cout << "\n>> 서랍을 열어 [소형 금고]를 발견했습니다." << endl;
                tryOpenSafe();
            }
            break;
        case CHECK_BED:
             // (이전 코드의 침대 로직 복사)
             if(!state.hasFlashlight) cout << "\n>> 너무 어두워서 안 보입니다." << endl;
             else { /* ... */ } 
             break;
        // ... 나머지 case들 (책상, 문 등) 여기에 복사 ...
        // 지면 관계상 생략했지만, 아까 작성한 로직 그대로 넣으시면 됩니다!
        case TRY_DOOR:
            if (state.hasMasterKey) escaped = true;
            else {
                cout << "\n>> 문은 잠겨있습니다." << endl;
                if (!state.triedDoor) state.triedDoor = true;
            }
            break;
    }
}

// 게임 실행
void Game::Run() {
    cout << "=== 방탈출 게임 시작 ===" << endl;
    while (!escaped) {
        vector<Option> options = getOptions();
        // ... 메뉴 출력 및 입력 받기 코드 ...
        // ... processEvent(options[choice-1].type); 호출 ...
    }
    cout << "=== 탈출 성공! ===" << endl;
}