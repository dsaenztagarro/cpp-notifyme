#include <iostream>
#include <thread>
#include <fstream>
#include <chrono>

using namespace std;

void background_task()
{
  this_thread::sleep_for(std::chrono::seconds(1));
  ofstream myfile;
  myfile.open ("example.txt");
  myfile << "Writing this to a file.\n";
  myfile.close();
  // cout << "Starting background task" << endl;
  // cout << "End background task" << endl;
}

int main()
{
  thread my_thread(background_task);
  std::cout << "after starting, joinable: " << my_thread.joinable() << '\n';
  my_thread.detach();
  std::cout << "after starting, joinable: " << my_thread.joinable() << '\n';
}
