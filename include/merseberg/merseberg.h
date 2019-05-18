#pragma once

#include <functional>
#include <mutex>
#include <thread>
#include <tuple>
#include <vector>

namespace merseberg {
  /**
   */
  template <class Container, class... Args>
  class incantation {
    using args_t = std::tuple<Args...>;
    using value_t = typename Container::value_type;
    using locker_t = std::lock_guard<std::mutex>;
    const std::size_t default_threads = 4;

    std::size_t m_thread_count = (std::thread::hardware_concurrency() > 0)
                                     ? std::thread::hardware_concurrency()
                                     : default_threads;
    args_t m_tuple;
    std::vector<std::thread> m_threads{};
    std::mutex m_invoke_mutex;

    /// compliation of all results from all threads
    std::vector<value_t> m_results{};

    const Container& m_container;

    template <class Function, class Iterator, std::size_t... Is>
    void invoke_task(Function&& f, const Iterator begin, const Iterator end,
                     std::index_sequence<Is...>) {
      auto result = f(begin, end, std::get<Is>(m_tuple)...);

      locker_t lock(m_invoke_mutex);
      m_results.push_back(result);
    }

   public:
    /**
     * @param Workers -- Number of workers to override the default setting
     * matching number of cores
     */
    incantation(const Container& c, Args&&... args)
        : m_container(c), m_tuple(std::tuple<Args...>(args...)) {}

    std::size_t threads() { return m_thread_count; }

    /**
     * Run all the tasks. Start all threads running. Devide the contents of
     * container among all threads.
     */
    template <class Function>
    auto& invoke(Function&& f, std::size_t thread_count = 0) {
      if (thread_count != 0) {
        m_thread_count = thread_count;
      }

      std::size_t size_bucket = m_container.size() / m_thread_count;
      std::size_t dust = m_container.size() % m_thread_count;

      auto i = m_container.begin();
      while (i < m_container.end()) {
        auto j = i + size_bucket + (dust-- > 0 ? 1 : 0);
        m_threads.push_back(std::thread([=]() {
          invoke_task(f, i, j, std::index_sequence_for<Args...>());
        }));
        i = j;
      }
      return *this;
    }

    /**
     * Wait until all threads are completed.
     */
    auto& join() {
      for (auto& t : m_threads) {
        t.join();
      }
      return *this;
    }

    /**
     * Detach all running threads. You will not be able to join anymore.
     */
    auto& detach() { return *this; }

    /**
     * Reduction function / lambda passed in here.
     */
    template <class Function>
    value_t operator()(Function&& freduce) {
      return freduce(m_results);
    }
  };

}  // namespace merseberg
