import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		int[] x = new int[n];
		String[] parts = br.readLine().split(" ");
		for (int i = 0; i < n; i++)
			x[i] = Integer.parseInt(parts[i]);
		long[][] dp = new long[n+1][];
		for (int i = n; i >= 0; i--) {
			dp[i] = new long[n + 1 - i];
			dp[i][0] = 0;
			long T = 0;
			for (int j = i + 1; j <= n; j++) {
				T += x[j - 1];
				dp[i][j-i] = T - Math.min(dp[i + 1][j-(i+1)], dp[i][j - 1-i]);
			}
		}
		System.out.println(dp[0][n]);
	}

}
