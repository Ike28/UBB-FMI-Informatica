import java.util.Queue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ThreadSafeQueue<T> {
    private Queue<T> queue;
    private final Integer capacity;
    final Lock lock = new ReentrantLock();
    final Condition notFull = lock.newCondition();
    final Condition notEmpty = lock.newCondition();

    public ThreadSafeQueue(Queue<T> queue, Integer capacity) {
        this.queue = queue;
        this.capacity = capacity;
    }

    boolean isFull() {
        return queue.size() == capacity;
    }

    boolean isEmpty() {
        return queue.isEmpty();
    }

    void push(T element) throws InterruptedException {
        lock.lock();
        try {
            while(isFull()) {
                notFull.await();
            }
            queue.add(element);
            notEmpty.signal();
        }
        finally {
            lock.unlock();
        }
    }

    T pop() throws InterruptedException {
        lock.lock();
        try {
            while (isEmpty()) {
                notEmpty.await();
            }
            notFull.signal();
            return queue.poll();
        }
        finally {
            lock.unlock();
        }
    }
}
