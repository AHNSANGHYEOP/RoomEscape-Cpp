// Game.cpp
#include "Game.h"
#include <iostream>
#include <limits>

using namespace std;

// 생성자: 게임 초기화
RoomEscapeGame::RoomEscapeGame() {
    escaped = false;
    // GameState의 멤버들은 구조체 정의 시 false로 초기화됨
}

// 현재 상태에 따른 선택지 반환
vector<Option> RoomEscapeGame::getOptions() const {
    vector<Option> options;
    options.push_back({"서랍을 열어본다.", CHECK_DRAWER});
    options.push_back({"침대 밑을 살펴본다.", CHECK_BED});
    options.push_back({"책상 위를 살펴본다.", CHECK_DESK});
    options.push_back({"방문을 열어본다.", TRY_DOOR});

    // 히든 선택지: 문을 한번 시도했고, 손전등이 없을 때 등장
    if (state.triedDoor && !state.hasFlashlight) {
        options.push_back({"문 옆을 자세히 살펴본다.", CHECK_BESIDE_DOOR});
    }
    return options;
}

// 금고 퍼즐 로직
void RoomEscapeGame::tryOpenSafe() {
    if (state.isSafeOpen) {
        cout << "\n>> 이미 금고를 열어 아이템을 챙겼습니다." << endl;
        return;
    }

    string inputPassword;
    cout << "\n[ 금고 잠금 장치 ]" << endl;
    cout << ">> 4자리 비밀번호를 입력하세요: ";
    cin >> inputPassword;

    // 정답: 2의 10승 = 1024
    if (inputPassword == "1024") {
        cout << "\n>> 금고가 열렸습니다." << endl;
        cout << ">> 안에서 [만능 열쇠]를 발견했습니다!" << endl;
        state.hasMasterKey = true;
        state.isSafeOpen = true;
    } else {
        cout << "\n>> 비밀번호가 틀렸습니다." << endl;
        cout << ">> (쪽지의 내용을 다시 생각해봐야 할 것 같다...)" << endl;
    }
}

// 이벤트 처리 로직
void RoomEscapeGame::processEvent(EventType event) {
    switch (event) {
    // 1. 서랍 (금고)
    case CHECK_DRAWER:
        if (!state.hasOldKey) {
            cout << "\n>> 서랍이 잠겨있습니다. 낡은 열쇠 구멍이 보입니다." << endl;
        } else {
            cout << "\n>> 낡은 열쇠를 사용해 서랍을 열었습니다." << endl;
            cout << ">> 서랍 안에 [소형 금고]가 있습니다!" << endl;
            tryOpenSafe();
        }
        break;

    // 2. 침대 (낡은 열쇠)
    case CHECK_BED:
        if (!state.hasFlashlight) {
            cout << "\n>> 너무 어두워서 침대 밑이 보이지 않습니다." << endl;
        } else {
            if (state.hasOldKey) {
                cout << "\n>> 먼지구덩이 뿐입니다." << endl;
            } else {
                cout << "\n>> 손전등을 비추자 구석에서 [낡은 열쇠]를 발견했습니다!" << endl;
                state.hasOldKey = true;
            }
        }
        break;

    // 3. 책상 (쪽지 & 힌트)
    case CHECK_DESK:
        if (!state.hasFlashlight) {
            cout << "\n>> 너무 어두워서 책상 위를 확인할 수 없습니다." << endl;
        } else {
            if (!state.hasMemo) {
                cout << "\n>> 책상 위에서 꼬깃꼬깃한 [쪽지]를 발견했습니다." << endl;
                state.hasMemo = true;
            }
            
            cout << "\n=========== [ 쪽 지 ] ===========" << endl;
            cout << " 비밀번호 힌트:" << endl << endl;
            cout << "   S2   S2   S2   S2   S2   " << endl;
            cout << "=================================" << endl;
            cout << ">> (하트 5개가 그려져 있다...)" << endl;
        }
        break;

    // 4. 방문 (탈출)
    case TRY_DOOR:
        if (state.hasMasterKey) {
            cout << "\n>> 만능 열쇠로 문을 열었습니다. 탈출 성공!" << endl;
            escaped = true;
        } else {
            cout << "\n>> 문은 잠겨있습니다." << endl;
            if (!state.triedDoor) {
                cout << ">> (주변을 좀 더 자세히 살펴봐야 할 것 같다...)" << endl;
                state.triedDoor = true;
            }
        }
        break;

    // 4-2. 문 옆 (손전등)
    case CHECK_BESIDE_DOOR:
        cout << "\n>> 문 옆 벽에 붙어있는 비상용 보관함에서 [비상용 손전등]을 획득했습니다!" << endl;
        state.hasFlashlight = true;
        break;
    }
}

// 게임 메인 루프
void RoomEscapeGame::run() {
    cout << "=== 방탈출 게임 ===" << endl;
    cout << "어두운 방에 갇혀있습니다. 탈출 방법을 찾아야 합니다." << endl;

    while (!escaped) {
        vector<Option> currentOptions = getOptions();

        cout << "\n----------------------------------------" << endl;
        cout << "무엇을 하시겠습니까?" << endl;
        for (size_t i = 0; i < currentOptions.size(); ++i) {
            cout << (i + 1) << ". " << currentOptions[i].text << endl;
        }
        cout << "----------------------------------------" << endl;

        int choice;
        cout << ">> 선택: ";
        if (!(cin >> choice)) {
            cout << "숫자를 입력해주세요." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice < 1 || choice > static_cast<int>(currentOptions.size())) {
            cout << "잘못된 선택입니다." << endl;
            continue;
        }

        processEvent(currentOptions[choice - 1].type);
    }
}