#include <iostream>
#include <vector>
using namespace std;

struct Coffee {
    long long c; // このコーヒーの残りのカップ数
    long long t; // 賞味期限
    int s; // 満足度
    Coffee(long long c, long long t, int s) :
        c(c), t(t), s(s) {}
};

bool GreaterT(const Coffee& lhs, const Coffee& rhs) {
    return lhs.t > rhs.t;
}

// {days}日間で、{coffee}配列の先頭{availableNum}個の種類の中から、
// 満足度が高い順に飲んでいってトータルの満足度を返す
long long consume(int availableNum, vector<Coffee>& coffee, long long days) {
    long long score = 0;
    long long remainDays = days;
    long long remainigCups = 0;
    for (int i = 0; i < availableNum; i++) remainigCups += coffee[i].c;
    // コーヒー飲んでない日が無くなるか、コーヒーが無くなるまで
    // 満足度MAXのコーヒー探して飲めるだけ飲む
    while (remainDays != 0 && remainigCups != 0) {
        int maxS = 0;
        int indexForMaxS = 0;
        for (int i = 0; i < availableNum; i++) {
            if (coffee[i].c != 0 && coffee[i].s > maxS) {
                maxS = coffee[i].s;
                indexForMaxS = i;
            }
        }
        long long cupsToDrink = min(remainDays, coffee[indexForMaxS].c);
        remainDays -= cupsToDrink;
        remainigCups -= cupsToDrink;
        coffee[indexForMaxS].c -= cupsToDrink;
        score += coffee[indexForMaxS].s * cupsToDrink;
    }
    return score;
}

// 貪欲法。期間内のおしりの方から順に満足度高いコーヒーを埋めていく。
long long solve(int N, long long K, vector<Coffee>& coffee) {
    long long score = 0;
    // 期限が遠い順にコーヒーのリストをソート
    sort(coffee.begin(), coffee.end(), GreaterT);

    // 未来の方から、「n日間はi種類のコーヒーが飲める」
    // という区間を取り出して、その期間内でどれだけ満足
    // できるかをconsume()関数で計算する
    long long curT = coffee[0].t;
    int startIndex = 0;
    int availableNum;
    for (int i = 0; i < coffee.size(); i++) {
        // i番目のコーヒーは期限が違う場合、
        // i-1番目までのi種類のコーヒーを飲めた期間を計算して、
        // その期間内でいいやつから飲んだ場合の満足度を足しこむ
        if (coffee[i].t != curT) {
            curT = coffee[i].t;
            long long days = coffee[startIndex].t - coffee[i].t;
            score += consume(i, coffee, days);
            startIndex = i;
        }
        // 初日を含む期間も同じ要領
        if (i == coffee.size() - 1) {
            long long days = coffee[startIndex].t;
            score += consume(coffee.size(), coffee, days);
        }
    }
    return score;
}

int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        // read parameter from standard input
        int N;
        long long K;
        cin >> N >> K;
        vector<Coffee> coffee;
        for (int j = 0; j < N; j++) {
            long long c, t; int s;
            cin >> c >> t >> s;
            Coffee cof(c, t, s);
            coffee.push_back(cof);
        }
        // solve and print answer to standard output
        long long answer = solve(N, K, coffee);
        cout << "Case #" << i << ": " << answer << endl;
    }
}
