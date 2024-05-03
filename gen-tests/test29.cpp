// !test buffer_overflow
// !test format_string_error
// !test sql_injection
// !test command_intrusion
// !test unsafe_data_storage
// !test memory_leak
// !test bad_file_access
// !test null_pointer_derefence
// !test number_overflow
// !test race_condition
// !test incorr_rw_sync
// !test uninit_var

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;

int x = 10, y = 1;

#include <pthread.h>

pthread_t tidReader;
pthread_t tidWriter;

ofstream out("file.txt");
ifstream in("file.txt");

class Y {
  int y = 0;
  
  public:
  void test() {
      cout << y;
  }
}

DWORD TestFunc1(void* tmp) {
  x++; // !vuln race_condition
  y++;
}

DWORD TestFunc2(void* tmp) {
  printf("x = %d", x); // !vuln race_condition
}

void Reader(void *arg) {
  int t;
  while(1) {
      for (i = 0; i < 10; i++)
          in >> t; // !vuln incorr_rw_sync
      cout << t;
  }
}

void Writer(void *arg) {
  while(1) {
      for (i = 0; i < 10; i++) {
          out << i; // !vuln incorr_rw_sync
      }
  }
}

int main() {
  int i = 0;
  cout << i << endl;

  int err;
  err = pthread_create(&tidReader, NULL, &Reader, NULL);
  err = pthread_create(&tidWriter, NULL, &Writer, NULL);
  
  pthread_join(tidReader, NULL);
  pthread_join(tidWriter, NULL);

  QSqlDatabase db = QsqlDatabase::addDatabase("SQL", "db");
  db.setHostName("rtg");
  db.setDatabaseName("ghtdb");
  db.setUserName("lily");
  db.setPassword("4gdjstf6");
  bool ok = db.open();
  QSqlQuery query();
  string login = "";
  cin >> login;
  query.exec("SELECT name, salary FROM dbtbl WHERE login = " + login + ";"); // !vuln sql_injection

  char *filename = "file.txt";
  FILE *ptrFile = fopen(filename, "w"); // !vuln bad_file_access

  int *p = malloc(4); // !novuln
  double *w = malloc(8); // !vuln memory_leak
  free(p);

  int a = 11;
  int b = 23;
  int c = a + b;

  int x, y(42), z;
  z = y; // !novuln
  z = x; // !vuln uninit_var
  cin >> x;
  cout << x + y + z; // !novuln

  float exp = 2.7;
  cout << "Hello!" << endl;

  char i1[];
  system(i1); // !vuln command_intrusion

  double pi = 3.14;

  Y* i = 0;
  i->test(); // !vuln null_pointer_derefence

  set<int> int_set1 = {1, 2}, int_set2("error");
  bool* /* comment */ *bpp1;

  string pass = ""; // !vuln unsafe_data_storage

  int d = 1000000; // !vuln number_overflow
  d += 92000000450000;

  char *ptr1 = NULL;
  ptr1 = new char[32];
  delete [] ptr1;

  DWORD thread1, thread2;
  CreateThread(NULL, 0, TestFunc1, NULL, 0, &thread1);
  CreateThread(NULL, 0, TestFunc2, NULL, 0, &thread2);

  char src[6] = "Hello";
  char dst[6] = "World";
  strcat(src, dst); // !vuln buffer_overflow

  char fs[15];
  int a = 23, b = 45;
  sprintf(fs, "%d %d"); // !vuln format_string_error
}
