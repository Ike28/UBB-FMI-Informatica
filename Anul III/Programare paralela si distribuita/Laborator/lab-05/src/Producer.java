import java.io.*;
import java.util.Queue;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class Producer implements Runnable {
    private ThreadSafeQueue<Participant> queue;
    private final File file;

    private final Integer threadIndex;
    private CheckClass counter;
    CyclicBarrier barrierForAll;

    CyclicBarrier barrier;

    private ThreadSafeLinkedList<Participant> lst;

    public Producer(ThreadSafeQueue<Participant> queue, File file, Integer threadIndex, ThreadSafeLinkedList<Participant> lst, CheckClass counter, CyclicBarrier barrier, CyclicBarrier barrierForAll) {
        this.queue = queue;
        this.file = file;
        this.threadIndex = threadIndex;
        this.lst = lst;
        this.barrier = barrier;
        this.counter = counter;
        this.barrierForAll = barrierForAll;
    }

    @Override
    public void run() {
        try(BufferedReader bufferedReader = new BufferedReader(new FileReader(file))){
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                Participant participant = Participant.fromString(line, file);
                try {
                    queue.push(participant);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }

            }
        }catch (IOException e) {
            e.printStackTrace();
        }

        counter.increment();
        //System.out.println("producer finishsed");
    }
}
