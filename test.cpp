#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// 사다리 클래스
class LadderGame {
private:
    int players; // 플레이어 수
    int steps; // 사다리의 높이 (세로 줄 수)
    vector<vector<bool>> ladder; // 사다리의 가로줄 여부를 나타내는 2차원 벡터
    vector<string> playerNames; // 플레이어 이름
    vector<string> results; // 결과

public:
    LadderGame(int p, int s, const vector<string>& names, const vector<string>& res) 
        : players(p), steps(s), playerNames(names), results(res) {
        ladder.resize(steps, vector<bool>(players - 1, false));
        generateLadder();
    }

    // 사다리 생성
    void generateLadder() {
        srand(time(0));
        for (int i = 0; i < steps; ++i) {
            for (int j = 0; j < players - 1; ++j) {
                ladder[i][j] = rand() % 2;
            }
        }
    }

    // 사다리 출력
    void printLadder() {
        for (int i = 0; i < steps; ++i) {
            for (int j = 0; j < players; ++j) {
                cout << "|";
                if (j < players - 1) {
                    if (ladder[i][j]) {
                        cout << "---";
                    } else {
                        cout << "   ";
                    }
                }
            }
            cout << "|" << endl;
        }
    }

    // 사다리타기 진행
    int climbLadder(int start) {
        int position = start;
        for (int i = 0; i < steps; ++i) {
            if (position > 0 && ladder[i][position - 1]) {
                position--;
            } else if (position < players - 1 && ladder[i][position]) {
                position++;
            }
        }
        return position;
    }

    // 게임 진행 및 결과 출력
    void playGame() {
        cout << "사다리 구조: " << endl;
        printLadder();

        for (int i = 0; i < players; ++i) {
            int resultIndex = climbLadder(i);
            cout << playerNames[i] << "의 결과: " << results[resultIndex] << endl;
        }
    }
};

int main() {
    int players, steps;

    cout << "플레이어 수를 입력하세요: ";
    cin >> players;
    cout << "사다리 높이를 입력하세요: ";
    cin >> steps;

    vector<string> playerNames(players);
    vector<string> results;

    cout << "플레이어 이름을 입력하세요:" << endl;
    for (int i = 0; i < players; ++i) {
        cout << "플레이어 " << i + 1 << "의 이름: ";
        cin >> playerNames[i];
    }

    cout << "각 결과를 입력하세요:" << endl;
    for (int i = 0; i < steps; ++i) {
        string result;
        cout << "결과 " << i + 1 << ": ";
        cin >> result;
        results.push_back(result);
    }

    // 결과를 무작위로 섞음
    srand(time(0));
    random_shuffle(results.begin(), results.end());

    LadderGame game(players, steps, playerNames, results);
    game.playGame();

    return 0;
}
