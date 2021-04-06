#include <bits/stdc++.h>

constexpr int N = 100005;

int f[N], g[N];

int findSample(int n, int confidence[], int host[], int protocol[]) {
  for (int i = 0; i < n; ++i) {
    f[i] = confidence[i];
  }
  for (int i = n - 1; i; --i) {
    int p = host[i];
    switch (protocol[i]) {
      case 0: {
        f[p] += g[i], g[p] += std::max(f[i], g[i]);
        break;
      }
      case 1: {
        f[p] = std::max(f[p] + std::max(f[i], g[i]), g[p] + f[i]), g[p] += g[i];
        break;
      }
      case 2: {
        f[p] = std::max(f[p] + g[i], g[p] + f[i]), g[p] += g[i];
      }
    }
  }
  return std::max(f[0], g[0]);
}
