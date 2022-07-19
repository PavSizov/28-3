#include <iostream>
#include <vector>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <mutex>

std::string order[] = {"pizza", "soup","steak","salad","sushi"};
std::vector<std::string> dish;
std::mutex dish_access;
int count = 0;
int x = 0;
int y = 0;


void online_order ()
{
    while (count < 11)
    {
        srand(time(NULL));

        int time = rand()%16 + 5;

        int i = rand() % 5;
        std::this_thread::sleep_for(std::chrono::seconds(time));
        std::cout << "CALL - " << "order - " << order[i] << std::endl;

        std::cout << "the dish " << order[i] << " is handed over for cooking" << std::endl;

        dish.push_back(order[i]);
        x++;
    }

}
 void kitchen ()
{

    while (count < 11)
    {
        srand(time(NULL));
        int time_k = rand()%16 + 5;
        if (x !=0 ) {
            std::this_thread::sleep_for(std::chrono::seconds(time_k));

            dish_access.lock();
            std::cout << "the order " << dish[y] << "  is ready " << std::endl;
            y++;

            dish_access.unlock();
        }
    }


}




int main()
{

  while(count < 11)
  {
      std::thread call(online_order);
      call.detach();
      std::thread cook (kitchen);
      cook.detach();

      std::this_thread::sleep_for(std::chrono::seconds(30));
      std::cout << " The courier arrived" << std::endl;
      count++;

  }



    return 0;
}

