import java.util.List;
import java.util.concurrent.locks.Lock;

public class ThreadSafeLinkedList<T extends Comparable<T>> {
    private Node<T> start;
    private Node<T> head;
    private Node<T> end;

    public ThreadSafeLinkedList() {
        end = new Node<>(null, null);
        start = new Node<>(null, end);
        head = end;
    }

    public Node<T> getHead() {
        return head;
    }

    // return the node previous to the one that you're interested in
    Node<T> search(T element) {
        Node<T> prev = start;
        prev.lock();
        Node<T> curr = head;
        curr.lock();
        while (curr.getNext() != null) {
            //System.out.println(curr.getData() + " " + element);
            if (curr.getData().equals(element)) {
                return prev;
            }
            Node<T> pp = prev;
            prev = curr;
            pp.unlock();
            curr = curr.getNext();
            curr.lock();
        }
        curr.unlock();
        prev.unlock();
        return null;
    }

    void add(T element) {
        start.lock();
        head.lock();
        Node<T> new_node = new Node<>(element, head);
        start.setNext(new_node);
        Node<T> aux = head;
        head = new_node;

        aux.unlock();
        start.unlock();
    }

    void update(Node<T> prev, T element) {
        Node<T> found = prev.getNext();

        found.setData(element);

        found.unlock();
        prev.unlock();
    }

    void delete(Node<T> prev) {
        Node<T> found = prev.getNext();

        if (found == head) {
            head = found.getNext();
        }
        prev.setNext(found.getNext());


        found.unlock();
        prev.unlock();
    }

    public void sort()
    {
        Node<T> current = head, index = null;
        T temp;
        while (current.getNext().getNext() != null) {
            index = current.getNext();
            while (index.getNext() != null) {
                if (current.getData().compareTo(index.getData()) > 0) {
                    temp = current.getData();
                    current.setData(index.getData());
                    index.setData(temp);
                }
                index = index.getNext();
            }
            current = current.getNext();
        }
    }
}


/*

         L    L
    0 -> 1 -> 2 -> 3 -> 4 -> 0
              N
         P    C
    Node search(T element) {
        Node prev = start;
        lock(head);
        Node current = head;
        lock(current.getNext());
        Node next = current.getNext();
        while (next != Null) {
            if (current.getData().equals(element))
                return Node;
            prev = current;
            current = next;
            next = current.getNext();
            if (next != Null)
                lock(next);
        }
        unlock(end);
    }

    void add(T element) {
        if (exits(elements))
            ...
        else
        lock(start);
        lock(head);
        Node node = new Node(element, head);
        unlock(head);
        start.setNext(node);
        unlock(start);
    }

    void delete(T element) {

    }

 */