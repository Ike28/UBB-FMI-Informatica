import java.util.Queue;
import java.util.Set;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class Consumer extends Thread{
    private ThreadSafeQueue<Participant> queue;
    private ThreadSafeLinkedList<Participant> lst;
    private Set<Participant> synchronizedBlackListSet;
    private CheckClass counter;
    private ThreadSafeListManager listManager;
    CyclicBarrier barrierForAll;

    public Consumer(ThreadSafeQueue<Participant> queue, ThreadSafeLinkedList<Participant> lst, Set<Participant> synchronizedBlackListSet, CheckClass counter, CyclicBarrier barrierForAll) {
        this.queue = queue;
        this.lst = lst;
        this.synchronizedBlackListSet = synchronizedBlackListSet;
        listManager = new ThreadSafeListManager(
                lst,
                synchronizedBlackListSet
        );
        this.counter = counter;
        this.barrierForAll = barrierForAll;
    }

    @Override
    public void run() {
        while (!this.counter.finished() || !queue.isEmpty()) {
            try {
                listManager.processParticipant(queue.pop());
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
//        try {
//            barrierForAll.await();
//        } catch (InterruptedException | BrokenBarrierException e) {
//            throw new RuntimeException(e);
//        }

        //System.out.println("CONSUMER finished");
    }
}
