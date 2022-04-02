#include <iostream>

using namespace std;

const int MOD = 1000000007;

int dp[6];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	unsigned n; cin >> n;
	dp[5] = 1;
	unsigned long long s = 1;
	for (unsigned i=0;i<n;i++)
	{
		unsigned viejo = dp[i%6];
		dp[i%6] = (unsigned)(s%MOD);
		s += dp[i%6];
		s -= viejo;
	}
	cout << dp[(n-1)%6] << "\n";
	return 0;
}
