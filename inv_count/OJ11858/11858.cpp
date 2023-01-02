#include <bits/stdc++.h>

/**
 * O problema exige o número de "swaps" mínimos entre pares de números consecutivos
 * para ordenar um conjunto de números isso está relacionado ao número de inversões 
 * pois basta pegar cada número e fazer o número de trocas de acordo com o número de 
 * inversões.
 *
 * MergeSort pode ser utilizado para contagem de inversões
 * considerando que todos os elementos do vetor direito vem antes do vetor esquerdo,
 * basta contar como inversão quando um número do vetor direito é menor que do esquerdo
 * e considerar que o número de inversões será a quantidade de elementos que vem depois 
 * do elemento atual à esquerda (+ o próprio elemento), já que estão ordenados.
 */

using namespace std;

using ll = long long; // long long pois o problema não especifica
                      // o limite das variáveis
const int N = 1000010; // O máximo de elementos é 10e6
ll V[N];   // Inicialização dos vetores original e auxiliar
           // do mergesort
ll aux[N];

/**
 * O merge utiliza ponteiros para as metades do vetor
 * para poder operar ambas apartir do índice 0,
 * facilitando a contagem de inversões que só precisa ser
 * o tamanho do vetor esquerdo menos a posição atual
 * (ou seja o número de elementos após o elemento atual incluso o
 * próprio)
 */

ll merge(ll* left, ll* right, ll ln, ll rn) {
  ll ind1 = 0, ind2 = 0, k = 0;
  ll n = ln + rn;
  ll invs = 0;

  while(ind1 < ln && ind2 < rn) {
    if(left[ind1] <= right[ind2]) {
      aux[k++] = left[ind1++];
    } else {
      invs += ln - ind1;
      aux[k++] = right[ind2++];
    }
  }

  while(ind1 < ln) aux[k++] = left[ind1++];
  while(ind2 < rn) aux[k++] = right[ind2++];

  k = 0;

  /**
   * inicializa a partir do left pois apesar de 
   * serem ponteiros diferentes (left e right)
   * fazem parte do mesmo vetor e são contíguos
   */
  for (ll i = 0; i < n; ++i) left[i] = aux[k++];

  return invs;
}

/**
 * Merge sort com contagem de inversões
 */
ll inv_count(ll* v, ll n) {
  if (n <= 1) return (ll) 0; // Caso base (n = 1)

  ll m = (n / 2); // Metade do tamanho
  ll* mid = &v[m]; // Início do vetor da direita
  ll invs = 0;

  // cout << "n : " << n << " m: " << m << " mid elem: " << mid[0] << '\n';

  invs += inv_count(v, m); // de 0 a n/2 - 1 o tamanho é n/2
  invs += inv_count(mid, n - m); // O restante é o tamanho da direita (n - n/2)
  invs += merge(v, mid, m, n - m);

  return invs;
}

int main(void) {
  ll n;

  iostream::sync_with_stdio(false);
  cin.tie(NULL);

  while(cin >> n) {
    for (ll i = 0; i < n; ++i) cin >> V[i];
    cout << inv_count(V, n) << '\n';
   }

  return 0;
}
