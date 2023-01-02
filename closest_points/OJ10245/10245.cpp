#include <bits/stdc++.h>

using namespace std;

using ll = long double;

const string INF_MESSAGE = "INFINITY";
const ll INF = 100000000.0; // Utilizando o quadrado da distância
const ll END_INP = 0.0;
const int N = 10005;

using puu = pair<ll, ll>;

pair<ll, ll> points[N];

/**
 * Ordenação por y.
 */
bool by_y(const pair<ll, ll> & a,
    const pair<ll, ll> & b) {
  return a.second < b.second;
}

/**
 * Quadrado da distância euclidiana para
 * pontos bidimensionais.
 */
ll sq_dist(puu a, puu b) {
  return (a.first - b.first) * (a.first - b.first) 
    + (a.second - b.second) * (a.second - b.second) ;
}

/**
 * Compara um ponto com até os 6 próximos
 */
ll compare_dists(vector<puu> v) {
  if (v.size() <= 1) return INF;
  int n = (int) v.size();

  ll dist = INF;
  int i = 0;
  
  for (; i+6 < n; ++i) {
    for(int j = i+1; j <= i+6 && i+6 < n; ++j) {
      dist = min(dist, sq_dist(v[i], v[j]));
    }
  }

  while (i < n) {
    for(int j = i + 1; j < n; ++j) 
      dist = min(dist, sq_dist(v[i], v[j]));

    ++i;
  }

  return dist;
}

ll closest_pair(int l, int r) {
  if (l >= r) return INF;

  int m = (l+r)/2;
  int ind1 = m, ind2 = m;

//cout << "L: " << l << " R: " << r << '\n';
//cout << "M: " << m << '\n';

  ll da = closest_pair(l, m);
  ll db = closest_pair(m + 1, r);
  ll closest = min(da, db);

//cout << "Closest: " << closest << '\n';

  // Criação da faixa de pontos ao redor da mediana
  // para a esquerda.
  while(ind1 - 1 >= l &&
      abs(points[m].first - points[--ind1].first) <= closest)  {}

  // para a direita.
  while(ind2 + 1 <= r &&
      abs(points[m].first - points[++ind2].first) <= closest)  {}


//cout << "ind1: " << ind1 << " ind2: " << ind2 << '\n';

  
  // caso existam pontos nesta faixa:
  if (ind2 - ind1 + 1 > 0) {
    vector<puu> y_sorted(ind2 - ind1 + 1);
    copy_n(&points[ind1], ind2 - ind1 + 1, y_sorted.begin());

    sort(y_sorted.begin(), y_sorted.end(), by_y); //ordena por y
                                                  //
//cout << "Range before sort: " << '\n';
    for(int aux = ind1; aux <= ind2; ++aux) {
//cout << points[aux].first << ' ' << points[aux].second << '\n';
    }
//cout << "Y sorted range: " << '\n' ;
    for(int aux = 0; aux < (int) y_sorted.size(); ++aux) {
//cout << y_sorted[aux].first << ' ' << y_sorted[aux].second << '\n';
    }

    ll n_dist = compare_dists(y_sorted);

//cout << "N_DIST: " << n_dist << '\n';

    return min(min(n_dist, INF) , closest);
  }

  return min(closest, INF);
}

void solve(int n) {
  ll ans = closest_pair(0, n-1); 
  if (ans < INF)
    cout << sqrt(ans);
  else 
    cout << INF_MESSAGE;

  cout << '\n';
}

int main () {
  iostream::sync_with_stdio(false);
  cin.tie(NULL);

  cout << setprecision(4) << fixed;

  int n;
  while(cin >> n, n != END_INP) {
    for (int i = 0; i < n; ++i) cin >> points[i].first >> points[i].second;
    sort(points, points + n); // Por default, a função sort utiliza o primeiro elemento de um iterável para ordenar,
                              // seguindo a ordem crescente, portanto, ordena pela coordenada x;
    solve(n);
  }

  return 0;
}
