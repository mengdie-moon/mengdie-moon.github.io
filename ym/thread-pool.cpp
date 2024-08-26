// 写一个线程池
#include<iostream>
#include<mutex>
#include<condition_variable>
#include<vector>
#include<queue>
#include<thread>
#include<functional>

class ThreadPool {
private:
	std::vector<std::thread> thread_vec;
	std::queue<std::function<void()>> task_que;
	std::condition_variable condition;
	std::mutex mtx;
	bool stop;
public:
	ThreadPool(int TheadNumber) : stop(false) {
		for (int i = 0; i < TheadNumber; i++) {
			thread_vec.emplace_back([this]() {
				while (true) {
					std::unique_lock<std::mutex> lock(mtx);
					condition.wait(lock, [this]() {
						return !task_que.empty() || stop;
						});
					if (stop && task_que.empty()) return;
					std::function<void()> func(std::move(task_que.front()));
					task_que.pop();
					lock.unlock();
					func();
				}
			});
		}
	}

	~ThreadPool() {
		{
			std::unique_lock<std::mutex> lock(mtx);
			stop = true;
		}
		condition.notify_all();
		for (auto& a : thread_vec) {
			a.join();//析构join: 回收线程等待线程结束
		}
	}

	template<class T, class... Args>//模板T, 参数模板(参数不确定多少时用)
	void enqueue(T&& t, Args... args) {
		//func里绑定一个包含t,args的函数对象
		std::function<void()> func = std::bind(std::forward<T>(t), std::forward<Args>(args)...);
		{
			std::unique_lock<std::mutex> lock(mtx);
			task_que.emplace(std::move(func));
		}
		condition.notify_one();
	}
};

int main() {
	ThreadPool threadpool(5);
	for (int i = 1; i <= 10; i++) {
		//加入10个任务
		threadpool.enqueue([i]() {
			std::cout << "任务 " << i << " 正在执行" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "任务 " << i << " 执行完成" << std::endl;
		});
	}

	return 0;
}