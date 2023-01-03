#include <bits/stdc++.h>
#include <string.h>
#include <sstream>

using namespace std;

const double N_MAX = 0.3;
const int N_OPS = 52;

const string CONS_IN = "Fuel";
const string LEAK_IN = "Leak";
const string STATION_IN = "Gas";
const string FIX_IN = "Mechanic";
const string GOAL_IN = "Goal";

using info = struct info;
struct info {
  int ev;
  double km;
  int cons;
};

const int CONSUMPTION = 0;
const int LEAK = 1;
const int FIX = 2;
const int FILL = 3;
const int GOAL = 4;

info evs[N_OPS];
int e_size;

double model(double vi, int ops[2], double k1, double k0) {
  double vf = 0.0;
  double kf = k1 - k0; 
  //cout << "model: " << " d: " << kf;
  double consumption = (double) ops[CONSUMPTION] * kf / 100.0;
  double leak = (double) ops[LEAK] * kf;

  //cout << " cons: " << consumption;
  //cout << " leak: " << leak;

  vf = vi - consumption - leak;

  //cout << " vf: " << vf << '\n';
  return vf; 
}

pair<double, bool> process(double vi) {
  int ops[2] = {0, 0};
  double vf = vi;
  double k0 = 0;
  bool reached = false;
  
  for (int i = 0; i < e_size; ++i) {
    // cout << "Event: " << evs[i].ev << " km0: " << k0 << " km1 " << evs[i].km << " Consumption " << ops[CONSUMPTION] << " Leaks: " << ops[LEAK] << '\n';

    vf = model(vf, ops, evs[i].km, k0);
    if (vf < 0.0) break;

    if (evs[i].ev == CONSUMPTION) ops[CONSUMPTION] = evs[i].cons;
    if (evs[i].ev == FIX) ops[LEAK] = 0;
    if (evs[i].ev == LEAK) ++ops[LEAK];
    if (evs[i].ev == FILL) vf = vi;

    k0 = evs[i].km;
    if (evs[i].ev == GOAL) {
      reached = true;
    }
  }

  return make_pair(vf, reached);
}

double search_ans(double l, double r) {
  double vi = (l + r) / 2;

  // cout << "Left: " << l << " Right: " << r << " mid: " << vi << '\n';
  
  if (fabs(r - l) <= 10e-9) return vi;

  auto res = process(vi);

  // cout << "Reached: " << res.second << " Vol diff: " << res.first << '\n';
  if (res.second) {
    return search_ans(l, vi);
  } else {
    return search_ans(vi, r);
  }
}

void solve() {
  cout << search_ans(0, 10000.0) << '\n';
}

int main (void) {
  cout << setprecision(3) << fixed;
  string inp_line;
  
  while (getline(cin, inp_line))  {
    if (inp_line == "0 Fuel consumption 0") break;
    string event = CONS_IN, trash;

    int next = -1;
    do {
      istringstream inpstring(inp_line);
      ++next;
      inpstring >> evs[next].km >> event;

      //cout << "Km: " << evs[next].km << "Event: " << event << '\n';

      if (event == CONS_IN) evs[next].ev = CONSUMPTION; //, cout << "is cons";
      if (event == LEAK_IN) evs[next].ev = LEAK; //, cout << "is leak";
      if (event == STATION_IN) {
        evs[next].ev = FILL ; //, cout << "is Station";
      } 
      if (event == FIX_IN) evs[next].ev = FIX; //, cout << "is Mechanic";
      if (event == GOAL_IN) evs[next].ev = GOAL; //, cout << "is goal";
      // cout << '\n';

      if (event == CONS_IN || event == STATION_IN) inpstring >> trash;
      if (event == CONS_IN) {
        inpstring >> evs[next].cons;
        // cout << "Consumo: " << evs[next].cons << '\n';
      }

      if (event == GOAL_IN) break;

    } while(getline(cin, inp_line));

    e_size = next + 1;
    // cout << " number of evs: " << e_size << '\n';

    solve ();
    // cout << "\n ----------------------------------- \n";
  }

  return 0;
}
