import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Node<T extends Comparable<T>> {
    private T data;
    private Node<T> next;
    private Lock lock;

    public Node(T data, Node<T> next) {
        this.data = data;
        this.next = next;
        lock = new ReentrantLock();
    }

    public T getData() {
        return data;
    }

    public void setData(T data) {
        this.data = data;
    }

    public Node<T> getNext() {
        return next;
    }

    public void setNext(Node<T> next) {
        this.next = next;
    }

    void lock() {
        this.lock.lock();
    }

    void unlock() {
        this.lock.unlock();
    }

    @Override
    public String toString() {
        return "Node{" +
                "data=" + data + ", " +
                "next=" + next +
                '}';
    }
}
