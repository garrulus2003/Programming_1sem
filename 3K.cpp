//Contest 7: Problem K
//Neustroeva Liza 024
//https://codeforces.com/group/R3IJoiTue4/contest/316719/submission/109643988

/*
* Компания BrokenTiles планирует заняться выкладыванием во дворах у состоятельных клиентов
узор из черных и белых плиток, каждая из которых имеет размер 1×1 метр.
Известно, что дворы всех состоятельных людей имеют наиболее модную на сегодня форму прямоугольника M×N метров.

Однако при составлении финансового плана у директора этой организации
появилось целых две серьезных проблемы: во первых, каждый новый клиент очевидно захочет,
чтобы узор, выложенный у него во дворе, отличался от узоров всех остальных клиентов этой фирмы,
а во вторых, этот узор должен быть симпатичным.

Как показало исследование, узор является симпатичным, если в нем нигде не встречается квадрата 2×2 метра,
полностью покрытого плитками одного цвета.

Для составления финансового плана директору необходимо узнать, сколько клиентов он сможет обслужить,
прежде чем симпатичные узоры данного размера закончатся. Помогите ему!
*/

#include <iostream>
#include <vector>
#include <string>

bool bit(int mask, int pos) {
	return (mask / (1 << pos)) % 2;
}


bool is_compatible(int mask, int other_mask, int length) {
	bool compatible = true;
	for (int k = 1; k < length; ++k) {
		bool similar_first = bit(mask, k - 1) == bit(other_mask, k - 1);
		bool similar_second = bit(mask, k) == bit(other_mask, k);
		bool similar_column = bit(mask, k - 1) == bit(mask, k) % 2;
		if (similar_first && similar_second && similar_column) {
			compatible = false;
		}
	}
	return compatible;
}


int main() {
	int m, n;
	std::cin >> m >> n;
	int a = std::min(m, n);
	int b = std::max(m, n);
	int variants = 1 << a;


	//creating a table to get whether it is possible to place i-column after j-column
	std::vector<std::vector<bool>> possible(variants, std::vector<bool>(variants, false));
	std::vector<int> possibilities(variants, 0);
	for (int i = 0; i < variants; ++i) {
		for (int j = 0; j < variants; ++j) {
			possible[i][j] = is_compatible(i, j, a);
		}
	}


	//the vector dp contains possibilities to make i rows ending with j columns
	std::vector<std::vector<int>> dp(b, std::vector<int>(1 << a, 0));
	dp[0] = std::vector<int>(variants, 1);
	for (int i = 1; i < b; ++i) {
		for (int j = 0; j < variants; ++j) {
			for (int k = 0; k < variants; ++k) {
				if (possible[j][k]) {
					dp[i][j] += dp[i - 1][k];
				}
			}
		}
	}


	//summing by all the variats of terminal column
	int ans = 0;
	for (int i = 0; i < variants; ++i) {
		ans += dp[b - 1][i];
	}

	std::cout << ans;
	return 0;
}