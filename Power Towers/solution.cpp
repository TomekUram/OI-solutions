#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

template <typename _T> inline void _DBG(const char *s, _T x) {
  cerr << s << " = " << x << "\n";
}
template <typename _T, typename... args>
void _DBG(const char *s, _T x, args... a) {
  while (*s != ',')
    cerr << *s++;
  cerr << " = " << x << ',';
  _DBG(s + 1, a...);
}

#define DBG(...) _DBG(#__VA_ARGS__, __VA_ARGS__)

const long long test = LLONG_MAX;

long long power(long long x, long long exp) {
  if (x == 0) {
    return 0;
  }

  long long res = 1;
  for (long long k = 0; k < exp; k++) {
    if ((test / x) < res) {
      return -1;
    }
    res *= x;
  }
  return res;
}

long long find_root(long long exp, long long n) {
  // DBG(n, exp);
  long long low = 0, high = n, mid = 0;

  while (low <= high) {
    mid = (low + high) / 2;
    long long val = power(mid, exp);
    if (val == n) {
      return mid;
    }

    if (val > n || val == -1) {
      high = mid - 1;
    } else if (val < n) {
      low = mid + 1;
    }
    // DBG(mid, val, low, high);
  }
  return -1;
}

long long n;
const long long NAX = 1e18 + 7;
const long long max_exp = ceill(log2(NAX)) + 5;

long long ans(long long num) {
  if (num == 1) {
    return 0;
  }
  long long res = 0;

  for (long long exp = 2; exp <= max_exp; exp++) {
    long long root = find_root(exp, num);

    if (root != -1) {
      res += (ans(exp) + 1);
    }
  }
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> n;

  cout << ans(n);
  return 0;
}
