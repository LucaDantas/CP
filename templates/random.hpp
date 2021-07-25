std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count() ^ (long long) (make_unique<char>().get()));
std::mt19937_64 rng64(std::chrono::steady_clock::now().time_since_epoch().count() ^ (long long) (make_unique<char>().get()));

template<typename T> T rnd(T v) {
  T k;
  if constexpr(sizeof(T) <= 32) k = (T) rng(); else k = (T) rng64();
  return (T) (((k % v) + v) % v);
}

template<typename T> T rnd(T l, T r) {
  if (r < l) swap(l, r);
  return (T) (l + rnd(r - l + 1));
}
